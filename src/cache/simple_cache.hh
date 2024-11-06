#ifndef _SIMPLE_CACHE_
#define _SIMPLE_CACHE_

#include <iostream>
#include <map>
#include <utility>

class SimpleCache {
        std :: map <int, int> cache;
        std :: string instanceName;
        bool debugMode;
    public:
        SimpleCache();
        void addToCache(int addr, int data);
        int getCacheData(int addr);
        bool isCacheHit (int addr);
        void setDebugMode();
};
#endif