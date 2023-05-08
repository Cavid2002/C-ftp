#include"MYNET.h"


void error(const char* msg)
{
    fprintf(stderr, "[ERROR]%s!\n", msg);
    exit(EXIT_FAILURE);
}

int create_socket(int ip_family, int trs_protocol)
{
    int fd = socket(ip_family, trs_protocol, 0);

    if(fd == -1)
    {
        error("Unable to create socket");
    }
    return fd;
}


int bind_to_port(int sock_fd, int ip_family, unsigned short port)
{
    sockaddr_in name;
    name.sin_family = ip_family;
    name.sin_port = htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    char reuse = 1;

    if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1)
    {
        error("Unable to reuse the port");
    }

    if(bind(sock_fd, (sockaddr*)&name, sizeof(name)) == -1)
    {
        error("Unable to bind");
    }

    return 0;
}

int listen_to_port(int sock_fd, int q_size)
{
    if(listen(sock_fd, q_size) == -1)
    {
        error("Unable to listen");
    }

    return 0;
}

int accept_connection(int sock_fd)
{
    sockaddr_storage cln_addr;
    unsigned int cln_addr_size = sizeof(cln_addr);
    int cln_sock = accept(sock_fd, (sockaddr*)&cln_addr, &cln_addr_size);
    if(cln_sock == -1)
    {
        error("Unable to accept");
    }
    return cln_sock;
}


int connect_to_port(int sock_fd, int ip_family, const char* ip_addr, unsigned short port)
{
    sockaddr_in name;
    name.sin_family = ip_family;
    name.sin_port = htons(port);
    name.sin_addr.s_addr = htonl(atoi(ip_addr));
    if(connect(sock_fd, (sockaddr*)&name, sizeof(name)) == -1)
    {
        error("Unable to connect");
    }

    return 0;
}