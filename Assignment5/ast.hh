#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include "symbol_table.hh"
#include "tac.hh"
extern int ast_error;
using namespace std;

enum RelOp {
    OP_LE, OP_LT, OP_GT, OP_GE, OP_NE, OP_EQ
};
enum BinOp {
    OP_ADD, OP_SUB, OP_MULT, OP_DIV
};
enum LogOp {
    OP_AND, OP_OR
};

// enum DataType {
//     int_data_type,
//     float_data_type,
//     string_data_type,
//     bool_data_type,
//     void_data_type,
// };

class Ast;

class Ast {
protected :
    typedef enum {
        zero_arity = 0,
        unary_arity = 1,
        binary_arity = 2,
    } Arity;
    int lineno;
    Arity ast_arity;
    string node_data_type;

public :
    Ast();
    Ast(int line);
    ~Ast();

    virtual string get_data_type();
    virtual bool check_ast();
    virtual SymbolTableEntry& get_sym_tab_entry();
    virtual string gen_tac_code(TAC_Code &code) = 0;
    virtual void print(ostream &file_buffer) = 0;
};

class Assignment_Ast : public Ast {
    Ast *lhs;
    Ast *rhs;
public :
    Assignment_Ast(Ast* lhs, Ast* rhs, int line);
    ~Assignment_Ast();
    bool check_ast();
    void print(ostream& file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Name_Ast: public Ast {
    const string var_name;
public :
    Name_Ast(const string &name, const string &type, int line);
    ~Name_Ast();
    string get_data_type() const;
    const SymbolTableEntry& get_sym_tab_entry() const;
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Relational_Ast : public Ast {
    Ast *lhs;
    Ast *rhs;
    RelOp rel_op;
public :
    Relational_Ast(Ast *_lhs, Ast *_rhs, RelOp _rel_op, int line);
    ~Relational_Ast();
    string get_data_type();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Expression_Ast : public Ast {
    Ast *lhs;
    Ast *rhs;
    BinOp bin_op;
public :
    Expression_Ast(Ast *_lhs, Ast *_rhs, BinOp _bin_op, int line);
    ~Expression_Ast();
    string get_data_type();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Uminus_Ast : public Ast {
    Ast *operand;
public :
    Uminus_Ast(Ast *op, int line);
    ~Uminus_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};
// class Constant_Ast : public Ast {
// public :
//     Constant_Ast();
//     ~Constant_Ast();
// }

class Int_Ast : public Ast {
    int value;
public :
    Int_Ast(int _value, int line);
    ~Int_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Float_Ast : public Ast {
    float value;
public :
    Float_Ast(float _value, int line);
    ~Float_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class String_Ast : public Ast {
    string value;
public :
    String_Ast(string _value, int line);
    ~String_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Sequence_Ast : public Ast {
public :
    vector<Ast*> stmt_list;
    Sequence_Ast(vector<Ast*> &stmts);
    Sequence_Ast();
    ~Sequence_Ast();
    void add_statement(Ast *stmt);
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Ternary_Ast : public Ast {
    Ast *cond;
    Ast *true_expr;
    Ast *false_expr;
public :
    Ternary_Ast(Ast *c, Ast *t, Ast *f, int l);
    ~Ternary_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Logical_Ast : public Ast {
    Ast *lhs;
    Ast *rhs;
    LogOp log_op;
public :
    Logical_Ast(Ast *l, Ast *r, LogOp op, int line);
    ~Logical_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Logical_Not_Ast : public Ast {
    Ast *expr;
public :
    Logical_Not_Ast(Ast *e, int l);
    ~Logical_Not_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Compound_Statement_Ast : public Ast {
    Ast *body;
public :
    Compound_Statement_Ast(Ast *seq, int l);
    ~Compound_Statement_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class If_Else_Ast : public Ast {
    Ast *cond;
    Ast *if_stmt_list;
    Ast *else_stmt_list;
public :
    If_Else_Ast(Ast *c, Ast *i, Ast *e, int l);
    ~If_Else_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class While_Ast : public Ast {
    Ast *cond;
    Ast *body;
public :
    While_Ast(Ast *c, Ast *b, int l);
    ~While_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Do_While_Ast : public Ast {
    Ast *do_body;
    Ast *while_cond;
public :
    Do_While_Ast(Ast *c, Ast *b, int l);
    ~Do_While_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Print_Ast : public Ast {
    Ast *expr;
public :
    Print_Ast(Ast *e, int l);
    ~Print_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Read_Ast : public Ast {
    Ast *var;
public :
    Read_Ast(Ast *v, int l);
    ~Read_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

// class Void_Function_Call_Ast

class Function_Call_Ast : public Ast {
    string func_name;
    vector<Ast *> args;
    SymbolTableEntry *sym;
public :
    Function_Call_Ast(string n, vector<Ast*> &a, SymbolTableEntry *sym_pointer, int l);
    ~Function_Call_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Return_Ast : public Ast {
    Ast *ret_val;
public:
    Return_Ast(Ast *v, int l);
    ~Return_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Function_Ast : public Ast {
    string func_name;
    vector<pair<string, string>> parameters;
    Sequence_Ast *body;

public :
    bool is_declared;
    string return_type;
    string exit_label;
    Function_Ast(const string &n, const string &r, const vector<pair<string, string>> &p, Sequence_Ast *b, bool d, int l);
    ~Function_Ast();
    string get_func_name() const;
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};

class Program_Ast : public Ast {
    vector<Function_Ast *> function_list;
    vector<string> declared_func;
public :
    Program_Ast(vector<Function_Ast *> &f, vector<string> df = {});
    ~Program_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
    string gen_tac_code(TAC_Code &code);
};