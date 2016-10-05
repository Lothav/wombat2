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


void SecondPass::insertOnFile(string line, unsigned long current){

    string register_binary, label;
    unsigned long long int register_decimal;

    current = line.find_first_not_of("\t ");
    line = line.substr(current, line.size());
    current = line.find_first_not_of("\t ");

        /*  is register  */
    if( line[current] == "R"[0] ){
        register_binary = bitset<3>( line[current+1] ).to_string(); //to binary
        mif_out << register_binary;

        current = line.find_first_of("\t ");
        line = line.substr(current, line.size());
        this->insertOnFile(line, current);
    }
        /*  is label  */
    else if( line[current] == "_"[0] ){
        line = line.substr(current, line.size());
        current = line.find_first_of("\t; ");

        label = line.substr(0, current);

        for(int i = 0; i < labels.size(); i++){
            if(labels[i].label == label){
                register_binary = bitset<8>( labels[i].memPos ).to_string(); //to binary
                mif_out << register_binary;
                break;
            }
        }
        current = line.find_first_of("\t; ");
        line = line.substr(current, line.size());
        this->insertOnFile(line, current);
    }
        /*  is .data  */
    else if( isalpha(line[current]) ){

        //this->insertOnFile(line, current);
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
                name = line.substr(0, current);

                /*   Write Opcode  (5 bits)  */
                opcode = Wombat2IS::getInstructionCode(name);
                op_code_binary = bitset<8>( opcode ).to_string(); //to binary
                mif_out << op_code_binary;
                if(opcode == 7 || opcode == 15 ||opcode == 17 || opcode == 22|| opcode == 21){
                    mif_out << '000';
                }

                line = line.substr(current, line.size());
                insertOnFile(line, current);

                mif_out << "\n";
            }
        }
    }
    mif_out << "END;";
    mif_out.close();
}
