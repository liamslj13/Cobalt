#include "cobalt.h"

llvm::LLVMContext context; // llvm core
llvm::IRBuilder<> builder(context); // ir generation assist
std::unique_ptr<llvm::Module> module; // functions and global variables
std::map<std::string, llvm::Value *> values; // values in scope track
