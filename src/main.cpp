#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <iostream>

int main() {

    llvm::LLVMContext context;

    llvm::Module* module = new llvm::Module("AxLanguage", context);

    module->print(llvm::errs(), nullptr);

    delete module;
    return 0;
}