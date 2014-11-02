#ifndef SOURCEFILENODE_H
#define SOURCEFILENODE_H

//#include <iostream>
#include <string>
#include <vector>

class SourceFileNode {
    std::string sourcefilePath;
    std::vector<SourceFileNode*> dependencyFiles;

public:
    SourceFileNode(std::string path);

private:
    SourceFileNode(const SourceFileNode&);              // Not implemented
    SourceFileNode& operator= (const SourceFileNode&);  // Not implemented

    void findLocalDependencies();
    
    friend struct TESTsourceFileNode;
};

struct TESTsourceFileNode {
    static void testFindLocalDependencies(SourceFileNode* testObject);
};



#endif
