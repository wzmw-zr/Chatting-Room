/*************************************************************************
	> File Name: client.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月29日 星期日 18时16分24秒
 ************************************************************************/

#include "../common/head.h"
#include "../common/chatroom.h"
#include "../common/tcp_client.h"
#include "../common/common.h"

const char *conf = "./client.conf";

int main() {
    int port, sockfd;
    Msg msg;
    char ip[20] = {0};
    printf("%s\n", conf);
    port = atoi(get_value((char *) conf, "SERVER_PORT"));
    printf("port = %d\n", port);
    strcpy(ip, get_value((char *) conf, "SERVER_IP"));
    printf("ip = %s, port = %d\n", ip, port);
    if ((sockfd = socket_connect(ip, port)) < 0) {
        perror("socket_connect");
        return 1;
    }
    strcpy(msg.from, get_value((char *) conf, "MY_NAME"));
    msg.flag = 2;
    if (chat_send(msg, sockfd) < 0) return 2;
    return 0;
}
