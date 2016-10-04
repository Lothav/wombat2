#include <iostream>
#include <map>
#include <fstream>
#include <stdlib.h>

using namespace std;

//primeira passada
void readfile(ifstream &entrada){

    int pc = 0, flag = 0, b, a;
    unsigned long atual, espaco, tamanho = 0;
    string nome, linha, posic;
    pair <int, int> memoria;

    map<string, int> lables; //mapa dos lables
    map<string, pair<int, int> > data; //mapa dos nomes da memoria
    map<int, int> mem; //mapa da memoria <bytes, num>

    while( getline( entrada, linha ) ){
        if(linha[0] != ';'){
            atual = linha.find_first_not_of(" 	 ");	//remove os espa?os e tabs

            if( isalpha(linha[atual]) ){

                nome = linha.substr(atual, linha.size());
                espaco = nome.find_first_of(" ");
                nome = nome.substr(0, espaco);

                if(flag == 0){
                    //achou uma instrucao
                    pc += 2;
                    if(nome.compare("exit") == 0){
                        //terminou a parte das instrucoes
                        flag = 1;
                    }
                }
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
            }
            if(linha[atual] == '_'){	//leu uma lable
                tamanho = linha.find(':');
                nome = linha.substr(0, tamanho);
                lables[nome] = pc; 	//mapeia o lable
                pc += 2;
            }
        }
    }
}

int main( int argc, char *argv[] ){
    ifstream entrada;
    entrada.open(argv[1]);
    if( !entrada.is_open() ){ //erro
        return(1);
    }
    readfile(entrada); //primeira passada (mapeia as lables)
    entrada.close();

    return 0;
}
