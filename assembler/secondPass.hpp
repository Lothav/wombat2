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
    string line;

public:
    SecondPass(  vector< DataTable > data, vector< LabelTable >  labels,ifstream &file);
    void doSecondPass();
};


#endif //ASSEMBLER_SECONDPASS_H
