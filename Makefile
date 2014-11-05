all: *cpp *h
	clang++ -std=c++11 -Wall main.cpp subArchitecture.cpp sourceFileNode.cpp systemsInterface.cpp -o dependency.out           &&           ./dependency.out  
    
#sourceFileNode: sourceFileNode.cpp sourceFileNode.h
#	clang++ -std=c++11 -Wall -pthread sourceFileNode.cpp systemsInterface.cpp -o dependency.out           &&           ./dependency.out  

