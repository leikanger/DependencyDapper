#include "sourceFileNode.h"
//#include <string>
//#include <vector>
//#include <memory>
#include "systemsInterface.h"
#include "fargar.h"

// TODO Gjør slik at dei to komponentane subArchitecture og sourceFileNode blir til en component! XXX
//  => Flytt alt inn i ei kildefil og ei headerfil!
#include "subArchitecture.h"
// TODO

#include <iostream>
#include <memory>

using std::cout;
using std::vector;
using std::string;


SourceFileNode::SourceFileNode(string path) 
    : sourcefilePath(path)
{
    cout<<"CONSTRUCTOR for SourceFileNode\n";
    /* Gjør det som skal gjørast når man først oppretter eit element!
    cout<<"Find all local dependencies\n";
    findLocalDependencies();
    */
}

/** ** * * * * * * * * * * * * * * * * * * * * * * * * 
/ * Just for now: Insert pointer to new object 
/ * ** * * * * * * * * * * * * * * * * * * * * * * * */
// TODO WRITE TEST for the following function!
void SourceFileNode::constructLocalDependencies()
{
    /* PLAN (raskt etter hukommelsen)
     */
    //*  1) finn filnavna
    vector<string> localDependencies = SystemsInterface::getLocalDependencies(sourcefilePath);
    if (localDependencies.empty()) {
        cout<<"Source file node [" <<sourcefilePath <<"]: " 
            <<REDCOLOR <<"No local dependency found\n" <<DEFAULTCOLOR;
        return;
    }

    //*  2) kall SubArch::getStaticHeaderFile(path) for kvar path
    //*  2b) legg returverdien inn i SourceFileNode::dependencies;
    cout<<"Local dependencies of file " <<REDCOLOR <<sourcefilePath <<DEFAULTCOLOR <<":\n";
    for (auto iter : localDependencies) {
        cout<<"\t" <<iter <<" inserted\n";
        size_t pos = sourcefilePath.find_last_of("/");
        string folderPath = sourcefilePath.substr(0, pos+1); // second arg is length of substr
        //dependencies.push_back(new SourceFileNode(folderPath+iter));
        dependencies.push_back(SubArchitecture::getStaticHeaderFile(folderPath+iter));
        // TODO Neste blir å legge til static-liste i SubArch som har alle konstruerte .h filer
        // og gjøre som står rett over, i pkt. 2)
    }
}







void TESTsourceFileNode::testAll() 
{
    std::cout<<YELLOWCOLOR <<"TEST" <<DEFAULTCOLOR <<" class SourceFileNode\n";
    // TODO Forsøk å gjøre dette med try-catch statement rundt kall for testane, 
    // og kast exceptions ved feil!
    int returnVal = test_constructLocalDependencies();
    if (returnVal == 0)
        cout<<GREENCOLOR <<"TEST" <<DEFAULTCOLOR <<" class SourceFileNode \t: All Tests "
            <<GREENCOLOR <<"PASSED\n" <<DEFAULTCOLOR;
    else
        cout<<REDCOLOR <<"TEST" <<DEFAULTCOLOR <<" class SourceFileNode \t: Test "
            <<REDCOLOR <<"FAILED" <<DEFAULTCOLOR <<"\t:\t test failed.\n";
}

int TESTsourceFileNode::test_constructLocalDependencies() 
{
    // In the folder [testFolder/], I have placed a couple of source files.
    //   testFolder/source1.cpp
    //      -> headerA.h
    //      -> headerB.h
    //      -> headerC.h
    //      -> newFolder/headerD.h
    std::shared_ptr<SourceFileNode> testObject (new SourceFileNode("testFolder/source1.cpp"));

    testObject->constructLocalDependencies();
    // Confirm that testObject->dependencies has elements:
    if (testObject->dependencies.empty()) {
        cout<<"The class constainer vector<SourceFileNode*> dependencies  is empty() : \n";
        return -1;
    }
    // Confirm that it contains the right elements (with right path)
    bool foundHeaderA = false;
    bool foundHeaderB = false;
    bool foundHeaderC = false;
    bool foundHeaderD = false;
    for (const SourceFileNode* iter : testObject->dependencies) {
        if (iter->getFilePath() == "testFolder/headerA.h")     foundHeaderA = true;
        if (iter->getFilePath() == "testFolder/headerB.h")     foundHeaderB = true;
        if (iter->getFilePath() == "testFolder/headerC.h")     foundHeaderC = true;
        if (iter->getFilePath() == "testFolder/newFolder/headerD.h")     foundHeaderD = true;
    }
    if (!foundHeaderA) cout<<REDCOLOR <<"ERROR" <<DEFAULTCOLOR <<"Could not locate headerA.h\n";
    if (!foundHeaderB) cout<<REDCOLOR <<"ERROR" <<DEFAULTCOLOR <<"Could not locate headerB.h\n";
    if (!foundHeaderC) cout<<REDCOLOR <<"ERROR" <<DEFAULTCOLOR <<"Could not locate headerC.h\n";
    if (!foundHeaderD) cout<<REDCOLOR <<"ERROR" <<DEFAULTCOLOR <<"Could not locate newFolder/headerD.h\n";

    if (!(foundHeaderA && foundHeaderB && foundHeaderC && foundHeaderD))
        return -1;

    cout<<"Source file in testFolder/ contains the correct headers.\n";
    return 0;
}
