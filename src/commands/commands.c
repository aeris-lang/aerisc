#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "commands.h"
#include "../tokenize/tokenize.h"

bool parseFile(const char path[], long *outContentC, char **outContentV) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("File '%s' %s\n", path, (errno == ENOENT ? "does not exist" : "could not be opened"));
        return false;
    }

    fseek(file, 0, SEEK_END);
    *outContentC = ftell(file);
    rewind(file);

    *outContentV = malloc(*outContentC * sizeof(char));
    for (int i = 0; i < *outContentC; i++) {
        char c;
        if ((c = fgetc(file)) == EOF) {
            fclose(file);
            return false;
        }
        (*outContentV)[i] = c;
    }

    fclose(file);
    return true;
}

int help() {
    printf("-h: help\n");
    printf("-p: print file\n");
    printf("-t: transpile\n");
    return 0;
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

int transpile(const char path[]) {
    long contentC = 0;
    char *contentV = NULL;
    if (!parseFile(path, &contentC, &contentV)) {
        free(contentV);
        return -1;
    }

    long tokenC = 0;
    enum Token *tokenV;
    if (!tokenize(&contentC, &contentV, &tokenC, &tokenV)) {
        free(contentV);
        return -1;
    }

    free(contentV);
    return 0;
}