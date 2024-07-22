#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdlib.h>

#define MAX_TEXT 512

struct my_msg_st
{
    long int my_msg_type;
    char some_text[MAX_TEXT];
};

int main()
{
    int running = 1, msgid;
    struct my_msg_st some_data;
    char buffer[BUFSIZ];

    printf("Demonstration of IPC using Messege queue\n");

    msgid = msgget( (key_t) 1234, 0666 | IPC_CREAT);
    if(msgid == -1)
    {
        printf("failed to create:\n");
        exit(EXIT_FAILURE);
    }    

    printf("Messege Queue is created successfully\n");

    while(running)
    {
        printf("Entre Some messege : ");
        fgets(buffer, BUFSIZ, stdin);
        some_data.my_msg_type = 1; 
        strcpy(some_data.some_text, buffer);

        if(msgsnd(msgid, (void *) &some_data, MAX_TEXT, 0) == -1)
        {
            printf("msgsnd failed\n");
            exit(EXIT_FAILURE);
        }

        if(strncmp(buffer, "end", 3) == 0)
        {
            running = 0; 
        }
    }

    printf("Terminating the server process\n");

    exit(EXIT_SUCCESS);
}