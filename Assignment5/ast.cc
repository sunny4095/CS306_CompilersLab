#include "ast.hh"
#include <iomanip>
#include <algorithm>
#include <map>
// string print_data_type(const DataType & t) {
//     if (t == DataType::int_data_type) return "int";
//     else if (t == DataType::float_data_type) return "float";
//     else if (t == DataType::bool_data_type) return "int";
//     else if (t == DataType::string_data_type) return "string";
//     else if (t == DataType::void_data_type) return "void";
//     return "Undefined";
// }

string print_rel_op(const RelOp &op) {
    if (op == OP_LE) return "LE<bool>";
    else if (op == OP_LT) return "LT<bool>";
    else if (op == OP_GT) return "GT<bool>";
    else if (op == OP_GE) return "GE<bool>";
    else if (op == OP_EQ) return "EQ<bool>";
    else if (op == OP_NE) return "NE<bool>";
    return "Undefined";
}

string print_bin_op(const BinOp &op) {
    if (op == OP_ADD) return "Plus";
    else if (op == OP_SUB) return "Minus";
    else if (op == OP_MULT) return "Mult";
    else if (op == OP_DIV) return "Div";
    return "Undefined";
}

string print_log_op(const LogOp &op) {
    if (op == OP_OR) return "OR";
    else if (op == OP_AND) return "AND";
    return "Undefined";
}

// Base Ast
Ast::Ast() : ast_arity(zero_arity), lineno(0) {}
Ast::Ast(int line) : lineno(line) {}
Ast::~Ast() {}
string Ast::get_data_type() {return node_data_type;}
bool Ast::check_ast() {return true;}
SymbolTableEntry& Ast::get_sym_tab_entry() {
    cerr << "get_sym_tab_entry called on Base Ast\n";
    ast_error = 1;
    exit(1);
}

// Assignmet Ast
Assignment_Ast::Assignment_Ast(Ast* _lhs, Ast* _rhs, int line) {
    lhs = _lhs;
    rhs = _rhs;
    lineno = line;
    ast_arity = binary_arity;
}
Assignment_Ast::~Assignment_Ast() {}
bool Assignment_Ast::check_ast() {
    bool semantic_check = true;
    if (!lhs->check_ast()) semantic_check = false;
    if (!rhs->check_ast()) semantic_check = false;
    if (lhs->get_data_type() != rhs->get_data_type()) {
        cerr << "Semantic Type Error at Line " << this->lineno << "\n";
        semantic_check = false;
        ast_error = 1;
    }
    node_data_type = lhs->get_data_type();
    return semantic_check;
}
void Assignment_Ast::print(ostream &file_buffer) {
    file_buffer << "Asgn:\n";
    file_buffer << "LHS (";
    lhs->print(file_buffer);
    file_buffer << ")\n";
    file_buffer << "RHS (";
    rhs->print(file_buffer);
    file_buffer << ")\n";
}
string Assignment_Ast::gen_tac_code(TAC_Code &code) {
    string t1 = lhs->gen_tac_code(code);
    string t2 = rhs->gen_tac_code(code);
    code.add(new TAC_Assignment_Statement(t1, t2, "", "", rhs->get_data_type()));
    return "";
}

// Name Ast
Name_Ast::Name_Ast(const string &name, const string &type, int line) : Ast(line), var_name(name) {
    // sym_tab_entry = &var;
    // if (var.type == "int") node_data_type = DataType::int_data_type;
    // else if (var.type == "float") node_data_type = DataType::float_data_type;
    // else if (var.type == "bool") node_data_type = DataType::bool_data_type;
    // else if (var.type == "string") node_data_type = DataType::string_data_type;
    // else if (var.type == "void") node_data_type = DataType::void_data_type;
    node_data_type = type;
    ast_arity = zero_arity;
}
Name_Ast::~Name_Ast() {}
string Name_Ast::get_data_type() const {return node_data_type;}
// const SymbolTableEntry& Name Ast::get_sym_tab_entry() const {return *sym_tab_entry;}
void Name_Ast::print(ostream &file_buffer) {
    file_buffer << "Name : " << var_name << " _Type<" << node_data_type << ">";
}
string Name_Ast::gen_tac_code(TAC_Code &code) {
    return var_name;
}

