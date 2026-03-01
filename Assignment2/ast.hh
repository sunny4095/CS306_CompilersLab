#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include "symbol_table.hh"
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
};

class Name_Ast: public Ast {
    const string var_name;
public :
    Name_Ast(const string &name, const string &type, int line);
    ~Name_Ast();
    string get_data_type() const;
    const SymbolTableEntry& get_sym_tab_entry() const;
    void print(ostream &file_buffer);
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
};

class Uminus_Ast : public Ast {
    Ast *operand;
public :
    Uminus_Ast(Ast *op, int line);
    ~Uminus_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
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
};

class Float_Ast : public Ast {
    float value;
public :
    Float_Ast(float _value, int line);
    ~Float_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
};

class String_Ast : public Ast {
    string value;
public :
    String_Ast(string _value, int line);
    ~String_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
};

class Sequence_Ast : public Ast {
    vector<Ast*> stmt_list;
public :
    Sequence_Ast(vector<Ast*> &stmts);
    Sequence_Ast();
    ~Sequence_Ast();
    void add_statement(Ast *stmt);
    bool check_ast();
    void print(ostream &file_buffer);
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
};

class Logical_Not_Ast : public Ast {
    Ast *expr;
public :
    Logical_Not_Ast(Ast *e, int l);
    ~Logical_Not_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
};

class Print_Ast : public Ast {
    Ast *expr;
public :
    Print_Ast(Ast *e, int l);
    ~Print_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
};

class Read_Ast : public Ast {
    Ast *var;
public :
    Read_Ast(Ast *v, int l);
    ~Read_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
};

class Function_Ast : public Ast {
    string func_name;
    string return_type;
    vector<pair<string, string>> parameters;
    Sequence_Ast *body;
public :
    Function_Ast(const string &n, const string &r, const vector<pair<string, string>> &p, Sequence_Ast *b, int l);
    ~Function_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
};

class Program_Ast : public Ast {
    vector<Function_Ast *> function_list;
public :
    Program_Ast(vector<Function_Ast *> &f);
    ~Program_Ast();
    bool check_ast();
    void print(ostream &file_buffer);
};