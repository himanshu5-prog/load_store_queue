#ifndef _COMMON_
#define _COMMON_

#include <iostream>
#define Load_Queue_Size 8
#define Store_Queue_Size 8
#define QueueSize 8


enum Opcode {
    NONE = 0,
    LOAD,
    STORE
};

enum Stage {
    NONE=0,
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
    const int EXECUTE_TO_RETIRE_MISS = 10;
    const int EXECUTE_TO_RETIRE_HIT = 2;
}

namespace Store_Pipeline_Latency {
    const int DISPATCH_TO_EXECUTE = 2;
    const int EXECUTE_TO_RETIRE_MISS = 12;
    const int EXECUTE_TO_RETIRE_HIT = 2;
}

std :: string convertStage2String(Stage stage);

#endif

