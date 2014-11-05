#include "subArchitecture.h"
#include "sourceFileNode.h"
#include "systemsInterface.h"
#include <iostream>

using std::vector;
using std::map;
using std::string;
using std::cout;

// Define static memeber variable
std::map<std::string, SourceFileNode*> SubArchitecture::allHeaderFiles;

SubArchitecture::SubArchitecture(string path)
    : subArchPath(path)
{
    cout<<"Inne i constructor. Path " <<subArchPath <<"\n";
    findRelevantSourceFiles();
}

void SubArchitecture::findRelevantSourceFiles()
{
    // For now: just take all cpp files in directory. Later, we can consider using Makefile or so.
    vector<string> allSourceFilePaths = SystemsInterface::getAllSourcefilePaths();
    for (auto it : allSourceFilePaths) {
        cout<<"TODO: construct \t\"" <<it <<"\"\n";
        // TODO Gjør SourceFileNode ferdig. Lag den "heilt plain"
    }
}

const SourceFileNode* SubArchitecture::getStaticHeaderFile(string pathArg)
{
    // See if item does not excists, construct element and insert pointer to list
    if (allHeaderFiles.find(pathArg) == allHeaderFiles.end()) 
        allHeaderFiles[pathArg] = new SourceFileNode(pathArg);

    return allHeaderFiles[pathArg];
}







// TESTsubArchitecture 
// TODO TODO TODO Lag unit-test mykje betre! Sjå test-schema i SourceFileNode! TODO TODO TODO
// Lag også unit test som også legg inn elementa i SourceFileNode som blir funnen under!
//   (sjå TESTsourceFileNode::constructLocalDependencies() )
void TESTsubArchitecture::constructor()
{
    std::cout<<"\n\n" <<YELLOWCOLOR <<"TEST" <<DEFAULTCOLOR <<": SubArchitecture ctor(string)\n";
    SubArchitecture testObj("./");
    std::cout<<"Har laga SubArchitecture instans. Den har fått path " <<testObj.subArchPath <<"\n";

    SubArchitecture testObj2("testFolder/");
    std::cout<<"Har laga SubArchitecture instans. Den har fått path " <<testObj2.subArchPath <<"\n";
    cout<<"TODO: Må verifisere at rett folder blir gjennomsøkt! " <<DEFAULTCOLOR <<"\n";

    std::cout<<"\n\n" <<YELLOWCOLOR <<"TEST" <<DEFAULTCOLOR <<": SubArchitecture ctor(string)"
                <<YELLOWCOLOR <<" completed \n" <<DEFAULTCOLOR;

    for (auto i : SubArchitecture::allHeaderFiles)
        cout<<"SubArchitecture::allHeaderFiles contains "
            <<GREYTEXT <<i.second->getFilePath() <<DEFAULTCOLOR <<"\n";
}
