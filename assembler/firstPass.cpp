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
    while( getline( (*file), line ) ){
        if(line[0] != ';'){
            
            current = line.find_first_not_of(" 	 "); // jump spaces, get first character index
            if( isalpha(line[current]) ){

                name = line.substr(current, line.size());
                espaco = name.find_first_of(" ");
                name = name.substr(0, espaco);

                /* wait for exit call
                 * .data step */
                if(found_exit){
                    line = line.substr( (espaco+1), line.size() );
                    current = line.find_first_of("0123456789");
                    a = atoi( line.c_str() );

                    posic = line.substr(( current + JUMP_2_ADDRS ), line.size());
                    posic = posic.substr(0, posic.find_first_of(" 	 "));
                    b = atoi( posic.c_str() );

                    dat.label = name;
                    dat.byte_size = a;
                    dat.value = b;

                    data.push_back(dat);

                    //memoria = make_pair( a, b); // < bytes , numero >
                    //[name] = memoria; // < name , memoria >
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
                tamanho = line.find(':');
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