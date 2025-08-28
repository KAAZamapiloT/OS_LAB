#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<fcntl.h>
#include<sys/sendfile.h>
#include<unistd.h>
void main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);   // Port number (use htons!)
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, &addr, sizeof(addr));
    listen(sockfd, 10);

    int client_fd=accept(sockfd, NULL, NULL);
    char buffer[1024]={0};
    recv(client_fd, buffer, sizeof(buffer), 0);
//GET /file.html ....
    char* f=buffer+5;
    *strchr(f, ' ') = 0;
  int  opened_fd = open(f, O_RDONLY);
  sendfile(client_fd,opened_fd,0,1024);
    close(opened_fd);
    close(client_fd);
    close(sockfd);

}