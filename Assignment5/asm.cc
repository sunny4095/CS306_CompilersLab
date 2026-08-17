#include "asm.hh"

// --- Directive_Asm_Statement ---
Directive_Asm_Statement::Directive_Asm_Statement(string d) : directive(d) {}

void Directive_Asm_Statement::print(ostream &out) {
    out << directive << "\n";
}

// --- Label_Asm_Statement ---
Label_Asm_Statement::Label_Asm_Statement(string l) : label(l) {}

void Label_Asm_Statement::print(ostream &out) {
    out << label << ":\n";
}

// --- Instruction_Asm_Statement ---
Instruction_Asm_Statement::Instruction_Asm_Statement(string op, string o1, string o2, string o3) 
    : opcode(op), op1(o1), op2(o2), op3(o3) {}

void Instruction_Asm_Statement::print(ostream &out) {
    out << "\t" << opcode << " " << op1;
    if (op2 != "") out << ", " << op2;
    if (op3 != "") out << ", " << op3;
    out << "\n";
}

// --- Memory_Asm_Statement ---
Memory_Asm_Statement::Memory_Asm_Statement(string op, string r, int off, string base)
    : opcode(op), reg(r), offset(off), base_reg(base) {}

void Memory_Asm_Statement::print(ostream &out) {
    out << "\t" << opcode << " " << reg << ", " << offset << "(" << base_reg << ")\n";
}

// --- Syscall_Asm_Statement ---
void Syscall_Asm_Statement::print(ostream &out) {
    out << "\tsyscall\n";
}

// --- Asm_Code ---
Asm_Code::Asm_Code(SymbolTable *s) {
    sym_tab = s;
}

Asm_Code::~Asm_Code() {
    for (auto stmt : code) {
        delete stmt;
    }
}

void Asm_Code::add(Asm_Statement* stmt) {
    code.push_back(stmt);
}

void Asm_Code::print(ostream &out) {
    for (auto stmt : code) {
        stmt->print(out);
    }
}