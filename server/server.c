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
#include "../common/color.h"

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
    int *sub = (int *) arg;
    int client_fd = client[*sub].fd;
    RecvMsg rmsg;
    while (1) {
        rmsg = chat_recv(client_fd);
        if (rmsg.retval < 0) {
            printf(PINK"Logout:"NONE"%s\n", client[*sub].name);
            close(client_fd);
            client[*sub].online = 0;
            return NULL;
        }
        printf(BLUE"%s"NONE" : %s\n", client[*sub].name, rmsg.msg.message);
    }
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
        if (client[i].online && !strcmp(client[i].name, name)){
            printf(YELLOW"%s is online\n"NONE, name);
            return true;
        } 
    }
    return false;
}

int main() {
    int port, server_listen, fd;
    RecvMsg recvmsg;
    Msg msg;
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
            msg.flag = 3;
            strcpy(msg.message, "You have Already Loginned!\n");
            chat_send(msg, fd);
            close(fd);
            continue;
        } else {
            msg.flag = 2;
            strcpy(msg.message, "Welcome to this chat room!\n");
            chat_send(msg, fd);
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
