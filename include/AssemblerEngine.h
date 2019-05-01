#pragma once
#include "Parser.h"
#include "SymbolTable.h"
#include <bitset>

namespace HackAssembler {
    class AssemblerEngine {
    public:
        /**
         * \brief Creates a new AssemblerEngine object
         * \param inputStream The stream to be parsed for Hack commands
         * \param outputStream The stream to which the translated binary code will be written
         */
        AssemblerEngine(std::istream& inputStream, std::ostream& outputStream) : parser_{inputStream}, outputStream_{outputStream} {}

        /**
         * \brief Performs the translation of Hack language commands obtained from the input-stream 
         * and writes the resulting binary code to the output-stream.
         */
        void execute();
    private:
        Parser parser_;
        SymbolTable symbolTable_;
        std::ostream& outputStream_;

        void parseLabels();
        void generateBinaryCodeOutput();
        std::bitset<16> getCurrentCommandAsBinaryCode();
    };
}
