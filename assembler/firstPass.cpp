//
// Created by luizorv on 04/10/16.
//

#include <map>
#include <fstream>
#include <stdlib.h>
#include "firstPass.hpp"

using namespace std;

FirstPass::FirstPass( ifstream &entrada ){
    file = (&entrada);
}

void FirstPass::doFirstPass(void){

    const int JUMP_2_ADDRS = 2;

    LabelTable lab;
    DataTable dat;
    int pc = 0, found_exit = false, value, byte_size;
    unsigned long current, espaco, tamanho = 0;
    string name, line, posic;

    while( getline( (*file), line ) ){
        if(line[0] != ';'){
            
            current = line.find_first_not_of(" 	 "); // jump spaces, get first character index
            if( isalpha(line[current]) ){

                name = line.substr(current, line.size());
                espaco = name.find_first_of("\t: ");
                name = name.substr(0, espaco);

                /* wait for exit call
                 * .data step */
                if(found_exit){

                    current = line.find_first_of("0123456789");
                    line = line.substr( current, line.size() );
                    byte_size = atoi( line.c_str() );

                    posic = line.substr(2 , line.size());
                    //posic = posic.substr(0, posic.find_first_of(" 	 "));
                    value = atoi( posic.c_str() );

                    dat.label = name;
                    dat.byte_size = byte_size;
                    dat.value = value;
                    dat.memPos = pc;

                    data.push_back(dat);

                    pc += JUMP_2_ADDRS;
                }

                /* instruction count memory addrs
                 * watch exit call
                 * */
                if(!found_exit){
                    pc += JUMP_2_ADDRS;
                    if(name.compare("exit") == 0){
                        //  finish instruction step -> jump to .data step
                        found_exit = true;
                    }
                }
            }
            /* found label */
            if(line[current] == '_'){
                tamanho =   line.find(':');
                lab.label = line.substr(0, tamanho);
                lab.memPos = pc;
                labels.push_back(lab);
                //labels[name] = pc; 	// label map
                pc += JUMP_2_ADDRS;
            }
        }
    }
}

vector< DataTable > FirstPass::getData(){
    return data;
};

vector< LabelTable > FirstPass::getLabels(){
    return labels;
};