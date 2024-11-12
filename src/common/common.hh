#ifndef _COMMON_
#define _COMMON_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#define Load_Queue_Size 8
#define Store_Queue_Size 8
#define QueueSize 8 // Max size of load-store queue


enum Opcode {
    NONE = 0,
    LOAD,
    STORE
};

//Currently, not using '_TO_' stages now
enum Stage {
    NOT_VALID=0,
    //Stages of load instruction
    LD_DISPATCH,
    LD_ADDR_GEN,
    LD_DISPATCH_TO_ADDR_GEN,
    LD_EXECUTE,
    LD_ADDRGEN_TO_EXECUTE,
    LD_RETIRE,
    LD_EXECUTE_TO_RETIRE,
    //Stages of store instruction
    ST_DISPATCH,
    ST_DISPATCH_TO_EXECUTE,
    ST_EXECUTE,
    ST_RETIRE,
    ST_EXECUTE_TO_RETIRE
};

namespace Load_Pipeline_Latency {
    const int DISPATCH_TO_ADDR_GEN = 1;
    const int ADDRGEN_TO_EXECUTE = 1;
    const int EXECUTE_TO_RETIRE_MISS = 20;
    const int EXECUTE_TO_RETIRE_HIT = 4;
}

namespace Store_Pipeline_Latency {
    const int DISPATCH_TO_EXECUTE = 2;
    const int EXECUTE_TO_RETIRE_MISS = 20;
    const int EXECUTE_TO_RETIRE_HIT = 2;
}

struct SystemStats{

    int storeInstructionCount;
    int loadInstructionCount;
    int totalCycleCount;

    SystemStats() {
        storeInstructionCount = 0;
        loadInstructionCount = 0;
        totalCycleCount = 0;
    } 
};

struct LoadStoreQueueStats {
    int storeMemoryAccess;
    int loadMemoryAccess;
    int storeToLoadForwarding;
    int storeInstructionRetired;
    int loadInstructionRetired;

    LoadStoreQueueStats(){
        storeMemoryAccess = 0;
        loadMemoryAccess = 0;
        storeToLoadForwarding = 0;
        storeInstructionRetired = 0;
        loadInstructionRetired = 0;
    }

}; 

std :: string convertStage2String(Stage stage);
std :: string convertOpcode2String(Opcode op);
std :: vector < std :: string> split_sentence(std::string s);
#endif

