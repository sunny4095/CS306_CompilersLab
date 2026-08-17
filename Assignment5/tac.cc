#include "tac.hh"
#include <iostream>
using namespace std;

string get_operand_reg(string opd, bool is_float, RTL_Code &code) {
    string r;
    if (is_temp(opd)) {
        r = code.get_reg(opd, is_float, true);
    }
    else if (is_source_variable(opd)) {
        r = code.get_reg(opd, is_float, false);
        code.add(new Load_RTL_Statement(r, opd, is_float));
    }
    else { // constant
        r = code.get_reg(opd, is_float, false);
        code.add(new ILoad_RTL_Statement(r, opd, is_float));
    }
    return r;
}

TAC_Assignment_Statement::TAC_Assignment_Statement(string l, string o1, string o, string o2, string o1_type, string o2_type) : lhs(l), opd1(o1), opd2(o2), op(o), opd1_type(o1_type), opd2_type(o2_type) {}
TAC_Assignment_Statement::~TAC_Assignment_Statement() {}
void TAC_Assignment_Statement::print() {
    cout << lhs << " = " << opd1 << " " << op << " " << opd2 << "\n";
}
void TAC_Assignment_Statement::gen_rtl_code(RTL_Code &code) {
    bool is_float = (opd1_type == "float" || opd2_type == "float");

    if (opd1 != "" && opd2 != "") {
        string r1, r_dest, r2;

        if (op == "+") {
            r1 = get_operand_reg(opd1, is_float, code);
            r_dest = code.get_reg(lhs, is_float, false);
            r2 = get_operand_reg(opd2, is_float, code);
            if (is_float) code.add(new Compute_RTL_Statement(r_dest, "add.d", r1, r2));
            else code.add(new Compute_RTL_Statement(r_dest, "add", r1, r2));
        }
        else if (op == "-") {
            r1 = get_operand_reg(opd1, is_float, code);
            r_dest = code.get_reg(lhs, is_float, false);
            r2 = get_operand_reg(opd2, is_float, code);
            if (is_float) code.add(new Compute_RTL_Statement(r_dest, "sub.d", r1, r2));
            else code.add(new Compute_RTL_Statement(r_dest, "sub", r1, r2));
        }
        else if (op == "*") {
            r1 = get_operand_reg(opd1, is_float, code);
            r_dest = code.get_reg(lhs, is_float, false);
            r2 = get_operand_reg(opd2, is_float, code);
            if (is_float) code.add(new Compute_RTL_Statement(r_dest, "mul.d", r1, r2));
            else code.add(new Compute_RTL_Statement(r_dest, "mul", r1, r2));
        }
        else if (op == "/") {
            r1 = get_operand_reg(opd1, is_float, code);
            r_dest = code.get_reg(lhs, is_float, false);
            r2 = get_operand_reg(opd2, is_float, code);
            if (is_float) code.add(new Compute_RTL_Statement(r_dest, "div.d", r1, r2));
            else code.add(new Compute_RTL_Statement(r_dest, "div", r1, r2));
        }
        else if (op == "<") {
            if (is_float) {
                r1 = get_operand_reg(opd1, is_float, code);
                string temp0 = code.get_temp_reg();
                r_dest = code.get_reg(lhs, false, false);
                r2 = get_operand_reg(opd2, is_float, code);
                code.add(new Compute_RTL_Statement("", "slt.d", r1, r2));
                code.add(new ILoad_RTL_Statement(temp0, "1", false));
                code.add(new Move_RTL_Statement("zero", r_dest, false));
                code.add(new Move_True_RTL_Statement(temp0, "0", r_dest, false));
                code.free_reg(temp0, false);
            }
            else {
                r1 = get_operand_reg(opd1, is_float, code);
                r_dest = code.get_reg(lhs, false, false);
                r2 = get_operand_reg(opd2, is_float, code);
                code.add(new Compute_RTL_Statement(r_dest, "slt", r1, r2));
            }
        }
        else if (op == "<=") {
            if (is_float) {
                r1 = get_operand_reg(opd1, is_float, code);
                string temp0 = code.get_temp_reg();
                r_dest = code.get_reg(lhs, false, false);
                r2 = get_operand_reg(opd2, is_float, code);
                code.add(new Compute_RTL_Statement("", "sle.d", r1, r2));
                code.add(new ILoad_RTL_Statement(temp0, "1", false));
                code.add(new Move_RTL_Statement("zero", r_dest, false));
                code.add(new Move_True_RTL_Statement(temp0, "0", r_dest, false));
                code.free_reg(temp0, false);
            }
            else {
                r1 = get_operand_reg(opd1, is_float, code);
                r_dest = code.get_reg(lhs, false, false);
                r2 = get_operand_reg(opd2, is_float, code);
                code.add(new Compute_RTL_Statement(r_dest, "sle", r1, r2));
            }
        }
        else if (op == ">") {
            if (is_float) {
                r1 = get_operand_reg(opd1, is_float, code);
                string temp0 = code.get_temp_reg();
                r_dest = code.get_reg(lhs, false, false);
                r2 = get_operand_reg(opd2, is_float, code);
                code.add(new Compute_RTL_Statement("", "sle.d", r1, r2));
                code.add(new ILoad_RTL_Statement(temp0, "1", false));
                code.add(new Move_RTL_Statement("zero", r_dest, false));
                code.add(new Move_False_RTL_Statement(temp0, "0", r_dest, false));
                code.free_reg(temp0, false);
            }
            else {
                r1 = get_operand_reg(opd1, is_float, code);
                r_dest = code.get_reg(lhs, false, false);
                r2 = get_operand_reg(opd2, is_float, code);
                code.add(new Compute_RTL_Statement(r_dest, "sgt", r1, r2));
            }
        }
        else if (op == ">=") {
            if (is_float) {
                r1 = get_operand_reg(opd1, is_float, code);
                string temp0 = code.get_temp_reg();
                r_dest = code.get_reg(lhs, false, false);
                r2 = get_operand_reg(opd2, is_float, code);
                code.add(new Compute_RTL_Statement("", "slt.d", r1, r2));
                code.add(new ILoad_RTL_Statement(temp0, "1", false));
                code.add(new Move_RTL_Statement("zero", r_dest, false));
                code.add(new Move_False_RTL_Statement(temp0, "0", r_dest, false));
                code.free_reg(temp0, false);
            }
            else {
                r1 = get_operand_reg(opd1, is_float, code);
                r_dest = code.get_reg(lhs, false, false);
                r2 = get_operand_reg(opd2, is_float, code);
                code.add(new Compute_RTL_Statement(r_dest, "sge", r1, r2));
            }
        }
        else if (op == "==") {
            if (is_float) {
                r1 = get_operand_reg(opd1, is_float, code);
                string temp0 = code.get_temp_reg();
                r_dest = code.get_reg(lhs, false, false);
                r2 = get_operand_reg(opd2, is_float, code);
                code.add(new Compute_RTL_Statement("", "seq.d", r1, r2));
                code.add(new ILoad_RTL_Statement(temp0, "1", false));
                code.add(new Move_RTL_Statement("zero", r_dest, false));
                code.add(new Move_True_RTL_Statement(temp0, "0", r_dest, false));
                code.free_reg(temp0, false);
            }
            else {
                r1 = get_operand_reg(opd1, is_float, code);
                r_dest = code.get_reg(lhs, false, false);
                r2 = get_operand_reg(opd2, is_float, code);
                code.add(new Compute_RTL_Statement(r_dest, "seq", r1, r2));
            }
        }
        else if (op == "!=") {
            if (is_float) {
                r1 = get_operand_reg(opd1, is_float, code);
                string temp0 = code.get_temp_reg();
                r_dest = code.get_reg(lhs, false, false);
                r2 = get_operand_reg(opd2, is_float, code);
                code.add(new Compute_RTL_Statement("", "seq.d", r1, r2));
                code.add(new ILoad_RTL_Statement(temp0, "1", false));
                code.add(new Move_RTL_Statement("zero", r_dest, false));
                code.add(new Move_False_RTL_Statement(temp0, "0", r_dest, false));
                code.free_reg(temp0, false);
            }
            else {
                r1 = get_operand_reg(opd1, is_float, code);
                r_dest = code.get_reg(lhs, false, false);
                r2 = get_operand_reg(opd2, is_float, code);
                code.add(new Compute_RTL_Statement(r_dest, "sne", r1, r2));
            }
        }
        else if (op == "&&") {
            r1 = get_operand_reg(opd1, is_float, code);
            r_dest = code.get_reg(lhs, false, false);
            r2 = get_operand_reg(opd2, is_float, code);
            code.add(new Compute_RTL_Statement(r_dest, "and", r1, r2));
        }
        else if (op == "||") {
            r1 = get_operand_reg(opd1, is_float, code);
            r_dest = code.get_reg(lhs, false, false);
            r2 = get_operand_reg(opd2, is_float, code);
            code.add(new Compute_RTL_Statement(r_dest, "or", r1, r2));
        }
        else {
            cerr << "Unknown Operation In TAC Detected While Converting to RTL !!\n";
            exit(2);
        }

        code.free_reg(r1, is_float);
        code.free_reg(r2, is_float);
    }
    else if (op != "") { // unary op tac statement
        string r1 = get_operand_reg(opd2, is_float, code);
        string r_dest = code.get_reg(lhs, is_float, false);
        if (op == "!") {
            code.add(new Compute_RTL_Statement(r_dest, "not", r1, ""));
        }
        else if (op == "-") {
            if (is_float) code.add(new Compute_RTL_Statement(r_dest, "uminus.d", r1, ""));
            else code.add(new Compute_RTL_Statement(r_dest, "uminus", r1, ""));
        }
        else {
            cerr << "Unknown Unary Operation !!\n";
            exit(2);
        }
        code.free_reg(r1, is_float);
    }
    else { // simple assignment
        if (is_source_variable(lhs)) {
            if (is_num_const(opd1) || is_float_const(opd1)) {
                string r = "";
                if (is_float) r = code.get_float_reg();
                else r = code.get_temp_reg();
                code.add(new ILoad_RTL_Statement(r, opd1, is_float));
                code.add(new Store_RTL_Statement(lhs, r, is_float));
                code.free_reg(r, is_float);
            }
            else if (is_str_const(opd1)) {
                string r = code.get_temp_reg();
                string str_const = code.get_str_const(opd1);
                code.add(new Compute_RTL_Statement(r, "load_addr", str_const, ""));
                code.add(new Store_RTL_Statement(lhs, r, false));
                code.free_reg(r, false);
            }
            else if (is_temp(opd1)) {
                string r = code.get_reg(opd1, is_float, true);
                code.add(new Store_RTL_Statement(lhs, r, is_float));
                code.free_reg(r, is_float);
            }
            else if (is_source_variable(opd1)) {
                string r = get_operand_reg(opd1, is_float, code);
                code.add(new Store_RTL_Statement(lhs, r, is_float));
                code.free_reg(r, is_float);
            }
            else {
                cerr << "Unknown operand type\n";

                exit(1);
            }
        }
        else {
            cerr << "Simple assignment with lhs as temp or constanst shoudn't be possible\n";
            exit(1);
        }
    }
}

