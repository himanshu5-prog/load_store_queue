#include "common_queue.hh"

CommonQueue :: CommonQueue(){
    instanceName = "LoadStoreQueue";
    cycleCount = 0;
    debugMode = false;
}

void CommonQueue :: setDebugMode(){
    debugMode = true;
}

bool CommonQueue :: isEmpty(){
    return entry.empty();
}

bool CommonQueue :: isFull(){
    return (entry.size() == QueueSize);
}

bool CommonQueue :: canAddToEntry(){
    return (!isFull());
}

void CommonQueue :: addToQueue(int addr, int data, int id, Opcode op){
    LSQ_Entry e;

    e.address = addr;
    e.data = data;
    e.age = id;
    e.startCycle = cycleCount;
    e.ready = false;
    e.valid = true;
    e.opcode = op;

    if (op == LOAD){
        e.stage = LD_DISPATCH;
        e.endCycle = cycleCount;
    } else if ( op == STORE){
        e.stage = ST_DISPATCH;
        e.endCycle = cycleCount;
    }


    entry.push_back(e);
}

void CommonQueue :: removeEntry(){
    entry.pop_front();
}

SimpleCacheEntry CommonQueue :: getRetireEntry(){
    SimpleCacheEntry s;
    s.address = 0;
    s.data = -1;
    if (entry.front().stage == ST_RETIRE){
        // Need to retire store instruction
        s.address = entry.front().address;
        s.data = entry.front().data;
    }

    return s;
}

void CommonQueue :: incrementCycleCount(){
    cycleCount += 1;
}

void CommonQueue :: UpdateEntry(){
    // This function update the entry till Retire for Store
    // For Load, it is updated till Add

    // Store stages: Dispatch -> Execute -> Retire (Ready to retire)
    // Load stage:   Dispatch -> Addr Gen -> Execute -> Retire (Ready to retire)
    std :: deque <LSQ_Entry> :: iterator itr;
    Stage prev_stage;
    int entry_id = 0;
    for ( itr = entry.begin(); itr != entry.end(); ++itr){

        if ( itr->opcode == STORE){
            if (itr->stage == ST_DISPATCH){
                //if (debugMode) std :: cout << instanceName << ":: UpdateEntry: Found ST_DISPATCH entry. endCycle: " << itr->endCycle << ", current cyclecount: " << cycleCount <<"\n";
                if (cycleCount >= itr->endCycle){
                    prev_stage = ST_DISPATCH;
                    itr->stage = ST_EXECUTE;
                    itr->startCycle = cycleCount;
                    itr->endCycle = cycleCount + Store_Pipeline_Latency ::DISPATCH_TO_EXECUTE;

                    if (debugMode){
                        std ::  cout << instanceName << " :: UpdateEntry: Found Store entry. Changed stage from " << convertStage2String(prev_stage) 
                        << " to " << convertStage2String(itr->stage) << ", entry id: " << entry_id<< ", cycleCount: " << cycleCount << ", endCycleCount: " << 
                        itr->endCycle<< "\n";
                    }
                }
            } else if (itr->stage == ST_EXECUTE){
                //if (debugMode) std :: cout << instanceName << "UpdateEntry: Found ST_EXECUTE entry. endCycle: " << itr->endCycle << ", current cycle: " << cycleCount << "\n";
                
                if (cycleCount >= itr->endCycle){
                    prev_stage = ST_EXECUTE;
                    itr->stage = ST_RETIRE;
                    itr->startCycle = cycleCount;
                    itr->endCycle = cycleCount + Store_Pipeline_Latency :: EXECUTE_TO_RETIRE_MISS;
                    if (debugMode){
                        std ::  cout << instanceName << ":: UpdateEntry: Found Store entry. Changed stage from " << convertStage2String(prev_stage) 
                        << " to " << convertStage2String(itr->stage) << ", entry id: " << entry_id<< ", cycleCount: " << cycleCount << ", endCycleCount: " << 
                        itr->endCycle<< "\n";
                    }
                }
            }

            
        } else if ( itr -> opcode == LOAD){
            if ( itr -> stage == LD_DISPATCH){
                prev_stage = LD_DISPATCH;

                if (cycleCount >= itr->endCycle){
                    itr->stage = LD_ADDR_GEN;
                    itr->startCycle = cycleCount;
                    itr->endCycle = cycleCount + Load_Pipeline_Latency :: DISPATCH_TO_ADDR_GEN;
                     if (debugMode){
                std ::  cout << instanceName << ":: UpdateEntry: Found Load entry. Changed stage from " << convertStage2String(prev_stage) 
                << " to " << convertStage2String(itr->stage) << ", entry id: " << entry_id << ", cycleaCount: " << cycleCount << ", endcycle: " << itr->endCycle<< "\n";
            }
                }

            } else if ( itr->stage == LD_ADDR_GEN){
                prev_stage = LD_ADDR_GEN;

                if (cycleCount >= itr->endCycle){
                    itr->stage = LD_EXECUTE;
                    itr->startCycle = cycleCount;
                    itr->endCycle = cycleCount + Load_Pipeline_Latency :: ADDRGEN_TO_EXECUTE;

                     if (debugMode){
                std ::  cout << instanceName << ":: UpdateEntry: Found Load entry. Changed stage from " << convertStage2String(prev_stage) 
                << " to " << convertStage2String(itr->stage) << ", entry id: " << entry_id << ", cycleCount: " << cycleCount << ", endcycle: " << itr->endCycle<< "\n";
            }
                } 
            }

           
        }

        ++entry_id;
       
    }
}

