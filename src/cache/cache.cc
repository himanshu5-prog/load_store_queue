#include "cache.hh"

Cache::Cache(){
    cycleCount = 0;
}

void Cache :: addEntry( Cache_Entry ce){
    int addr;
    int index;
    addr = ce.address;
    index = addr & 0xF;

    entry[index] = ce;

}

void Cache :: removeEntry(int addr){
    int index;
    
    index = addr & 0xF;
    entry[index].valid = false;
}

bool Cache :: isCacheHit(int address){
    int index;
    index = address & 0xF;

    if (entry[index].valid){
        return true;
    } else {
        return false;
    }
}

void Cache :: increment_cycle_count(){
    cycleCount += 1;
}