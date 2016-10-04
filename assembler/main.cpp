#include <iostream>
#include <fstream>
#include "firstPass.h"

using namespace std;

int main( int argc, char *argv[] ){

    ifstream file;
    map<string, pair<int, int> > data;
    map<string, int> labels;

    file.open(argv[1]);
    if( !file.is_open() ){  return(ENOENT); } /* No such file or directory */

    FirstPass firstPass(file);
    firstPass.doFirstPass();
    data = firstPass.getData();
    labels = firstPass.getLabels();

    file.close();

    return 0;
}
