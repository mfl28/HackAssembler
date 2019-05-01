#include "Code.h"
#include <unordered_map>

using std::bitset;
using std::string;
using std::unordered_map;

namespace HackAssembler {
    namespace {
        const unordered_map<string, bitset<3>> DEST_TO_CODE{
            { "null", bitset<3>{"000"} },
            { "M",    bitset<3>{"001"} },
            { "D",    bitset<3>{"010"} },
            { "MD",   bitset<3>{"011"} },
            { "A",    bitset<3>{"100"} },
            { "AM",   bitset<3>{"101"} },
            { "AD",   bitset<3>{"110"} },
            { "AMD",  bitset<3>{"111"} }
        };

        const unordered_map<string, bitset<3>> JUMP_TO_CODE{
            { "null", bitset<3>{"000"} },
            { "JGT",  bitset<3>{"001"} },
            { "JEQ",  bitset<3>{"010"} },
            { "JGE",  bitset<3>{"011"} },
            { "JLT",  bitset<3>{"100"} },
            { "JNE",  bitset<3>{"101"} },
            { "JLE",  bitset<3>{"110"} },
            { "JMP",  bitset<3>{"111"} }
        };

        const unordered_map<string, bitset<7>> COMP_TO_CODE{
            { "0",   bitset<7>{"0101010"} },
            { "1",   bitset<7>{"0111111"} },
            { "-1",  bitset<7>{"0111010"} },
            { "D",   bitset<7>{"0001100"} },
            { "A",   bitset<7>{"0110000"} },
            { "!D",  bitset<7>{"0001101"} },
            { "!A",  bitset<7>{"0110001"} },
            { "-D",  bitset<7>{"0001111"} },
            { "-A",  bitset<7>{"0110011"} },
            { "D+1", bitset<7>{"0011111"} },
            { "A+1", bitset<7>{"0110111"} },
            { "D-1", bitset<7>{"0001110"} },
            { "A-1", bitset<7>{"0110010"} },
            { "D+A", bitset<7>{"0000010"} },
            { "D-A", bitset<7>{"0010011"} },
            { "A-D", bitset<7>{"0000111"} },
            { "D&A", bitset<7>{"0000000"} },
            { "D|A", bitset<7>{"0010101"} },
            { "M",   bitset<7>{"1110000"} },
            { "!M",  bitset<7>{"1110001"} },
            { "-M",  bitset<7>{"1110011"} },
            { "M+1", bitset<7>{"1110111"} },
            { "M-1", bitset<7>{"1110010"} },
            { "D+M", bitset<7>{"1000010"} },
            { "D-M", bitset<7>{"1010011"} },
            { "M-D", bitset<7>{"1000111"} },
            { "D&M", bitset<7>{"1000000"} },
            { "D|M", bitset<7>{"1010101"} }
        };
    }

    namespace Code {
        bitset<3> dest(const string& mnemonic) { return DEST_TO_CODE.at(mnemonic); }
        bitset<7> comp(const string& mnemonic) { return COMP_TO_CODE.at(mnemonic); }
        bitset<3> jump(const string& mnemonic) { return JUMP_TO_CODE.at(mnemonic); }
    }
}
