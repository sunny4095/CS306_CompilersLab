#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;

enum class SymbolKind {
    VARIABLE, FUNCTION, PARAMETER,
};

enum class Type {
    INT_TYPE, FLOAT_TYPE, VOID_TYPE, STRING_TYPE,
};

struct SymbolTableEntry {
    string name;
    string type;
    SymbolKind sym_kind;
    int line;
    vector<pair<string,string>> params_of_func;
    bool is_defined = false;

    SymbolTableEntry() = default;
    SymbolTableEntry(const string &n, const string &t, SymbolKind k, int l, vector<pair<string,string>> params = {}, bool d = false) : name(n), type(t), sym_kind(k), line(l), params_of_func(params), is_defined(d) {}
};

class SymbolTable {
private :
    vector<unordered_map<string, SymbolTableEntry>> scopes;
public :
    SymbolTable();
    void enter_scope();
    void exit_scope();
    bool insert(const string &n, const string &t, SymbolKind k, int l, vector<pair<string,string>> params = {}, bool d = false);
    SymbolTableEntry* lookup_all_scopes(const string& name);
    SymbolTableEntry* lookup_curr_scope(const string& name);
    void print();
};