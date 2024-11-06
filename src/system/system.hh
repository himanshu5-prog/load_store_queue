#ifndef __SYSTEM__
#define __SYSTEM__

#include <iostream>
#include <cassert>
#include "../Load_Store_Queue/load_store_queue.hh"
#include "../Load_Store_Queue/common_queue.hh"
#include "../Instruction_Queue/instruction_queue.hh"
class System {
    //SimpleCache cache;
    InstructionQueueDS instQ_DS;
    CommonQueue loadStoreQueue;
    int cycleCount;
    int maxCycleCount;
    bool debugMode;
    std :: string instructionFile;

    public:
        System();
        void setDebugMode();
        void run();
        void issue();
        void increment_cycle_count();
        void setMaxCycleCount(int x) { maxCycleCount = x;}
        bool allBufferEmpty();
        void setInstructionFile(std :: string f);
        void readInstructionFile();
};

#endif