#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <cstdio>
#include "ast.hh"
extern int yyparse();
extern int yylex();
extern FILE *yyin;
extern int yylineno;
extern Ast* ast_root;
int print_tokens = 0;
int check_semantics = 1;
int semantic_errors = 0;
int ast_error = 0;
FILE *fp = nullptr;
using namespace std;

string new_file_name(const string &filename, const string &extension) {
    return filename + extension;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: sclp [OPTION...] [FILE]\n";
        return 1;
    }

    bool show_tokens = false;
    bool show_ast = false;
    bool sa_scan = false;
    bool sa_parse = false;
    string input_file;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--show-tokens") == 0) show_tokens = true;
        else if (strcmp(argv[i], "--show-ast") == 0) show_ast = true;
        else if (strcmp(argv[i], "--sa-scan") == 0) sa_scan = true;
        else if (strcmp(argv[i], "--sa-parse") == 0) sa_parse = true;
        else input_file = argv[i];
    }

    if (input_file.empty()) {
        cerr << "Usage: sclp [OPTION...] [FILE]\n";
        return 1;
    }

    yyin = fopen(input_file.c_str(), "r");
    if (!yyin) return 1;

    if (sa_scan) {
        check_semantics = 0;
        if (show_tokens) {
            string tok_file = new_file_name(input_file, ".toks");
            fp = fopen(tok_file.c_str(), "w");
            if (!fp) return 1;
            print_tokens = 1;
        }
        while (yylex());
        fclose(yyin);
        if (show_tokens) fclose(fp);
        return 0;
    }

    if (sa_parse) {
        check_semantics = 0;
        if (show_tokens) {
            string tok_file = new_file_name(input_file, ".toks");
            fp = fopen(tok_file.c_str(), "w");
            if (!fp) return 1;
            print_tokens = 1;
        }
        int parse_status = yyparse();
        if (parse_status != 0) {
            fclose(yyin);
            fclose(fp);
            return 1;
        }
        fclose(yyin);
        if (show_tokens) fclose(fp);
        return 0;
    }

    if (show_tokens) {
        string tok_file = new_file_name(input_file, ".toks");
        fp = fopen(tok_file.c_str(), "w");
        if (!fp) return 1;
        print_tokens = 1;
    }

    int parse_status = yyparse();
    if (parse_status != 0) {
        fclose(yyin);
        if (show_tokens) fclose(fp);
        return 1;
    }

    if (ast_root) {
        if (!ast_root->check_ast()) {
            cerr << "Semantic Errors Detected\n";
            fclose(yyin);
            if (show_tokens) fclose(fp);
            return 1;
        }
        if (show_ast) {
            string ast_file = new_file_name(input_file, ".ast");
            ofstream out(ast_file);
            if (!out) {
                cerr << "Cannot Open Ast File to Print\n";
                return 1;
            }
            ast_root->print(out);
            out.close();
        }
    }
    fclose(yyin);
    if (show_tokens) fclose(fp);
    return 0 || semantic_errors || ast_error;
}