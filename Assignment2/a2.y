%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <vector>
    #include <string>
    #include <cstring>
    #include <iostream>
    #include "symbol_table.hh"
    #include "ast.hh"
    using namespace std;

    extern int yylineno;
    extern FILE *yyin;
    int yylex(void);
    int yyparse(void);
    int yyerror(const char *s);
    extern FILE *fp;
    extern int print_tokens;
    extern int check_semantics;
    extern int semantic_errors;
    SymbolTable symtab;
    Ast* ast_root = nullptr;
%}

%union {
    int int_val;
    float float_val;
    char *string_val;
    vector<char *> *id_list;
    Ast *ast;
    vector<Ast *> *ast_list;
    Sequence_Ast *seq_ast;
    vector<pair<string,string>> *param_list;
}

%token INTEGER
%token FLOAT
%token STRING
%token VOID
%token READ
%token PRINT
%token BOOL
%token PLUS
%token MINUS
%token MULT
%token DIV
%token GT
%token GE
%token LT
%token LE
%token NE
%token EQ
%token AND
%token OR
%token COLON
%token QUESTION_MARK
%token NOT
%token LEFT_ROUND_BRACKET
%token RIGHT_ROUND_BRACKET
%token LEFT_CURLY_BRACKET
%token RIGHT_CURLY_BRACKET
%token ASSIGN_OP
%token SEMICOLON
%token COMMA
%token <float_val> FLOAT_VAL
%token <int_val> INT_VAL
%token <string_val> STR_CONST
%token <string_val> NAME

%type <string_val> named_type
%type <id_list> var_decl_item_list
%type <seq_ast> statement_list
%type <ast> statement
%type <ast> assignment_statement
%type <ast> print_statement
%type <ast> read_statement
%type <ast> expression
%type <ast> rel_expression
%type <ast> main_function
%type <param_list> formal_param_list
%type <param_list> formal_param

%right QUESTION_MARK COLON
%right NOT
%left OR
%left AND
%left EQ NE
%left LT LE GT GE
%left PLUS MINUS
%left MULT DIV
%right UMINUS

%%
program 
    : global_decl_statement_list main_function
    | main_function
    ;

global_decl_statement_list
    : global_decl_statement_list var_decl_stmt
    | global_decl_statement_list func_decl
    | var_decl_stmt
    | func_decl
    ;

func_decl
    : named_type NAME LEFT_ROUND_BRACKET formal_param_list RIGHT_ROUND_BRACKET SEMICOLON
      {
          if (!symtab.insert($2, $1, SymbolKind::FUNCTION, yylineno, *$4, false) && check_semantics) {
              printf("Semantic Error: redeclaration of function '%s' at line %d\n", $2, yylineno);
              semantic_errors = 1;
            }
          delete $4;
      }
    | named_type NAME LEFT_ROUND_BRACKET RIGHT_ROUND_BRACKET SEMICOLON
      {
          if (!symtab.insert($2, $1, SymbolKind::FUNCTION, yylineno) && check_semantics) {
              printf("Semantic Error: redeclaration of function '%s' at line %d\n", $2, yylineno);
              semantic_errors = 1;
          }
      }
    ;





