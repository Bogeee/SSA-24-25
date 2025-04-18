#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_BUF_SIZE 1024
#define MAX_ERR_BUF_SIZE 1044
#define LOG_ERROR(msg)                                  \
    do                                                  \
    {                                                   \
        fprintf(stderr, "[ERROR] %s:%d (%s): %s\n",     \
                __FILE__, __LINE__, __FUNCTION__, msg); \
    } while (0)

void func1(char *src)
{
    if(src == NULL)
    {
        LOG_ERROR("src is NULL");
        return;
    }
    size_t dst_size = (strlen(src) + 1) * sizeof(char); /* Flawfinder: ignore */
    char dst[dst_size]; /* Flawfinder: ignore */

    strlcpy(dst, src, dst_size);
}

void func2(int fd)
{
    char *buf;
    size_t len;
    read(fd, &len, sizeof(len)); /* Flawfinder: ignore */

    if (len > MAX_BUF_SIZE)
        return;
    buf = (char *)malloc(len + 1);
    read(fd, buf, len); /* Flawfinder: ignore */
    buf[len] = '\0';

    free(buf);
    buf = NULL;
}

char * func3()
{
    char buffer[MAX_BUF_SIZE]; /* Flawfinder: ignore */
    printf("Please enter your user id :");
    fgets(buffer, MAX_BUF_SIZE, stdin);
    if (!isalpha(buffer[0]))
    {
        char *errormsg = (char *)malloc(MAX_ERR_BUF_SIZE);
        strlcpy(errormsg, buffer, MAX_ERR_BUF_SIZE);
        strlcat(errormsg, " is not a valid ID", MAX_ERR_BUF_SIZE);
        return errormsg;
    }
    return NULL;
}

char * func4(char *foo)
{
    if (foo == NULL)
    {
        LOG_ERROR("foo is NULL");
        return NULL;
    }
    size_t buf_size = (strlen(foo) + 1) * sizeof(char); /* Flawfinder: ignore */
    char *buffer = (char *)malloc(buf_size);
    strlcpy(buffer, foo, buf_size);
    
    return buffer;
}

int main()
{
    int y = 9;
    int a[10];

    char *copied = func4("fooooooooooooooooooooooooooooooooooooooooooooooooooo");
    if(copied != NULL)
    {
        printf("%s", copied);
        free(copied);
        copied = NULL;
    }

    char *err_message = func3();
    if (err_message != NULL)
    {
        fprintf(stderr, "%s", err_message);
        free(err_message);
        err_message = NULL;
    }

    while (y >= 0)
    {
        a[y] = y;
        y = y - 1;
    }
    return 0;
}