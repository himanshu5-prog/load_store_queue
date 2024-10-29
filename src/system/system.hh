#ifndef __SYSTEM__
#define __SYSTEM__

#include <iostream>
#include <cassert>
#include "../Cache/cache.hh"
#include "../Load_Store_Queue/load_store_queue.hh"
#include "../Instruction_Queue/instruction_queue.hh"
class System {
    Cache cache;
    Load_Store_Queue loadQ;
    Load_Store_Queue storeQ;
    InstructionQueueDS instQ_DS;
    int cycleCount;
    int maxCycleCount;

    public:
        System();
        void run();
        void issue();
};

#endif