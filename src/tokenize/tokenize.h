#pragma once
#include <stdbool.h>
#include "token.h"

bool peak (
    long *index,
    char desiredPeak[],
    long *sourceC,
    char **sourceV
);

bool tokenize (
    long *sourceC,
    char **sourceV,
    long *outTokenC,
    enum Token *outTokenV[]
);