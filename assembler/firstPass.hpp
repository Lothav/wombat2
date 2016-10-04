//
// Created by luizorv on 04/10/16.
//


#ifndef ASSEMBLER_FIRSTPASS_H
#include <iostream>
#include <map>
#include <fstream>
#include <stdlib.h>

#define ASSEMBLER_FIRSTPASS_H
using namespace std;

class FirstPass {

private:

    const int JUMP_2_ADDRS = 2;

    int pc = 0, found_exit = false, b, a;
    unsigned long current, espaco, tamanho = 0;
    string name, line, posic;
    pair <int, int> memoria;
    ifstream *file;

    map<string, int> labels; //mapa dos lables
    map<string, pair<int, int> > data; //mapa dos nomes da memoria

public:
    FirstPass (ifstream &file);
    void doFirstPass(void);
    map<string, pair<int, int> > getData();
    map<string, int> getLabels();
};
#endif //ASSEMBLER_FIRSTPASS_H
