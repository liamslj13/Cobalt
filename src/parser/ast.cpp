#include <string>
#include <vector>
#include "../cobaltEnv/cobalt.cpp"
#include "../parser/lexer.cpp"

using namespace cblt::lex;

struct Node {
    [[nodiscard]] virtual std::string TokenLiteral() const = 0;
    [[nodiscard]] virtual std::string String() const = 0;
    virtual ~Node() {}
    virtual llvm::Value *llvm::codegen();
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

    [[nodiscard]] std::string TokenLiteral() const override {
        return token.literal;
    }

    [[nodiscard]] std::string String() const override {
        return value;
    }
};

struct Program final : Node {
    std::vector<std::unique_ptr<Stmt>> stmts;

    [[nodiscard]] std::string TokenLiteral() const override {
        if (!stmts.empty()) {
            return stmts[0]->TokenLiteral();
        }
        return "";
    }

    [[nodiscard]] std::string String() const override {
        std::string res;
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

    NumExpr(Token token, const double value) : token(std::move(token)), value(value) {}

    [[nodiscard]] std::string TokenLiteral() const override {
        return token.literal;
    }

    [[nodiscard]] std::string String() const override {
        return token.literal;
    }

    llvm::Value *codegen() override;
};