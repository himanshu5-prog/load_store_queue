#ifndef __SYSTEM__
#define __SYSTEM__

#include <iostream>
#include "../Cache/cache.hh"
#include "../Load_Store_Queue/load_store_queue.hh"

class System {
    Cache cache;
    Load_Store_Queue loadQ;
    Load_Store_Queue storeQ;

};

#endif