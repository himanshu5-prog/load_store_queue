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
        entry[tail] = e;
        increment_tail();
        return true;
    } else {
        if (debugMode){
            std :: cout << "Queue: " << instanceName << ": addToQueue : Can't enter entry to queue because it is full. Trying to add entry: \n";
        }

        return false;
    }
}

bool Load_Store_Queue :: canAddEntry(){
    if (entry.size() == QueueSize ){
        return false;
    }

    return true;
}
