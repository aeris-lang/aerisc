#pragma once
#include <stdbool.h>

bool parseFile (
    const char path[],
    long *outContentC,
    char **outContentV
);
int help();
int printFile(const char path[]);
int transpile(const char path[]);