TAC_Goto_Statement::TAC_Goto_Statement(string l, string con) : if_con(con), label(l) {}
TAC_Goto_Statement::~TAC_Goto_Statement() {}
void TAC_Goto_Statement::print() {
    if (if_con != "") cout << "if " << if_con << " ";
    cout << "goto " << label << "\n";
}
void TAC_Goto_Statement::gen_rtl_code(RTL_Code &code) {
    if (if_con == "") {
        code.add(new Goto_RTL_Statement(label));
    }
    else {
        string r = code.get_reg(if_con, false, true);
        code.add(new Compute_RTL_Statement("", "bgtz", r, label));
        code.free_reg(r, false);
    }
}

TAC_Label_Statement::TAC_Label_Statement(string l) : label(l) {}
TAC_Label_Statement::~TAC_Label_Statement() {}
void TAC_Label_Statement::print() {
    cout << "Label " << label << "\n";
}
void TAC_Label_Statement::gen_rtl_code(RTL_Code &code) {
    code.add(new Label_RTL_Statement(label));
}

TAC_IO_Statement::TAC_IO_Statement(string v, string io, string t, bool _v) : var(v), io(io), var_type(t), is_var(_v) {}
TAC_IO_Statement::~TAC_IO_Statement() {}
void TAC_IO_Statement::print() {
    cout << io << " " << var << "\n";
}
void TAC_IO_Statement::gen_rtl_code(RTL_Code &code) {
    bool is_float = var_type == "float";
    if (io == "write") {
        if (is_float) {
            if (is_var) {
                code.add(new ILoad_RTL_Statement("v0", "3", false));
                code.add(new Load_RTL_Statement("f12", var, true));
                code.add(new Write_RTL_Statement());
            }
            else {
                code.add(new ILoad_RTL_Statement("v0", "3", false));
                code.add(new Load_RTL_Statement("f12", var, true));
                code.add(new Write_RTL_Statement());
            }
        }
        else if (var_type == "string") {
            if (!is_var) {
                string str_const = code.get_str_const(var);
                code.add(new ILoad_RTL_Statement("v0", "4", false));
                code.add(new Compute_RTL_Statement("a0", "load_addr", str_const));
                code.add(new Write_RTL_Statement());
            }
            else {
                code.add(new ILoad_RTL_Statement("v0", "4", false));
                code.add(new Compute_RTL_Statement("a0", "load", var));
                code.add(new Write_RTL_Statement());
            }
        }
        else {
            if (is_var) {
                code.add(new ILoad_RTL_Statement("v0", "1", false));
                code.add(new Load_RTL_Statement("a0", var, false));
                code.add(new Write_RTL_Statement());
            }
            else {
                code.add(new ILoad_RTL_Statement("v0", "1", false));
                code.add(new Load_RTL_Statement("a0", var, false));
                code.add(new Write_RTL_Statement());
            }
        }
    }
    else if (io == "read") {
        if (is_float) {
            code.add(new ILoad_RTL_Statement("v0", "7", false));
            code.add(new Read_RTL_Statement());
            code.add(new Store_RTL_Statement(var, "f0", true));
        }
        else {
            code.add(new ILoad_RTL_Statement("v0", "5", false));
            code.add(new Read_RTL_Statement());
            code.add(new Store_RTL_Statement(var, "v0", false));
        }
    }
    else {
        cerr << "Unknown IO Operation " << io << "\n";
        exit(1);
    }
}

