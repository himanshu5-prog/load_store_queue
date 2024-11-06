#include "entry.hh"

void printCache_Entry(Cache_Entry e){
    std :: cout << "Printing Cache Entry\n";
    std :: cout << "valid: " << e.valid << ", opcode: " << e.opcode << ", address: " << e.address 
    << " data: " << e.data << ", dirty: " << e.dirty << "\n";
}

void printLSQ_Entry ( LSQ_Entry e){
    std :: cout << "Printing LSQ entry\n";
    std :: cout << "valid: " << e.valid << ", opcode: " << convertOpcode2String (e.opcode) << ", addr: " << e.address <<  ", data: " << e.data << ", age: " << e.age
    << ", startCycle: " << e.startCycle << ", endCycle: " << e.endCycle << ", stage: " << convertStage2String(e.stage) << "\n";
}