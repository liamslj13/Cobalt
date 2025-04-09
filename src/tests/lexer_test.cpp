// test_lexer.cpp
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "../parser/lexer.cpp"

using namespace cblt::lex;

void testLexer() {
    struct Expected {
        TokenType type;
        std::string literal;
        int line;
    };

    std::vector<Expected> expected = {
        { TokenType::FUNCTION, "fnc", 1 },
        { TokenType::IF,       "if", 1 },
        { TokenType::ELSE,     "else", 1 },
        { TokenType::WHILE,    "while", 1 },
        { TokenType::RETURN,   "return", 1 },
        { TokenType::BREAK,    "break", 1 },
        { TokenType::CONTINUE, "continue", 1 },
        { TokenType::TRUE,     "true", 1 },
        { TokenType::FALSE,    "false", 1 },
        { TokenType::IDENT,  "foo", 1 },
        { TokenType::NUM,    "123", 1 },
        { TokenType::NUM,  "45.67", 1 },
        { TokenType::ASSIGN,    "=", 1 },
        { TokenType::PLUS,      "+", 1 },
        { TokenType::MINUS,     "-", 1 },
        { TokenType::ASTERISK,  "*", 1 },
        { TokenType::SLASH,     "/", 1 },
        { TokenType::PERCENT,   "%", 1 },
        { TokenType::BANG,      "!", 1 },
        { TokenType::BAR,       "|", 1 },
        { TokenType::AMPERSAND, "&", 1 },
        { TokenType::CIRCUMFLEX,"^", 1 },
        { TokenType::DOT,       ".", 1 },
        { TokenType::DOLLAR,    "$", 1 },
        { TokenType::TERNARY,   "->", 1 },
        { TokenType::GT,    ">", 2 },
        { TokenType::LT,    "<", 2 },
        { TokenType::GTE,   ">=", 2 },
        { TokenType::LTE,   "<=", 2 },
        { TokenType::EQ,    "==", 2 },
        { TokenType::NEQ,   "!=", 2 },
        { TokenType::AND,   "&&", 2 },
        { TokenType::OR,    "||", 2 },
        { TokenType::LPAREN,   "(", 2 },
        { TokenType::RPAREN,   ")", 2 },
        { TokenType::LBRACE,   "{", 2 },
        { TokenType::RBRACE,   "}", 2 },
        { TokenType::LBRACKET, "[", 2 },
        { TokenType::RBRACKET, "]", 2 },
        { TokenType::SEMICOLON,";", 2 },
        { TokenType::COLON,    ":", 2 },
        { TokenType::COMMA,    ",", 2 },

        { TokenType::STRING,   "hello world", 2 },
        { TokenType::EoF,      "", 2 }
    };

    std::string input = R"(fnc if else while return break continue true false foo 123 45.67 =+-*/%!|&^.$->
> < >= <= == != && || (){}[];:,"hello world"
)";

    lexer l(input);
    for (int i = 0; i < expected.size(); ++i) {
        Token tok = l.nextToken();
        std::cout << tok.toString() << '\n';
        assert(tok.type    == expected[i].type    && "TokenType mismatch");
        assert(tok.literal == expected[i].literal && "Token literal mismatch");
        assert(tok.line    == expected[i].line    && "Token line mismatch");
    }

    std::cout << "lexer tests pass\n";
}