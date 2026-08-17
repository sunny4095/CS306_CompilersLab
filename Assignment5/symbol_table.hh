#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;

enum class SymbolKind {
    VARIABLE,
    FUNCTION, 
    PARAMETER,
};

struct SymbolTableEntry {
    string name;
    string type;
    SymbolKind sym_kind;
    int line;
    vector<pair<string,string>> params_of_func;
    bool is_defined = false;
    int offset;
    int size;

    SymbolTableEntry() = default;
    SymbolTableEntry(const string &n, const string &t, SymbolKind k, int l, vector<pair<string,string>> params = {}, bool d = false, int off = 0, int sz = 4) : name(n), type(t), sym_kind(k), line(l), params_of_func(params), is_defined(d), offset(off), size(sz) {}
};

class SymbolTable {
private :
    vector<unordered_map<string, SymbolTableEntry>> scopes;
    int param_offset_counter;
    int local_offset_counter;
    unordered_map<string, unordered_map<string, SymbolTableEntry>> preserved_func_scopes;
    unordered_map<string, int> func_sp_allocations;
    
public :
    vector<string> decl_func;
    vector<string> global_vars;
    SymbolTable();
    void enter_scope();
    void exit_scope();
    bool insert(const string &n, const string &t, SymbolKind k, int l, vector<pair<string,string>> params = {}, bool d = false);
    SymbolTableEntry* lookup_all_scopes(const string& name);
    SymbolTableEntry* lookup_curr_scope(const string& name);
    void print();
    void reset_offsets();
    int get_prologue_sp_allocation();
    void save_current_scope(const string& func_name);
    unordered_map<string, SymbolTableEntry> get_func_scope(const string& func_name);
    int get_func_sp_allocation(const string& func_name);
};
