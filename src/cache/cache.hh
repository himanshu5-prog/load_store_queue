#ifndef __CACHE__
#define __CACHE__
#include "../Entry/entry.hh"
#include <iostream>

class Cache {
    Cache_Entry entry[16];
    int cycleCount;
    public:
        Cache();
        void addEntry ( Cache_Entry ce);
        void removeEntry(int address);
        bool isCacheHit(int address);

        void increment_cycle_count();

};

#endif