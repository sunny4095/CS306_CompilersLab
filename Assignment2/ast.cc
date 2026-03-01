#include "ast.hh"
#include <iomanip>
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
    return true;
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
        cerr << "Semantic Type Error at Line " << lineno << " : Operands must have same type. LHS has data type - "
        << lhs->get_data_type() << " . RHS has data type - " << rhs->get_data_type() << "\n";
        cerr << "LHS :\n";
        lhs->print(cerr);
        cerr << "\n";
        cerr << "RHS :\n";
        rhs->print(cerr);
        cerr << "\n";
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
    if (bin_op == BinOp::OP_DIV) {
        // cout << "Debug Expression Ast : " << lineno << "\n";
        // cout << "LHS : " << lhs->get_data_type() << "\n";
        // cout << "RHS : " << rhs->get_data_type() << "\n";
    // }
    if (lhs->get_data_type() != rhs->get_data_type()) {
        cerr << "Semantic Type Error at Line " << lineno << " : Type Mismatch, Left Operand has Type = "
        << lhs->get_data_type() << " Right Operand has Type = " << rhs->get_data_type() << "\n";
        ast_error = 1;
        return false;
    }
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

// Print Ast
Print_Ast::Print_Ast(Ast *e, int l) {
    expr = e;
    lineno = l;
    node_data_type = e->get_data_type();
}
Print_Ast::~Print_Ast() {}
bool Print_Ast::check_ast() {
    return expr->check_ast();
}
void Print_Ast::print(ostream &file_buffer) {
    file_buffer << "Write : ";
    expr->print(file_buffer);
    file_buffer << "\n";
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
    return true;
}
void Read_Ast::print(ostream &file_buffer) {
    file_buffer << "Read: ";
    var->print(file_buffer);
    file_buffer << "\n";
}

// Function Ast
Function_Ast::Function_Ast(const string &n, const string &r, const vector<pair<string,string>> &p, Sequence_Ast* b, int l) {
    func_name = n;
    return_type = r;
    parameters = p;
    body = b;
    lineno = l;
}
Function_Ast::~Function_Ast() {delete body;}
bool Function_Ast::check_ast() {
    if (body) return body->check_ast();
    return true;
}
void Function_Ast::print(ostream &file_buffer) {
    file_buffer << "**PROCEDURE: " << func_name << "\n";
    file_buffer << "  Return Type: <" << return_type << ">\n";
    file_buffer << "  Formal Parameters:\n";
    for (pair<string,string> &param : parameters) {
        file_buffer << "  " << param.first << "_Type<" << param.second << ">\n";
    }
    file_buffer << "**BEGIN: Abstract Syntax Tree \n";
    body->print(file_buffer);
    file_buffer << "**END: Abstract Syntax Tree \n";
}

// Program Ast
Program_Ast::Program_Ast(vector<Function_Ast *> &f) {
    function_list = f;
}
Program_Ast::~Program_Ast() {}
bool Program_Ast::check_ast() {
    for (auto f : function_list) {
        if (f && !f->check_ast()) return false;
    }
    return true;
}
void Program_Ast::print(ostream &file_buffer) {
    file_buffer << fixed << setprecision(2);
    for (auto f : function_list) {
        if (f) {
            f->print(file_buffer);
        }
    }
}