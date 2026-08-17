#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "asm.hh"
using namespace std;

class RTL_Statement {
public:
    virtual ~RTL_Statement() = default;
    virtual void print(ostream &out) = 0;
    virtual void gen_asm_code(Asm_Code &code) = 0;
};

class Compute_RTL_Statement : public RTL_Statement {
private:
    string result, op1, op2, op;
    bool is_unary;

public:
    Compute_RTL_Statement(string res, string oper, string o1, string o2 = "");
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class Load_RTL_Statement : public RTL_Statement {
private:
    string reg, var;
    bool is_float;

public:
    Load_RTL_Statement(string r, string v, bool f);
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class ILoad_RTL_Statement : public RTL_Statement {
private:
    string reg, value;
    bool is_float;

public:
    ILoad_RTL_Statement(string r, string val, bool f);
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class Store_RTL_Statement : public RTL_Statement {
public:
    string var, reg;
    bool is_float;

public:
    Store_RTL_Statement(string v, string r, bool f);
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class Move_RTL_Statement : public RTL_Statement {
private:
    string reg, val;
    bool is_float;

public:
    Move_RTL_Statement(string v, string r, bool f);
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class Move_True_RTL_Statement : public RTL_Statement {
private:
    string reg, val1, val2;
    bool is_float;

public:
    Move_True_RTL_Statement(string v1, string v2, string r, bool f);
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class Move_False_RTL_Statement : public RTL_Statement {
private:
    string reg, val1, val2;
    bool is_float;

public:
    Move_False_RTL_Statement(string v1, string v2, string r, bool f);
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class Goto_RTL_Statement : public RTL_Statement {
private:
    string label;

public:
    Goto_RTL_Statement(string l);
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class If_Goto_RTL_Statement : public RTL_Statement {
private:
    string reg, label;

public:
    If_Goto_RTL_Statement(string r, string l);
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class Label_RTL_Statement : public RTL_Statement {
private:
    string label;

public:
    Label_RTL_Statement(string l);
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class Write_RTL_Statement : public RTL_Statement {
public:
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class Read_RTL_Statement : public RTL_Statement {
public:
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class Push_RTL_Statement : public RTL_Statement {
private:
    string reg;
    bool is_float;
public:
    Push_RTL_Statement(string r, bool f);
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class Pop_RTL_Statement : public RTL_Statement {
    bool is_float;
public:
    Pop_RTL_Statement(bool f);
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class Function_Call_RTL_Statement : public RTL_Statement {
private:
    string func_name;
    string return_reg;

public:
    Function_Call_RTL_Statement(string f, string r);
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class Func_Begin_RTL_Statement : public RTL_Statement {
private:
    string func_name;
    vector<string> headers;

public:
    Func_Begin_RTL_Statement(string f, vector<string> &h);
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class Func_End_RTL_Statement : public RTL_Statement {
private:
    vector<string> footers;

public:
    Func_End_RTL_Statement(vector<string> &f);
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class Return_RTL_Statement : public RTL_Statement {
private:
    string reg;

public:
    Return_RTL_Statement(string r);
    void print(ostream &out) override;
    void gen_asm_code(Asm_Code &code) override;
};

class RTL_Code {
private:
    vector<RTL_Statement*> code;
    vector<pair<string,bool>> int_regs;
    vector<pair<string,bool>> float_regs;
    unordered_map<string,string> temp_map;
    unordered_map<string,string> str_map;

public:
    RTL_Code();
    ~RTL_Code();

    string get_temp_reg();
    string get_float_reg();
    string get_reg(string tac_temp, bool is_float, bool search=true);
    string get_str_const(string s);
    void free_reg(string r, bool is_float);

    void add(RTL_Statement* stmt);
    void print(ostream &out);
    void gen_asm_code(Asm_Code &asm_code);
};

bool is_num_const(string s);
bool is_float_const(string s);
bool is_str_const(string s);
bool is_temp(string s);
bool is_source_variable(string s);
