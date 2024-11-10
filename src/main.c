#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

bool parseFile(const char path[], long *outCount, char **outContent) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("File '%s' %s\n", path, (errno == ENOENT ? "does not exist" : "could not be opened"));
        return false;
    }

    fseek(file, 0, SEEK_END);
    *outCount = ftell(file);
    rewind(file);

    *outContent = malloc(*outCount * sizeof(char));
    for (int i = 0; i < *outCount; i++) {
        char c;
        if ((c = fgetc(file)) == EOF) {
            fclose(file);
            return false;
        }
        (*outContent)[i] = c;
    }

    fclose(file);
    return true;
}

int printFile(const char path[]) {
    long contentCount = 0;
    char *content = NULL;
    if (!parseFile(path, &contentCount, &content)) {
        free(content);
        return -1;
    }

    for (int i = 0; i < contentCount; i++) {
        printf("%c", content[i]);
    }
    printf("\n");

    free(content);
    return 0;
}

int help() {
    printf("really?\n");
    return 0;
}

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
        if (strcmp(argv[i], "-p") == 0) return printFile("test/main.aeris");
    }

    printf("No flags could be found, use '-h' for help\n");
    return 0;
}