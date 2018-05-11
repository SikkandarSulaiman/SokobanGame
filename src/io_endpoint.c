#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sokoban.h>
#include <game_data.h>
#include <bitfields_tr.h>
#include <io_endpoint.h>


int sock_fd;
struct sockaddr_in client;
socklen_t client_len = sizeof(client);

static int write_to_sck(char *buf, int size)
{
	int wlen;
	int ret;
	
	wlen = sendto(sock_fd, buf, size, 0, (struct sockaddr *)&client, client_len);
	if (wlen == -1)
		error(1, errno, "unable to respond");

	ret = close(sock_fd);
	if (ret == -1)
		error(1, errno, "error closing socket");
	
	return SUCCESS;
}

int respond(game_data_t *data, int *redirect_key)
{
	int i;
	out_data_t d_out;

	d_out.err_flag = 0;
	*redirect_key = INPUT_END;
	
	if (data->err) {
		d_out.err_flag = 1;

		if (data->err & ERR_INT) {
			printf("Internal error\n");
			if (data->err == ERR_GAME_FINISHED)
				strcpy(d_out.err_msg, "END OF GAME");			
		} else if (data->err & ERR_IO) {
			strcpy(d_out.err_msg, "Invalid Command");			
			printf("I/O error\n");
		} else if (data->err & ERR_BOARD) {
			printf("Error in map\n");
		}
	}
	if (!(data->game_status & LEVEL_START)) {
		d_out.err_flag = 1;
			strcpy(d_out.err_msg, "Level Completed");
			printf("Level Completed\n");
	}

	d_out.row_count = data->row_count;
	d_out.col_count = data->col_count;
	bits_to_chars(d_out.level, data->level, data->row_count, data->col_count);

	for (i = 0; i < data->row_count; i++) {
		d_out.level[i][data->col_count] = 0 ;
		printf("%s\n", d_out.level[i]);
	}

	union ser {
		out_data_t data;
		char buf[sizeof(data)];
	};

	union ser s;
	s.data = d_out;

	write_to_sck(s.buf, sizeof(out_data_t));
	
	return SUCCESS;
}


static int read_from_sck(char *buf, int size)
{
	int ret;
	int rlen;
	int optval = 1;
	struct sockaddr_in me;


	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_fd == -1)
		error(1, errno, "unable to create socket");

	ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
					 &optval, sizeof(optval));
	if (ret == -1)
		error(1, errno, "unable to configure socket");
	
	me.sin_family = AF_INET;
	me.sin_port = htons(SERVER_PORT);
	me.sin_addr.s_addr = inet_addr(SERVER_IP);

	ret = bind(sock_fd, (struct sockaddr *)&me, sizeof(me));
	if (ret == -1)
		error(1, errno, "unable to bind socket to host");

	rlen = recvfrom(sock_fd, buf, sizeof(buf), 0, (struct sockaddr *)&client, &client_len);
	if (rlen == -1)
		error(1, errno, "unable to receive from client");
	buf[rlen] = 0;

	printf("Msg from %s: %s\n %d\n", inet_ntoa(client.sin_addr), buf, client_len);
	
	return SUCCESS;
}

int get_user_cmd(game_data_t *data, int *redirect_key)
{
	int ret;
	
	ret = read_from_sck(data->user_cmd, sizeof(data->user_cmd));
	
	if (ret == FAILURE) {
		*redirect_key = OUTPUT_END;
		return SUCCESS;
	}

	*redirect_key = INPUT_PROCESS;
	return SUCCESS;
}

