#include "symbol_table.hh"

// Constructor: start with global scope
SymbolTable::SymbolTable() {
    enter_scope();
}

void SymbolTable::enter_scope() {
    unordered_map<string, SymbolTableEntry> new_scope;
    scopes.push_back(new_scope);
}

void SymbolTable::exit_scope() {
    if (!scopes.empty()) {
        scopes.pop_back();
    }
}

bool SymbolTable::insert(const string &n, const string &t, SymbolKind k, int l, vector<pair<string,string>> params, bool d) {
    if (scopes.empty()) return false;
    auto& current_scope = scopes.back();
    if (current_scope.find(n) != current_scope.end()) {
        return false;
    }
    current_scope[n] = SymbolTableEntry(n,t,k,l,params,d);
    return true;
}

SymbolTableEntry* SymbolTable::lookup_all_scopes(const string& name) {
    // Search from innermost scope outward
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto found = it->find(name);
        if (found != it->end()) {
            return &found->second;
        }
    }
    return nullptr;
}

SymbolTableEntry* SymbolTable::lookup_curr_scope(const string& name) {
    // Search from innermost scope outward
    if (scopes.empty()) return nullptr;
    auto &curr_scope = scopes.back();
    if (curr_scope.find(name) == curr_scope.end()) return nullptr;
    return &curr_scope[name];
}

void SymbolTable::print() {
    std::cout << "\n========== SYMBOL TABLE ==========\n";

    int scope_level = 0;
    for (const auto& scope : scopes) {
        std::cout << "Scope " << scope_level++ << ":\n";
        for (const auto& [name, sym] : scope) {
            std::cout << "  " << sym.name
                      << " : " << sym.type;

            switch (sym.sym_kind) {
                case SymbolKind::VARIABLE:
                    std::cout << " (var)";
                    break;
                case SymbolKind::FUNCTION:
                    std::cout << " (func)";
                    break;
                case SymbolKind::PARAMETER:
                    std::cout << " (param)";
                    break;
            }

            std::cout << " [line " << sym.line << "]\n";
        }
    }

    std::cout << "=================================\n";
}
