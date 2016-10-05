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
                       ifstream &entrada,
                       string name_out) {
    file = (&entrada);
    labels = labels_map;
    data = data_map;

    /* get name from file input (without extension) to set output .mif and open it */
    mif_out.open (name_out.substr(0, name_out.find_first_of(".")) + ".mif");
}


void SecondPass::insertOnFile(string line, unsigned long current){

    string register_binary, label;
    int i;
    current = line.find_first_not_of("\t ");
    if(current > line.size()) return;
    line = line.substr(current, line.size());
    current = line.find_first_not_of("\t ");
    if(current > line.size()) return;

        /*  is register  */
    if( line[current] == 'R' ){
        register_binary = bitset<3>( line[current+1] ).to_string(); //to binary
        mif_out << register_binary;

        current = line.find_first_of("\t ");
        if(current > line.size()) return;
        line = line.substr(current, line.size());
        this->insertOnFile(line, current);
    }
        /*  is label  */
    else if( line[current] == '_' ){
        line = line.substr(current, line.size());
        current = line.find_first_of("\t; ");
        if(current > line.size()) return;
        label = line.substr(0, current);
        for(i = 0; i < labels.size(); i++){
            if(labels[i].label == label){
                register_binary = bitset<8>( labels[i].memPos ).to_string(); //to binary
                mif_out << register_binary;
                break;
            }
        }
        current = line.find_first_of("\t; ");
        if(current > line.size()) return;
        line = line.substr(current, line.size());
        this->insertOnFile(line, current);
    }
        /*  is .data  */
    else if( isalpha(line[current]) ){

        if(line[current] == 'I' && line[current+1] == 'O'){
            mif_out << "11111110";
        } else {
            line = line.substr(current, line.size());
            current = line.find_first_of("\t; ");
            if(current > line.size()) return;
            label = line.substr(0, current);

            for( i = 0; i < data.size(); i++ ){
                if(data[i].label == label){
                    register_binary = bitset< 8 >( data[i].memPos ).to_string(); //to binary
                    mif_out << register_binary;
                    break;
                }

            }
        }
        current = line.find_first_of("\t; ");
        if(current > line.size()) return;
        line = line.substr(current, line.size());
        this->insertOnFile(line, current);

    }
}

void SecondPass::doSecondPass(){

    string op_code_binary, line, name;
    size_t opcode;
    unsigned long current, gap;


    mif_out << "DEPTH = 256\n";
    mif_out << "WIDTH = 16\n";
    mif_out << "ADDRESS_RADIX = HEX\n";
    mif_out << "DATA_RADIX = BIN\n";
    mif_out << "CONTENT\n";
    mif_out << "BEGIN\n\n";

    while( getline( (*file), line ) ){
        if(line[0] != ';') {
            current = line.find_first_not_of("\t ");

            if( line[current] == '_'){
                current = line.find_first_of("\t ");
                line = line.substr(current, line.size());
                current = line.find_first_not_of("\t ");
                line = line.substr(current, line.size());
            }

            if( isalpha(line[current]) ){
                current = line.find_first_not_of("\t ");
                line = line.substr(current, line.size());
                current = line.find_first_of("\t: ");
                name = line.substr(0, current);

                /*   Write Opcode  (5 bits)  */
                opcode = Wombat2IS::getInstructionCode(name);
                op_code_binary = bitset<5>( opcode ).to_string(); //to binary
                mif_out << op_code_binary;
                if(opcode == 7 || opcode == 15 ||opcode == 17 || opcode == 22|| opcode == 21){
                    mif_out << "000";
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