// Relational Ast
Relational_Ast::Relational_Ast(Ast *_lhs, Ast *_rhs, RelOp _rel_op, int line) {
    lhs = _lhs;
    rhs = _rhs;
    rel_op = _rel_op;
    lineno = line;
    ast_arity = binary_arity;
    node_data_type = "bool";
}
Relational_Ast::~Relational_Ast() {}
string Relational_Ast::get_data_type() {return "bool";}
bool Relational_Ast::check_ast() {
    if (!lhs->check_ast()) return false;
    if (!rhs->check_ast()) return false;
    if (lhs->get_data_type() != rhs->get_data_type()) {
        cerr << "Semantic Type Error at Line " << lineno << " : Operands must have same type. LHS has data type - " << lhs->get_data_type() << " . RHS has data type - " << rhs->get_data_type() << "\n";
        cerr << "LHS :\n";
        lhs->print(cerr);
        cerr << "\n";
        cerr << "RHS :\n";
        rhs->print(cerr);
        cerr << "\n";
        ast_error = 1;
        return false;
    }
    if (lhs->get_data_type() == "bool" || lhs->get_data_type() == "string") {
        cerr << "Bool and String values cannot be compared\n";
        ast_error = 1;
        return false;
    }
    return true;
}
void Relational_Ast::print(ostream &file_buffer) {
    file_buffer << "\n";
    file_buffer << "Condition: " << print_rel_op(rel_op) << "\n";
    file_buffer << "L_Opd (";
    lhs->print(file_buffer);
    file_buffer << ")\n";
    file_buffer << "R_Opd (";
    rhs->print(file_buffer);
    file_buffer << ")";
}
string Relational_Ast::gen_tac_code(TAC_Code &code) {
    string t1 = lhs->gen_tac_code(code);
    string t2 = rhs->gen_tac_code(code);
    string t3 = code.get_new_temp();
    string op = "";
    if (rel_op == OP_LE) op = "<=";
    else if (rel_op == OP_LT) op = "<";
    else if (rel_op == OP_GT) op = ">";
    else if (rel_op == OP_GE) op = ">=";
    else if (rel_op == OP_EQ) op = "==";
    else if (rel_op == OP_NE) op = "!=";
    code.add(new TAC_Assignment_Statement(t3, t1, op, t2, lhs->get_data_type(), rhs->get_data_type()));
    return t3;
}

// Expression Ast
Expression_Ast::Expression_Ast(Ast *_lhs, Ast *_rhs, BinOp _bin_op, int line) {
    lhs = _lhs;
    rhs = _rhs;
    bin_op = _bin_op;
    lineno = line;
    ast_arity = binary_arity;
    node_data_type = lhs->get_data_type();
    // cout << "called at : " << line << "\n";
}
Expression_Ast::~Expression_Ast() {}
string Expression_Ast::get_data_type() {return node_data_type;}
bool Expression_Ast::check_ast() {
    if (!lhs->check_ast()) return false;
    if (!rhs->check_ast()) return false;
    // if (bin_op == BinOp::OP_DIV) {
        // cout << "Debug Expression Ast : " << lineno << "\n";
        // cout << "LHS : " << lhs->get_data_type() << "\n";
        // cout << "RHS : " << rhs->get_data_type() << "\n";
    // }
    if (lhs->get_data_type() != rhs->get_data_type()) {
        cerr << "Semantic Type Error at Line " << lineno << " : Type Mismatch, Left Operand has Type = " << lhs->get_data_type() << " Right Operand has Type = " << rhs->get_data_type() << "\n";
        ast_error = 1;
        return false;
    }
    node_data_type = lhs->get_data_type();
    return true;
}
void Expression_Ast::print(ostream &file_buffer) {
    file_buffer << "\n";
    file_buffer << "Arith: " << print_bin_op(bin_op) << " <" << node_data_type << ">\n";
    file_buffer << "L_Opd (";
    lhs->print(file_buffer);
    file_buffer << ")\n";
    file_buffer << "R_Opd (";
    rhs->print(file_buffer);
    file_buffer << ")";
}
string Expression_Ast::gen_tac_code(TAC_Code &code) {
    string t1 = lhs->gen_tac_code(code);
    string t2 = rhs->gen_tac_code(code);
    string t3 = code.get_new_temp();
    string op = "";
    if (bin_op == OP_ADD) op = "+";
    else if (bin_op == OP_SUB) op = "-";
    else if (bin_op == OP_MULT) op = "*";
    else if (bin_op == OP_DIV) op = "/";
    code.add(new TAC_Assignment_Statement(t3, t1, op, t2, lhs->get_data_type(), rhs->get_data_type()));
    return t3;
}

