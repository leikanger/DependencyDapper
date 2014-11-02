all: *cpp *h
	c++ -std=c++11 -Wall main.cpp sourceFileNode.cpp systemsInterface.cpp -o dependency.out           &&           ./dependency.out  
    
#sourceFileNode: sourceFileNode.cpp sourceFileNode.h
#	clang++ -std=c++11 -Wall -pthread sourceFileNode.cpp systemsInterface.cpp -o dependency.out           &&           ./dependency.out  

