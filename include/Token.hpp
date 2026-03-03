#pragma once

#include <string>


enum class TokenType
{
    //KEY WORDS
    PRINT_KEYWORD,
    
    
    IDENTIFIER,
    
    //LITERALS
    NUMBER,
    STRING,
    
    L_PAREN,
    R_PAREN,
    SEMICOLON,

    UNKNOWN,
    EOF_TOKEN
};

struct Token
{
    TokenType type;
    std::string value;
};
