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
    ifstream *file;
    vector< LabelTable > labels; //mapa dos lables
    vector< DataTable > data;   //mapa dos nomes da memoria

public:
    FirstPass (ifstream &file);
    void doFirstPass(void);
    vector< DataTable > getData();
    vector< LabelTable  >  getLabels();
};
#endif //ASSEMBLER_FIRSTPASS_H
