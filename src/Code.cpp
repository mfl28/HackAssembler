#include "Code.h"
#include <unordered_map>

using std::bitset;
using std::string;
using std::unordered_map;

namespace HackAssembler {
    namespace {
        const unordered_map<string, bitset<3>> DEST_TO_CODE{
            { "null", bitset<3>{0b000} },
            { "M",    bitset<3>{0b001} },
            { "D",    bitset<3>{0b010} },
            { "MD",   bitset<3>{0b011} },
            { "A",    bitset<3>{0b100} },
            { "AM",   bitset<3>{0b101} },
            { "AD",   bitset<3>{0b110} },
            { "AMD",  bitset<3>{0b111} }
        };

        const unordered_map<string, bitset<3>> JUMP_TO_CODE{
            { "null", bitset<3>{0b000} },
            { "JGT",  bitset<3>{0b001} },
            { "JEQ",  bitset<3>{0b010} },
            { "JGE",  bitset<3>{0b011} },
            { "JLT",  bitset<3>{0b100} },
            { "JNE",  bitset<3>{0b101} },
            { "JLE",  bitset<3>{0b110} },
            { "JMP",  bitset<3>{0b111} }
        };

        const unordered_map<string, bitset<7>> COMP_TO_CODE{
            { "0",   bitset<7>{0b0101010} },
            { "1",   bitset<7>{0b0111111} },
            { "-1",  bitset<7>{0b0111010} },
            { "D",   bitset<7>{0b0001100} },
            { "A",   bitset<7>{0b0110000} },
            { "!D",  bitset<7>{0b0001101} },
            { "!A",  bitset<7>{0b0110001} },
            { "-D",  bitset<7>{0b0001111} },
            { "-A",  bitset<7>{0b0110011} },
            { "D+1", bitset<7>{0b0011111} },
            { "A+1", bitset<7>{0b0110111} },
            { "D-1", bitset<7>{0b0001110} },
            { "A-1", bitset<7>{0b0110010} },
            { "D+A", bitset<7>{0b0000010} },
            { "D-A", bitset<7>{0b0010011} },
            { "A-D", bitset<7>{0b0000111} },
            { "D&A", bitset<7>{0b0000000} },
            { "D|A", bitset<7>{0b0010101} },
            { "M",   bitset<7>{0b1110000} },
            { "!M",  bitset<7>{0b1110001} },
            { "-M",  bitset<7>{0b1110011} },
            { "M+1", bitset<7>{0b1110111} },
            { "M-1", bitset<7>{0b1110010} },
            { "D+M", bitset<7>{0b1000010} },
            { "D-M", bitset<7>{0b1010011} },
            { "M-D", bitset<7>{0b1000111} },
            { "D&M", bitset<7>{0b1000000} },
            { "D|M", bitset<7>{0b1010101} }
        };
    }

    namespace Code {
        bitset<3> dest(const string& mnemonic) { return DEST_TO_CODE.at(mnemonic); }
        bitset<7> comp(const string& mnemonic) { return COMP_TO_CODE.at(mnemonic); }
        bitset<3> jump(const string& mnemonic) { return JUMP_TO_CODE.at(mnemonic); }
    }
}