// Uminus Ast
Uminus_Ast::Uminus_Ast(Ast *op, int line) {
    operand = op;
    lineno = line;
    node_data_type = operand->get_data_type();
}
Uminus_Ast::~Uminus_Ast() {}
bool Uminus_Ast::check_ast() {
    if (!operand->check_ast()) return false;
    if (operand->get_data_type() != "int" && operand->get_data_type() != "float") {
        cerr << "Semantic Error at Line " << lineno << " : Unary Minus can only be applied to integer and float variables\n";
        ast_error = 1;
        return false;
    }
    return true;
}
void Uminus_Ast::print(ostream &file_buffer) {
    file_buffer << "\n";
    file_buffer << "Arith: Uminus <" << node_data_type << ">\n";
    file_buffer << "L_Opd (";
    operand->print(file_buffer);
    file_buffer << ")";
}
string Uminus_Ast::gen_tac_code(TAC_Code &code) {
    string t1 = operand->gen_tac_code(code);
    string t2 = code.get_new_temp();
    code.add(new TAC_Assignment_Statement(t2, "", "-", t1, "", operand->get_data_type()));
    return t2;
}

// Int Ast
Int_Ast::Int_Ast(int _value, int line) {
    value = _value;
    lineno = line;
    node_data_type = "int";
}
Int_Ast::~Int_Ast() {}
bool Int_Ast::check_ast() { return true; }
void Int_Ast::print(ostream &file_buffer) {
    file_buffer << "Num : " << value << "<int>";
}
string Int_Ast::gen_tac_code(TAC_Code &code) {
    return to_string(value);
}

// Float Ast
Float_Ast::Float_Ast(float _value, int line) {
    value = _value;
    lineno = line;
    node_data_type = "float";
}
Float_Ast::~Float_Ast() {}
bool Float_Ast::check_ast() { return true; }
void Float_Ast::print(ostream &file_buffer) {
    file_buffer << "Num : " << value << "<float>";
}
string Float_Ast::gen_tac_code(TAC_Code &code) {
    ostringstream oss;
    oss << fixed << setprecision(2) << value;
    return oss.str();
}

// String Ast
String_Ast::String_Ast(string _value, int line) {
    value = _value;
    lineno = line;
    node_data_type = "string";
}
String_Ast::~String_Ast() {}
bool String_Ast::check_ast() { return true; }
void String_Ast::print(ostream &file_buffer) {
    file_buffer << "String : " << value << "<string>";
}
string String_Ast::gen_tac_code(TAC_Code &code) {
    return value;
}

// Sequence Ast
Sequence_Ast::Sequence_Ast(vector<Ast*> &stmts) : stmt_list(stmts) {}
Sequence_Ast::Sequence_Ast() : Ast(0) {}
Sequence_Ast::~Sequence_Ast() {}
void Sequence_Ast::add_statement(Ast *stmt) {
    if (stmt != nullptr) {
        stmt_list.push_back(stmt);
    }
}
bool Sequence_Ast::check_ast() {
    for (Ast *stmt : stmt_list) {
        if (stmt && !stmt->check_ast()) return false;
    }
    return true;
}
void Sequence_Ast::print(ostream &file_buffer) {
    for (Ast *stmt : stmt_list) {
        if (stmt) stmt->print(file_buffer);
    }
}
string Sequence_Ast::gen_tac_code(TAC_Code &code) {
    for (auto &stmt : stmt_list) stmt->gen_tac_code(code);
    return "";
}

