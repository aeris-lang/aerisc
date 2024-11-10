#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands/commands.h"

int main(int argc, char *argv[]) {
    if (system("clang --version\n") != 0) {
        printf("Clang could not be found!\n");
        return -1;
    }
    printf("\n");

    int flagc = 0;
    char *flagv[argc-1];
    int otherc = 0;
    char *otherv[argc-1];

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            flagv[flagc++] = argv[i];
        }
        else {
            otherv[otherc++] = argv[i];
        }
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) return help();
        if (strcmp(argv[i], "-p") == 0) return printFile("test/main.ars");
        if (strcmp(argv[i], "-t") == 0) return transpile("test/main.ars");
    }

    printf("No flags could be found, use '-h' for help\n");
    return 0;
}