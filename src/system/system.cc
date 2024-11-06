#include "system.hh"

System :: System (){
    cycleCount = 0;
    instQ_DS.createInstructionQ();
    cycleCount = 0;
    maxCycleCount = 100;
    debugMode = false;
}

void System :: run(){
    //int currentCycleCount;
    for (int currentCycleCount = 0; currentCycleCount < maxCycleCount; ++currentCycleCount){

        if (debugMode){
            std :: cout << "System:: run(): Cycle : " << cycleCount << "\n";
            std :: cout << " Pre-processing entry: \n";
            loadStoreQueue.printAllEntry();
        }


        loadStoreQueue.retireEntryHead();
        loadStoreQueue.updateAllLoadEntry();
        loadStoreQueue.UpdateEntry();
        issue();

        if (allBufferEmpty()){
            break;
        }
        increment_cycle_count();

    }
}

void System :: issue (){
    
    if (!instQ_DS.isEmpty()){
        Instruction_Queue_Entry instEntry;
        instEntry = instQ_DS.getEntry();
        assert(instEntry.valid);
        if (instEntry.opcode == LOAD && loadStoreQueue.canAddToEntry()){
            // Adding entry to load queue
            loadStoreQueue.addToQueue(instEntry.address, instEntry.data, instEntry.id ,LOAD);
            instQ_DS.popInstQ();

        } else if (instEntry.opcode == STORE && loadStoreQueue.canAddToEntry()){
            //Adding entry to store queue
            loadStoreQueue.addToQueue(instEntry.address, instEntry.data, instEntry.id, STORE);
            instQ_DS.popInstQ();
        }
    }
}

void System :: setDebugMode(){
    debugMode = true;
    //cache.setDebugMode();
    loadStoreQueue.setDebugMode();
}

void System :: increment_cycle_count(){
    cycleCount += 1;
    loadStoreQueue.incrementCycleCount();
}

bool System :: allBufferEmpty(){

    if (instQ_DS.isEmpty() && loadStoreQueue.isEmpty()){
        if (debugMode){
            std :: cout << "All buffers empty at cycle: " << cycleCount << "\n";
        }
        return true;
    }
       
    return false;
}