TAC_Func_Call_Statement::TAC_Func_Call_Statement(string l, string f, vector<string> &a, vector<string> &t, string ret_type) {
    lhs = l;
    func_name = f;
    args = a;
    arg_type = t;
    return_type = ret_type;
}
TAC_Func_Call_Statement::~TAC_Func_Call_Statement() {}
void TAC_Func_Call_Statement::print() {
    if (lhs != "") cout << lhs << " = ";
    cout << lhs << " = " << func_name << "_(";
    if (args.size() == 0) cout << ")\n";
    else  {
        cout << args[0] << "_";
        int k = args.size();
        for (int i=1; i<k; i++) {
            cout << ", " << args[i] << "_"; 
        }
        cout << ")\n";
    }
}
void TAC_Func_Call_Statement::gen_rtl_code(RTL_Code &code) {
    int k = args.size();
    string return_reg = "";
    for (int i = k-1; i >= 0; i--) {
        string r = get_operand_reg(args[i], arg_type[i] == "float", code);
        code.add(new Push_RTL_Statement(r, arg_type[i] == "float"));
        code.free_reg(r, arg_type[i] == "float");
    }
    if (return_type == "void") return_reg = "";
    else if (return_type == "float") return_reg = "f0";
    else return_reg = "v1";
    code.add(new Function_Call_RTL_Statement(func_name+"_", return_reg));
    for (int i=0; i<k; i++) {
        code.add(new Pop_RTL_Statement(arg_type[i] == "float"));
    }
    if (return_reg != "") {
        string r = get_operand_reg(lhs, return_reg == "f0", code);
        code.add(new Move_RTL_Statement(return_reg, r, return_reg == "f0"));
        code.free_reg(r, return_reg == "f0");
    }
}

