GCC:= g++ -std=c++11 -Wall
BIN_DIR:= bin
CLEAN := rm -r $(BIN_DIR)/


$(BIN_DIR):
	mkdir -p $(BIN_DIR)

all: bin/mainFunc.o bin/system.o bin/common.o bin/entry.o bin/instruction_queue.o bin/common_queue.o
	g++  bin/mainFunc.o bin/system.o bin/common.o bin/entry.o bin/instruction_queue.o bin/common_queue.o -o bin/lsq

bin/mainFunc.o: src/mainFunc.cpp
	$(GCC) -c src/mainFunc.cpp -o bin/mainFunc.o

bin/system.o: src/system/system.cc src/system/system.hh
	$(GCC) -c src/system/system.cc -o bin/system.o

bin/common.o: src/common/common.hh src/common/common.cc
	$(GCC) -c src/common/common.cc -o bin/common.o

bin/entry.o: src/Entry/entry.cc src/Entry/entry.hh
	$(GCC) -c src/Entry/entry.cc -o bin/entry.o

bin/instruction_queue.o: src/Instruction_Queue/instruction_queue.cc src/Instruction_Queue/instruction_queue.hh
	$(GCC) -c src/Instruction_Queue/instruction_queue.cc -o bin/instruction_queue.o

bin/common_queue.o: src/Load_Store_Queue/common_queue.cc src/Load_Store_Queue/common_queue.hh
	$(GCC) -c src/Load_Store_Queue/common_queue.cc -o bin/common_queue.o

clean :
	$(CLEAN)