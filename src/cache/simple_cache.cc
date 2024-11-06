#include "simple_cache.hh"

SimpleCache :: SimpleCache(){
    instanceName = "SimpleCache";
    debugMode = false;
}

void SimpleCache :: addToCache (int addr, int data){
    if (cache.find(addr) == cache.end()){
        // Not found in cache

        if (debugMode)
            std :: cout << instanceName << ":: addToCache : address: " << addr << " is not found. Cache MISS. Inserting data: " << data << "\n";

        cache.insert({addr,data});
    } else {
        // Found in cache. Update the cache
         if (debugMode)
            std :: cout << instanceName << ":: addToCache : address: " << addr << " is not found. Cache HIT. Inserting data: " << data << "\n";

        cache[addr] = data;
    }
}

int SimpleCache :: getCacheData(int addr){
    if (cache.find(addr) == cache.end()){
        // Not found in cache
        int data;
        data = addr + 256;
        cache.insert ( {addr, data});

        if (debugMode)
            std :: cout << instanceName << " :: getCacheData: address: " << addr << " is not found ( Cache MISS). Inserted entry to cache. Returning data: " << data << "\n";
        return data;

    } else {

        if (debugMode)
            std :: cout << instanceName << " :: getCacheData: address: " << addr << " is found ( Cache HIT). Returning data: " << cache[addr] << "\n";
            
        return cache[addr];
    }
}

bool SimpleCache :: isCacheHit (int addr){
    if ( cache.find(addr) == cache.end()){
        // Not found in cache
        std :: cout << instanceName << " :: isCacheHit: Cache miss for address: " << addr << "\n"; 
        return false;

    }

    if (debugMode)
        std :: cout << instanceName << ":: isCacheHit: Cache hit for address: " << addr << "\n";
    
    return true;
}

void SimpleCache :: setDebugMode (){
    debugMode = true;
}