#include "load_store_queue.hh"
#include "../common/common.hh"

Load_Store_Queue :: Load_Store_Queue(std :: string name){
    head = 0;
    tail = 0;
    cycleCount = 0;
    instanceName = name;
}

Load_Store_Queue :: Load_Store_Queue(){
    head = 0;
    tail = 0;
    cycleCount = 0;
    instanceName = "";
}

void Load_Store_Queue :: setInstancename(std::string name){
    instanceName = name;
}

void Load_Store_Queue :: increment_head(){
    head += ((head+1) % Load_Queue_Size);
}

void Load_Store_Queue :: increment_tail(){
    tail += ((tail+1) % Load_Queue_Size);
}

void Load_Store_Queue :: increment_cycle_count(){
    cycleCount += 1;
}

void Load_Store_Queue :: setDebugMode(){
    debugMode = true;
}

bool Load_Store_Queue :: addToQueue(LSQ_Entry e){
    if (canAddEntry()){

        if (debugMode){
            std :: cout << "Queue: " << instanceName << ": adding entry: \n";
            printLSQ_Entry(e); 
        }

        e.startCycle = cycleCount;
        if (instanceName == "Load Queue"){
            e.stage = LD_DISPATCH;
            e.endCycle = cycleCount + Load_Pipeline_Latency ::DISPATCH_TO_ADDR_GEN;
        } else if ( instanceName == "Store Queue"){
            e.stage = ST_DISPATCH;
            e.endCycle = cycleCount + Store_Pipeline_Latency :: DISPATCH_TO_EXECUTE;
        }
        entry.push_back(e);
        return true;
    } else {
        if (debugMode){
            std :: cout << "Queue: " << instanceName << ": addToQueue : Can't enter entry to queue because it is full.\n";
        }

    }

    return false;
}

bool Load_Store_Queue :: canAddEntry(){
    if (entry.size() == QueueSize ){
        return false;
    }

    return true;
}
/*
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
*/
void Load_Store_Queue :: updateStateLoadQ(){
    std :: deque <LSQ_Entry> :: iterator  itr;
    for (itr = entry.begin(); itr != entry.end(); ++itr){
        if (itr->stage == LD_DISPATCH && cycleCount == itr->endCycle){
            itr->stage = LD_ADDR_GEN;
            itr->startCycle = cycleCount;
            itr->endCycle = cycleCount + Load_Pipeline_Latency :: ADDRGEN_TO_EXECUTE;

        }  else if ( itr ->stage == LD_ADDR_GEN && cycleCount == itr->endCycle){
            //Check if we can go to execute stage
            itr -> stage = LD_EXECUTE;
            itr -> startCycle = cycleCount;

            // check if we have cache hit or miss and update latency accordingly.
            // Update cache if needed.
            itr -> endCycle = cycleCount + Load_Pipeline_Latency :: EXECUTE_TO_RETIRE_HIT;
        }
    }
}

void Load_Store_Queue :: updateStateStoreQ(){

}