// Ternary Ast
Ternary_Ast::Ternary_Ast(Ast *c, Ast *t, Ast *f, int l) {
    cond = c;
    true_expr = t;
    false_expr = f;
    lineno = l;
    node_data_type = t->get_data_type();
}
Ternary_Ast::~Ternary_Ast() {
    delete cond;
    delete true_expr;
    delete false_expr;
}
bool Ternary_Ast::check_ast() {
    if (!cond->check_ast()) return false;
    if (!true_expr->check_ast()) return false;
    if (!false_expr->check_ast()) return false;
    if (cond->get_data_type() != "bool") {
        cerr << "Semantic Error at Line " << lineno << " Ternary condition is not bool\n";
        ast_error = 1;
        return false;
    }
    if (true_expr->get_data_type() != false_expr->get_data_type()) {
        cerr << "Semantic Error at Line " << lineno << " Ternary true and false expressions are of different types\n";
        ast_error = 1;
        return false;
    }
    return true;
}
void Ternary_Ast::print(ostream &file_buffer) {
    cond->print(file_buffer);
    file_buffer << "\nTrue_Part (";
    true_expr->print(file_buffer);
    file_buffer << ")\n";
    file_buffer << "False_Part (";
    false_expr->print(file_buffer);
    file_buffer << ")";
}
string Ternary_Ast::gen_tac_code(TAC_Code &code) {

    TAC_Code c_cond(code.temp_count, code.label_count, code.stemp_count);
    string t0 = cond->gen_tac_code(c_cond);

    code.temp_count = c_cond.temp_count;
    code.label_count = c_cond.label_count;
    code.stemp_count = c_cond.stemp_count;

    string st0 = code.get_new_stemp();
    string l0 = code.get_new_label();
    string l1 = code.get_new_label();

    TAC_Code c_true(c_cond.temp_count, c_cond.label_count, c_cond.stemp_count);
    string t1 = true_expr->gen_tac_code(c_true);

    TAC_Code c_false(c_true.temp_count, c_true.label_count, c_true.stemp_count);
    string t2 = false_expr->gen_tac_code(c_false);

    code.temp_count = c_false.temp_count;
    code.label_count = c_false.label_count;
    code.stemp_count = c_false.stemp_count;

    string t3 = code.get_new_temp();
    
    for (auto stmt : c_cond.code) code.code.push_back(stmt);
    c_cond.code.clear();

    code.add(new TAC_Assignment_Statement(t3, "", "!", t0, "", cond->get_data_type()));
    code.add(new TAC_Goto_Statement(l0, t3));

    for (auto stmt : c_true.code) code.code.push_back(stmt);
    c_true.code.clear();

    code.add(new TAC_Assignment_Statement(st0, t1, "", "", true_expr->get_data_type(), ""));
    code.add(new TAC_Goto_Statement(l1));
    code.add(new TAC_Label_Statement(l0));

    for (auto stmt : c_false.code) code.code.push_back(stmt);
    c_false.code.clear();

    code.add(new TAC_Assignment_Statement(st0, t2, "", "", false_expr->get_data_type(), ""));
    code.add(new TAC_Label_Statement(l1));

    return st0;
}

// Logical Ast
Logical_Ast::Logical_Ast(Ast *l, Ast *r, LogOp op, int line) {
    lhs = l;
    rhs = r;
    log_op = op;
    lineno = line;
    node_data_type = "bool";
}
Logical_Ast::~Logical_Ast() {}
bool Logical_Ast::check_ast() {
    if (!lhs->check_ast()) return false;
    if (!rhs->check_ast()) return false;
    if (lhs->get_data_type() != "bool" || rhs->get_data_type() != "bool") {
        cerr << "Semantic Type Error at Line " << lineno << " : Logical Operand must be of bool type\n";
        ast_error = 1;
        return false;
    }
    return true;
}
void Logical_Ast::print(ostream &file_buffer) {
    file_buffer << "\nCondition: " << print_log_op(log_op) << "<bool>\n";
    file_buffer << "L_Opd (";
    lhs->print(file_buffer);
    file_buffer << ")\n";
    file_buffer << "R_Opd (";
    rhs->print(file_buffer);
    file_buffer << ")";
}
string Logical_Ast::gen_tac_code(TAC_Code &code) {
    string t1 = lhs->gen_tac_code(code);
    string t2 = rhs->gen_tac_code(code);
    string t3 = code.get_new_temp();
    string op = "";
    if (log_op == OP_AND) op = "&&";
    else if (log_op == OP_OR) op = "||";
    code.add(new TAC_Assignment_Statement(t3, t1, op, t2, lhs->get_data_type(), rhs->get_data_type()));
    return t3;
}

