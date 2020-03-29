/*************************************************************************
	> File Name: chatroom.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月29日 星期日 16时39分44秒
 ************************************************************************/

#include "./head.h"
#include "./chatroom.h"

RecvMsg chat_recv(int fd) {
    RecvMsg tmp;
    memset(&tmp, 0, sizeof(tmp));
    if (recv(fd, (void *) &(tmp.msg), sizeof(Msg), 0) <= 0) {
        tmp.retval = -1;
    } 
    return tmp;
}
