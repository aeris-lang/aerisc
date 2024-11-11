#pragma once
#include <stdbool.h>
#include "token.h"

bool peak (
    long *index,
    char desiredPeak[],
    long *sourceC,
    char **sourceV,
    struct Token *token
);

bool tokenize (
    long *sourceC,
    char **sourceV,
    long *outTokenC,
    struct Token *outTokenV[]
);