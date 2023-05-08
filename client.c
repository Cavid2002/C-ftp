#include"src/MYNET.h"


#define BUFF_SIZE 1000 
#define NAME_SIZE 100

int main(int argc, char* argv[1])
{
    if(argc != 2)
    {
        error("Invalid arguments");
    }
    int cln_fd = create_socket(AF_INET, SOCK_STREAM);
    connect_to_port(cln_fd, AF_INET, argv[1], 3340);

    int size;
    
    char* name = malloc(NAME_SIZE);
    char* buff = malloc(BUFF_SIZE);

    read(cln_fd, &size, sizeof(size));

    int c = read(cln_fd, name, size);
    name[c] = '\0';
    fprintf(stdout, "[INFO]File name: %s\n", name);
    
    int fd = open(name, O_CREAT|O_WRONLY, 0700);
    
    read(cln_fd, &size, sizeof(size));
    fprintf(stdout, "[INFO]File size(in bytes): %d\n", size);
    fflush(stdout);
    int sum = 0;
    c = 0;
    while (sum < size)
    {
        int c = read(cln_fd, buff, BUFF_SIZE);
        sum = sum + c;
        write(fd, buff, c);
    }
    
    fprintf(stdout, "[INFO]Bytes recivied: %d\n", sum);
    close(cln_fd);
    close(fd);
}