//
// Created by luizorv on 04/10/16.
//

#include <map>
#include <fstream>
#include <stdlib.h>
#include "firstPass.h"
#include <iostream>

using namespace std;


FirstPass::FirstPass(ifstream &entrada){
    file = (&entrada);
}

void FirstPass::doFirstPass(void){
    while( getline( (*file), linha ) ){
        if(linha[0] != ';'){
            atual = linha.find_first_not_of(" 	 ");	//remove os espa?os e tabs

            if( isalpha(linha[atual]) ){

                nome = linha.substr(atual, linha.size());
                espaco = nome.find_first_of(" ");
                nome = nome.substr(0, espaco);
                if(flag == 1){
                    //achou um .data
                    linha = linha.substr( (espaco+1), linha.size() );
                    atual = linha.find_first_of("0123456789");
                    a = atoi(linha.c_str());

                    posic = linha.substr((atual+2), linha.size());
                    posic = posic.substr(0, posic.find_first_of(" 	 "));
                    b = atoi(posic.c_str());
                    memoria = make_pair( a, b); // < bytes , numero >
                    data[nome] = memoria; // < nome , memoria >
                }
                if(flag == 0){
                    //achou uma instrucao
                    pc += 2;
                    if(nome.compare("exit") == 0){
                        //terminou a parte das instrucoes
                        flag = 1;
                    }
                }
            }
            if(linha[atual] == '_'){	//leu uma lable
                tamanho = linha.find(':');
                nome = linha.substr(0, tamanho);
                labels[nome] = pc; 	//mapeia o lable
                pc += 2;
            }
        }
    }
}

map<string, pair<int, int> > FirstPass::getData(){
    return data;
};

map<string, int> FirstPass::getLabels(){
    return labels;
};