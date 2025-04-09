#include <string>
#include <vector>
#include "../cobaltEnv/cobalt.h"
#include "../parser/lexer.cpp"

using namespace cblt::lex;

struct Node {
    virtual std::string TokenLiteral() const = 0;
    virtual std::string String() const = 0;
    virtual ~Node() {}
};

struct Stmt : Node {
    virtual void stmtNode() = 0;
};

struct Expr : Node {
    virtual void exprNode() = 0;
};

struct Identifier : Expr {
    Token token;
    std::string value;

    void exprNode() override {}

    Identifier(const Token &token, std::string value) : token(token), value(std::move(value)) {}

    std::string TokenLiteral() const override {
        return token.literal;
    }

    std::string String() const override {
        return value;
    }
};

struct Program final : Node {
    std::vector<std::unique_ptr<Stmt>> stmts;

    std::string TokenLiteral() const override {
        if (!stmts.empty()) {
            return stmts[0]->TokenLiteral();
        }
        return "";
    }

    std::string String() const override {
        std::string res = "";
        for (const auto& stmt : stmts) {
            res += stmt->String();
        }
        return res;
    }
};



struct NumExpr final : Expr {
    Token token;
    double value;
    void exprNode() override {}

    std::string TokenLiteral() const override {
        return token.literal;
    }

    std::string String() const override {
        return token.literal;
    }
};