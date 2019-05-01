#pragma once
#include <string>

namespace HackAssembler {
    /**
     * \brief Translates a valid input .hack file containing Hack assembly commands
     * into binary code and writes the result to a .asm output-file with the same name.
     * \param inputPathName The path of the input-file
     * \return 0 if the resulting binary code was successfully written to the
     * output-file, otherwise -1 (will write error message to cerr)
     */
    int assemble(const std::string& inputPathName);
}
