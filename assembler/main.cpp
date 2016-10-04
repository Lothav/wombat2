#include <iostream>
#include <fstream>
#include "firstPass.hpp"

using namespace std;

int main( int argc, char *argv[] ){

    ifstream file;
    map<string, pair<int, int> > data;
    map<string, int> labels;

    file.open(argv[1]);
    if( !file.is_open() ){  return(ENOENT); } /* No such file or directory */

    FirstPass firstPass(file);
    firstPass.doFirstPass();
    data = firstPass.getData(); /* Get .data table */
    labels = firstPass.getLabels(); /* Get label table */

    file.close();

    return 0;
}
