#include "HackAssembler.h"
#include <iostream>

using std::cerr;
using std::flush;

int main(int argc, char* argv[]) {
    if(argc == 2) {
        return HackAssembler::assemble(argv[1]);
    }

    cerr << "Wrong number of arguments. Usage: HackAssembler filename.asm." << flush;
    return  -1;
}

