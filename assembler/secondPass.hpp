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

private:
    ifstream *file;
    ofstream mif_out;
    vector< DataTable > data;
    vector< LabelTable > labels;
    int count_bits;
public:
    SecondPass(  vector< DataTable > data, vector< LabelTable > labels, ifstream &file, string name_out);
    void doSecondPass();
    void insertOnFile(string line, unsigned long current);
};

#endif //ASSEMBLER_SECONDPASS_H