int CommonQueue :: updateLoadEntry(int id, int addr){

    int store_id = -1;
    int data = -1;
    Stage prevStage;
    prevStage = entry[id].stage;
    if (entry[id].opcode == LOAD && entry[id].stage == LD_EXECUTE){
        
        for ( int i =0; i < id; ++i){
            if (entry[i].opcode == STORE && entry[i].stage == ST_RETIRE){
                if (addr == entry[id].address){
                    store_id = i;
                    data = entry[i].data;

                    if (debugMode){
                        std :: cout << instanceName << " :: updateLoadEntry: looking for load entry: " << id << ", found store with matching address: " << addr
                        << " at entry id: " << i << "\n";
                    }

                    
                }
            }
        }

        if (data != -1){
            entry[id].data = data;
            entry[id].stage = LD_RETIRE;
            entry[id].startCycle = cycleCount;
            entry[id].endCycle = cycleCount + Load_Pipeline_Latency :: EXECUTE_TO_RETIRE_MISS;

            if (debugMode){
                std :: cout << "----------------------------------------------------------------------------------------------\n";
                std :: cout << instanceName << ": updateLoadEntry for load entry id: " << id << ", found older storen of id: " << store_id << ", changing load entry stage from "
                << convertStage2String(prevStage) << " to " << convertStage2String(entry[id].stage) << "\n";
                printLSQ_Entry(entry[id]);
                std :: cout << "----------------------------------------------------------------------------------------------\n";

            }
        }


    }

    return store_id;
}

void CommonQueue :: updateAllLoadEntry(){
    std :: deque <LSQ_Entry> :: iterator itr;
    int entryId = 0;
    for (itr = entry.begin(); itr != entry.end(); ++itr){

        
        if (itr -> opcode == LOAD && itr->stage == LD_EXECUTE && cycleCount >= itr->endCycle){
            if (foundPrevStore(entryId, itr->address)){
                updateLoadEntry(entryId, itr->address);

            } else {
                // Get from cache
                itr->stage = LD_RETIRE;
                itr->startCycle = cycleCount;
                itr->endCycle = cycleCount + Load_Pipeline_Latency::EXECUTE_TO_RETIRE_MISS;
            }
        }
        ++entryId;
    }
}

bool CommonQueue :: foundPrevStore(int id, int addr){

    for ( int i = 0; i < id; ++i){
        if (entry[i].opcode == STORE  && addr == entry[i].address){
            return true;
        }

    }

    return false;
}

void CommonQueue :: retireEntryHead(){
    if (!isEmpty()){
        if (entry.front().stage == LD_RETIRE || entry.front().stage == ST_RETIRE){
            if (cycleCount >= entry.front().endCycle){
                std :: cout << "Retiring the entry at cycle: " << cycleCount << "\n";
                printLSQ_Entry(entry.front());
                entry.pop_front();
            }
        }
    }
}

void CommonQueue :: printAllEntry(){
    
    std :: deque <LSQ_Entry> :: iterator itr;
    int entry_id = 0;
    std :: cout << "-----------------------------------------------------------------\n";
    for ( itr = entry.begin(); itr != entry.end(); ++itr){
       
        std :: cout << "entry id: " << entry_id << " ";
        printLSQ_Entry(*itr);
        ++entry_id;
    }
     std :: cout << "-----------------------------------------------------------------\n";
}