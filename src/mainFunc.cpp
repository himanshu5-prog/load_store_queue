#include "system/system.hh"

int main(){

    System sys;

    sys.setDebugMode();
    sys.setMaxCycleCount(50);
    sys.run();
    
    return 0;
}