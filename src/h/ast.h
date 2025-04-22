#pragma once

#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include "../h/cobalt.h"
#include "h/lexer.h"


namespace cblt::ast {
    struct Node {
        [[nodiscard]] virtual std::string TokenLiteral() const = 0;
        [[nodiscard]] virtual std::string String() const = 0;
        virtual ~Node() = default;
        virtual llvm::Value *codegen() = 0;
    };

    struct Stmt : Node {
        virtual void stmtNode() = 0;
    };

    struct Expr : Node {
        virtual void exprNode() = 0;
    };

    struct Identifier : Expr {
        lex::Token token;
        std::string value;

        void exprNode() override {}
        explicit Identifier(lex::Token token, std::string value);
        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;
    };

    struct Program final : Node {
        std::vector<std::unique_ptr<Stmt>> stmts;
        [[nodiscard]] std::string  TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;

        llvm::Value *codegen() override;
    };

    struct VarDeclStmt final : Stmt {
        lex::Token token;
        std::unique_ptr<Identifier> name;
        std::unique_ptr<Expr> value;
        void stmtNode() override {}

        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;

        llvm::Value *codegen() override;
    };

    struct ReturnStmt final : Stmt {
        lex::Token token;
        std::unique_ptr<Expr> returnValue;

        void stmtNode() override {}
        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;

        llvm::Value *codegen() override;
    };

    struct ExpressionStmt final : Stmt {
        lex::Token token;
        std::unique_ptr<Expr> expr;

        void stmtNode() override;
        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;

        llvm::Value *codegen() override;
    };

    struct BlockStmt final : Stmt {
        lex::Token token;
        std::vector<std::unique_ptr<Stmt>> stmts;

        void stmtNode() override {}
        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;

        llvm::Value *codegen() override;
    };

    struct NumExpr final : Expr {
        lex::Token token;
        double value;
        void exprNode() override {}

        explicit NumExpr(lex::Token token, double value);
        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;

        llvm::Value *codegen() override;
    };

    struct Boolean final : Expr {
        lex::Token token;
        bool value;

        explicit Boolean(bool value);

        void exprNode() override {}
        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;

        llvm::Value *codegen() override;
    };
}


#endif //AST_H
