//
// Created by luizorv on 04/10/16.
//

#ifndef ASSEMBLER_SECONDPASS_H

#include <iostream>
#include <map>
#include <fstream>
#include <stdlib.h>
#include "tables.h"

#define ASSEMBLER_SECONDPASS_H

using namespace std;

class SecondPass {

    vector< DataTable > data;
    vector< LabelTable > labels;
    ifstream *file;
    string line, name, posic;;

    size_t opcode;

    unsigned long current, espaco, tamanho = 0;

public:
    SecondPass(  vector< DataTable > data, vector< LabelTable >  labels,ifstream &file);
    void doSecondPass(string name_out);
};


#endif //ASSEMBLER_SECONDPASS_H
