#include "instruction_queue.hh"

void InstructionQueueDS :: createInstructionQ() {
    Instruction_Queue_Entry inst;
    
    // ST Addr:20 Data:10
    inst.valid = true;
    inst.opcode = STORE;
    inst.address = 20;
    inst.data = 10;
    inst.id = 0;
    
    instructionQ.push(inst);

    // LD Addr: 30
    inst.opcode = LOAD;
    inst.address = 30;
    inst.data = 10;
    inst.id = 1;

    instructionQ.push(inst);

    // ST Addr:40 Data: 14
    inst.opcode = STORE;
    inst.address = 40;
    inst.data = 10;
    inst.id = 2;

    instructionQ.push(inst);

}

bool InstructionQueueDS :: isEmpty(){
    return instructionQ.empty();
}

Instruction_Queue_Entry InstructionQueueDS :: getEntry(){
    return instructionQ.front();
}

void InstructionQueueDS :: popInstQ(){
    instructionQ.pop();
}

void InstructionQueueDS :: increment_cycle_count(){
    cycleCount += 1;
}