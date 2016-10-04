#include <iostream>
#include <fstream>
#include "firstPass.h"

using namespace std;

int main( int argc, char *argv[] ){
    ifstream entrada;
    map<string, pair<int, int> > data;

    entrada.open(argv[1]);
    if( !entrada.is_open() ){ //erro
        return(1);
    }
    FirstPass firstPass(entrada);
    firstPass.doFirstPass();
    data = firstPass.getData();
    labels = firstPass.getLabels();
    //readfile(entrada); //primeira passada (mapeia as lables)
    entrada.close();

    return 0;
}