// Logical Not Ast
Logical_Not_Ast::Logical_Not_Ast(Ast *a, int l) {
    expr = a;
    lineno = l;
    node_data_type = "bool";
}
Logical_Not_Ast::~Logical_Not_Ast() {}
bool Logical_Not_Ast::check_ast() {
    if (!expr) return false;
    if (!expr->check_ast()) return false;
    if (expr->get_data_type() != "bool") {
        cerr << "Semantic Type Error at Line " << lineno << " Operand is not of bool type\n";
        ast_error = 1;
        return false;
    }
    return true;
}
void Logical_Not_Ast::print(ostream &file_buffer) {
    file_buffer << "\n";
    file_buffer << "Condition: NOT<bool>\n";
    file_buffer << "L_Opd (";
    expr->print(file_buffer);
    file_buffer << ")";
}
string Logical_Not_Ast::gen_tac_code(TAC_Code &code) {
    string t1 = expr->gen_tac_code(code);
    string t2 = code.get_new_temp();
    code.add(new TAC_Assignment_Statement(t2, "", "!", t1, "", expr->get_data_type()));
    return t2;
}

// Compound Statement Ast
Compound_Statement_Ast::Compound_Statement_Ast(Ast *seq, int l) {
    body = seq;
    lineno = l;
}
Compound_Statement_Ast::~Compound_Statement_Ast() {
    delete body;
}
bool Compound_Statement_Ast::check_ast() {
    if (!body) return true;
    return body->check_ast();
}
void Compound_Statement_Ast::print(ostream &file_buffer) {
    if (body) body->print(file_buffer);
}
string Compound_Statement_Ast::gen_tac_code(TAC_Code &code) {
    if (body) body->gen_tac_code(code);
    return "";
}

// If Else Ast
If_Else_Ast::If_Else_Ast(Ast *c, Ast *i, Ast *e, int l) {
    cond = c;
    if_stmt_list = i;
    else_stmt_list = e;
    lineno = l;
}
If_Else_Ast::~If_Else_Ast() {
    delete cond;
    delete if_stmt_list;
    delete else_stmt_list;
}
bool If_Else_Ast::check_ast() {
    if (!cond->check_ast()) return false;
    if (cond->get_data_type() != "bool") {
        cerr << "Semantic Error at Line " << lineno << " : IF condition must be bool\n";
        ast_error = 1;
        return false;
    }
    if (if_stmt_list) {
        if (!if_stmt_list->check_ast()) return false;
    }
    if (else_stmt_list) {
        if (!else_stmt_list->check_ast()) return false;
    }
    return true;
}
void If_Else_Ast::print(ostream &file_buffer) {
    file_buffer << "If:\n";
    file_buffer << "Condition (";
    cond->print(file_buffer);
    file_buffer << ")";
    file_buffer << "Then (\n";
    if_stmt_list->print(file_buffer);
    file_buffer << ")\n";
    if (else_stmt_list) {
        file_buffer << "Else (\n";
        else_stmt_list->print(file_buffer);
        file_buffer << ")\n";
    }
}
string If_Else_Ast::gen_tac_code(TAC_Code &code) {
    TAC_Code c_cond(code.temp_count, code.label_count, code.stemp_count);
    string t0 = cond->gen_tac_code(c_cond);

    TAC_Code c_then(c_cond.temp_count, c_cond.label_count, c_cond.stemp_count);
    if_stmt_list->gen_tac_code(c_then);

    code.temp_count = c_then.temp_count;
    code.label_count = c_then.label_count;
    code.stemp_count = c_then.stemp_count;

    string t1 = code.get_new_temp();
    string l0 = code.get_new_label();
    string l1;
    if (!else_stmt_list) l1 = l0;
    else l1 = code.get_new_label();

    for (auto stmt : c_cond.code) code.code.push_back(stmt);
    c_cond.code.clear();

    code.add(new TAC_Assignment_Statement(t1, "", "!", t0, "", cond->get_data_type()));
    code.add(new TAC_Goto_Statement(l1, t1));

    for (auto stmt : c_then.code) code.code.push_back(stmt);
    c_then.code.clear();
    code.add(new TAC_Goto_Statement(l0));

    if (else_stmt_list) {
        code.add(new TAC_Label_Statement(l1));
        else_stmt_list->gen_tac_code(code);
        code.add(new TAC_Label_Statement(l0));
    }

    return "";
}

