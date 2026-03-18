#pragma once
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Instructions.h>
#include "Token.hpp"

// Type Aliases for cleaner signatures
using SymbolTable = std::map<std::string, llvm::AllocaInst*>;
using Context     = llvm::LLVMContext&;
using IRBuild     = llvm::IRBuilder<>&;
using Mod         = llvm::Module&;

/**
 * @brief Base class for all Abstract Syntax Tree nodes.
 */
class AST {
public:
    virtual ~AST() = default;

    /**
     * @brief Generates LLVM IR for this node.
     */
    virtual llvm::Value* codegen(Context context, IRBuild builder, Mod module, 
                                 SymbolTable& symbolTable) = 0;

    /**
     * @brief Returns a string representation for debugging/testing.
     */
    virtual std::string toString() = 0;
};

// --- Container Nodes ---

/**
 * @brief Represents a function declaration.
 */
class FunctionAST : public AST {
private:
    std::string name_;
    std::vector<std::pair<TokenType, std::string>> args_; // {Type, Name}
    TokenType returnType_;
    std::unique_ptr<BlockAST> body_;
public:
    FunctionAST(std::string name, std::vector<std::pair<TokenType, std::string>> args, 
                TokenType retType, std::unique_ptr<BlockAST> body);
    llvm::Value* codegen(Context context, IRBuild builder, Mod module, SymbolTable& symbolTable) override;
    std::string toString() override;
};


/**
 * @brief Represents a block of code enclosed in braces { ... }
 */
class BlockAST : public AST {
private:
    std::vector<std::unique_ptr<AST>> statements_;
public:
    BlockAST(std::vector<std::unique_ptr<AST>> statements);
    llvm::Value* codegen(Context context, IRBuild builder, Mod module, SymbolTable& symbolTable) override;
    std::string toString() override;
};


// --- Statement Nodes ---

class PrintStmtAST : public AST {
private:
    std::unique_ptr<AST> expression_;
public:
    PrintStmtAST(std::unique_ptr<AST> expression);
    llvm::Value* codegen(Context context, IRBuild builder, Mod module, SymbolTable& symbolTable) override;
    std::string toString() override;
};

class VarDeclarationStmtAST : public AST {
private:
    TokenType varType_;
    std::string identifier_;
    std::unique_ptr<AST> expression_;
public:
    VarDeclarationStmtAST(TokenType vt, std::string id, std::unique_ptr<AST> expr);
    llvm::Value* codegen(Context context, IRBuild builder, Mod module, SymbolTable& symbolTable) override;
    std::string toString() override;
};

class IfStmtAST : public AST {
private:
    std::unique_ptr<AST> condition_;
    std::unique_ptr<BlockAST> thenBlock_;
    std::unique_ptr<BlockAST> elseBlock_; // Can be nullptr
public:
    IfStmtAST(std::unique_ptr<AST> cond, std::unique_ptr<BlockAST> thenB, std::unique_ptr<BlockAST> elseB);
    llvm::Value* codegen(Context context, IRBuild builder, Mod module, SymbolTable& symbolTable) override;
    std::string toString() override;
};

class ReturnStmtAST : public AST {
private:
    std::unique_ptr<AST> expression_;
public:
    ReturnStmtAST(std::unique_ptr<AST> expression);
    llvm::Value* codegen(Context context, IRBuild builder, Mod module, SymbolTable& symbolTable) override;
    std::string toString() override;
};

// --- Expression Nodes ---

class BinaryExprAST : public AST {
private:
    TokenType op_;
    std::unique_ptr<AST> lhs_, rhs_;
public:
    BinaryExprAST(TokenType op, std::unique_ptr<AST> l, std::unique_ptr<AST> r);
    llvm::Value* codegen(Context context, IRBuild builder, Mod module, SymbolTable& symbolTable) override;
    std::string toString() override;
};

class VariableExprAST : public AST {
private:
    std::string name_;
public:
    VariableExprAST(std::string name);
    llvm::Value* codegen(Context context, IRBuild builder, Mod module, SymbolTable& symbolTable) override;
    std::string toString() override;
};

class IntegerExprAST : public AST {
private:
    int val_;
public:
    IntegerExprAST(int val);
    llvm::Value* codegen(Context context, IRBuild builder, Mod module, SymbolTable& symbolTable) override;
    std::string toString() override;
};