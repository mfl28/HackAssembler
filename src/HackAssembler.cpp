#include "HackAssembler.h"
#include "AssemblerEngine.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

using std::ifstream;
using std::ofstream;
using std::runtime_error;
using std::string;
using std::stringstream;
using std::cerr;
namespace fs = std::filesystem;

namespace HackAssembler {
    int assemble(const string& inputPathName) {
        const fs::path inputPath{inputPathName};

        if(inputPath.extension() != ".asm") {
            cerr << "Assembler error: Invalid file extension: Expected \".asm\" but was " << inputPath.extension() << '.';
            return -1;
        }

        if(ifstream inputFile{inputPath}; inputFile) {
            stringstream outputBuffer;
            AssemblerEngine engine{inputFile, outputBuffer};

            try {
                engine.execute();
            }
            catch(const runtime_error& e) {
                cerr << "Assembler error: " << e.what();
                return -1;
            }

            const auto outputPath{fs::path{inputPath}.replace_extension(".hack")};

            if(ofstream outputFile{outputPath}; outputFile) {
                outputFile << outputBuffer.str();
            }
            else {
                cerr << "Assembler error: Could not create output-file " << outputPath << '.';
                return -1;
            }
        }
        else {
            cerr << "Assembler error: Could not open file " << inputPath << '.';
            return -1;
        }

        return 0;
    }
}