// While Ast
While_Ast::While_Ast(Ast *c, Ast *b, int l) {
    cond = c;
    body  = b;
    lineno = l;
}
While_Ast::~While_Ast() {
    delete cond;
    delete body;
}
bool While_Ast::check_ast() {
    if (!cond->check_ast()) return false;
    if (cond->get_data_type() != "bool") {
        cerr << "Semantic Error at line :" << lineno << "Condition must be of boolean type";
        ast_error = 1;
        return false;
    }
    if (!body->check_ast()) return false;
    return true;
}
void While_Ast::print(ostream &file_buffer) {
    file_buffer << "While:\n";
    file_buffer << "Condition (";
    cond->print(file_buffer);
    file_buffer << ")\n";
    file_buffer << "Body (\n";
    body->print(file_buffer);
    file_buffer << ")\n"; 
}
string While_Ast::gen_tac_code(TAC_Code &code) {
    TAC_Code c_cond(code.temp_count, code.label_count, code.stemp_count);
    string t0 = cond->gen_tac_code(c_cond);

    TAC_Code c_body(c_cond.temp_count, c_cond.label_count, c_cond.stemp_count);
    body->gen_tac_code(c_body);

    code.temp_count = c_body.temp_count;
    code.label_count = c_body.label_count;
    code.stemp_count = c_body.stemp_count;    

    string l0 = code.get_new_label();
    string l1 = code.get_new_label();
    string t1 = code.get_new_temp();

    code.add(new TAC_Label_Statement(l0));

    for (auto stmt : c_cond.code) code.code.push_back(stmt);
    c_cond.code.clear();

    code.add(new TAC_Assignment_Statement(t1, "", "!", t0, "", cond->get_data_type()));
    code.add(new TAC_Goto_Statement(l1, t1));

    for (auto stmt : c_body.code) code.code.push_back(stmt);
    c_body.code.clear();

    code.add(new TAC_Goto_Statement(l0));
    code.add(new TAC_Label_Statement(l1));

    return "";
}

// Do While Ast
Do_While_Ast::Do_While_Ast(Ast *c, Ast *b, int l) {
    while_cond = c;
    do_body = b;
    lineno = l;
}
Do_While_Ast::~Do_While_Ast() {
    delete while_cond;
    delete do_body;
}
bool Do_While_Ast::check_ast() {
    if (!while_cond->check_ast()) return false;
    if (while_cond->get_data_type() != "bool") {
        cerr << "Semantic Error at line :" << lineno << "Condition must be of boolean type";
        ast_error = 1;
        return false;
    }
    if (!do_body->check_ast()) return false;
    return true;
}
void Do_While_Ast::print(ostream &file_buffer) {
    file_buffer << "Do:\n";
    file_buffer << "Body (\n";
    do_body->print(file_buffer);
    file_buffer << ")\n";
    file_buffer << "While Condition (\n";
    while_cond->print(file_buffer);
    file_buffer << ")\n";
}
string Do_While_Ast::gen_tac_code(TAC_Code &code) {
    TAC_Code c_body(code.temp_count, code.label_count, code.stemp_count);
    do_body->gen_tac_code(c_body);

    code.temp_count = c_body.temp_count;
    code.label_count = c_body.label_count;
    code.stemp_count = c_body.stemp_count; 

    string l0 = code.get_new_label();
    code.add(new TAC_Label_Statement(l0));

    for (auto stmt : c_body.code) code.code.push_back(stmt);
    c_body.code.clear();
    
    string t0 = while_cond->gen_tac_code(code);
    code.add(new TAC_Goto_Statement(l0,t0));

    return "";
}

// Print Ast
Print_Ast::Print_Ast(Ast *e, int l) {
    expr = e;
    lineno = l;
    node_data_type = e->get_data_type();
}
Print_Ast::~Print_Ast() {}
bool Print_Ast::check_ast() {
    string type = expr->get_data_type();
    if (type == "bool") {
        cerr << "Semantic type error at line : " << lineno << " Cannot print boolean variables\n";
        ast_error = 1;
        return false;
    }
    return expr->check_ast();
}
void Print_Ast::print(ostream &file_buffer) {
    file_buffer << "Write : ";
    expr->print(file_buffer); file_buffer << "\n";
}
string Print_Ast::gen_tac_code(TAC_Code &code) {
    string t = expr->gen_tac_code(code);
    bool is_var = (dynamic_cast<Name_Ast*>(expr) != nullptr);
    code.add(new TAC_IO_Statement(t, "write", expr->get_data_type(), is_var));
    return "";
}

