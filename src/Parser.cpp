#include "Parser.h"
#include <iostream>
#include <string>
#include <algorithm>

using std::istream;
using std::string;
using std::regex;
using std::runtime_error;
using std::to_string;
using std::ios;

namespace HackAssembler {
    namespace {
        const regex A_COMMAND_PATTERN{R"(^@([[:alpha:]_:\.\$][:\w\.\$]*|[[:digit:]]+)$)", regex::nosubs | regex::optimize};
        const regex L_COMMAND_PATTERN{R"(^\([[:alpha:]_:\.\$][:\w\.\$]*\)$)", regex::nosubs | regex::optimize};
        const regex C_COMMAND_PATTERN{"^((M|D|MD|A|AM|AD|AMD)=(0|-?1|[-!]?[ADM]|D[+-][1AM]|D[\\|&][AM]|[AM][+-]1|[AM]-D)(;(JGT|JEQ|JGE|JLT|JNE|JLE|JMP))?|"
                                      "(0|-?1|[-!]?[ADM]|D[+-][1AM]|D[\\|&][AM]|[AM][+-]1|[AM]-D);(JGT|JEQ|JGE|JLT|JNE|JLE|JMP))$", regex::nosubs | regex::optimize};

        void trimWhiteSpaceAndComments(string& line) {
            line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
            line = line.substr(0, line.find("//"));
        }

        bool hasValidCommandSyntax(const string& line) {
            return regex_match(line, A_COMMAND_PATTERN) || regex_match(line, L_COMMAND_PATTERN) || regex_match(line, C_COMMAND_PATTERN);
        }
    }

    void Parser::updateNextCommand() {
        string line;

        while(inputStream_ && line.empty()) {
            getline(inputStream_, line);
            trimWhiteSpaceAndComments(line);
            ++currentLineNr_;
        }

        nextCommand_ = line;
    }

    void Parser::advance() {
        currentCommand_ = nextCommand_;

        if(syntaxChecking_ && !hasValidCommandSyntax(currentCommand_)) {
            throw runtime_error("Invalid syntax in line " + to_string(currentLineNr_) + ": " + currentCommand_);
        }

        updateNextCommand();
    }

    void Parser::reset() {
        inputStream_.clear();
        inputStream_.seekg(0, ios::beg);
        currentCommand_.clear();
        currentLineNr_ = 0;
        syntaxChecking_ = true;
        updateNextCommand();
    }

    Parser::CommandType Parser::commandType() const {
        switch(currentCommand_.front()) {
            case '@':
                return CommandType::A;
            case '(':
                return CommandType::L;
            default:
                return CommandType::C;
        }
    }

    string Parser::symbol() const {
        if(commandType() == CommandType::A) {
            return currentCommand_.substr(1);
        }

        return currentCommand_.substr(1, currentCommand_.size() - 2);
    }

    string Parser::dest() const {
        const auto eqIndex = currentCommand_.find('=');
        return eqIndex != string::npos ? currentCommand_.substr(0, eqIndex) : "null";
    }

    string Parser::comp() const {
        const auto eqIndex = currentCommand_.find('=');
        const auto startIndex = eqIndex != string::npos ? eqIndex + 1 : 0;

        const auto semiColIndex = currentCommand_.find(';');
        const auto compLength = semiColIndex != string::npos ? semiColIndex - startIndex : string::npos;

        return currentCommand_.substr(startIndex, compLength);
    }

    string Parser::jump() const {
        const auto semiColIndex = currentCommand_.find(';');
        return semiColIndex != string::npos ? currentCommand_.substr(semiColIndex + 1) : "null";
    }
}
