#pragma once

#ifndef PARSER_H
#define PARSER_H

#include "../h/lexer.h"
#include "../h/ast.h"
#include <unordered_map>
#include <vector>

namespace cblt::parse {

    using PrefixParseFn = std::function<std::unique_ptr<ast::Expr>()>;
    using InfixParseFn  = std::function<std::unique_ptr<ast::Expr>(std::unique_ptr<ast::Expr>)>;

    enum class Precedence {
        NONE = 0,
        LOWEST,
        EQUALS,
        LESSGREATER,
        SUM,
        PRODUCT,
        PREFIX,
        CALL,
        INDEX
    };

    inline std::unordered_map<lex::TokenType, Precedence> precedences = {
        {lex::TokenType::EQ, Precedence::EQUALS},
        {lex::TokenType::NEQ, Precedence::EQUALS},
        {lex::TokenType::LT, Precedence::LESSGREATER},
        {lex::TokenType::GT, Precedence::LESSGREATER},
        {lex::TokenType::PLUS, Precedence::SUM},
        {lex::TokenType::MINUS, Precedence::SUM},
        {lex::TokenType::SLASH, Precedence::PRODUCT},
        {lex::TokenType::ASTERISK, Precedence::PRODUCT},
        {lex::TokenType::LPAREN, Precedence::CALL},
        {lex::TokenType::LBRACKET, Precedence::INDEX},
    };

    class Parser {
        lex::Lexer &lexer;
        std::vector<std::string> errors;
        lex::Token curToken;
        lex::Token peekToken;
        std::unordered_map<lex::TokenType, PrefixParseFn> prefixParseFns;
        std::unordered_map<lex::TokenType, InfixParseFn> infixParseFns;
    public:
        explicit Parser(lex::Lexer &lexer);
        void registerPrefix(lex::TokenType tt, PrefixParseFn func);
        void registerInfix(lex::TokenType tt, InfixParseFn func);
        void nextToken();

        void peekError(lex::TokenType tt);
        void noPrefixParseFnError(lex::TokenType tt);

        bool curTokenIs(lex::TokenType tt) const;
        bool peekTokenIs(lex::TokenType tt) const;
        bool expectPeek(lex::TokenType tt) const;
        std::vector<std::string> getErrors() const;

        ast::Program *parseProgram();
        ast::Stmt *parseStmt();
        ast::VarDeclStmt *parseVarDeclStmt();
        ast::Expr *parseExpr(int precedence);
        ast::ExprStmt


    };
} //cblt::parse

#endif //PARSER_H