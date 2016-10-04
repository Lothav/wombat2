//
// Created by luizorv on 04/10/16.
//

#ifndef ASSEMBLER_WOMBAT2IS_H
#include <fstream>
#include <map>

#define ASSEMBLER_WOMBAT2IS_H

using namespace std;

class Wombat2IS {
public:
    static size_t getInstructionCode(string code);
private:
    string codes[26] = {"exit", "loadi", "storei", "add", "subtract",
                       "multiply", "divide", "jump", "jmpz", "jmpn", "move",
                       "load", "store", "loadc", "clear", "moveSp", "slt",
                       "call", "loadSp", "storeSp", "ret", "loadRa", "storeRa"
                               "addi", "sgt", "seq", "jmpp"};
};


#endif //ASSEMBLER_WOMBAT2IS_H
