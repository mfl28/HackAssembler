#pragma once
#include <unordered_map>
#include <string>

namespace HackAssembler {
    class SymbolTable {
    public:
        /**
         * \brief Creates a new symbol-table filled with the predefined symbols
         * SP, LCL, ARG, THIS, THAT, R0-R15, SCREEN, KBD as well as their respective addresses.
         */
        SymbolTable();

        /**
         * \brief Adds a new (symbol, address) pair to the table or updates an existing symbol's address.
         * \param symbol
         * \param address
         */
        void addLabelSymbol(const std::string& symbol, unsigned address) { table_.insert_or_assign(symbol, address); }

        /**
         * \brief Adds a new variable-symbol to the table using a running address counter that starts at
         * address 16 (just after the addresses of the predefined symbols R0-R15). Must only be used if
         * the symbol-table does not already contain a variable with the same name.
         * \param name
         */
        void addVariableSymbol(const std::string& name) { table_.emplace(name, currentNewVariableAddress_++); }

        /**
         * \brief Allows to check if a symbol is contained in the symbol-table
         * \param symbol
         * \return True if symbol exists in the table, false otherwise
         */
        bool contains(const std::string& symbol) const { return table_.find(symbol) != table_.cend(); }

        /**
         * \brief Retrieves the address of a symbol. The provided symbol must exist in the table.
         * \param symbol
         * \return
         */
        unsigned getAddress(const std::string& symbol) const { return table_.at(symbol); }

    private:
        std::unordered_map<std::string, unsigned> table_;
        unsigned currentNewVariableAddress_{16};
    };
}

