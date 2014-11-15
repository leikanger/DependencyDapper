#include "sourceFileNode.h"
//#include <string>
//#include <vector>
//#include <memory>
#include "systemsInterface.h"
#include "fargar.h"

#include <iostream>
#include <memory>

using std::cout;
using std::vector;
using std::string;

// Define static memeber variable
std::map<std::string, SourceFileNode*> SourceFileNode::allSourceFiles;
std::map<std::string, SourceFileNode*> SourceFileNode::allHeaderFiles;

SourceFileNode::SourceFileNode(string path) 
    : sourcefilePath(path)
{
    cout<<"CONSTRUCTOR for SourceFileNode\t" <<path <<"\n";
    constructLocalDependencies();
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
    vector<fs::path> localDependencies = SystemsInterface::getLocalDependencies(sourcefilePath);
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
        dependencies.push_back(findOrConstructSourcefileWithPath(folderPath+iter, true));
        // Insert the new header file into map allHeaderFiles[path]:
        allHeaderFiles[folderPath+iter] = findOrConstructSourcefileWithPath(folderPath+iter, true);
        // TODO Neste blir å legge til static-liste i SubArch som har alle konstruerte .h filer
        // og gjøre som står rett over, i pkt. 2)
    }
}

void SourceFileNode::printAllSourceFiles()
{
    cout<<"ALL ITEMS IN LIST allSourceFiles: \n";
    for (auto iter : allSourceFiles)
        cout<<"SOURCE F:\t" <<iter.first <<"\n";
}

void SourceFileNode::printAllHeaderFiles() 
{
    cout<<"ALL ITEMS IN LIST allHeaderFiles: \n";
    for (auto iter : allHeaderFiles)
        cout<<"HEADER:  \t" <<iter.first <<"\n";
}

/* The following function finds or generates a new SourceFileNode if free store, and returns pointer to it */
SourceFileNode* SourceFileNode::findOrConstructSourcefileWithPath(  string pathArg
                                                                  , bool isHeaderFile_arg /*=false*/)
{
    // Headerfiles are handled in different container than sourcefiles:
    if (isHeaderFile_arg) {
        // See if item does not excists, construct element and insert pointer to list
        if (allHeaderFiles.find(pathArg) == allHeaderFiles.end()) {
            allHeaderFiles[pathArg] = new SourceFileNode(pathArg);
        }
        return allHeaderFiles[pathArg];   
    } else {
        cout<<"\n\nNext source file\t:\n";
        if (allSourceFiles.find(pathArg) == allSourceFiles.end()) {
            allSourceFiles[pathArg] = new SourceFileNode(pathArg);
        }
        return allSourceFiles[pathArg];
    }
}







void TESTsourceFileNode::testAll() 
{
    std::cout<<YELLOWCOLOR <<"TEST" <<DEFAULTCOLOR <<" class SourceFileNode\n";
    // TODO Forsøk å gjøre dette med try-catch statement rundt kall for testane, 
    // og kast exceptions ved feil!
    int returnVal = test_constructLocalDependencies();
    int returnVal2 = test_sourceDependencies();
    if (returnVal == 0 && returnVal2 == 0)
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
    string path("testFolder/source1.cpp"); 
    //std::shared_ptr<SourceFileNode> testObject (new SourceFileNode(path));
    SourceFileNode* testObjectP = new SourceFileNode(path);
    SourceFileNode::allSourceFiles[path] = testObjectP;

    // Confirm that testObject->dependencies has elements:
    if (testObjectP->dependencies.empty()) {
        cout<<"The class constainer vector<SourceFileNode*> dependencies  is empty() : \n";
        return -1;
    }

    cout<<"\nTotal number of dependencies for " <<path <<YELLOWCOLOR <<" "
        <<testObjectP->dependencies.size() <<DEFAULTCOLOR <<"\n";
    
    // Confirm that it contains the right elements (with right path)
    bool foundHeaderA = false;
    bool foundHeaderB = false;
    bool foundHeaderC = false;
    bool foundHeaderD = false;
    for (const SourceFileNode* iter : testObjectP->dependencies) {
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
    
    SourceFileNode::printAllSourceFiles();
    SourceFileNode::printAllHeaderFiles();
    return 0;
}

int TESTsourceFileNode::test_sourceDependencies()
{
    cout<<"\nTEST: Sourcefile items dependencies:\n";
    for (auto iter : SourceFileNode::allSourceFiles) {
        //cout<<"KEY : " <<iter.first <<"\n";
        cout<<"PATH: " <<iter.second->getFilePath() <<"\n";
        for (auto i : iter.second->dependencies) {
            cout<<"\tHEADER:\t" <<i->getFilePath() <<"\n";
        }
    }
    cout<<"\nTEST: Headerfile items dependencies:\n";
    for (auto iter : SourceFileNode::allHeaderFiles) {
        //cout<<"KEY : " <<iter.first <<"\n";
        cout<<"PATH: " <<iter.second->getFilePath() <<"\n";
        for (auto i : iter.second->dependencies) {
            cout<<"\tHEADER:\t" <<i->getFilePath() <<"\n";
        }
    }
    return 0;
}
