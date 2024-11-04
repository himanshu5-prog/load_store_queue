#ifndef __INSTRUCTION_QUEUE__
#define __INSTRUCTION_QUEUE__

#include "../Common/common.hh"
#include "../Entry/entry.hh"
#include <queue>

class InstructionQueueDS{
    std :: queue <Instruction_Queue_Entry> instructionQ;
    bool cycleCount;

    public:
        InstructionQueueDS(){};
        void createInstructionQ();
        bool isEmpty();

        Instruction_Queue_Entry getEntry();
        void popInstQ();
        void increment_cycle_count();

};

#endif