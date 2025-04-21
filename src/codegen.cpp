#include "h/ast.h"
#include "h/cobalt.h"

using namespace cblt::ast;
using namespace cblt::globals;

llvm::Value *NumExpr::codegen() {
    return llvm::ConstantFP::get(Context, llvm::APFloat(value));
}

/*
llvm::Value *VarDeclStmt::codegen() {
    llvm::Value* val = value->codegen();
    if (!val) {
        return nullptr;
    }

    llvm::Function* function = Builder->GetInsertBlock()->getParent();
    llvm::IRBuilder<> tmpB(&function->getEntryBlock(), function->getEntryBlock().begin());
    llvm::AllocaInst* alloca = tmpB.CreateAlloca(
        llvm::Type::getC)



}
*/