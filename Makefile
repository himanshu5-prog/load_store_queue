lsq: mainFunc.o system.o common.o entry.o instruction_queue.o common_queue.o
	g++  mainFunc.o system.o common.o entry.o instruction_queue.o common_queue.o -o lsq

mainFunc.o: src/mainFunc.cpp
	g++ -c src/mainFunc.cpp -std=c++11

system.o: src/system/system.cc src/system/system.hh
	g++ -c src/system/system.cc -std=c++11

common.o: src/common/common.hh src/common/common.cc
	g++ -c src/common/common.cc -std=c++11

entry.o: src/Entry/entry.cc src/Entry/entry.hh
	g++ -c src/Entry/entry.cc -std=c++11

instruction_queue.o: src/Instruction_Queue/instruction_queue.cc src/Instruction_Queue/instruction_queue.hh
	g++ -c src/Instruction_Queue/instruction_queue.cc -std=c++11

common_queue.o: src/Load_Store_Queue/common_queue.cc src/Load_Store_Queue/common_queue.hh
	g++ -c src/Load_Store_Queue/common_queue.cc -std=c++11

clean :
	rm *.o lsq