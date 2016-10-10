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
    string file_name_out;
    vector< DataTable > data;
    vector< LabelTable > labels;
    int count_bits, stack_pointer;
    void writeOnFinalFile();

    /*      utils    */
    void completeWithZeros();
    void insertZerosFirstRegIns(size_t opcode);
    void dotDataIns(string name);
    void jumpLabelIns( unsigned long current, string* line );
    void insertSecondLineBitsOnFile(string line, unsigned long current);
public:
    SecondPass(  vector< DataTable > data, vector< LabelTable > labels, ifstream &file, string name_out);
    void doSecondPass();
};

#endif //ASSEMBLER_SECONDPASS_H