TAC_Return_Statement::TAC_Return_Statement(string v, string r) {
    var = v;
    return_type = r;
}
TAC_Return_Statement::~TAC_Return_Statement() {}
void TAC_Return_Statement::print() {
    cout << "return " << var << "\n";
}
void TAC_Return_Statement::gen_rtl_code(RTL_Code &code) {
    if (return_type == "float") {
        code.add(new Load_RTL_Statement("f0", var, true));
        code.add(new Return_RTL_Statement("f0"));
    }
    else {
        code.add(new Load_RTL_Statement("v1", var, true));
        code.add(new Return_RTL_Statement("v1"));
    }
}

TAC_Func_Begin_Statement::TAC_Func_Begin_Statement(string f, vector<string> &h) {
    func_name = f;
    headers = h;
}
TAC_Func_Begin_Statement::~TAC_Func_Begin_Statement() {}
void TAC_Func_Begin_Statement::print() {
    for (string h : headers) cout << h;
}
void TAC_Func_Begin_Statement::gen_rtl_code(RTL_Code &code) {
    string s1 = "PROCEDURE: " + func_name;
    string s2 = "**BEGIN RTL STATEMENTS";
    vector<string> h;
    h.push_back(s1);
    h.push_back(s2);
    code.add(new Func_Begin_RTL_Statement(func_name, h));
}

