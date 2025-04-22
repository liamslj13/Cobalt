#include "h/ast.h"
#include "h/cobalt.h"

using namespace cblt::ast;
using namespace cblt::globals;

llvm::Value *NumExpr::codegen() {
    return llvm::ConstantFP::get(Context, llvm::APFloat(value));
}

llvm::Value *Boolean::codegen() {
    return nullptr;
}

llvm::Value *VarDeclStmt::codegen() {
    return nullptr;
}

llvm::Value *Program::codegen() {
    return nullptr;
}

llvm::Value *ExpressionStmt::codegen() {
    return nullptr;
}

llvm::Value *BlockStmt::codegen() {
    return nullptr;
}

