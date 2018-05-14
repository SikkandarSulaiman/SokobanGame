#include <error.h>
#include <errno.h>
#include <ncurses.h>

#include <ncurses_io.h>
#include <sokoban.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdlib.h>
#include <string.h>

#define SOKO_IN_FILE "sokoban_in_sck"
#define SOKO_OUT_FILE "sokoban_out_sck"

#define IP_ADDRESS "127.0.0.1"
#define CLIENT_PORT 3001

int communicate_soc_data(char *buf, int size)
{
	int sock_fd;
	int rlen;
	int ret;

	struct sockaddr_in server;
	struct sockaddr_in client;
	socklen_t server_len;

	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_fd == -1)
		error(1, errno, "unable to create socket");

	client.sin_family = AF_INET;
	client.sin_port = htons(CLIENT_PORT);
	client.sin_addr.s_addr = inet_addr(IP_ADDRESS);

	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = inet_addr(IP_ADDRESS);

	ret = connect(sock_fd, (struct sockaddr *)&server, sizeof(server));
	if (ret == -1)
		error(1, errno, "unable to connect to server");

	ret = send(sock_fd, buf, strlen(buf), 0);
	if (ret == -1)
		error(1, errno, "unable to send to server");

	ret = recv(sock_fd, buf, size, 0);
	if (ret == -1)
		error(1, errno, "unable to recv from server");

	ret = shutdown(sock_fd, SHUT_RDWR) || close(sock_fd);
	if (ret == 1)
		error(1, errno, "unable to close parent socket");

	return SUCCESS;
}

int main(void)
{
	int flag = 1;

	union deser {
		out_data_t data;
		char buf[sizeof(out_data_t)];
	};

	union deser d;

	char welcome_msg[][MAX_COL] = {"Welcome to Sokoban",
			      "Press F2 to start"};

	display_ncurses(welcome_msg, 2);

	while (flag == 1) {
		get_input_ncurses(d.buf);
		if (strcmp(d.buf, U_QUIT) == 0)
			flag = 0;
		communicate_soc_data(d.buf, sizeof(out_data_t));
		if (flag == 0)
			break;
		display_ncurses(d.data.level, d.data.row_count);
		if (d.data.err_flag == 1)
			print_user_msg(d.data.err_msg);

	}

	return 0;
}
