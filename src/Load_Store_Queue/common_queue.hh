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
    LoadStoreQueueStats stats;

    public:
        CommonQueue();
        bool isEmpty();
        bool isFull();
        void addToQueue(int addr, int data, int id, Opcode op);
        void removeEntry();

        void setDebugMode();
        bool canAddToEntry();

        SimpleCacheEntry getRetireEntry();

        void incrementCycleCount();

        //Function related to entries in queue

        // Function to update entries stages
        void UpdateEntry();
        int updateLoadEntry(int load_entry_id, int addr);
        void updateAllLoadEntry();

        //Check if older store is present with matching address for a load
        bool foundPrevStore(int id, int addr);

        //Retire instruction at the front of buffer
        void retireEntryHead();
        

        void printAllEntry();
        void printStats();

        

};
#endif