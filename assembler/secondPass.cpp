//
// Created by luizorv on 04/10/16.
//

#include "secondPass.hpp"

SecondPass::SecondPass(map<string, int> labels_map,
                       map<string, pair<int, int> > data_map,
                       ifstream &entrada) {
    file = (&entrada);
    labels = labels_map;
    data = data_map;
}
