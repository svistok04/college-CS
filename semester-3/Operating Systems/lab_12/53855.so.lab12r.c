// SO IS1 223A LAB12
// Vladyslav Zosimchuk
// zv53855@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#define MAX_SIZE 100

typedef struct {
    char message[MAX_SIZE];
    int length;
    int eof;
    int receiver_ready;
    int sender_sent;
} DATA;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s key_name target_file\n", argv[0]);
        return 1;
    }
    key_t key = atoi(argv[1]);
    char* target_file = argv[2];

    if(key < 0) {
        fprintf(stderr, "Wrong key\n");
        return 2;
    }
    int shmid = shmget(key, MAX_SIZE, 0666);
    if(shmid < 0) {
        fprintf(stderr, "Error getting shared memory\n");
        return 3;
    }
    DATA* memseg = (DATA*)shmat(shmid, NULL, 0);
    if(memseg == (DATA*)-1) {
        fprintf(stderr, "Error attaching shared memory segment\n");
        return 4;
    }
    memseg->receiver_ready = 1;
    int dest = open(target_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest < 0) {
        fprintf(stderr, "Error creating target file\n");
        return 5;
    }
    int signal;
    while (1) {
        if (memseg->eof) {
            memseg->receiver_ready = 0;
            break;
        }
        if (memseg->sender_sent) {
            signal = write(dest, memseg->message, memseg->length);
            if (signal == -1) {
                printf("Failed to write!\n");
                memseg->receiver_ready = 0;
                memseg->sender_sent = 0;
                break;
            }
        } else if (!memseg->receiver_ready) {
            fprintf(stderr, "Sender failed to read from file!\n");
            break;
        }
        memseg->sender_sent = 0;
        while(!memseg->sender_sent) {

        }
    }

    close(dest);

    if(shmdt(memseg) == -1) {
        fprintf(stderr, "Error detaching shared memory segment\n");
        return 7;
    }
    return 0;
}
