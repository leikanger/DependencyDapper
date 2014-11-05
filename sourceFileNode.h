#ifndef SOURCEFILENODE_H
#define SOURCEFILENODE_H

//#include <iostream>
#include <string>
#include <vector>
#include <map>

// Forward declarations
class SourceFileNode;

/************************************
 * TODO Alt dette skal gjøres om! Gjør det heller på måten med SubArchitecture!
 * *********************************/


// Implementation
class SourceFileNode {
    std::string sourcefilePath;
    std::vector<const SourceFileNode*> dependencies;

public:
    SourceFileNode(std::string path);
    std::string getFilePath() const { return sourcefilePath; }

private:
    SourceFileNode(const SourceFileNode&);              // Not implemented
    SourceFileNode& operator= (const SourceFileNode&);  // Not implemented

    void constructLocalDependencies();
    
    friend struct TESTsourceFileNode;
};



struct TESTsourceFileNode {
    static void testAll();
    static int test_constructLocalDependencies();
};



#endif
