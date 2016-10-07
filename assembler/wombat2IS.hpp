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
            RET = 19,
            LOADRA = 20,
            STORERA = 21,
            ADDI = 22,
            SGT = 23,
            SEQ = 24,
            JMPP = 25;

private:
    string codes[27] =
            {"exit", "loadi", "storei", "add", "subtract",
             "multiply", "divide", "jump", "jmpz", "jmpn", "move",
             "load", "store", "loadc", "clear", "moveSp", "slt",
             "call", "loadSp", "storeSp", "ret", "loadRa", "storeRa",
             "addi", "sgt", "seq", "jmpp"};
};


#endif //ASSEMBLER_WOMBAT2IS_H
