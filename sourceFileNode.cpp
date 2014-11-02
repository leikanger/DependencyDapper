#include "sourceFileNode.h"

#include <iostream>
#include <vector>

using std::cout;
using std::vector;
using std::string;

SourceFileNode::SourceFileNode(string path) 
    : sourcefilePath(path)
{
    cout<<"In construcor for SourceFileNode: " <<sourcefilePath <<std::endl;
}
