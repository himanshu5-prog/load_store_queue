#ifndef __COMMON_QUEUE_
#define __COMMON_QUEUE_
#include <iostream>
#include <deque>
#include <cassert>
#include "../Entry/entry.hh"

class CommonQueue{
    std :: deque <LSQ_Entry> entry;
    std :: string instanceName;
    int cycleCount;
    bool debugMode;

    public:
        CommonQueue();
        bool isEmpty();
        bool isFull();
        void addToQueue(int addr, int data, int id, Opcode op);
        void removeEntry();

        void setDebugMode();
        bool canAddToEntry();

        void UpdateEntry();
        SimpleCacheEntry getRetireEntry();

        void incrementCycleCount();
        int updateLoadEntry(int load_entry_id, int addr);
        void updateAllLoadEntry();
        bool foundPrevStore(int id, int addr);

        void retireEntryHead();
        void printAllEntry();

        

};
#endif