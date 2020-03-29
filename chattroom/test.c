/*************************************************************************
	> File Name: test.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月29日 星期日 15时59分48秒
 ************************************************************************/

#include "../common/head.h"
#include "../common/common.h"

int main(int argc, char **argv) {
    char *value = NULL;
    value = get_value("a.conf", "SERVERIP");
    if (value) {
        printf("%s\n", value);
        free(value);
    }
    else printf("Not find\n");
    return 0;
}
