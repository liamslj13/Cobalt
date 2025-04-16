#pragma once

#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <iostream>

namespace cblt::lex {
    enum struct TokenType {
        IDENT,
        NUM,
        STRING,
        DECLARE,

        // type keywrods
        NUM_TYPE, // num
        BOOL_TYPE, // bool
        STRING_TYPE, // str

        ASSIGN,
        PLUS,
        MINUS,
        ASTERISK,
        SLASH,
        PERCENT,

        LPAREN,
        RPAREN,
        LBRACE,
        RBRACE,
        LBRACKET,
        RBRACKET,

        SEMICOLON,
        COLON,
        COMMA,
        BANG,
        BAR,
        AMPERSAND,
        CIRCUMFLEX,
        DOT,
        DOLLAR,
        TERNARY,

        // boolean operators
        GT,
        LT,
        GTE,
        LTE,
        EQ,
        NEQ,
        AND,
        OR,

        // keywords
        FUNCTION,
        IF,
        ELSE,
        WHILE,
        RETURN,
        BREAK,
        CONTINUE,
        TRUE,
        FALSE,

        NEWLINE,
        ILLEGAL,
        EoF,
    };

    std::string tokenTypeToString(TokenType type);

    struct Token {
        TokenType type;
        std::string literal;
        int line;

        // Constructors
        Token();

        Token(TokenType type, std::string literal, int line);

        [[nodiscard]] std::string toString() const;
    };

    class Lexer {
        std::string input;
        char ch;
        int pos, readPos, line;
        std::vector<std::string> errors;
        std::unordered_map<std::string, TokenType> keywords;

    public:
        explicit Lexer(std::string input);

        void readChar();

        void skipWhitespace();

        [[nodiscard]] Token nextToken();

        [[nodiscard]] char peekChar() const;

        static Token newToken(TokenType tt, const std::string &lit, int lineNum);

        std::string readIdent();

        std::vector<std::string> readNumber();

        std::string readString();
    };
}
#endif //LEXER_H
