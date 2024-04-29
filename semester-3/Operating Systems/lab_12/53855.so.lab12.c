// SO IS1 223A LAB11
// Vladyslav Zosimchuk
// zv53855@zut.edu.pl

#include <sys/types.h>
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
    if (argc != 2) {
        fprintf(stderr, "Usage: %s source_file\n", argv[0]);
        return 1;
    }
    int source = open(argv[1], O_RDONLY);
    if (source < 0) {
        fprintf(stderr, "Error opening source file\n");
        return 2;
    }
    key_t key = ftok(argv[1], 'a');
    if(key < 0) {
        fprintf(stderr, "Error creating key\n");
        return 3;
    }
    printf("Key obtained: %d\n", key);

    int shmid = shmget(key, MAX_SIZE, 0666 | IPC_CREAT | IPC_EXCL);
    if(shmid < 0) {
        fprintf(stderr, "Error getting shared memory\n");
        return 4;
    }
    DATA* memseg = (DATA*)shmat(shmid, NULL, 0);
    if(memseg == (DATA*)-1) {
        fprintf(stderr, "Error attaching shared memory segment\n");
        return 5;
    }
    ssize_t read_bytes;
    memseg->length = 0;
    memseg->sender_sent = 0;
    memseg->eof = 0;
    memseg->receiver_ready = 0;
    int data_read;
    while(!memseg->receiver_ready) {
    }
    while (1) {
        if (!memseg->sender_sent) {
            data_read = read(source, memseg->message, MAX_SIZE);
            if (data_read == 0) {
                memseg->eof = 1;
                memseg->sender_sent = 1;
                while(memseg->receiver_ready) {

                }
                break;
            } else if (data_read == -1) {
                fprintf(stderr, "Failed to read from file!\n");
                memseg->receiver_ready = 0;
                break;
            } else {
                memseg->sender_sent = 1;
                memseg->length = data_read;
            }
        } else if (!memseg->receiver_ready) {
            fprintf(stderr, "Receiver failed to write!\n");
            break;
        }
        while(memseg->sender_sent) {

        }
    }

    close(source);

    if(shmdt(memseg) == -1) {
        fprintf(stderr, "Error detaching shared memory segment\n");
        return 6;
    }
    if(shmctl(shmid, IPC_RMID, NULL) == -1) {
        fprintf(stderr, "Error removing shared memory\n");
        return 7;
    }
    return 0;
}

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