// Read Ast
Read_Ast::Read_Ast(Ast *v, int l) {
    var = v;
    lineno = l;
    node_data_type = v->get_data_type();
}
Read_Ast::~Read_Ast() {}
bool Read_Ast::check_ast() {
    if (!var->check_ast()) return false;
    Name_Ast* name = dynamic_cast<Name_Ast*>(var);
    if (!name) {
        cerr << "Semantic Type Error at Line " << lineno << " Read should be with a variable\n";
        ast_error = 1;
        return false;
    }
    string type = name->get_data_type();
    if (type == "bool") {
        cerr << "Semantic Type Error at Line " << lineno << " Boolean values cannot be read\n";
        ast_error = 1;
        return false;
    }
    if (type == "string") {
        cerr << "Semantic Type Error at Line " << lineno << " String values cannot be read\n";
        ast_error = 1;
        return false;
    }
    return true;
}
void Read_Ast::print(ostream &file_buffer) {
    file_buffer << "Read: ";
    var->print(file_buffer);
}
string Read_Ast::gen_tac_code(TAC_Code &code) {
    string t = var->gen_tac_code(code);
    code.add(new TAC_IO_Statement(t, "read", var->get_data_type(), false));
    return "";
}

// Function_Call_Ast
Function_Call_Ast::Function_Call_Ast(string n, vector<Ast*> &a, SymbolTableEntry *sym_pointer, int l) {
    func_name = n;
    args = a;
    lineno = l;
    sym = sym_pointer;
    node_data_type = sym_pointer->type;
}
Function_Call_Ast::~Function_Call_Ast() {
    for (auto arg : args) delete arg;
}
bool Function_Call_Ast::check_ast() {
        for (auto arg : args) {
            if (!arg->check_ast()) {
                cerr << "Invalid Arguments provided to the Function : " << func_name << " at line : " << lineno << "\n";
                ast_error = 1;
                return false;
            }
        }
        if (args.size() != sym->params_of_func.size()) {
            cerr << "Invalid Number of Argumnets provided to the Function : " << func_name << " at line : " << lineno << "\n";
            ast_error = 1;
            return false;
        }
        int k = args.size();
        for (int i=0; i<k; i++) {
            if (sym->params_of_func[i].first != args[i]->get_data_type()) {
                cerr << "Invalid Argument Type provided to the Function : " << func_name << " at line : " << lineno << "\n";
                ast_error = 1;
                return false;
            }
        }
        return true;
}
void Function_Call_Ast::print(ostream &file_buffer) {
    file_buffer << "\nFN CALL: ";
    file_buffer << func_name << "_(";
    for (auto arg : args) {
        file_buffer << "\n";
        arg->print(file_buffer);
    }
    file_buffer << ")";
}
string Function_Call_Ast::gen_tac_code(TAC_Code &code) {
    string temp = "";
    if (sym->type != "void") temp = code.get_new_temp();
    vector<string> a;
    vector<string> t;
    for(auto arg : args) {
        a.push_back(arg->gen_tac_code(code));
        t.push_back(arg->get_data_type());
    }
    code.add(new TAC_Func_Call_Statement(temp, func_name, a, t, sym->type));
    return temp;
}

// Return Ast
Return_Ast::Return_Ast(Ast *v, int l) {
    ret_val = v;
    lineno = l;
}
Return_Ast::~Return_Ast() {
    if (ret_val) delete ret_val;
}
bool Return_Ast::check_ast() {
    if (ret_val) return ret_val->check_ast();
    return true;
}
void Return_Ast::print(ostream &file_buffer) {
    file_buffer << "Return :";
    ret_val->print(file_buffer);
}
string Return_Ast::gen_tac_code(TAC_Code &code) {
    string t = ret_val->gen_tac_code(code);
    code.add(new TAC_Assignment_Statement(code.exit_stemp, t, "", "", ret_val->get_data_type()));
    code.add(new TAC_Goto_Statement(code.exit_label));
    return "";
}

