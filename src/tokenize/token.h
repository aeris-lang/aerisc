#pragma once

enum Token {
// Formatting
    WHITESPACE,

// Keywords
    // Control Flows
        IF,
        ELSE,
        ELIF,
        WHILE,
        RETURN,
        BREAK,

    // DataTypes
        VOID,
        INT,
        FLOAT,
        CHAR,

// Separators
    // Punctuation
        SEMICOLON,
        COMMA,

    // Brackets
        OPENING_CURLY,
        CLOSING_CURLY,
        OPENING_PARENTHESES,
        CLOSING_PARENTHESES,
        OPENING_SQUARE,
        CLOSING_SQUARE
};