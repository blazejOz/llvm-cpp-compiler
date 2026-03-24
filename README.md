# ToyLang Compiler

[![CI](https://github.com/blazejOz/llvm-cpp-compiler/actions/workflows/pipeline.yml/badge.svg)](https://github.com/blazejOz/llvm-cpp-compiler/actions)

A learning compiler project implemented in C++20 and built atop LLVM 21.
It demonstrates an end-to-end pipeline for a small custom language (inspired by LLVM Kaleidoscope) in an object-oriented style.

Reference: https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/index.html


<p align="center">
  <img src="assets/demo.gif" width="900px" alt="Compiler Demo">
</p>

## Try it with Docker
You can run the compiler without installing LLVM locally:
```bash
# Pull the image
docker pull ghcr.io/blazejoz/toylang-compiler:latest

# Run on your local file
docker run --rm -v $(pwd):/app ghcr.io/blazejoz/toylang-compiler:latest <your_file>.toy 
```

## Language Specification

- [docs/lang_spec.txt](docs/lang_spec.txt)

## Architecture Overview

The compiler follows a classical 3-phase architecture:

1. Frontend
   - Lexer: hand-written scanner and tokenizer.
   - Parser: recursive descent parser constructs an AST.

2. Middle-end (IR Generation)
   - Transforms AST to LLVM IR.
   - Manages variable scope, symbol tables, and functions.

3. Backend
   - JIT Engine (LLVM ORCv2) for immediate execution.
   - Object emitter (platform target triple + CPU features) for .o output.
   - Linker integration using the system `cc` for executables.
  
<details>
<summary><b>View Project Structure</b></summary>

```text
├── include/            # Headers (AST nodes, Parser, Lexer interfaces)
├── src/
│   ├── frontend/       # Lexer.cpp, Parser.cpp
│   ├── middleend/      # IR_Generator.cpp (AST -> LLVM IR)
│   ├── backend/        # JIT Engine & Object Emitter
│   └── main.cpp        # Compiler driver & CLI handling
├── tests/              # Unit tests (Catch2)
├── docs/               # Language specification
└── CMakeLists.txt
```
</details>

## Requirements

- LLVM 21+
- C++20 toolchain
- CMake

## Quick Build & Run

From repository root:

```bash
cmake -B build
cmake --build build
```

Run with JIT (default mode):

```bash
./build/compiler lang_examples/example.toy -jit
```

Generate LLVM IR (assembly):

```bash
./build/compiler lang_examples/example.toy -S
```

Compile to native binary:

```bash
./build/compiler lang_examples/example.toy -o my_app
./my_app
```


## Current Features

- `if` / `else` / `while`
- integer variable declaration and assignment
- function definitions and calls
- LLVM IR generation (`-S`)
- JIT execution (`-jit`)
- native object emission / executable generation

## Roadmap & Planned Features

Phase 1: Core Control Flow & Logic
- [x] Function Definitions: Support for multiple arguments and return types.
- [x] AOT Compilation: Native .o emission and linking via clang/cc.
- [x] Standard Flow: if-else branching and while loops.
- [ ] For Loops: Implementation of C-style for(init; cond; step) sugar.
- [ ] Logical Operators: Short-circuiting && and ||.

Memory & Data Structures
- [ ] Arrays: Fixed-size stack arrays with bounds checking.
- [ ] Structs (User Defined Types): Implementing GetElementPtr (GEP) for member access.
- [ ] Global Variables: Support for state that persists across function calls.
- [ ] Strings: Basic char* support and integration with printf.

Middle-end & LLVM Optimizations
- [ ] SSA Infrastructure: Proper use of Phi nodes for control flow merging (moving away from "everything is a variable").
- [ ] Mem2Reg Pass: Promoting stack-allocated variables to LLVM registers to enable cleaner IR.
- [ ] Optimization Pipeline: Integrating PassBuilder to run Constant Folding and Dead Code Elimination (DCE).
- [ ] CFG Visualization: Exporting Control Flow Graphs to .dot files for debugging.

Developer Experience & Quality
- [ ] Better Error Reporting: Tracking line/column numbers in the Lexer for "Clang-style" error messages.
- [ ] Standard Library: A small stdlib.toy for math and basic I/O.
- [ ] Dockerized Toolchain: Full AOT pipeline available via a single Docker image.

## Notes

This repository is intended for learning and experimentation. APIs and implementation details may change frequently.

## License

See `LICENSE`.
