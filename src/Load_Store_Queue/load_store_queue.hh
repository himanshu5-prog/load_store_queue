#ifndef __LOAD_STORE_QUEUE__
#define __LOAD_STORE_QUEUE__

#include "../Entry/entry.hh"

class Load_Store_Queue{
    LSQ_Entry entry[16];
    int head; // entry to consider for execution
    int tail; // entry where new entry needs to be added
    int cycleCount;
    bool debugMode;
    std::string instanceName;

    public:
        Load_Store_Queue(std::string name);
        Load_Store_Queue();
        void setDebugMode();

        // Increment function---------
        void increment_head();
        void increment_tail();
        void increment_cycle_count();
        //----------------------------

        void addToQueue(LSQ_Entry e);
        bool canAddEntry();
        void setInstancename(std :: string name);
};

#endif


