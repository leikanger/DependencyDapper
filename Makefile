CPP_FLAGS = -lboost_system -lboost_filesystem

all: 
	make compileAll

runAll: compileAll
	./dependency.out

compileAll: main.cpp subArchitecture.cpp systemsInterface.o sourceFileNode.o
	clang++ -std=c++11 $(CPP_FLAGS) -Wall main.cpp subArchitecture.cpp sourceFileNode.o systemsInterface.o -o dependency.out

systemsInterface.o: systemsInterface.cpp systemsInterface.h
	clang++ -std=c++11 $(CPP_FLAGS) -Wall systemsInterface.cpp -c 

sourceFileNode.o: sourceFileNode.cpp sourceFileNode.h systemsInterface.cpp systemsInterface.h
	clang++ -std=c++11 -Wall sourceFileNode.cpp systemsInterface.cpp -c
    


test: testSystemstIterface_TEST
	make all
	echo "\n"
	./testSystemstIterface_TEST.out
	echo JA!

testSystemstIterface_TEST: systemsInterface.cpp systemsInterface.h systemsInterface_TEST.cpp
	clang++ -std=c++11 $(CPP_FLAGS) -lboost_unit_test_framework -Wall systemsInterface.cpp systemsInterface_TEST.cpp -o testSystemstIterface_TEST.out

systemsInterface_TEST.o: systemsInterface.*
	clang++ -std=c++11 $(CPP_FLAGS) -lboost_unit_test_framework -Wall systemsInterface.o systemsInterface_TEST.cpp -c 



clean: 
	rm *.o *.out



# SystemstInterface : TODO
# 	lag default-argument for getAllSourcefilePaths (med path som arg-type i stadenfor string)