main_function
    : named_type NAME LEFT_ROUND_BRACKET formal_param_list RIGHT_ROUND_BRACKET 
      {
        SymbolTableEntry *prev_def = symtab.lookup_all_scopes($2);
        if (prev_def) {
        // Function Already Declared
        // Check return type
        if (prev_def->type != string($1) && check_semantics) {
            printf("Semantic Error: return type mismatch in definition of '%s'\n", $2);
            semantic_errors = 1;
        }
        if (prev_def->params_of_func.size() != $4->size() && check_semantics) {
            printf("Semantic Error: parameter count mismatch in '%s'\n", $2);
            semantic_errors = 1;
        }
        else {
            for (size_t i = 0; i < $4->size(); i++) {
                if (prev_def->params_of_func[i].first != (*$4)[i].first && check_semantics) {
                    printf("Semantic Error: parameter type mismatch in '%s'\n", $2);
                    semantic_errors = 1;
                    break;
                }
            }
        }
        }
        else {
        // First time definition
        symtab.insert($2, $1, SymbolKind::FUNCTION, yylineno, *$4);
        }
        symtab.enter_scope();
        for (auto &p : *$4) {
        symtab.insert(p.second, p.first,SymbolKind::PARAMETER,yylineno);
        }
        delete $4;
      }
      LEFT_CURLY_BRACKET optional_local_var_decl_stmt_list statement_list RIGHT_CURLY_BRACKET
      {

        if (strcmp($2, "main") == 0) {
            Sequence_Ast *seq = $9;
            vector<pair<string,string>> params;
            Function_Ast *f = new Function_Ast(string($2), string($1), params, seq, yylineno);
            vector<Function_Ast*> funcs;
            funcs.push_back(f);
            ast_root = new Program_Ast(funcs);
        }
        symtab.exit_scope();
      }
    | named_type NAME LEFT_ROUND_BRACKET RIGHT_ROUND_BRACKET 
      {
        SymbolTableEntry *prev_def = symtab.lookup_all_scopes($2);
        if (prev_def) {
        if (prev_def->type != string($1) && check_semantics) {
            printf("Semantic Error: return type mismatch in definition of '%s'\n", $2);
            semantic_errors = 1;
        }
        if (prev_def->params_of_func.empty() && check_semantics) {
            printf("Semantic Error: parameter count mismatch in '%s'\n", $2);
            semantic_errors = 1;
        }
        }
        else {
            symtab.insert($2, $1, SymbolKind::FUNCTION, yylineno);
        }
        symtab.enter_scope();
      }
      LEFT_CURLY_BRACKET optional_local_var_decl_stmt_list statement_list RIGHT_CURLY_BRACKET
      {
        if (strcmp($2, "main") == 0) {
            Sequence_Ast *seq = $8;
            vector<pair<string,string>> params;
            Function_Ast *f = new Function_Ast(string($2), string($1), params, seq, yylineno);
            vector<Function_Ast*> funcs;
            funcs.push_back(f);
            ast_root = new Program_Ast(funcs);
        }
        symtab.exit_scope();
      }
    ;

formal_param_list
    : formal_param_list COMMA formal_param 
    {
        $1->insert($1->begin(), $3->begin(), $3->end());
        delete $3;
        $$ = $1;
    }
    | formal_param
    {
        $$ = $1;
    }
    ;

formal_param 
    : named_type NAME
    {
        $$ = new vector<pair<string,string>> ();
        $$->push_back({string($1), string($2)});
    }
    ;








optional_local_var_decl_stmt_list
    : var_decl_stmt_list
    | /* empty */
    ;

var_decl_stmt_list
    : var_decl_stmt_list var_decl_stmt
    | var_decl_stmt
    ;

var_decl_stmt
    : named_type var_decl_item_list SEMICOLON
      {
        for (auto name : *$2) {
        if (!symtab.insert(name, $1, SymbolKind::VARIABLE, yylineno) && check_semantics) {
            printf("Semantic Error: redeclaration of variable '%s' at line %d\n",name, yylineno);
            semantic_errors = 1;
        }
        }
        delete $2;
      }
    ;

var_decl_item_list
    : var_decl_item_list COMMA NAME
      {
        $1->push_back($3);
        $$ = $1;
      }
    | NAME
      {
        $$ = new vector<char*>();
        $$->push_back($1);
      }
    ;

named_type
    : INTEGER { $$ = strdup("int"); }
    | FLOAT   { $$ = strdup("float"); }
    | BOOL    { $$ = strdup("bool"); }
    | STRING  { $$ = strdup("string"); }
    | VOID    { $$ = strdup("void"); }
    ;




