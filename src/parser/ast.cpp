#include <string>
#include <vector>
#include "../cobaltEnv/cobalt.h"

struct Node {
    virtual std::string TokenLiteral() const = 0;
    virtual std::string String() const = 0;
    virtual ~Node() {}
    virtual llvm::Value *codegen() = 0;
};

struct Stmt : Node {
    virtual void stmtNode() = 0;
};

struct Expr : Node {
    virtual void exprNode() = 0;
};

struct Program : Node {
    std::vector<std::unique_ptr<Stmt>> stmts;
};