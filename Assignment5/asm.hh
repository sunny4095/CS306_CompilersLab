#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "symbol_table.hh"
using namespace std;

class Asm_Statement {
public:
    virtual ~Asm_Statement() = default;
    virtual void print(ostream &out) = 0;
};

class Directive_Asm_Statement : public Asm_Statement {
private:
    string directive;

public:
    Directive_Asm_Statement(string d);
    void print(ostream &out) override;
};

class Label_Asm_Statement : public Asm_Statement {
private:
    string label;

public:
    Label_Asm_Statement(string l);
    void print(ostream &out) override;
};

class Instruction_Asm_Statement : public Asm_Statement { // For standard instructions: op, op1, op2, op3 Covers things like: add $t0, $v0, $t1 | li $v0, 3 | j Label0 | move $v0, $v1
private:
    string opcode;
    string op1, op2, op3;

public:
    Instruction_Asm_Statement(string op, string o1, string o2 = "", string o3 = "");
    void print(ostream &out) override;
};

class Memory_Asm_Statement : public Asm_Statement { // For memory load/store instructions: lw $v0, -8($fp) | sw $ra, 0($sp)
private:
    string opcode, reg, base_reg;
    int offset;

public:
    Memory_Asm_Statement(string op, string r, int off, string base);
    void print(ostream &out) override;
};

class Syscall_Asm_Statement : public Asm_Statement { // For syscalls
public:
    void print(ostream &out) override;
};

class Asm_Code { // Container class to hold and manage the assembly instructions
private:
    vector<Asm_Statement*> code;

public:
    SymbolTable *sym_tab;
    string current_func_name;
    int current_sp_allocation;
    Asm_Code(SymbolTable *s);
    ~Asm_Code();

    void add(Asm_Statement* stmt);
    void print(ostream &out);
};
