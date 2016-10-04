//
// Created by luizorv on 04/10/16.
//

#include "wombat2IS.hpp"

using namespace std;

size_t findIndex(  string codes[], size_t size, string value ) {
    size_t index = 0;
    while ( index < size && codes[index].compare(value) != 0 ) ++index;
    return ( index == size ? -1 : index );
}

size_t Wombat2IS::getInstructionCode(string code){
    Wombat2IS womb;
    return findIndex(womb.codes, 26, code);
};

