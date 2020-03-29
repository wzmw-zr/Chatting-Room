/*************************************************************************
	> File Name: server.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月29日 星期日 16时13分23秒
 ************************************************************************/

#include "../common/head.h"
#include "../common/common.h"
#include "../common/tcp_server.h"
#include "../common/chatroom.h"

typedef struct User {
    char name[20];
    int online;
    pthread_t tid;
    int fd;
} User;

#define MAX_CLIENT 512
const char *conf = "./server.conf";

User *client;

void *work(void *arg) {
    printf("client login!\n");
    return NULL;
}

int find_sub() {
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (!client[i].online) return i;
    }
    return -1;
}

bool check_online(char *name) {
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (client[i].online && !strcmp(client[i].name, name)) return true;
    }
    return false;
}

int main() {
    int port, server_listen, fd;
    RecvMsg recvmsg;
    port = atoi(get_value((char *) conf, "SERVER_PORT"));
    client = (User *) calloc(sizeof(User), MAX_CLIENT);
    if ((server_listen = socket_create(port)) < 0) {
        perror("socket_create");
        return 1;
    }
    while (1) {
        if ((fd = accept(server_listen, NULL, NULL)) < 0) {
            perror("accept");
            continue;
        }
        recvmsg = chat_recv(fd); 
        if (recvmsg.retval == -1) {
            close(fd);
            continue;
        }
        if (check_online(recvmsg.msg.from)) { 

        } else {
            int sub;
            sub = find_sub();
            client[sub].online = 1;
            client[sub].fd = fd;
            strcpy(client[sub].name, recvmsg.msg.from);
            pthread_create(&client[sub].tid, NULL, work, NULL);
        }
    }
    return 0;
}
