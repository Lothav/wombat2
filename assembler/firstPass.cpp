//
// Created by luizorv on 04/10/16.
//

#include <map>
#include <fstream>
#include <stdlib.h>
#include "firstPass.hpp"

using namespace std;

FirstPass::FirstPass(ifstream &entrada){
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
                    a = atoi(line.c_str());

                    posic = line.substr(( current + JUMP_2_ADDRS ), line.size());
                    posic = posic.substr(0, posic.find_first_of(" 	 "));
                    b = atoi(posic.c_str());
                    
                    memoria = make_pair( a, b); // < bytes , numero >
                    data[name] = memoria; // < name , memoria >
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
                name = line.substr(0, tamanho);
                labels[name] = pc; 	// label map
                pc += JUMP_2_ADDRS;
            }
        }
    }
}

map<string, pair<int, int> > FirstPass::getData(){
    return data;
};

map<string, int> FirstPass::getLabels(){
    return labels;
};