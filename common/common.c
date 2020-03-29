/*************************************************************************
	> File Name: common.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月29日 星期日 15时35分48秒
 ************************************************************************/

#include "head.h"

char *get_value(char *path, char *key) {
    FILE *fp = NULL;
    ssize_t nrd;
    char *line = NULL, *sub = NULL, *ans = (char *) calloc(sizeof(char) ,100);
    size_t linecap = 0;
    if (path == NULL || key == NULL) {
        fprintf(stderr, "Error in argument!\n");
        return NULL;
    }
    if ((fp = fopen(path, "r")) == NULL) {
        perror("fopen");
        return NULL;
    }
    while ((nrd = getline(&line, &linecap, fp)) != -1) {
        if ((sub = strstr(line, key)) == NULL) {
            free(line);
            line = NULL;
            linecap = 0;
            continue;
        }
        if (line[strlen(key)] == '=') {
            strncpy(ans, sub + strlen(key) + 1, nrd - strlen(key) - 1);
            ans[strlen(ans) - 1] = '\0';
        }
    }
    free(line);
    fclose(fp);
    if (sub == NULL) return NULL;
    return ans;
}
