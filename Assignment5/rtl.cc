#include "rtl.hh"
#include "symbol_table.hh"

Compute_RTL_Statement::Compute_RTL_Statement(string res, string oper, string o1, string o2) : result(res), op(oper), op1(o1), op2(o2) {
    is_unary = (o2 == "");
}
void Compute_RTL_Statement::print(ostream &out) {
    if (is_unary) out << op << ": " << result << " <- " << op1 << "\n";
    else {
        if (result != "") out << op << ": " << result << " <- " << op1 << ", " << op2 << "\n";
        else out << op << ": " << op1 << ", " << op2 << "\n";
    }
}
void Compute_RTL_Statement::gen_asm_code(Asm_Code &code) {
    string asm_op = "";
    if (op == "slt.d") asm_op = "c.lt.d";
    else if (op == "sle.d") asm_op = "c.le.d";
    else if (op == "seq.d") asm_op = "c.eq.d";
    else if (op == "not") asm_op = "xori";
    else if (op == "uminus") asm_op = "neg";
    else if (op == "uminus.d") asm_op = "neg.d";
    else if (op == "load_addr") asm_op = "la";
    else if (op == "load") asm_op = "lw";
    else asm_op = op;

    if (is_unary) {
        code.add(new Instruction_Asm_Statement(asm_op, result, op1));
    } 
    else {
        if (result != "") {
            code.add(new Instruction_Asm_Statement(asm_op, result, op1, op2)); // Standard 3-operand instruction: op dest, src1, src2
        } 
        else {
            code.add(new Instruction_Asm_Statement(asm_op, op1, op2)); // No destination register (e.g., float comparisons: c.lt.d $f2, $f4)
        }
    }
}

Load_RTL_Statement::Load_RTL_Statement(string r, string v, bool f) : reg(r), var(v), is_float(f) {}
void Load_RTL_Statement::print(ostream &out) {
    out << (is_float ? "load.d: " : "load: ") << reg << " <- " << var << "\n";
}
void Load_RTL_Statement::gen_asm_code(Asm_Code &code) {
    int offset = 0;
    bool is_global = false;
    for (string global_var : code.sym_tab->global_vars) {
        if (global_var == var) {
            is_global = true;
            break;
        }
    }

    if (is_global) {
        code.add(new Memory_Asm_Statement(is_float ? "l.d" : "lw", "$"+reg, 1, var));
    }
    else {
        auto local_scope = code.sym_tab->get_func_scope(code.current_func_name);
        if (local_scope.find(var) == local_scope.end()) {
            cerr << "could not find " << var << " in the scope of " << code.current_func_name << "\n";
        }
        offset = local_scope[var].offset;
        code.add(new Memory_Asm_Statement(is_float ? "l.d" : "lw", "$"+reg, offset, "$fp"));
    }
}

ILoad_RTL_Statement::ILoad_RTL_Statement(string r, string val, bool f) : reg(r), value(val), is_float(f) {}
void ILoad_RTL_Statement::print(ostream &out) {
    out << (is_float ? "iload.d: " : "iload: ") << reg << " <- " << value << "\n";
}
void ILoad_RTL_Statement::gen_asm_code(Asm_Code &code) {
    code.add(new Instruction_Asm_Statement(is_float ? "li.d" : "li", "$"+reg, value));
}

Store_RTL_Statement::Store_RTL_Statement(string v, string r, bool f) : var(v), reg(r), is_float(f) {}
void Store_RTL_Statement::print(ostream &out) {
    out << (is_float ? "store.d: " : "store: ") << var << " <- " << reg << "\n";
}
void Store_RTL_Statement::gen_asm_code(Asm_Code &code) {
    int offset = 0;
    bool is_global = false;
    for (string global_var : code.sym_tab->global_vars) {
        if (global_var == var) {
            is_global = true;
            break;
        }
    }

    if (is_global) {
        code.add(new Memory_Asm_Statement(is_float ? "s.d" : "sw", "$"+reg, 1, var));
    }
    else {
        auto local_scope = code.sym_tab->get_func_scope(code.current_func_name);
            if (local_scope.find(var) == local_scope.end()) {
            cerr << "could not find " << var << " in the scope of " << code.current_func_name << "in store rtl\n";
        }
        offset = local_scope[var].offset;
        code.add(new Memory_Asm_Statement(is_float ? "s.d" : "sw", "$"+reg, offset, "$fp"));
    }
}

Move_RTL_Statement::Move_RTL_Statement(string v, string r, bool f) : val(v), reg(r), is_float(f) {}
void Move_RTL_Statement::print(ostream &out) {
    out << (is_float ? "move.d: " : "move: ") << reg << " <- " << val << "\n";
}
void Move_RTL_Statement::gen_asm_code(Asm_Code &code) {
    code.add(new Instruction_Asm_Statement(is_float ? "mov.d" : "move", "$"+reg, val));
}

