#pragma once
#include <string>
#include <vector>
#include "rtl.hh"
using namespace std;

class TAC_Statement {
public:
    virtual ~TAC_Statement() = default;
    virtual void print() = 0;
    virtual void gen_rtl_code(RTL_Code &rtl) = 0;
};

class TAC_Assignment_Statement : public TAC_Statement {
private:
    string lhs;
    string opd1;
    string opd2;
    string op;
    string opd1_type;
    string opd2_type;

public:
    TAC_Assignment_Statement(string l, string o1, string o = "", string o2 = "", string o1_type = "", string o2_type = "");
    ~TAC_Assignment_Statement() override;
    void print() override;
    void gen_rtl_code(RTL_Code &rtl) override;
};

class TAC_Goto_Statement : public TAC_Statement {
private:
    string if_con;
    string label;

public:
    TAC_Goto_Statement(string l, string con = "");
    ~TAC_Goto_Statement() override;
    void print() override;
    void gen_rtl_code(RTL_Code &rtl) override;
};

class TAC_Label_Statement : public TAC_Statement {
private:
    string label;

public:
    TAC_Label_Statement(string l);
    ~TAC_Label_Statement() override;
    void print() override;
    void gen_rtl_code(RTL_Code &rtl) override;
};

class TAC_IO_Statement : public TAC_Statement {
private:
    string io;
    string var;
    string var_type;
    bool is_var;
    
public:
    TAC_IO_Statement(string v, string io, string t, bool is_var);
    ~TAC_IO_Statement() override;
    void print() override;
    void gen_rtl_code(RTL_Code &rtl) override;
};

class TAC_Func_Call_Statement : public TAC_Statement {
private:
    string lhs;
    string func_name;
    string return_type;
    vector<string> args;
    vector<string> arg_type;

public:
    TAC_Func_Call_Statement(string l, string f, vector<string> &a, vector<string> &t, string ret_type);
    ~TAC_Func_Call_Statement() override;
    void print() override;
    void gen_rtl_code(RTL_Code &rtl) override;
};

class TAC_Return_Statement : public TAC_Statement {
private:
    string var;
    string return_type;

public:
    TAC_Return_Statement(string v, string r);
    ~TAC_Return_Statement() override;
    void print() override;
    void gen_rtl_code(RTL_Code &rtl) override;
};

class TAC_Func_Begin_Statement : public TAC_Statement {
private :
    string func_name;
    vector<string> headers;

public: 
    TAC_Func_Begin_Statement(string f, vector<string> &h);
    ~TAC_Func_Begin_Statement() override;
    void print() override;
    void gen_rtl_code(RTL_Code &rtl) override;
};

class TAC_Func_End_Statement : public TAC_Statement {
private:
    vector<string> footers;

public:
    TAC_Func_End_Statement(vector<string> &f);
    ~TAC_Func_End_Statement();
    void print() override;
    void gen_rtl_code(RTL_Code &rtl) override;
};

class TAC_Code {
public:
    int temp_count;
    int label_count;
    int stemp_count;
    string exit_label;
    string exit_stemp;
    vector<TAC_Statement*> code;

    TAC_Code(int t = 0, int l = 0, int s = 0, string ex = "", string st = "");
    ~TAC_Code();

    string get_new_temp();
    string get_new_stemp();
    string get_new_label();

    void add(TAC_Statement* tac_stmt);
    void print();
    void gen_rtl_code(RTL_Code &rtl);
};
