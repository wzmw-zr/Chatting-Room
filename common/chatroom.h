/*************************************************************************
	> File Name: chatroom.h
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月29日 星期日 16时27分18秒
 ************************************************************************/

#ifndef _CHATROOM_H
#define _CHATROOM_H
typedef struct Msg {
    char from[20];
    int flag;
    char message[512];
} Msg;

typedef struct RecvMsg {
    Msg msg;
    int retval;
} RecvMsg;

typedef struct SendMsg {
    Msg msg;
    int retval;
} SendMsg;

int chat_send(Msg msg, int fd) {
    if (send(fd, (void *) &msg, sizeof(msg), 0) <= 0) return -1;
    return 0;
}

RecvMsg chat_recv(int fd);
#endif
