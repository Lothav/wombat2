//
// Created by tracksale on 10/4/16.
//

#ifndef ASSEMBLER_TABLES_H
#define ASSEMBLER_TABLES_H

using namespace std;

class LabelTable{
public:
    string label;
    int memPos;
};

class DataTable{
public:
    string label;
    int byte_size;
    int memPos;
    int value;
};

#endif //ASSEMBLER_TABLES_H
