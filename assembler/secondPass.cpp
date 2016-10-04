//
// Created by luizorv on 04/10/16.
//

#include <vector>
#include "secondPass.hpp"
using namespace std;

SecondPass::SecondPass(vector< DataTable > data_map,
                       vector< LabelTable  >  labels_map,
                       ifstream &entrada) {
    file = (&entrada);
    labels = labels_map;
    data = data_map;
}

void SecondPass::doSecondPass(){
    ofstream mif_out;
    mif_out.open ("mif_out.mif");
    while( getline( (*file), line ) ){
        if(line[0] != ';') {

        }
    }
}
