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
    bool ready;
};

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

void printLSQ_Entry( LSQ_Entry e);
void printCache_Entry ( Cache_Entry e);

struct Instruction_Queue_Entry{
    bool valid;
    Opcode opcode;
    int address;
    int data;
    int id;
};
#endif