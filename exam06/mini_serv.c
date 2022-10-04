#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

int max_fd;
fd_set actual_set, read_set, write_set;
int arr_id[5000];
char *arr_str[5000];
char buff_send[100];
char buff_read[1001];
char *message = NULL;

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

void print(int fd, char *str) {
    write(fd, str, strlen(str));
    exit(1);
}

void send_msg(int fd) {
    for (int current_fd = 3; current_fd <= max_fd; current_fd++) {
        if (FD_ISSET(current_fd, &write_set) && current_fd != fd) {
            send(current_fd, buff_send, strlen(buff_send), 0);
			if (message) {
				send(current_fd, message, strlen(message), 0);
			}
        }
    }
}


int main(int argc, char **argv) {
	int sockfd, connfd;
    socklen_t   len;
	struct sockaddr_in servaddr, cli; 

    if (argc != 2) {
        print(2, "Wrong number of arguments\n");
    }

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		print(2, "Fatal error\n"); 
		exit(0); 
	} 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(argv[1])); 
  
	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		print(2, "Fatal error\n");
	} 
	else
	if (listen(sockfd, 10) != 0) {
		print(2, "Fatal error\n");
	}

	len = sizeof(cli);
    max_fd = sockfd;
    FD_ZERO(&actual_set);
    FD_SET(sockfd, &actual_set);

    int client_id = 0;

    while(1) {
        read_set = write_set = actual_set;
        if (select(max_fd + 1, &read_set, &write_set, NULL, NULL) <= 0) {
            continue;
        }

        if (FD_ISSET(sockfd, &read_set)) {
            connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
            if (connfd < 0) { 
                print(2, "Fatal error\n"); 
            } 
            arr_id[connfd] = client_id++;
            FD_SET(connfd, &actual_set);
            max_fd = connfd > max_fd ? connfd : max_fd;
			sprintf(buff_send, "server: client %d just arrived\n", arr_id[connfd]);
            arr_str[connfd] = NULL;
			send_msg(connfd);
        }

		for (int fd = 3; fd <= max_fd; fd++) {
			if (FD_ISSET(fd, &read_set) && fd != sockfd) {
				size_t count = recv(fd, buff_read, 1000, 0);
				if (count <= 0) {
					FD_CLR(fd, &actual_set);
					sprintf(buff_send, "server: client %d just left\n", arr_id[fd]);
					send_msg(fd);
					close(fd);
					break;
				} else {
					buff_read[count] = '\0';
					arr_str[fd] = str_join(arr_str[fd], buff_read); 
					message = NULL;

					while (extract_message(&arr_str[fd], &message)) {
						sprintf(buff_send, "client %d: ", arr_id[fd]);					
						send_msg(fd);
					}
					free(message);
					message = NULL;
				}
			}
		}
    }
}