Move_True_RTL_Statement::Move_True_RTL_Statement(string v1, string v2, string r, bool f) : val1(v1), val2(v2), reg(r), is_float(f) {}
void Move_True_RTL_Statement::print(ostream &out) {
    out << (is_float ? "movt.d: " : "movt: ") << reg << " <- " << val1 << ", " << val2 << "\n";
}
void Move_True_RTL_Statement::gen_asm_code(Asm_Code &code) {
    code.add(new Instruction_Asm_Statement(is_float ? "movt.d" : "movt", "$"+reg, val1, val2));
}

Move_False_RTL_Statement::Move_False_RTL_Statement(string v1, string v2, string r, bool f) : val1(v1), val2(v2), reg(r), is_float(f) {}
void Move_False_RTL_Statement::print(ostream &out) {
    out << (is_float ? "movf.d: " : "movf: ") << reg << " <- " << val1 << ", " << val2 << "\n";
}
void Move_False_RTL_Statement::gen_asm_code(Asm_Code &code) {
    code.add(new Instruction_Asm_Statement(is_float ? "movf.d" : "movf", "$"+reg, val1, val2));
}

Goto_RTL_Statement::Goto_RTL_Statement(string l) : label(l) {}
void Goto_RTL_Statement::print(ostream &out) {
    out << "goto: " << label << "\n";
}
void Goto_RTL_Statement::gen_asm_code(Asm_Code &code) {
    code.add(new Instruction_Asm_Statement("j", label));
}

If_Goto_RTL_Statement::If_Goto_RTL_Statement(string r, string l) : reg(r), label(l) {}
void If_Goto_RTL_Statement::print(ostream &out) {
    out << "bgtz: " << reg << ", " << label << "\n";
}
void If_Goto_RTL_Statement::gen_asm_code(Asm_Code &code) {
    code.add(new Instruction_Asm_Statement("bgtz", reg, label));
}

Label_RTL_Statement::Label_RTL_Statement(string l) : label(l) {}
void Label_RTL_Statement::print(ostream &out) {
    out << label << ":\n";
}
void Label_RTL_Statement::gen_asm_code(Asm_Code &code) {
    code.add(new Label_Asm_Statement(label));
}

void Write_RTL_Statement::print(ostream &out) {
    out << "write\n";
}
void Write_RTL_Statement::gen_asm_code(Asm_Code &code) {
    code.add(new Syscall_Asm_Statement());
}

void Read_RTL_Statement::print(ostream &out) {
    out << "read\n";
}
void Read_RTL_Statement::gen_asm_code(Asm_Code &code) {
    code.add(new Syscall_Asm_Statement());
}

Push_RTL_Statement::Push_RTL_Statement(string r, bool f) {
    reg = r;
    is_float = f;
}
void Push_RTL_Statement::print(ostream &out) {
    out << "push: " << reg << "\n";
}
void Push_RTL_Statement::gen_asm_code(Asm_Code &code) {
    if (is_float) {
        code.add(new Memory_Asm_Statement("s.d", "$"+reg, -4, "$sp"));
        code.add(new Instruction_Asm_Statement("sub", "$sp", "$sp", "8"));
    }
    else {
        code.add(new Memory_Asm_Statement("sw", "$"+reg, 0, "$sp"));
        code.add(new Instruction_Asm_Statement("sub", "$sp", "$sp", "4"));        
    }
}

Pop_RTL_Statement::Pop_RTL_Statement(bool f) {
    is_float = f;
}
void Pop_RTL_Statement::print(ostream &out) {
    out << "pop\n";
}
void Pop_RTL_Statement::gen_asm_code(Asm_Code &code) {
    if (is_float) code.add(new Instruction_Asm_Statement("add", "$sp", "$sp", "8"));
    else code.add(new Instruction_Asm_Statement("add", "$sp", "$sp", "4"));
}

Function_Call_RTL_Statement::Function_Call_RTL_Statement(string f, string r) {
    func_name = f;
    return_reg = r;
}
void Function_Call_RTL_Statement::print(ostream &out) {
    if (return_reg == "") out << "call " << func_name << "\n";
    else out << return_reg << " = call " << func_name << "\n";
}
void Function_Call_RTL_Statement::gen_asm_code(Asm_Code &code) {
    code.add(new Instruction_Asm_Statement("jal", func_name));
}

Return_RTL_Statement::Return_RTL_Statement(string r) {
    reg = r;
}
void Return_RTL_Statement::print(ostream &out) {
    out << "return " << reg << "\n";
}
void Return_RTL_Statement::gen_asm_code(Asm_Code &code) {
    code.add(new Instruction_Asm_Statement("j", "epilogue_" + code.current_func_name));
}

