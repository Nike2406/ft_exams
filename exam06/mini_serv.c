#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

const int BUFF = 65536 * 2;
typedef struct s_clients {
	int 	id;
	char	msg[1024];
} t_clients;
t_clients clients[1024];

fd_set read_set, write_set, actual_set;
int max_fd = 0, id_next = 0;
char buff_read[BUFF], buff_write[BUFF];

void print(char *str) {
	if (str) {
		write(2, str, strlen(str));
	} else {
		write(2, "Fatal error", strlen("Fatal error"));
	}
	write(2, "\n", 1);
	exit(1);
}

void sendAll(int fd) {
	for (int i = 0; i <= max_fd; i++) {
		if (FD_ISSET(i, &write_set) && i != fd) {
			send(i, buff_write, strlen(buff_write), 0);
		}
	}
}

int main(int ac, char **av) {
	if (ac != 2) {
		print("Wrong args");
	}

	// socket create and verification
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		print(NULL);
	}

	FD_ZERO(&actual_set);
	bzero(&clients, sizeof(clients));
	max_fd = sockfd;
	FD_SET(sockfd, &actual_set);

	struct sockaddr_in servaddr;
	socklen_t len;
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
		print(NULL);
	}
	if (listen(sockfd, 10) != 0) {
		print(NULL);
	}

	while (1) {
		read_set = write_set = actual_set;
		if (select(max_fd + 1, &read_set, &write_set, NULL, NULL) < 0)
			continue;

		for (int fd = 0; fd <= max_fd; fd++){
			if (FD_ISSET(fd, &read_set) && fd == sockfd) {
				int connfd = accept(sockfd, (struct sockaddr *)&servaddr, &len);
				if (connfd < 0) {
					continue;
				}
				max_fd = connfd > max_fd ? connfd : max_fd;
				clients[connfd].id = id_next++;
				FD_SET(connfd, &actual_set);
				sprintf(buff_write, "%d arrived", clients[connfd].id;
				sendAll(connfd);
				break;
			}

			if (FD_ISSET(fd, &read_set) && fd != sockfd) {
				int res = recv(fd, buff_read, BUFF, 0);
				if (res <= 0) {
					sprintf(buff_write, "%d left", clients[fd].id);
					sendAll(fd);
					FD_CLR(fd, &actual_set);
					close(fd);
					break;
				} else {
					for (int i = 0, j = strlen(clients[fd].msg); i < res; i++, j++) {
						clients[fd].msg[j] = buff_read[i];
						if (clients[fd].msg[j] == '\n') {
							clients[fd].msg[j] = '\0';
							sprintf(buff_write, "%d: %s\n", clients[fd].id, clients[fd].msg);
							sendAll(fd);
							bzero(clients[fd].msg, sizeof(clients[fd].msg));
							j = -1;
						}
					}
					break;
				}
			}
		}
	}
}