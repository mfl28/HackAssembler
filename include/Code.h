#pragma once
#include <bitset>
#include <string>

namespace HackAssembler::Code {

    /**
     * \brief Gets the binary code of the destination-mnemonic.
     * \param mnemonic One of 8 possible dest-mnemonics defined in the Hack assembly language.
     * \return The binary code (3 bits)
     */
    std::bitset<3> dest(const std::string& mnemonic);

    /**
    * \brief Gets the binary code of the computation-mnemonic.
    * \param mnemonic One of 28 possible comp-mnemonics defined in the Hack assembly language.
    * \return The binary code (7 bits)
    */
    std::bitset<7> comp(const std::string& mnemonic);

    /**
    * \brief Gets the binary code of the jump-instruction-mnemonic.
    * \param mnemonic One of 8 possible jump-mnemonics defined in the Hack assembly language.
    * \return The binary code (3 bits)
    */
    std::bitset<3> jump(const std::string& mnemonic);
}
