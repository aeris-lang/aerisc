#include <stdlib.h>
#include <string.h>
#include "tokenize.h"
#include "token.h"

bool peak (
    long *index,
    char desiredPeak[],
    long *sourceC,
    char **sourceV,
    struct Token *token
) {
    long cachedIndex = *index;

    for (int i = 0; i < strlen(desiredPeak); i++) {
        if (cachedIndex >= *sourceC) return false;
        if ((*sourceV)[cachedIndex] != desiredPeak[i]) return false;
        token->content[i] = ((*sourceV)[cachedIndex++]);
        token->content[i+1] = '\0';
    }

    *index = --cachedIndex;
    return true;
}

bool tokenize (
    long *sourceC,
    char **sourceV,
    long *outTokenC,
    struct Token *outTokenV[]
) {
    *outTokenC = 0;
    *outTokenV = malloc(*sourceC * sizeof(struct Token));

    #define PEAK(desiredPeak, Token)                                            \
    if (peak(&l, desiredPeak, sourceC, sourceV, &(*outTokenV)[*outTokenC])) {   \
        (*outTokenV)[(*outTokenC)++].type = Token;                              \
        continue;                                                               \
    }

    #define CASE(char, peaks)   \
    case char: {                \
        peaks                   \
        break;                  \
    }

    for (long l = 0; l < *sourceC; l++) {
        switch ((*sourceV)[l]) {
            CASE('b', PEAK("break", BREAK))
            CASE('c', PEAK("char", CHAR))
            CASE('e',
                PEAK("else", ELSE)
                PEAK("elif", ELIF)
            )
            CASE('f', PEAK("float", FLOAT))
            CASE('i',
                PEAK("if", IF)
                PEAK("int", INT)
            )
            CASE('r', PEAK("return", RETURN))
            CASE('v', PEAK("void", VOID))
            CASE('w', PEAK("while", WHILE))
            CASE(' ', PEAK(" ", WHITESPACE))
            CASE(';', PEAK(";", SEMICOLON))
            CASE(',', PEAK(",", COMMA))
            CASE('{', PEAK("{", OPENING_CURLY))
            CASE('}', PEAK("}", CLOSING_CURLY))
            CASE('(', PEAK("(", OPENING_PARENTHESES))
            CASE(')', PEAK(")", CLOSING_PARENTHESES))
            CASE('[', PEAK("[", OPENING_SQUARE))
            CASE(']', PEAK("", CLOSING_SQUARE))
        }

        int index = 0;
        do {
            (*outTokenV)[*outTokenC].content[index++] = (*sourceV)[l++];
        } while (
            ((*sourceV)[l] >= 'A' && (*sourceV)[l] <= 'Z')
        ||  ((*sourceV)[l] >= 'a' && (*sourceV)[l] <= 'z')
        );
        (*outTokenV)[*outTokenC].content[index] = '\0';
        (*outTokenV)[(*outTokenC)++].type = IDENTIFIER;
        l--;
    }

    return true;
};