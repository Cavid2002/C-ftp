#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include<signal.h>
#include<unistd.h>
#include<fcntl.h>

#include<sys/socket.h>
#include<arpa/inet.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr_storage sockaddr_storage;
typedef struct sockaddr sockaddr;


void error(const char* msg);
int create_socket(int ip_family, int trs_protocol);
int bind_to_port(int sock_fd, int ip_family, unsigned short port);
int listen_to_port(int sock_fd, int q_size);
int accept_connection(int sock_fd);
int connect_to_port(int sock_fd, int ip_family, const char* ip_addr, unsigned short port);