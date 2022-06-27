#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <hiredis/hiredis.h>

int main(int argc, char **argv)
{
    const char *hostname = "127.0.0.1";
    int port = 6379;
    struct timeval timeout = { 1, 500000 };
    redisContext *redisContext = redisConnectWithTimeout(hostname, port, timeout);
    if (redisContext == NULL || redisContext->err) {
        if (redisContext) {
            printf("Connection error: %s\n", redisContext->errstr);
            redisFree(redisContext);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }
    time_t refTime = time(NULL);
    int count = 0;
    for(;;)
    {
        redisReply *reply;
        reply = redisCommand(redisContext,"GET demo1");
        time_t now = time(NULL);
        if(now != refTime)
        {
            printf("GET demo1: %s, %d\n", reply->str, count);
            refTime = now;
            count = 0;
        }
        freeReplyObject(reply);
        count += 1;
    }
}