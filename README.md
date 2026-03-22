# ToyLang Compiler

[![CI](https://github.com/blazejOz/llvm-cpp-compiler/actions/workflows/pipeline.yml/badge.svg)](https://github.com/blazejOz/llvm-cpp-compiler/actions)

A learning compiler project implemented in C++20 and built atop LLVM 21.
It demonstrates an end-to-end pipeline for a small custom language (inspired by LLVM Kaleidoscope) in an object-oriented style.

Reference: https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/index.html


<p align="center">
  <img src="assets/demo.gif" width="900px" alt="Compiler Demo">
</p>

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
./build/compiler example.toy -jit
```

Generate LLVM IR (assembly):

```bash
./build/compiler example.toy -S
```

Compile to native binary:

```bash
./build/compiler example.toy -o my_app
./my_app
```

## Project Layout

- `src/`
  - `main.cpp`
  - `frontend/Lexer.cpp`
  - `frontend/Parser.cpp`
  - `frontend/IR_Generator.cpp`
  - backend sources in `src/backend/`
- `include/`
  - `AST.hpp`
  - `Lexer.hpp`
  - `Parser.hpp`
  - `IR_Generator.hpp`
- `tests/` (Catch2 unit tests)
- `docs/` (language spec, compiler design notes)

## Current Features

- `if` / `else` / `while`
- integer variable declaration and assignment
- function definitions and calls
- LLVM IR generation (`-S`)
- JIT execution (`-jit`)
- native object emission / executable generation

## Notes

This repository is intended for learning and experimentation. APIs and implementation details may change frequently.

## License

See `LICENSE`.
