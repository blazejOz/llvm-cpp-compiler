#pragma once
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/ExecutionEngine/Orc/ThreadSafeModule.h>
#include <llvm/ExecutionEngine/Orc/ExecutionUtils.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/MemoryBuffer.h>
#include <iostream>

/** @brief Simple Just-In-Time compiler wrapper using LLVM JITengine.
 *  This class handles the translation of LLVM IR from a Module into 
 *  machine code in memory and executes the 'main' entry point. */
class JITengine
{
private:

public:
    JITengine(){}

    void runFromIRString(const std::string& irCode);
};