statement_list
    : statement_list statement {$1->add_statement($2); $$ = $1;}
    | /* empty */              {$$ = new Sequence_Ast();}
    ;

statement
    : assignment_statement { $$ = $1; }
    | print_statement      { $$ = $1; }
    | read_statement       { $$ = $1; }
    ;

assignment_statement
    : NAME ASSIGN_OP expression SEMICOLON
    {
        SymbolTableEntry* sym = symtab.lookup_all_scopes($1);
        if (!sym && check_semantics) {
            printf("Semantic Error: undeclared variable '%s' at line %d\n",$1, yylineno);
            semantic_errors = 1;
            $$ = nullptr;
        }
        else {
            Ast* lhs = new Name_Ast(string($1), sym->type, yylineno);
            $$ = new Assignment_Ast(lhs, $3, yylineno);
        }
    }
    ;

print_statement
    : PRINT expression SEMICOLON
      {
          $$ = new Print_Ast($2, yylineno);
      }
    ;

read_statement
    : READ NAME SEMICOLON
      {
          SymbolTableEntry* sym = symtab.lookup_all_scopes($2);
          if (!sym) {
              printf("Semantic Error: undeclared variable '%s' at line %d\n",$2, yylineno);
              $$ = nullptr;
              semantic_errors = 1;
          } 
          else {
              $$ = new Read_Ast(new Name_Ast(string($2), sym->type, yylineno), yylineno);
          }
      }
    ;

expression
    : expression PLUS expression                             {$$ = new Expression_Ast($1, $3, OP_ADD, yylineno);}
    | expression MINUS expression                            {$$ = new Expression_Ast($1, $3, OP_SUB, yylineno);}
    | expression MULT expression                             {$$ = new Expression_Ast($1, $3, OP_MULT, yylineno);}
    | expression DIV expression                              {$$ = new Expression_Ast($1, $3, OP_DIV, yylineno);}
    | MINUS expression %prec UMINUS                          {$$ = new Uminus_Ast($2, yylineno);}
    | LEFT_ROUND_BRACKET expression RIGHT_ROUND_BRACKET      {$$ = $2;}
    | expression QUESTION_MARK expression COLON expression   {$$ = new Ternary_Ast($1, $3, $5, yylineno);}
    | expression AND expression                              {$$ = new Logical_Ast($1, $3, OP_AND, yylineno);}
    | expression OR expression                               {$$ = new Logical_Ast($1, $3, OP_OR, yylineno);}
    | NOT expression                                         {$$ = new Logical_Not_Ast($2, yylineno);}
    | rel_expression
    | NAME
     {
        const SymbolTableEntry* sym = symtab.lookup_curr_scope($1);
        if (!sym) {
            printf("Semantic Error: undeclared variable '%s' at line %d\n",$1, yylineno);
            $$ = nullptr;
            semantic_errors = 1;
        } 
        else {
            $$ = new Name_Ast(string($1), sym->type, yylineno);
        }
     }
    | INT_VAL { $$ = new Int_Ast($1, yylineno);}
    | FLOAT_VAL {$$ = new Float_Ast($1, yylineno);}
    | STR_CONST {$$ = new String_Ast(std::string($1), yylineno);}
    ;

rel_expression
    : expression LT expression {$$ = new Relational_Ast($1, $3, OP_LT, yylineno);}
    | expression LE expression {$$ = new Relational_Ast($1, $3, OP_LE, yylineno);}
    | expression GT expression {$$ = new Relational_Ast($1, $3, OP_GT, yylineno);}
    | expression GE expression {$$ = new Relational_Ast($1, $3, OP_GE, yylineno);}
    | expression EQ expression {$$ = new Relational_Ast($1, $3, OP_EQ, yylineno);}
    | expression NE expression {$$ = new Relational_Ast($1, $3, OP_NE, yylineno);}
    ;

%%

int yyerror(const char *s) {
    fprintf(stderr, "Parse Error: %s at line %d\n", s, yylineno);
    return 1;
}
