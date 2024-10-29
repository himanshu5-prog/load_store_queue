#include "system.hh"

System :: System (){
    cycleCount = 0;
    loadQ.setInstancename("Load Queue");
    storeQ.setInstancename("Store Queue");
    instQ_DS.createInstructionQ();

    cycleCount = 0;
    maxCycleCount = 100;
}

void System :: run(){

}

void System :: issue (){
    
    if (!instQ_DS.isEmpty()){
        Instruction_Queue_Entry instEntry;
        instEntry = instQ_DS.getEntry();
        assert(instEntry.valid);
        if (instEntry.opcode == LOAD && loadQ.canAddEntry()){
            // Adding entry to load queue
            LSQ_Entry e;
            e.valid = instEntry.valid;
            e.opcode = LOAD;
            e.data = instEntry.data;
            e.ready = false;
            e.age = instEntry.id;
            e.address = instEntry.address;
            e.startCycle = cycleCount;
            e.stage = LD_DISPATCH;
            e.endCycle = cycleCount + Load_Pipeline_Latency::DISPATCH_TO_ADDR_GEN;

            loadQ.addToQueue(e);
            instQ_DS.popInstQ();

        } else if (instEntry.opcode == STORE && storeQ.canAddEntry()){
            //Adding entry to store queue
            LSQ_Entry e;
            e.valid = instEntry.valid;
            e.opcode = STORE;
            e.data = instEntry.data;
            e.ready = false;
            e.age = instEntry.id;
            e.address = instEntry.address;
            e.startCycle = cycleCount;
            e.stage = ST_DISPATCH;
            e.endCycle = cycleCount + Store_Pipeline_Latency::DISPATCH_TO_EXECUTE;

            storeQ.addToQueue(e);
            instQ_DS.popInstQ();
        }
    }
}