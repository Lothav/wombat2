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

    int pc = 0, flag = 0, b, a;
    unsigned long atual, espaco, tamanho = 0;
    string nome, linha, posic;
    pair <int, int> memoria;
    ifstream *file;

    map<string, int> lables; //mapa dos lables
    map<string, pair<int, int> > data; //mapa dos nomes da memoria
    map<int, int> mem; //mapa da memoria <bytes, num>

public:
    FirstPass (ifstream &entrada);
    void doFirstPass(void);
    map<int, int> getMem(){
        return mem;
    };
};
#endif //ASSEMBLER_FIRSTPASS_H
