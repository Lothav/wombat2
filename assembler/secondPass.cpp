//
// Created by luizorv on 04/10/16.
//

#include <vector>
#include <bitset>
#include <cstring>
#include <stdlib.h>
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


void insertOnFile(string line, unsigned long current, ofstream mif_out){

    string register_binary;

    line = line.substr(current, line.size());
    current = line.find_first_not_of("\t ");

    if( line[current] == "R"[0] ){
        line = line.substr(current, line.size());
        current = line.find_first_not_of("\t ");
        register_binary = bitset<8>( atoi(line[current]) ).to_string(); //to binary
    }
}

void SecondPass::doSecondPass(string name_out){
    ofstream mif_out;
    string op_code_binary, line, name;
    size_t opcode;
    unsigned long current, gap;

    /* get name from file input (without extension) to set output .mif and open it */
    mif_out.open (name_out.substr(0, name_out.find_first_of(".")) + ".mif");

    mif_out << "DEPTH = 256\n";
    mif_out << "WIDTH = 16\n";
    mif_out << "ADDRESS_RADIX = HEX\n";
    mif_out << "DATA_RADIX = BIN\n";
    mif_out << "CONTENT\n";
    mif_out << "BEGIN\n\n";

    while( getline( (*file), line ) ){
        if(line[0] != ';') {
            current = line.find_first_not_of("\t ");
            if( isalpha(line[current]) ){
                line = line.substr(current, line.size());
                current = line.find_first_of("\t: ");
                name = name.substr(0, current);

                /*   Write Opcode  (5 bits)  */
                opcode = Wombat2IS::getInstructionCode(name);
                op_code_binary = bitset<8>( opcode ).to_string(); //to binary
                mif_out << op_code_binary;

                insertOnFile(line, current,mif_out);

                mif_out << "\n";
            }
        }
    }
    mif_out << "END;";
}
