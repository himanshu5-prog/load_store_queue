#include "system/system.hh"
#include<string>

struct argInfo{
    bool debugMode;
    std :: string fileName;
};

int main(int argc, char* argv[]){

    System sys;

    std :: string dirName = "Instruction";
    std :: string fileName = "multiple_store_load.txt";
    

    bool debugMode = false;
    int i = 1;

    argInfo info;
    while( i < argc){
        if (!strcmp(argv[i], "-debug")){
            debugMode = std :: stoi(argv[i+1]);
            i += 2;
            std :: cout << "Got debugMode: " << debugMode << " from command line argument\n";
        } else if (!strcmp(argv[i], "-file")){
            fileName = argv[i+1];
            i += 2;
            std :: cout << "Got fileName: " << fileName << " from command line argument\n";
        } else {
            i += 1;
        }
    }

    info.debugMode = debugMode;
    info.fileName = dirName + "/" + fileName;
    std :: string fName = dirName + "/" + fileName;


    if (debugMode)
        sys.setDebugMode();
    
    sys.setMaxCycleCount(50);
    sys.setInstructionFile(fName);
    sys.run();
    sys.printStats();
    
    return 0;
}