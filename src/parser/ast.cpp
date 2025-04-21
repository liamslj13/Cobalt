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

    NumExpr::NumExpr(Token token, const double value)
        : token(std::move(token)), value(value) {
    }

    [[nodiscard]] std::string NumExpr::TokenLiteral() const override {
        return token.literal;
    }

    [[nodiscard]] std::string NumExpr::String() const override {
        return token.literal;
    }
} // cblt::ast
