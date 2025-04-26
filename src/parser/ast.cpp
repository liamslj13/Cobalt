#include "../h/ast.h"

using namespace cblt::lex;
using namespace cblt::ast;

namespace cblt::ast {

    // ---------- Identifier Implementations ---------
    Identifier::Identifier(Token token, std::string value)
        : token(std::move(token)), value(std::move(value)) {
    }

    [[nodiscard]] std::string Identifier::TokenLiteral() const override {
        return token.literal;
    }

    [[nodiscard]] std::string Identifier::String() const override {
        return value;
    }

    // ---------- Program Implementations ---------
    [[nodiscard]] std::string Program::TokenLiteral() const override {
        if (!stmts.empty()) {
            return stmts[0]->TokenLiteral();
        }
        return "";
    }

    [[nodiscard]] std::string Program::String() const override {
        std::string res;
        for (const auto &stmt: stmts) {
            res += stmt->String();
        }
        return res;
    }

    // ---------- Variable Declaration Implementations ---------
    [[nodiscard]] std::string VarDeclStmt::TokenLiteral() const override {
        return token.literal;
    }

    [[nodiscard]] std::string VarDeclStmt::String() const override {
        std::string res;
        res += "decl ";
        res += name->String();
        res += " -> ";
        if (!value) {
            res += "null";
        } else {
            res += value->String();
        }
        res += ";";
        return res;
    }

    // ---------- Number Expression Implementations ---------
    NumLiteral::NumLiteral(Token token, const double value)
        : token(std::move(token)), value(value) {
    }

    [[nodiscard]] std::string NumLiteral::TokenLiteral() const override {
        return token.literal;
    }

    [[nodiscard]] std::string NumLiteral::String() const override {
        return token.literal;
    }

    // ---------- Boolean Implementations ---------
    Boolean::Boolean(bool value) : value(value) {}
    [[nodiscard]] std::string Boolean::TokenLiteral() const override {
        return token.literal;
    }

    [[nodiscard]] std::string Boolean::String() const override {
        return token.literal;
    }




    // ---------- Return Stmt Implementations ---------
    [[nodiscard]] std::string ReturnStmt::TokenLiteral() const override {
        return  token.literal;
    }

    [[nodiscard]] std::string ReturnStmt::String() const override {
        std::string res = "";
        res += token.literal;
        if (returnValue) {
            res += returnValue->String();
        }

        res += ';';
        return res;
    }

    // ---------- ExprStmt Implementations ---------
    [[nodiscard]] std::string ExprStmt::TokenLiteral() const override {
        return token.literal;
    }

    [[nodiscard]] std::string ExprStmt::String() const override {
        if (expr) {
            return expr->String();
        }
        return "";
    }

    // ---------- BlockStmt Implementations ---------
    [[nodiscard]] std::string BlockStmt::TokenLiteral() const override {
        return  token.literal;
    }

    [[nodiscard]] std::string BlockStmt::String() const override {
        std::string res = "{";
        for (const auto &stmt: stmts) {
            res += stmt->String() + " ";
        }
        res += "}";
        return res;
    }


} // cblt::ast
