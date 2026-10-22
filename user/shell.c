#include "user.h"
#include "../common/common.h"

void main(void) {
    while (1) {
        prompt:
        printf("$ ");
        char cmdline[128];
        for (int i = 0;; i++) {
            char ch = getchar();
            putchar(ch);
            if (i == sizeof(cmdline) - 1) {
                printf("command line too long\n");
                goto prompt;
            } else if (ch == '\r') { // FYI '\r' is a new line character.
                printf("\n");
                cmdline[i] = '\0';
                break;
            } else {
                cmdline[i] = ch;
            }
        }

        if (strcmp(cmdline, "hello") == 0)
            printf("Hello from the shell!\n");
        else if (strcmp(cmdline, "exit") == 0)
            exit();
        else
            printf("unknown command %s\n", cmdline);
    }
}