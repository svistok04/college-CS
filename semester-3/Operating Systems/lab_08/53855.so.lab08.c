// SO IS1 223A LAB08
// Vladyslav Zosimchuk
// zv53855@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2 || strlen(argv[1]) > 25) {
        fprintf(stderr, "Error: Invalid argument\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++) {
        if (argv[1][i] < '0' || argv[1][i] > '9') {
            fprintf(stderr, "Error: Invalid argument\n");
            return 2;
        }
    }

    int length = strlen(argv[1]);

    if (length == 1) {
        return argv[1][0] - '0';
    }

    int mid = length / 2;
    char firstHalf[mid + 1];
    strncpy(firstHalf, argv[1], mid);
    firstHalf[mid] = '\0';
    char secondHalf[length - mid + 1];
    strncpy(secondHalf, argv[1] + mid, length - mid);
    secondHalf[length - mid] = '\0';

    int fork1 = fork();
    if (fork1 == 0) {
        execl(argv[0], argv[0], firstHalf, NULL);
    } else if (fork1 == -1) {
        fprintf(stderr, "Error creating a fork");
        return 0;
    }

    int fork2 = fork();
    if (fork2 == 0) {
        execl(argv[0], argv[0], secondHalf, NULL);
    } else if (fork2 == -1) {
        fprintf(stderr, "Error creating a fork");
        return 0;
    }

    int status1, status2;
    waitpid(fork1, &status1, 0);
    waitpid(fork2, &status2, 0);

    printf("%d %d\t\t%s %d\n", getpid(), fork1, firstHalf, WEXITSTATUS(status1));
    printf("%d %d\t\t%s %d\n", getpid(), fork2, secondHalf, WEXITSTATUS(status2));

    return WEXITSTATUS(status1) + WEXITSTATUS(status2);
}
