#ifndef __SYSTEM__
#define __SYSTEM__

#include <iostream>
#include <cassert>
#include "../Load_Store_Queue/common_queue.hh"
#include "../Instruction_Queue/instruction_queue.hh"
class System {
    //SimpleCache cache;
    InstructionQueueDS instQ_DS;
    CommonQueue loadStoreQueue;

    // Current cycle count
    int cycleCount;

    int maxCycleCount;

    // When enabled detailed log file will be generated
    bool debugMode;

    // instruction file containing the instructions
    std :: string instructionFile;

    // System stats
    SystemStats stats;

    public:
        System();
        void setDebugMode();
        
        // Run function which calls functions corresponding to pipeline stage
        void run();

        // Function for issue stage
        void issue();

        //Function to increment cycle count
        void increment_cycle_count();
        void setMaxCycleCount(int x) { maxCycleCount = x;}

        //Check if all buffers are empty so that simulation can be stopped
        bool allBufferEmpty();

        // Set instruction file
        void setInstructionFile(std :: string f);

        //Function to print stats
        void printStats();

        // Function to update load-store queue
        void updateLoadStoreQueue();

        // Function to retire instruction
        void retireInstruction();
};

#endif