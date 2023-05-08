#include"src/MYNET.h"

#define BUFF_SIZE 1000 

int get_file_size(int fd)
{
    int size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    return size;
}


int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        error("Invalid number of arguments");
    }
    
    int fd = open(argv[1], O_RDONLY, 0700);
    int size = get_file_size(fd);
    
    char* buff = malloc(BUFF_SIZE);
    memset(buff, 0, BUFF_SIZE);

    int listen_fd = create_socket(AF_INET, SOCK_STREAM);
    bind_to_port(listen_fd, AF_INET, 3340);
    listen_to_port(listen_fd, 10);

    while(1)
    {   
        int cln_fd = accept_connection(listen_fd);
        
        printf("HERE\n");
        fprintf(stdout, "[INFO]File name: %s\n", argv[1]);
        fprintf(stdout, "[INFO]File size(in bytes): %d\n", size);

        fflush(stdout);


        int size2 = strlen(argv[1]);
        write(cln_fd, &size2, sizeof(size2));
        write(cln_fd, argv[1], strlen(argv[1]));       


        write(cln_fd, &size, sizeof(size));
        int sum = 0, c = 0;
        while(sum < size)
        {
            c = read(fd, buff, BUFF_SIZE);
            c = write(cln_fd, buff, c);
            sum = sum + c; 
        }
        
        fprintf(stdout, "[INFO]Bytes transfared: %d\n", sum);

        close(cln_fd);

    }
    close(fd);

    return 0;
}

