#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
int main(void) {
for(int c = 0; c < 3; c++) {
int child = fork();
if(child == 0) {
srand(getpid());
int secs = rand() % 5 + 1;
char buf[10];
sprintf(buf, "%d", secs);
char *newargv[3] = { "./lin_prog", buf, NULL };
execvp("./lin_prog", newargv);
fprintf(stderr, "exec failed: %s\n", strerror(errno));
return 1;
}
}
for(int c = 0; c < 3; c++) {
int status, child = wait(&status);
printf("Parent: child #%d exited: PID=%d, retcode=%d\n", c, child, WEXITSTATUS(status));
}
return 0;
}
