#pragma once

#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include "../h/cobalt.h"
#include "../h/lexer.h"


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

    struct ExprStmt final : Stmt {
        lex::Token token;
        std::unique_ptr<Expr> expr;

        void stmtNode() override {}
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

    struct NumLiteral final : Expr {
        lex::Token token;
        double value;

        void exprNode() override {}
        explicit NumLiteral(lex::Token token, double value);
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

    struct PrefixExpr final : Expr {
        lex::Token token;
        std::string op;
        std::unique_ptr<Expr> right;

        void exprNode() override {}
        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;
        llvm::Value *codegen() override;
    };

    struct InfixExpr final : Expr {
        lex::Token token;
        std::unique_ptr<Expr> lhs;
        std::unique_ptr<Expr> rhs;
        std::string op;

        void exprNode() override {}
        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;
        llvm::Value *codegen() override;
    };

    struct IfExpr final : Expr {
        lex::Token token; // must be if
        std::unique_ptr<Expr> condition;
        std::unique_ptr<BlockStmt> consequence;
        std::unique_ptr<BlockStmt> alternative;

        void exprNode() override {}
        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;
        llvm::Value *codegen() override;
    };

    struct FuncLiteral final : Expr {
        lex::Token token;
        std::vector<std::unique_ptr<Identifier>> parameters;
        std::unique_ptr<BlockStmt> body;

        void  exprNode() override {}
        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;
        llvm::Value *codegen() override;
    };

    struct CallExpr final : Expr {
        lex::Token token;
        std::unique_ptr<Expr> function;
        std::vector<std::unique_ptr<Expr>> args;

        void exprNode() override {}
        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;
        llvm::Value *codegen() override;
    };

    struct StringLiteral final : Expr {
        lex::Token token;
        std::string value;

        void exprNode() override {}
        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;
        llvm::Value *codegen() override;
    };

    // this array structure will need to be altered
    // there is are challenges in the way that arrays are handled
    // depending on whether they are of dynamic or static size
    // -> come back to later
    struct ArrayLiteral final : Expr {
        lex::Token token;
        std::vector<std::unique_ptr<Expr>> elements;

        void exprNode() override {}
        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;
        llvm::Value *codegen() override;
    };

    // this too
    struct IndexExpr final : Expr {
        lex::Token token;
        std::unique_ptr<Expr> left;
        std::unique_ptr<Expr> index;

        void exprNode() override {}
        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;
        llvm::Value *codegen() override;
    };


    // This must also be looked at, not very easy to implement
    /*
    struct HashLiteral final : Expr {
        lex::Token token;
        std::unordered_map<Expr, Expr> pairs;

        void exprNode() override {}
        [[nodiscard]] std::string TokenLiteral() const override;
        [[nodiscard]] std::string String() const override;
        llvm::Value *codegen() override;
    };
    */
}

#endif //AST_H
