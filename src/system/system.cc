#include "system.hh"

System :: System (){
    cycleCount = 0;
    //instQ_DS.createInstructionQ();
    //instQ_DS.createInstructionQFile("Instruction/one_load_store_ind.txt");
    cycleCount = 0;
    maxCycleCount = 100;
    debugMode = false;
    stats.loadInstructionCount = 0;
    stats.storeInstructionCount = 0;
    stats.totalCycleCount = 0;
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
            stats.totalCycleCount = cycleCount;
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

        if (loadStoreQueue.canAddToEntry()){
            if (instEntry.opcode == LOAD){
                // Adding entry to load queue
                stats.loadInstructionCount += 1;
                loadStoreQueue.addToQueue(instEntry.address, instEntry.data, instEntry.id ,LOAD);
                instQ_DS.popInstQ();

            } else if (instEntry.opcode == STORE){
                //Adding entry to store queue
                stats.storeInstructionCount += 1;
                loadStoreQueue.addToQueue(instEntry.address, instEntry.data, instEntry.id, STORE);
                instQ_DS.popInstQ();
            }
        } else {
            std :: cout << "Load store queue is full. Can't add instruction. Cycle: " << cycleCount << "\n";
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

void System :: setInstructionFile(std :: string f){
    instQ_DS.createInstructionQFile(f);
}

void System :: printStats(){
    std :: cout << "####### System Stats #############\n";
    std :: cout << "load instruction count: " << stats.loadInstructionCount << "\n";
    std :: cout << "store instruction count: " << stats.storeInstructionCount << "\n";
    std :: cout << "Total cycle count: " << stats.totalCycleCount << "\n";
    std :: cout << "####################################\n";

    loadStoreQueue.printStats();
}