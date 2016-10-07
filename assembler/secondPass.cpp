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


void SecondPass::insertSecondLineBitsOnFile(string line, unsigned long current){

    string register_binary, label;
    int i;
    current = line.find_first_not_of("\t ");
    if(current > line.size()) return;
    line = line.substr(current, line.size());
    current = line.find_first_not_of("\t ");
    if(current > line.size()) return;

    /*  is register  */
    if( line[current] == 'R' ){
        register_binary = bitset<3>( (unsigned long long int)line[current+1] ).to_string(); //to binary
        mif_out << register_binary;
        count_bits += 3;
        if(count_bits == 8) {
            mif_out << "\n";
        }
        current = line.find_first_of("\t ");
        if(current > line.size()) return;
        line = line.substr(current, line.size());
        this->insertSecondLineBitsOnFile(line, current);
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
                count_bits += 8;
                break;
            }
        }
        current = line.find_first_of("\t; ");
        if(current > line.size()) return;
        line = line.substr(current, line.size());
        this->insertSecondLineBitsOnFile(line, current);
    }
        /*  is .data  */
    else if( isalpha(line[current]) ){

        if(line[current] == 'I' && line[current+1] == 'O'){
            mif_out << "11111110";
            count_bits += 8;
        } else {
            line = line.substr(current, line.size());
            current = line.find_first_of("\t; ");
            if(current < line.size()) {
                label = line.substr(0, current);
            }else{
                label = line;
            }

            for( i = 0; i < data.size(); i++ ){
                if(data[i].label == label){
                    register_binary = bitset< 8 >( data[i].memPos ).to_string(); //to binary
                    mif_out << register_binary;
                    count_bits += 8;
                    break;
                }
            }
        }
        current = line.find_first_of("\t; ");
        if(current > line.size()) return;
        line = line.substr(current, line.size());
        this->insertSecondLineBitsOnFile(line, current);

    }
}

void SecondPass::doSecondPass(){

    string op_code_binary, line, name;
    size_t opcode;
    unsigned long current;

    mif_out << "DEPTH = 256\n";
    mif_out << "WIDTH = 16\n";
    mif_out << "ADDRESS_RADIX = HEX\n";
    mif_out << "DATA_RADIX = BIN\n";
    mif_out << "CONTENT\n";
    mif_out << "BEGIN\n\n";

    while( getline( (*file), line ) ){
        count_bits = 0;
        if(line[0] != ';') {
            current = line.find_first_not_of("\t ");

            /*  here, we just ignore labels instructions */
            jumpLabelIns(current, &line);

            if( isalpha(line[current]) ){
                /*  got a instruction  */
                current = line.find_first_not_of("\t ");
                line = line.substr(current, line.size());
                current = line.find_first_of("\t: ");
                name = line.substr(0, current);

                if( line.find(".data") != string::npos ){
                    /*  line has substring .data  */
                    dotDataIns( name );
                } else {
                    /*   write opcode  (5 bits)  */
                    opcode = Wombat2IS::getInstructionCode( name );
                    op_code_binary = bitset<5>( opcode ).to_string(); //to binary
                    mif_out << op_code_binary;
                    count_bits += 5;

                    /*  instructions that has first reg (3bits) equals zero  */
                    insertZerosFirstRegIns( opcode );
                    /*  at this point, we have first line instruction (8bits)  */

                    /*  lets get/insert the second one:  */
                    line = line.substr( current, line.size() );
                    insertSecondLineBitsOnFile( line, current );

                    /*   complete with zeros instruction that not fill 16 bits   */
                    completeWithZeros();
                }
                mif_out << "\n";
            }
        }
    }
    mif_out << "END;";
    mif_out.close();
}

void SecondPass::completeWithZeros(){
    while (  count_bits < 16 ){
        mif_out << '0';
        count_bits++;
        if(count_bits == 8) { mif_out << "\n"; }
    }
}

void SecondPass::insertZerosFirstRegIns(size_t opcode){
    if(opcode == Wombat2IS::JUMP || opcode == Wombat2IS::MOVESP ||
       opcode == Wombat2IS::CALL || opcode == Wombat2IS::STORERA || opcode == Wombat2IS::ADDI){
        mif_out << "000";
        count_bits += 3;
        mif_out << "\n";
    }
}

void SecondPass::dotDataIns(string name){
    int i, j;
    string data_value;
    for( i = 0; i < data.size(); i++ ){
        if(data[i].label == name){
            //@TODO bitset variable
            data_value = bitset<  2*8 >( data[i].value ).to_string(); //to binary
            for(j = 0; j < 2*8; j++){
                if( !(j % 8) && j ){ mif_out << "\n"; }
                mif_out << data_value[j];
            }
            break;
        }
    }
}

void SecondPass::jumpLabelIns( unsigned long current, string* line ) {
    if( (*line)[current] == '_'){
        current = (*line).find_first_of("\t ");
        (*line) = (*line).substr(current, (*line).size());
        current = (*line).find_first_not_of("\t ");
        (*line) = (*line).substr(current, (*line).size());
    }
}