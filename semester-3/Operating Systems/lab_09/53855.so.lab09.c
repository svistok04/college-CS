// SO IS1 223A LAB09
// Vladyslav Zosimchuk
// zv53855@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    if (strlen(argv[1]) > 25 || argc != 2) {
        fprintf(stderr, "Error: Invalid argument\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++) {
        if (argv[1][i] < '0' || argv[1][i] > '9') {
            fprintf(stderr, "Error: Invalid argument\n");
            return 1;
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

    STARTUPINFOA si1, si2;
    PROCESS_INFORMATION pi1, pi2;

    memset(&si1, 0 ,sizeof(si1));
    si1.cb = sizeof(si1);
    memset(&pi1, 0, sizeof(pi1));

    memset(&si2, 0, sizeof(si2));
    si2.cb = sizeof(si2);
    memset(&pi2, 0, sizeof(pi2));

    char argline1[50];
    sprintf(argline1, "%s %s", argv[0], firstHalf);
    char argline2[50];
    sprintf(argline2, "%s %s", argv[0], secondHalf);


    if (!CreateProcessA(NULL, argline1, NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1)) {
        fprintf(stderr, "Error creating process\n");
        return 1;
    }


    if (!CreateProcessA(NULL, argline2, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2)) {
        fprintf(stderr, "Error creating process\n");
        return 1;
    }

    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);

    DWORD status1, status2;
    GetExitCodeProcess(pi1.hProcess, &status1);
    GetExitCodeProcess(pi2.hProcess, &status2);
    printf("%d %d\t\t%s %d\n", GetCurrentProcessId(), pi1.dwProcessId, firstHalf, status1);
    printf("%d %d\t\t%s %d\n", GetCurrentProcessId(), pi2.dwProcessId, secondHalf, status2);

    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

    return status1 + status2;
}
