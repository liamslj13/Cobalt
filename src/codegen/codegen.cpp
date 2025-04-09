#include "../parser/ast.cpp"
#include "../cobaltEnv/cobalt.cpp"

llvm::Value *NumExpr::codegen() {
    return llvm::ConstantFP::get(globals::Context, llvm::APFloat(value));
}