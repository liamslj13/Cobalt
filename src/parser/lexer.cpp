#include <iostream>
#include <string>
#include <vector>

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

    std::string tokenTypeToString(const TokenType type) {
        switch (type) {
            case TokenType::IDENT: return "IDENT";
            case TokenType::NUM: return "NUM";
            case TokenType::STRING: return "STRING";
            case TokenType::DECLARE: return "DECLARE";

            case TokenType::ASSIGN: return "ASSIGN";
            case TokenType::PLUS: return "PLUS";
            case TokenType::MINUS: return "MINUS";
            case TokenType::ASTERISK: return "ASTERISK";
            case TokenType::SLASH: return "SLASH";
            case TokenType::PERCENT: return "PERCENT";

            case TokenType::LPAREN: return "LPAREN";
            case TokenType::RPAREN: return "RPAREN";
            case TokenType::LBRACE: return "LBRACE";
            case TokenType::RBRACE: return "RBRACE";
            case TokenType::LBRACKET: return "LBRACKET";
            case TokenType::RBRACKET: return "RBRACKET";

            case TokenType::SEMICOLON: return "SEMICOLON";
            case TokenType::COLON: return "COLON";
            case TokenType::COMMA: return "COMMA";
            case TokenType::BANG: return "BANG";
            case TokenType::BAR: return "BAR";
            case TokenType::AMPERSAND: return "AMPERSAND";
            case TokenType::CIRCUMFLEX: return "CIRCUMFLEX";
            case TokenType::DOT: return "DOT";
            case TokenType::DOLLAR: return "DOLLAR";
            case TokenType::TERNARY: return "TERNARY";

            case TokenType::GT: return "GT";
            case TokenType::LT: return "LT";
            case TokenType::GTE: return "GTE";
            case TokenType::LTE: return "LTE";
            case TokenType::EQ: return "EQ";
            case TokenType::NEQ: return "NEQ";
            case TokenType::AND: return "AND";
            case TokenType::OR: return "OR";

            case TokenType::FUNCTION: return "FUNCTION";
            case TokenType::IF: return "IF";
            case TokenType::ELSE: return "ELSE";
            case TokenType::WHILE: return "WHILE";
            case TokenType::RETURN: return "RETURN";
            case TokenType::BREAK: return "BREAK";
            case TokenType::CONTINUE: return "CONTINUE";
            case TokenType::TRUE: return "TRUE";
            case TokenType::FALSE: return "FALSE";

            case TokenType::NEWLINE: return "NEWLINE";
            case TokenType::ILLEGAL: return "ILLEGAL";
            case TokenType::EoF: return "EOF";

            default: return "UNKNOWN";
        }
    }

    struct Token {
        TokenType type;
        std::string literal;
        int line;

        explicit Token() = default;

        explicit Token(const TokenType type, const std::string &literal, const int line) : type(type), literal(literal),
            line(line) {
        }

        std::string toString() const {
            return "Token(Type: " + tokenTypeToString(type) + ", Literal: " +
                   literal + ", Line: " + std::to_string(line) + ")";
        }
    };

    class lexer {
        std::string input;
        char ch;
        int pos;
        int readPos;
        int line;
        std::vector<std::string> errors;

        std::unordered_map<std::string, TokenType> keywords = {
            {"fnc", TokenType::FUNCTION},
            {"if", TokenType::IF},
            {"else", TokenType::ELSE},
            {"while", TokenType::WHILE},
            {"return", TokenType::RETURN},
            {"break", TokenType::BREAK},
            {"continue", TokenType::CONTINUE},
            {"true", TokenType::TRUE},
            {"false", TokenType::FALSE},
            {"decl", TokenType::DECLARE},
        };

    public:
        explicit lexer(std::string input) : input(std::move(input)), pos(0), readPos(0), line(1) {
            readChar();
        }


        void readChar() {
            if (readPos >= input.length()) {
                ch = 0;
            } else {
                ch = input[readPos];
            }
            pos = readPos;
            readPos++;
        }

        void skipWhiteSpace() {
            while (ch == ' ' || ch == '\t' || ch == '\r' ||  ch == '\n') {
                if (ch == '\n') {
                    line++;
                }
                readChar();
            }
        }

        Token nextToken() {
            Token tok;
            skipWhiteSpace();

            switch (ch) {
                // basic operators
                case '=':
                    if (peekChar() == '=') {
                        readChar();
                        tok = newToken(TokenType::EQ, "==", line);
                    } else {
                        tok = newToken(TokenType::ASSIGN, std::string(1, ch), line);
                    }
                    break;
                case '+':
                    tok = newToken(TokenType::PLUS, std::string(1, ch), line);
                    break;
                case '-':
                    if (peekChar() == '>') {
                        readChar();
                        tok = newToken(TokenType::TERNARY, "->", line);
                    } else {
                        tok = newToken(TokenType::MINUS, std::string(1, ch), line);
                    }
                    break;
                case '*':
                    tok = newToken(TokenType::ASTERISK, std::string(1, ch), line);
                    break;
                case '/':
                    if (peekChar() == '/') {
                        while (ch != '\n') {
                            readChar();
                        }
                        readChar();
                    } else {
                        tok = newToken(TokenType::SLASH, std::string(1, ch), line);
                    }
                    break;
                case '%':
                    tok = newToken(TokenType::PERCENT, std::string(1, ch), line);
                    break;

                // braces, brackets etc
                case '(':
                    tok = newToken(TokenType::LPAREN, std::string(1, ch), line);
                    break;
                case ')':
                    tok = newToken(TokenType::RPAREN, std::string(1, ch), line);
                    break;
                case '{':
                    tok = newToken(TokenType::LBRACE, std::string(1, ch), line);
                    break;
                case '}':
                    tok = newToken(TokenType::RBRACE, std::string(1, ch), line);
                    break;
                case '[':
                    tok = newToken(TokenType::LBRACKET, std::string(1, ch), line);
                    break;
                case ']':
                    tok = newToken(TokenType::RBRACKET, std::string(1, ch), line);
                    break;

                // statement separators, other char/op etc
                case ';':
                    tok = newToken(TokenType::SEMICOLON, std::string(1, ch), line);
                    break;
                case ':':
                    tok = newToken(TokenType::COLON, std::string(1, ch), line);
                    break;
                case ',':
                    tok = newToken(TokenType::COMMA, std::string(1, ch), line);
                    break;
                case '!':
                    if (peekChar() == '=') {
                        readChar();
                        tok = newToken(TokenType::NEQ, "!=", line);
                    } else {
                        tok = newToken(TokenType::BANG, std::string(1, ch), line);
                    }
                    break;
                case '|':
                    if (peekChar() == '|') {
                        readChar();
                        tok = newToken(TokenType::OR, "||", line);
                    } else {
                        tok = newToken(TokenType::BAR, std::string(1, ch), line);
                    }
                    break;
                case '&':
                    if (peekChar() == '&') {
                        readChar();
                        tok = newToken(TokenType::AND, "&&", line);
                    } else {
                        tok = newToken(TokenType::AMPERSAND, std::string(1, ch), line);
                    }
                    break;
                case '^':
                    tok = newToken(TokenType::CIRCUMFLEX, std::string(1, ch), line);
                    break;
                case '.':
                    tok = newToken(TokenType::DOT, std::string(1, ch), line);
                    break;
                case '$':
                    tok = newToken(TokenType::DOLLAR, std::string(1, ch), line);
                    break;

                // boolean operators
                case '>':
                    if (peekChar() == '=') {
                        readChar();
                        tok = newToken(TokenType::GTE, ">=", line);
                    } else {
                        tok = newToken(TokenType::GT, std::string(1, ch), line);
                    }
                    break;
                case '"':
                    tok = newToken(TokenType::STRING, readString(), line);
                    break;
                case '<':
                    if (peekChar() == '=') {
                        readChar();
                        tok = newToken(TokenType::LTE, "<=", line);
                    } else {
                        tok = newToken(TokenType::LT, std::string(1, ch), line);
                    }
                    break;

                // special cases
                case 0:
                    tok.literal = "";
                    tok.type = TokenType::EoF;
                    break;
                default: {
                    if (isalpha(ch)) {
                        tok.literal = readIdent();
                        if (keywords.find(tok.literal) != keywords.end()) {
                            tok.type = keywords[tok.literal];
                        } else {
                            tok.type = TokenType::IDENT;
                        }
                        tok.line = line;
                        return tok;
                    }
                    if (isdigit(ch)) {
                        std::vector<std::string> res = readNumber();
                        if (res[1] == "inv") {
                            tok = newToken(TokenType::ILLEGAL, res[0], line);
                            std::string err = "Lex error: illegal num literal, num must have one decimal\nline=" +
                                              std::to_string(line) + ", expected=FLOAT, got=ILLEGAL";
                            errors.emplace_back(err);
                        } else {
                            tok = newToken(TokenType::NUM, res[0], line);
                        }
                        return tok;
                    }
                    std::string err = "Lex error: unknown symbol: " +
                                      tok.literal + ", line=" + std::to_string(line) +
                                      "\nexpected valid TokenType, got=ILLEGAL";
                    errors.emplace_back(err);
                    tok = newToken(TokenType::ILLEGAL, "", line);
                }
            }
            readChar();
            return tok;
        }

        char peekChar() const {
            if (readPos >= input.length()) {
                return 0;
            }
            return input[readPos];
        }

        static Token newToken(const TokenType tt, const std::string &lit, const int lineNum) {
            return Token(tt, lit, lineNum); // i think this specifies length of object to be cast
        }

        std::string readIdent() {
            const int start = pos;
            while (isalpha(ch)) {
                readChar();
            }
            return input.substr(start, pos - start);
        }

        // We will mimic multiple value return by utilizing a vector
        // vec[0] -> num value, vec[1] -> "int" || "float"? -> if inv throw error
        // after rereading could have used static arr
        // too lazy to fix now
        std::vector<std::string> readNumber() {
            const int startPosition = pos;
            bool hasDecimal = false;
            bool isInvalid = false;

            while (isdigit(ch) || ch == '.') {
                if (ch == '.') {
                    if (hasDecimal) {
                        isInvalid = true;
                    }
                    hasDecimal = true;
                }

                readChar();
            }

            std::string literal = input.substr(startPosition, pos - startPosition);
            std::string valid;

            std::string type;
            if (isInvalid) {
                valid = "inv";
            } else {
                valid = "valid";
            }

            return {literal, valid};
        }


        std::string readString() {
            std::string res;
            readChar();
            while (ch != '"' && ch != 0) {
                res += ch;
                readChar();
            }

            if (ch == 0) {
                errors.emplace_back("Lex error: unterminated string sequence, line=" + std::to_string(line));
                return res;
            }

            return res;
        }
    };
} // cblt::lex
