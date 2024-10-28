#include "common.hh"

std :: string convertStage2String(Stage st){
    switch (st){
        case 0: 
            return "NONE";
        case 1:
            return "LD_DISPATCH";
        case 2:
            return "LD_ADDR_GEN";
        case 3:
            return "LD_DISPATCH_TO_ADDR_GEN";
        case 4:
            return "LD_EXECUTE";
        case 5:
            return "LD_ADDRGEN_TO_EXECUTE";
        case 6:
            return "LD_RETIRE";
        case 7:
            return "LD_EXECUTE_TO_RETIRE";
        case 8:
            return "ST_DISPATCH";
        case 9:
            return "ST_DISPATCH_TO_EXECUTE";
        case 10:
            return "ST_EXECUTE";
        case 11:
            return "ST_EXECUTE";
        case 12:
            return "ST_EXECUTE_TO_RETIRE";

    }
}