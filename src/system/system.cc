#include "system.hh"

System :: System (){
    cycleCount = 0;
    cycleCount = 0;
    maxCycleCount = 100;
    debugMode = false;
    stats.loadInstructionCount = 0;
    stats.storeInstructionCount = 0;
    stats.totalCycleCount = 0;
}

void System :: run(){
    for (int currentCycleCount = 0; currentCycleCount < maxCycleCount; ++currentCycleCount){

        if (debugMode){
            std :: cout << "System:: run(): Cycle : " << cycleCount << "\n";
            std :: cout << " Pre-processing entry: \n";
            loadStoreQueue.printAllEntry();
        }

        /*
        Pipeline:

        issue -> Update LSQ -> retire
        Issue: Instruction is moved from instruction queue. Once the instruction is in LSQ, it goes into dispatch stage
        update LSQ: the entries in LSQ are updated (instruction goes through address generation, data calculation, cache access).
        Retire: Instructions are retired (for load, it means the destination register is updated or store instruction updates the cache)
        */
       
        // Retire instructions in load store queue
        retireInstruction();

        // Update stages in load store queue
        updateLoadStoreQueue();

        // Issue instruction from instruction queue
        issue();

        // Check if all buffers are empty and simulation can be stopped
        if (allBufferEmpty()){
            stats.totalCycleCount = cycleCount;
            break;
        }
        
        //Update cycle count
        increment_cycle_count();

    }
}

void System :: issue (){
    
    if (!instQ_DS.isEmpty()){
        Instruction_Queue_Entry instEntry;
        instEntry = instQ_DS.getEntry();
        assert(instEntry.valid);

        //Instruction can be added to load-Store queue if there is space available
        if (loadStoreQueue.canAddToEntry()){
            if (instEntry.opcode == LOAD){
                // Adding entry to load queue

                // Updating stats
                stats.loadInstructionCount += 1;
                loadStoreQueue.addToQueue(instEntry.address, instEntry.data, instEntry.id ,LOAD);

                // Removing instruction from instQ
                instQ_DS.popInstQ();

            } else if (instEntry.opcode == STORE){
                //Adding entry to store queue

                //Updating stats
                stats.storeInstructionCount += 1;
                loadStoreQueue.addToQueue(instEntry.address, instEntry.data, instEntry.id, STORE);

                // Removing instruction from instQ
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

void System :: updateLoadStoreQueue(){
    loadStoreQueue.updateAllLoadEntry();
    loadStoreQueue.UpdateEntry();
}

void System :: retireInstruction(){
    loadStoreQueue.retireEntryHead();
}