#include "AssemblerEngine.h"
#include <bitset>
#include <string>
#include "Code.h"

using std::string;
using std::bitset;

namespace HackAssembler {
    namespace {
        bool isInteger(const string& input) {
            return all_of(input.cbegin(), input.cend(), isdigit);
        }

        template<size_t L1, size_t L2>
        void setBitSetAt(std::bitset<L1>& input, size_t startPos, const bitset<L2>& val) {
            const auto end = std::min<size_t>(L1, L2 + startPos);

            for(auto i = startPos; i < end; ++i) {
                input[i] = val[i - startPos];
            }
        }
    }

    void AssemblerEngine::execute() {
        parseLabels();
        parser_.reset();
        // syntax-checking was already turned on in the first pass.
        parser_.setSyntaxChecking(false);
        generateBinaryCodeOutput();
    }

    void AssemblerEngine::parseLabels() {
        unsigned programCounter{};

        while(parser_.hasMoreCommands()) {
            parser_.advance();

            if(parser_.commandType() == Parser::CommandType::L) {
                symbolTable_.addLabelSymbol(parser_.symbol(), programCounter);
            }
            else {
                ++programCounter;
            }
        }
    }

    void AssemblerEngine::generateBinaryCodeOutput() {
        while(parser_.hasMoreCommands()) {
            parser_.advance();
            if(parser_.commandType() != Parser::CommandType::L) {
                outputStream_ << getCurrentCommandAsBinaryCode() << '\n';
            }
        }
    }

    bitset<16> AssemblerEngine::getCurrentCommandAsBinaryCode() {
        bitset<16> result;

        if(parser_.commandType() == Parser::CommandType::A) {
            const auto currentSymbol = parser_.symbol();

            if(symbolTable_.contains(currentSymbol)) {
                result = {symbolTable_.getAddress(currentSymbol)};
            }
            else if(isInteger(currentSymbol)) {
                result = {stoul(currentSymbol)};
            }
            else {
                symbolTable_.addVariableSymbol(currentSymbol);
                result = {symbolTable_.getAddress(currentSymbol)};
            }
        }
        else {
            result.set();
            setBitSetAt(result, 0, Code::jump(parser_.jump()));
            setBitSetAt(result, 3, Code::dest(parser_.dest()));
            setBitSetAt(result, 6, Code::comp(parser_.comp()));
        }

        return result;
    }
}

