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
    static const int
            EXIT = 0,
            LOADI = 1,
            STOREI = 2,
            ADD = 3,
            SUBTRACT = 4,
            MULTIPLY = 5,
            DIVIDE = 6,
            JUMP = 7,
            JMPZ = 8,
            JMPN = 9,
            MOVE = 10,
            LOAD = 11,
            STORE = 12,
            LOADC = 13,
            CLEAR = 14,
            MOVESP = 15,
            SLT = 16,
            CALL = 17,
            LOADSP = 18,
            STORESP = 19,
            RET = 20,
            LOADRA = 21,
            STORERA = 22,
            ADDI = 23,
            SGT = 24,
            SEQ = 25,
            JMPP = 26;

private:
    string codes[27] =
            {"exit", "loadi", "storei", "add", "subtract",
             "multiply", "divide", "jump", "jmpz", "jmpn", "move",
             "load", "store", "loadc", "clear", "moveSp", "slt",
             "call", "loadSp", "storeSp", "ret", "loadRa", "storeRa",
             "addi", "sgt", "seq", "jmpp"};
};


#endif //ASSEMBLER_WOMBAT2IS_H
