#include <iostream>
#include <fstream>
#include "firstPass.hpp"
#include "secondPass.hpp"

using namespace std;

int main( int argc, char *argv[] ){

    ifstream file;
    vector< DataTable > data;
    vector< LabelTable  >labels;
    file.open(argv[1]);
    if( !file.is_open() ){  return(ENOENT); } /* No such file or directory */

    FirstPass firstPass(file);
    firstPass.doFirstPass();
    labels = firstPass.getLabels(); /* Get label table */
    data = firstPass.getData(); /* Get .data table */

    SecondPass secondPass(data, labels, file);
    secondPass.doSecondPass();

    file.close();

    return 0;
}
