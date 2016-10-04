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
    int pc = 0, found_exit = false, b, a;
    unsigned long atual, espaco, tamanho = 0;
    string nome, linha, posic;
    pair <int, int> memoria;
    ifstream *file;

    map<string, int> labels; //mapa dos lables
    map<string, pair<int, int> > data; //mapa dos nomes da memoria

public:
    FirstPass (ifstream &entrada);
    void doFirstPass(void);
    map<string, pair<int, int> > getData();
    map<string, int> getLabels();
};
#endif //ASSEMBLER_FIRSTPASS_H