Func_Begin_RTL_Statement::Func_Begin_RTL_Statement(string f, vector<string> &h) {
    func_name = f;
    headers = h;
}
void Func_Begin_RTL_Statement::print(ostream &out) {
    for (string h : headers) out << h;
}
void Func_Begin_RTL_Statement::gen_asm_code(Asm_Code &code) {
    code.current_func_name = func_name;
    int alloc = code.sym_tab->get_func_sp_allocation(func_name);
    code.current_sp_allocation = alloc;

    code.add(new Directive_Asm_Statement(".text"));
    code.add(new Directive_Asm_Statement(".globl " + func_name));
    code.add(new Label_Asm_Statement(func_name));
    
    code.add(new Memory_Asm_Statement("sw", "$ra", 0, "$sp"));
    code.add(new Memory_Asm_Statement("sw", "$fp", -4, "$sp"));
    code.add(new Instruction_Asm_Statement("sub", "$fp", "$sp", "4"));
    code.add(new Instruction_Asm_Statement("sub", "$sp", "$sp", to_string(alloc)));
}

Func_End_RTL_Statement::Func_End_RTL_Statement(vector<string> &f) {
    footers = f;
}
void Func_End_RTL_Statement::print(ostream &out) {
    for (string f : footers) out << f;
}
void Func_End_RTL_Statement::gen_asm_code(Asm_Code &code) {
    string epilogue_label = "epilogue_" + code.current_func_name;

    code.add(new Label_Asm_Statement(epilogue_label));
    code.add(new Instruction_Asm_Statement("add", "$sp", "$sp", to_string(code.current_sp_allocation)));
    code.add(new Memory_Asm_Statement("lw", "$fp", -4, "$sp"));
    code.add(new Memory_Asm_Statement("lw", "$ra", 0, "$sp"));
    code.add(new Instruction_Asm_Statement("jr", "$ra"));
}

RTL_Code::RTL_Code() {
    int_regs.push_back({"v0", true});
    for (int i = 0; i < 9; i++) int_regs.push_back({"t" + to_string(i), true});
    for (int i = 2; i <= 30; i += 2) float_regs.push_back({"f" + to_string(i), true});
}
RTL_Code::~RTL_Code() {
    for (auto stmt : code) delete stmt;
}
void RTL_Code::add(RTL_Statement* stmt) {
    code.push_back(stmt);
}
void RTL_Code::print(ostream &out) {
    if (!size(code)) return;
    for (auto stmt : code) stmt->print(out);
}
string RTL_Code::get_temp_reg() {
    for (auto &r : int_regs) {
        if (r.second) {
            r.second = false;
            return r.first;
        }
    }
    cerr << "Out of integer registers\n";
    exit(1);
}
string RTL_Code::get_float_reg() {
    for (auto &r : float_regs) {
        if (r.second) {
            r.second = false;
            return r.first;
        }
    }
    cerr << "Out of float registers\n";
    exit(1);
}
string RTL_Code::get_reg(string tac_temp, bool is_float, bool search) {
    if (search && temp_map.count(tac_temp)) {return temp_map[tac_temp];}
    string reg = is_float ? get_float_reg() : get_temp_reg();
    temp_map[tac_temp] = reg;
    return reg;
}
void RTL_Code::free_reg(string r, bool is_float) {
    auto &regs = is_float ? float_regs : int_regs;
    for (auto &x : regs) {
        if (x.first == r) {
            x.second = true;
            break;
        }
    }
    for (auto it = temp_map.begin(); it != temp_map.end(); ) {
        if (it->second == r) it = temp_map.erase(it);
        else ++it;
    }
}
string RTL_Code::get_str_const(string s) {
    if (str_map.find(s) == str_map.end()) {
        int k = str_map.size();
        str_map[s] = "_str_" + to_string(k);
    }
    return str_map[s];
}
void RTL_Code::gen_asm_code(Asm_Code &asm_code) {
    if (asm_code.sym_tab->global_vars.size() != 0) {
        asm_code.add()
    }
    for (auto stmt : code) {
        stmt->gen_asm_code(asm_code);
    }
}

bool is_num_const(string s) {
    if (s.empty()) return false;
    int i = (s[0] == '-') ? 1 : 0;
    for (; i < s.size(); i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

bool is_float_const(string s) {
    bool dot = false;
    int i = (s[0] == '-') ? 1 : 0;
    for (; i < s.size(); i++) {
        if (s[i] == '.') {
            if (dot) return false;
            dot = true;
        } 
        else if (!isdigit(s[i])) return false;
    }
    return dot;
}

bool is_str_const(string s) {
    if (s.size() < 2) return false;
    if (s.front() != '"' || s.back() != '"') return false;
    return true;
}

bool is_temp(string s) {
    if (s.size() < 5 || s.substr(0,4) != "temp") return false;
    for (int i = 4; i < s.size(); i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

bool is_source_variable(string s) {
    return !(is_temp(s) || is_num_const(s) || is_float_const(s));
}
