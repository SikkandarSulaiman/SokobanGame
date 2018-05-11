#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#include <output_process.h>
#include <game_data.h>

#include <stdio.h>
#include <consts.h>

#include <bitfields_tr.h>

#define SOCK_FILE "sokoban_out_sck"

/* int open_write_sck */


static int write_to_sck(out_data_t data)
{
	int sock_fd;
	int wlen;
	int ret;
	struct sockaddr_un host = {AF_UNIX, SOCK_FILE};
	
	union ser {
		out_data_t data;
		char buf[sizeof(data)];
	};

	union ser s;
	s.data = data;

	sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sock_fd == -1)
		error(1, errno, "unable to create socket");

	usleep(100000);
	ret = connect(sock_fd, (struct sockaddr *)&host, sizeof(host));
	if (ret == -1)
		error(1, errno, "unable to connect to host");

	wlen = send(sock_fd, s.buf, sizeof(data), 0);
	if (wlen == -1)
		error(1, errno, "unable to send message");
 
	ret = shutdown(sock_fd, SHUT_RDWR) || close(sock_fd);
	if (ret == 1)
		error(1, errno, "unable to close parent socket");

	return SUCCESS;
}

int display(game_data_t *data, int *redirect_key)
{
	int i;
	out_data_t d_out;

	d_out.err_flag = 0;
	*redirect_key = INPUT_END;

	printf("Error: %x\n", data->err);
	if (data->err) {
		if (data->err & ERR_INT)
			printf("Internal error\n");
		else if (data->err & ERR_IO)
			printf("I/O error\n");
		else if (data->err & ERR_BOARD)
			printf("Error in map\n");

		d_out.err_flag = 1;
		strcpy(d_out.err_msg, "Invalid command");
	}

	d_out.row_count = data->row_count;
	d_out.col_count = data->col_count;
	bits_to_chars(d_out.board, data->board, data->row_count, data->col_count);

	for (i = 0; i < data->row_count; i++) {
		d_out.board[i][data->col_count] = 0 ;
		printf("%s\n", d_out.board[i]);
	}

	write_to_sck(d_out);
	
	return SUCCESS;
}



