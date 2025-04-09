#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <map>

namespace globals {

    static llvm::LLVMContext Context; // llvm core
    static std::unique_ptr<llvm::IRBuilder<>> Builder; // ir generation assist
    static std::unique_ptr<llvm::Module> Module; // functions and global variables
    static std::map<std::string, llvm::Value *> Values; // values in scope track

}