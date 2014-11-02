#ifndef SOURCEFILENODE_H
#define SOURCEFILENODE_H

#include <iostream>
#include <vector>

class SourceFileNode {
    std::string sourcefilePath;
    //std::vector<SourceFileNode*> includedFiles;

public:
    SourceFileNode(std::string path);

private:
//    SourceFileNode(const SourceFileNode&);
        // Private copy constructor
//    SourceFileNode& operator= (const SourceFileNode&);
        // Private assignment operator
};



#endif