TAC_Func_End_Statement::TAC_Func_End_Statement(vector<string> &f) {
    footers = f;
}
TAC_Func_End_Statement::~TAC_Func_End_Statement() {}
void TAC_Func_End_Statement::print() {
    for (string f : footers) cout << f;
}
void TAC_Func_End_Statement::gen_rtl_code(RTL_Code &code) {
    string s = "**END RTL STATEMENTS";
    vector<string> f;
    f.push_back(s);
    code.add(new Func_End_RTL_Statement(f));
}

TAC_Code::TAC_Code(int t, int l, int s, string ex, string st) : temp_count(t), label_count(l), stemp_count(s), exit_label(ex), exit_stemp(st) {}
TAC_Code::~TAC_Code() {
    // for (auto stmt : code) {
    //     delete stmt;
    // }
}
string TAC_Code::get_new_temp() {
    return "temp" + to_string(temp_count++);
}
string TAC_Code::get_new_label() {
    return "L" + to_string(label_count++);
}
string TAC_Code::get_new_stemp() {
    return "stemp" + to_string(stemp_count++);
}
void TAC_Code::add(TAC_Statement* tac_stmt) {
    code.push_back(tac_stmt);
}
void TAC_Code::print() {
    for (auto& t : code) {
        t->print();
    }
}
void TAC_Code::gen_rtl_code(RTL_Code &rtl) {
    for (auto stmt : code) {
        stmt->gen_rtl_code(rtl);
    }
}
