#include "instruction_queue.hh"

void InstructionQueueDS :: createInstructionQ() {
    Instruction_Queue_Entry inst;
    
    // ST Addr:20 Data:10
    inst.valid = true;
    inst.opcode = STORE;
    inst.address = 20;
    inst.data = 10;
    inst.id = 0;
    
    instructionQ.push(inst);
    
    // LD Addr: 20
    inst.opcode = STORE;
    inst.address = 20;
    inst.data = 100;
    inst.id = 1;

    instructionQ.push(inst);

    // ST Addr:40 Data: 14
    inst.opcode = LOAD;
    inst.address = 20;
    inst.data = -1;
    inst.id = 2;
    
    instructionQ.push(inst);

}

bool InstructionQueueDS :: isEmpty(){
    return instructionQ.empty();
}

Instruction_Queue_Entry InstructionQueueDS :: getEntry(){
    return instructionQ.front();
}

void InstructionQueueDS :: popInstQ(){
    instructionQ.pop();
}

void InstructionQueueDS :: increment_cycle_count(){
    cycleCount += 1;
}

void InstructionQueueDS :: createInstructionQFile(std ::string fileName){
    std :: ifstream readFile(fileName);
    std :: string line;

    if (readFile){
        std :: cout << "Opened file: " << fileName << "\n";
    } else {
        std :: cout << "Not able to open file: " << fileName << "\n";
        return;
    }

    char *c;
    std :: vector < std :: string> words;
    int count=0;
    Opcode op;
    int addr, data, id;
    bool val;
    bool flag = false;
    Instruction_Queue_Entry inst;
    while (getline(readFile, line)){
        //std :: vector < std :: string> split_sentence(std::string s);
        words = split_sentence(line);  
        
        for (auto w: words){
          //  std :: cout << w <<", count: " << count << "\n";
            
            if (count == 0){
                if (w == "LD"){
                    val = true;
                    op = LOAD;
                } else if ( w == "ST"){
                    op = STORE;
                } else {
                    std :: cout << "Error: Opcode not identified\n";
                    break;
                }
            } else if (count == 1){
                addr = stoi(w);
            } else if (count == 2){
                data = stoi(w);
            } else if (count == 3){
                id = stoi(w);
                inst.valid = true;
                inst.address = addr;
                inst.opcode = op;
                inst.data = data;
                inst.id = id;

                instructionQ.push(inst);
            }

           
            count = (count +1)%4;
        }
    }

    readFile.close();

}