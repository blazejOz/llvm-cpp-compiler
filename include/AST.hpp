#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>

/**
 * @brief Base class for all expression nodes
 */
class AST
{
public:
    virtual ~AST() = default;
};

/**
 * @brief Represents a literal integer like '1' or '42'
 */
class IntegerExprAST: public AST
{
private:
    int val_;
public:
    IntegerExprAST(int val): val_{val} {}
};

/**
 * @brief Represents a 'print' statement
 */
class PrintStmtAST: public AST
{
private:
    std::unique_ptr<AST> expression_;
public:
    PrintStmtAST(std::unique_ptr<AST> expression)
        : expression_(std::move(expression)) {}
};

