#include <iostream>
#include <string>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <utility>

using namespace std;

//primeira passada
void readfile(ifstream &entrada){	 
	int pc = 0, tamanho =0, atual, espaco, flag = 0, b, a;
	map<string, int> lables; //mapa dos lables
	map<string, pair<int, int> > data; //mapa dos nomes da memoria
	map<int, int>mem; //mapa da memoria <bytes, num>
	string nome, linha, posic;
	pair <int, int> memoria;
	while( getline( entrada, linha ) ){
  		if(linha[0] != ';'){
			atual = linha.find_first_not_of(" 	 ");	//remove os espa?os e tabs
			if((linha[atual] >64 && linha[atual] <91) ||(linha[atual] > 96 && linha[atual] < 123)){
				nome = linha.substr(atual, linha.size());	
				espaco = nome.find_first_of(" ");
				nome = nome.substr(0, espaco);			
				if(flag == 1){
					//achou um .data
					linha = linha.substr((espaco+1), linha.size());
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
			if(linha[atual] == 95){	//leu uma lable
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
