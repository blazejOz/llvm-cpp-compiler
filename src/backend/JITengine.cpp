#include "JITengine.hpp"

/**
 * @brief run jit from irCodes represented in a string
 * based on https://llvm.org/docs/ORCv2.html documentation
 */
void JITengine::runFromIRString(const std::string& irCode)
{
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::ExitOnError ExitOnErr;

    auto JIT = ExitOnErr(llvm::orc::LLJITBuilder().create());

    // add libc library to jit
    JIT->getMainJITDylib().addGenerator(
        ExitOnErr(llvm::orc::DynamicLibrarySearchGenerator::GetForCurrentProcess(
            JIT->getDataLayout().getGlobalPrefix()))
    );

    //parse irCode string into module for jit
    auto ctx = std::make_unique<llvm::LLVMContext>();
    llvm::SMDiagnostic err;
    auto buffer = llvm::MemoryBuffer::getMemBuffer(irCode);
    auto mod = llvm::parseIR(*buffer, err, *ctx);

    if (!mod) {
        err.print("JIT_Error", llvm::errs());
        return;
    }

    // add module
    ExitOnErr(JIT->addIRModule(llvm::orc::ThreadSafeModule(std::move(mod), std::move(ctx))));

    //find main and RUN IT
    auto mainSym = ExitOnErr(JIT->lookup("main"));
    auto mainFn = mainSym.toPtr<int(*)()>();

    std::cout << "--- JIT START ---" << std::endl;
    mainFn(); 
    std::cout << "--- JIT END ---" << std::endl;
}