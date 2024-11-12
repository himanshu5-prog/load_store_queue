#ifndef _ENTRY_
#define _ENTRY_
#include <iostream>
#include "../common/common.hh"

struct LSQ_Entry {
    bool valid;
    Opcode opcode;
    int address;
    int data;
    int age;
    int startCycle;
    int endCycle;
    Stage stage;
    bool ready; // Not using this field now.
};

//Not using the struct------
struct Cache_Entry{
    bool valid;
    Opcode opcode;
    int address;
    int data;
    bool dirty;
};

struct SimpleCacheEntry {
    int address;
    int data;
};
//----------------------------

void printLSQ_Entry( LSQ_Entry e);
void printCache_Entry ( Cache_Entry e);

//Instruction queue entry
struct Instruction_Queue_Entry{
    bool valid;
    Opcode opcode;
    int address;
    int data;
    int id;
};
//------------------------------
#endif