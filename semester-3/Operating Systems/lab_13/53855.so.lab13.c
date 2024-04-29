// SO IS1 223A LAB13
// Vladyslav Zosimchuk
// zv53855@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <io.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#define MEM_SIZE 1000

typedef struct{
    char square[9];
    int turn;
    int pids[2];
} Data;

void displayBoard(const char *square) {
    printf(" %c | %c | %c\n", square[0], square[1], square[2]);
    printf("-----------\n");
    printf(" %c | %c | %c\n", square[3], square[4], square[5]);
    printf("-----------\n");
    printf(" %c | %c | %c\n", square[6], square[7], square[8]);
}

int checkStatus(const char* square) {
    // horizontal lines
    for (int i = 0; i < 9; i += 3) {
        if (square[i] == square[i + 1] && square[i] == square[i + 2]) {
            if (square[i] == 'x') {
                return 1;
            } else if (square[i] == 'o') {
                return 2;
            }
        }
    }

    // vertical lines
    for (int i = 0; i < 3; ++i) {
        if (square[i] == square[i + 3] && square[i] == square[i + 6]) {
            if (square[i] == 'x') {
                return 1;
            } else if (square[i] == 'o') {
                return 2;
            }
        }
    }

    // diagonals
    if ((square[0] == square[4] && square[0] == square[8]) ||
        (square[2] == square[4] && square[2] == square[6])) {
        if (square[4] == 'x') {
            return 1;
        } else if (square[4] == 'o') {
            return 2;
        }
    }

    // draw
    for (int i = 0; i < 9; ++i) {
        if (square[i] >= '0' && square[i] <= '9') {
            return 0;
        }
    }
    return 3;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Invalid arguments!");
        return 1;
    }
    Data* data = malloc(sizeof(Data));
    char square[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    memcpy(data->square, square, sizeof(square));
    data->turn = 1;
    HANDLE MapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, argv[1]);
    if (MapFile == NULL) {
        MapFile = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,MEM_SIZE, argv[1]);
        if (MapFile == NULL) {
            fprintf(stderr, "Could not create file mapping object\n");
            return 1;
        }
        //printf("You created a MapFile!\n");
        data->turn = 1;
    } else {
        //printf("You opened a MapFile\n");
        data->turn = 2;
    }
    Data* buf = (Data*)MapViewOfFile(MapFile, FILE_MAP_ALL_ACCESS, 0, 0, MEM_SIZE);
    if (buf == NULL) {
        free(data);
        fprintf(stderr, "Could not map view of file\n");
        CloseHandle(MapFile);
        return 3;
    }
    if (data->turn == 1) memcpy(buf, data, sizeof(Data));
    if (data->turn == 1) {
        buf->pids[0] = GetCurrentProcessId();
    } else if (data->turn == 2) {
        buf->pids[1] = GetCurrentProcessId();
    }
    if (!buf->pids[1]) {
       printf("Wait until Player 2 joins!\n");
       while(!buf->pids[1]) {}
       printf("\033[2J\033[1;1H");
    }
    free(data);
    buf->turn = 1;
    int gameStatus = 0; // 0 - going on, 1 - first player won, 2 - second player won, 3 - draw
    char choice;
    while (!gameStatus) {
        printf("\033[2J\033[1;1H");
        displayBoard(buf->square);
        if (buf->turn == 1) {
            if (GetCurrentProcessId() == buf->pids[0]) {
                printf("It's your turn! Make a choice\n");
                while (1) {
                    choice = getch();
                    printf("\n");
                    if (choice >= '0' && choice <= '9') {
                        if (buf->square[choice-'1'] == choice) {
                            buf->square[choice-'1'] = 'x';
                            buf->turn = 2;
                            break;
                        } else {
                            printf("Please, try again! This index is already occupied.\n");
                        }
                    } else {
                        printf("Please, try again! Wrong index.\n");
                    }
                }
            } else {
                printf("Please wait for the other user's move!\n");
                while(buf->turn == 1) {}
            }
        } else if (buf->turn == 2) {
            if (GetCurrentProcessId() == buf->pids[1]) {
            printf("It's your turn! Make a choice.\n");
            while (1) {
                choice = getch();
                printf("\n");
                if (choice >= '0' && choice <= '9') {
                    if (buf->square[choice-'1'] == choice) {
                        buf->square[choice-'1'] = 'o';
                        buf->turn = 1;
                        break;
                    } else {
                        printf("Please, try again! This index is already occupied.\n");
                    }
                } else {
                    printf("Please, try again! Wrong index.\n");
                }
            }
        } else {
            printf("Please wait for the other user's move!\n");
            while (buf->turn == 2) {}
        }
    }
        gameStatus = checkStatus(buf->square);
        if (gameStatus == 1) {
            printf("Player 1 wins!");
            break;
        }
        if (gameStatus == 2) {
            printf("Player 2 wins!");
            break;
        }
        if (gameStatus == 3) {
            printf("It's a draw!");
            break;
        }
    }
    if(!UnmapViewOfFile(buf)) {
        fprintf(stderr, "Could not unmap view of file\n");
        CloseHandle(MapFile);
        return 2;
    }
    CloseHandle(MapFile);
    return 0;
}
