// test_lexer.cpp
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "../parser/lexer.cpp"

void testLexer() {
    struct Expected {
        cblt::lex::TokenType type;
        std::string literal;
        int line;
    };

    std::vector<Expected> expected = {
        { cblt::lex::TokenType::FUNCTION, "fnc", 1 },
        { cblt::lex::TokenType::IF,       "if", 1 },
        { cblt::lex::TokenType::ELSE,     "else", 1 },
        { cblt::lex::TokenType::WHILE,    "while", 1 },
        { cblt::lex::TokenType::RETURN,   "return", 1 },
        { cblt::lex::TokenType::BREAK,    "break", 1 },
        { cblt::lex::TokenType::CONTINUE, "continue", 1 },
        { cblt::lex::TokenType::TRUE,     "true", 1 },
        { cblt::lex::TokenType::FALSE,    "false", 1 },
        { cblt::lex::TokenType::IDENT,  "foo", 1 },
        { cblt::lex::TokenType::NUM,    "123", 1 },
        { cblt::lex::TokenType::NUM,  "45.67", 1 },
        { cblt::lex::TokenType::ASSIGN,    "=", 1 },
        { cblt::lex::TokenType::PLUS,      "+", 1 },
        { cblt::lex::TokenType::MINUS,     "-", 1 },
        { cblt::lex::TokenType::ASTERISK,  "*", 1 },
        { cblt::lex::TokenType::SLASH,     "/", 1 },
        { cblt::lex::TokenType::PERCENT,   "%", 1 },
        { cblt::lex::TokenType::BANG,      "!", 1 },
        { cblt::lex::TokenType::BAR,       "|", 1 },
        { cblt::lex::TokenType::AMPERSAND, "&", 1 },
        { cblt::lex::TokenType::CIRCUMFLEX,"^", 1 },
        { cblt::lex::TokenType::DOT,       ".", 1 },
        { cblt::lex::TokenType::DOLLAR,    "$", 1 },
        { cblt::lex::TokenType::TERNARY,   "->", 1 },
        { cblt::lex::TokenType::GT,    ">", 2 },
        { cblt::lex::TokenType::LT,    "<", 2 },
        { cblt::lex::TokenType::GTE,   ">=", 2 },
        { cblt::lex::TokenType::LTE,   "<=", 2 },
        { cblt::lex::TokenType::EQ,    "==", 2 },
        { cblt::lex::TokenType::NEQ,   "!=", 2 },
        { cblt::lex::TokenType::AND,   "&&", 2 },
        { cblt::lex::TokenType::OR,    "||", 2 },
        { cblt::lex::TokenType::LPAREN,   "(", 2 },
        { cblt::lex::TokenType::RPAREN,   ")", 2 },
        { cblt::lex::TokenType::LBRACE,   "{", 2 },
        { cblt::lex::TokenType::RBRACE,   "}", 2 },
        { cblt::lex::TokenType::LBRACKET, "[", 2 },
        { cblt::lex::TokenType::RBRACKET, "]", 2 },
        { cblt::lex::TokenType::SEMICOLON,";", 2 },
        { cblt::lex::TokenType::COLON,    ":", 2 },
        { cblt::lex::TokenType::COMMA,    ",", 2 },

        { cblt::lex::TokenType::STRING,   "hello world", 2 },
        { cblt::lex::TokenType::EoF,      "", 2 }
    };

    std::string input = R"(fnc if else while return break continue true false foo 123 45.67 =+-*/%!|&^.$->
> < >= <= == != && || (){}[];:,"hello world"
)";

    cblt::lex::Lexer l(input);
    for (int i = 0; i < expected.size(); ++i) {
        cblt::lex::Token tok = l.nextToken();
        std::cout << tok.toString() << '\n';
        assert(tok.type    == expected[i].type    && "TokenType mismatch");
        assert(tok.literal == expected[i].literal && "Token literal mismatch");
        assert(tok.line    == expected[i].line    && "Token line mismatch");
    }

    std::cout << "lexer tests pass\n";
}