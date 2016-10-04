//
// Created by luizorv on 04/10/16.
//

#include <vector>
#include <bitset>
#include "secondPass.hpp"
#include "wombat2IS.hpp"

using namespace std;

SecondPass::SecondPass(vector< DataTable > data_map,
                       vector< LabelTable > labels_map,
                       ifstream &entrada) {
    file = (&entrada);
    labels = labels_map;
    data = data_map;
}

void SecondPass::doSecondPass(string name_out){
    ofstream mif_out;
    string op_code_binary, line, name;
    size_t opcode;
    unsigned long current, gap;

    /* get name from file input (without extension) to set output .mif*/
    mif_out.open (name_out.substr(0, name_out.find_first_of(".")) + ".mif");

    while( getline( (*file), line ) ){
        if(line[0] != ';') {
            current = line.find_first_not_of(" 	 ");
            if( isalpha(line[current]) ){
                name = line.substr(current, line.size());
                gap = name.find_first_of("\t: ");
                name = name.substr(0, gap);

                /*   Write Opcode  (5 bits)  */
                opcode = Wombat2IS::getInstructionCode(name);
                op_code_binary = bitset<8>( opcode ).to_string(); //to binary
                mif_out << op_code_binary;



                mif_out << "\n";
            }
        }
    }
}
