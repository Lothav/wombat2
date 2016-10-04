//
// Created by luizorv on 04/10/16.
//


#ifndef ASSEMBLER_FIRSTPASS_H
#include <iostream>
#include <map>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "tables.h"

#define ASSEMBLER_FIRSTPASS_H
using namespace std;

class FirstPass {

private:

    const int JUMP_2_ADDRS = 2;

    int pc = 0, found_exit = false, value, byte_size;
    unsigned long current, espaco, tamanho = 0;
    string name, line, posic;
    pair <int, int> memoria;
    ifstream *file;

    LabelTable lab;
    DataTable dat;

    vector< LabelTable > labels; //mapa dos lables
    vector< DataTable > data;   //mapa dos nomes da memoria

public:
    FirstPass (ifstream &file);
    void doFirstPass(void);
    vector< DataTable > getData();
    vector< LabelTable  >  getLabels();
};
#endif //ASSEMBLER_FIRSTPASS_H
