//
// Created by luizorv on 04/10/16.
//

#ifndef ASSEMBLER_SECONDPASS_H

#include <iostream>
#include <map>
#include <fstream>
#include <stdlib.h>

#define ASSEMBLER_SECONDPASS_H

using namespace std;

class SecondPass {

    map<string, int> labels; //mapa dos lables
    map<string, pair<int, int> > data; //mapa dos nomes da memoria
    ifstream *file;

public:
    SecondPass(map<string, int> labels,  map<string, pair<int, int> > data, ifstream &file);
    void doSecondPass();
};


#endif //ASSEMBLER_SECONDPASS_H
