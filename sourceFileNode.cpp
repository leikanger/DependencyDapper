#include "sourceFileNode.h"
#include "systemsInterface.h"

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::vector;
using std::string;

SourceFileNode::SourceFileNode(string path) 
    : sourcefilePath(path)
{
    cout<<"In construcor for SourceFileNode: " <<sourcefilePath <<std::endl;
}



// TODO WRITE TEST for the following function!
void SourceFileNode::findLocalDependencies()
{
    vector<string> localDependencies = systemsInterface::getLocalDependencies(sourcefilePath);
    if (localDependencies.empty()) {
        cout<<"Source file node [" <<sourcefilePath <<"]: " 
            <<REDCOLOR <<"No local dependency found\n" <<DEFAULTCOLOR;
        return;
    }

    cout<<"Local dependencies of file " <<sourcefilePath <<":\n";
    for (auto iter : localDependencies)
        cout<<"\t" <<iter <<"\n";

}


/* TEST FUNCTIONS */
void TESTsourceFileNode::testFindLocalDependencies(SourceFileNode* testObject)
{
    testObject->findLocalDependencies();
}
