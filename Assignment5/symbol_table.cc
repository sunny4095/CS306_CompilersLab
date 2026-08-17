#include "symbol_table.hh"

SymbolTable::SymbolTable() {
    param_offset_counter = 8;
    local_offset_counter = -8;
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

void SymbolTable::reset_offsets() {
    param_offset_counter = 8; 
    local_offset_counter = 0;
}

int SymbolTable::get_prologue_sp_allocation() {
    // According to your stack layout, total SP decrement matches the absolute 
    // value of the current local offset counter, plus 4 extra bytes for alignment/padding.
    // E.g., main (1 var) -> local_counter ends at -8 -> (-(-8)) + 4 = 12 bytes
    // E.g., f1 (return val + 1 var) -> local_counter ends at -12 -> (-(-12)) + 4 = 16 bytes
    return (-local_offset_counter) + 8;
}

bool SymbolTable::insert(const string &n, const string &t, SymbolKind k, int l, vector<pair<string,string>> params, bool d) {
    if (scopes.empty()) return false;
    auto& current_scope = scopes.back();
    if (current_scope.find(n) != current_scope.end()) {
        return false;
    }
    if (k != SymbolKind::FUNCTION) {
        SymbolTableEntry *existing = lookup_all_scopes(n);
        if (existing && existing->sym_kind == SymbolKind::FUNCTION) return false;
    }
    if (k == SymbolKind::VARIABLE && scopes.size() == 1) {
        global_vars.push_back(n);
    }

    int current_offset = 0;
    int size = 4; // Default to 4 bytes for ints
    if (t == "float") size = 8; // If your floats map to MIPS double-precision (.d instructions), they need 8 bytes!
     
    if (scopes.size() > 1) {
        if (k == SymbolKind::PARAMETER) {
            current_offset = param_offset_counter;
            param_offset_counter += size;     
        } 
        else if (k == SymbolKind::VARIABLE) {
            local_offset_counter -= size;   // For negative offsets, subtract the size FIRST so the variable   
            current_offset = local_offset_counter; // has enough room extending upwards to the previous variable.
        }
    }

    current_scope[n] = SymbolTableEntry(n,t,k,l,params,d, current_offset, size);
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

void SymbolTable::save_current_scope(const string& func_name) {
    if (scopes.size() > 1) { // Ensure we are actually in a local scope
        preserved_func_scopes[func_name] = scopes.back();
        func_sp_allocations[func_name] = get_prologue_sp_allocation();
    }
}

unordered_map<string, SymbolTableEntry> SymbolTable::get_func_scope(const string& func_name) {
    if (preserved_func_scopes.find(func_name) == preserved_func_scopes.end()) {
        cerr << func_name << " does not exist in preserved func scopes\n";
        exit(1);
    }
    return preserved_func_scopes[func_name];
}

int SymbolTable::get_func_sp_allocation(const string& func_name) {
    if (func_sp_allocations.find(func_name) == func_sp_allocations.end()) {
        cerr << func_name << " does not exist in func_sp_allocations\n";
        exit(1);
    }
    return func_sp_allocations[func_name];
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