// Function Ast
Function_Ast::Function_Ast(const string &n, const string &r, const vector<pair<string,string>> &p, Sequence_Ast* b, bool d, int l) {
    func_name = n;
    return_type = r;
    parameters = p;
    body = b;
    is_declared = d;
    lineno = l;
    exit_label = "";
}
Function_Ast::~Function_Ast() {delete body;}
string Function_Ast::get_func_name() const {
    if (func_name == "main") return func_name;
    return func_name + "_";
}
bool Function_Ast::check_ast() {
    if (body) return body->check_ast();
    return true;
}
void Function_Ast::print(ostream &file_buffer) {
    file_buffer << "**PROCEDURE: " << func_name;
    if (func_name != "main") file_buffer << "_\n";
    else file_buffer << "\n";
    file_buffer << "  Return Type: <" << return_type << ">\n";
    file_buffer << "  Formal Parameters:\n";
    for (pair<string,string> &param : parameters) {
        file_buffer << "  " << param.second << "_Type<" << param.first << ">\n";
    }
    file_buffer << "**BEGIN: Abstract Syntax Tree \n";
    body->print(file_buffer);
    file_buffer << "\n**END: Abstract Syntax Tree \n";
}
string Function_Ast::gen_tac_code(TAC_Code &code) {
    string s1 = "**PROCEDURE: " + func_name;
    if (func_name == "main") s1 = s1 + "\n";
    else s1 = s1 + "_\n";
    string s2 = "**BEGIN: Three Address Code Statements\n";
    string s3 = "**END: Three Address Code Statements\n";
    vector<string> headers;
    vector<string> footers;
    headers.push_back(s1);
    headers.push_back(s2);
    footers.push_back(s3);
    code.add(new TAC_Func_Begin_Statement(func_name, headers));
    body->gen_tac_code(code);
    if (return_type != "void") {
        code.add(new TAC_Label_Statement(code.exit_label));
        code.add(new TAC_Return_Statement(code.exit_stemp, return_type));
    }
    code.add(new TAC_Func_End_Statement(footers));
    return "";
}

// Program Ast
Program_Ast::Program_Ast(vector<Function_Ast *> &f, vector<string> df) {
    function_list = f;
    declared_func = df;
}
Program_Ast::~Program_Ast() {}
bool Program_Ast::check_ast() {
    for (auto f : function_list) {
        if (f && !f->check_ast()) return false;
    }
    return true;
}
bool compare(Function_Ast* a, Function_Ast* b) {
    if (a->is_declared && b->is_declared) return a->get_func_name() < b->get_func_name();
    if (a->is_declared) return true;
    if (b->is_declared) return false;
    return a->get_func_name() < b->get_func_name();
}
void Program_Ast::print(ostream &file_buffer) {
    file_buffer << fixed << setprecision(2);
    sort(function_list.begin(), function_list.end(), compare);
    for (auto f : function_list) {
        if (f) {
            f->print(file_buffer);
        }
    }
}
string Program_Ast::gen_tac_code(TAC_Code &code) {
    for (string decl_func_name : declared_func) {
        string _temp = decl_func_name;
        if (_temp != "main") _temp = _temp + "_";
        for (auto f : function_list) {
            if (f->get_func_name() == _temp && f->return_type != "void") f->exit_label = code.get_new_label(); 
        }
    }
    for (auto f : function_list) {
        if (f->return_type != "void" && f->exit_label == "") f->exit_label = code.get_new_label();
    }
    sort(function_list.begin(), function_list.end(), compare);
    map<string, TAC_Code> func_code_map;
    for (auto f : function_list) {
        TAC_Code func_tac_code = TAC_Code();
        func_tac_code.label_count = code.label_count;
        if (f->return_type != "void") {
            func_tac_code.exit_label = func_tac_code.get_new_label();
            func_tac_code.exit_stemp = func_tac_code.get_new_stemp();
        }
        f->gen_tac_code(func_tac_code);
        code.label_count = func_tac_code.label_count;
        func_code_map.insert({f->get_func_name(), func_tac_code});
    }
    for (auto &tac_code : func_code_map) {
        for (auto stmt : tac_code.second.code) code.code.push_back(stmt);
        tac_code.second.code.clear();
    }
    return "";
}