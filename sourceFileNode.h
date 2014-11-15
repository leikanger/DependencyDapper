#ifndef SOURCEFILENODE_H
#define SOURCEFILENODE_H

//#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/filesystem.hpp>

// Forward declarations
class SourceFileNode;

/************************************
 * TODO Alt dette skal gjøres om! Gjør det heller på måten med SubArchitecture!
 * *********************************/


// Implementation
class SourceFileNode {
    std::string sourcefilePath;
    std::vector<SourceFileNode*> dependencies;
    static std::map<std::string, SourceFileNode*> allSourceFiles;
    static std::map<std::string, SourceFileNode*> allHeaderFiles;

public:
    //SourceFileNode* getStaticHeaderFile(std::string pathArg);
    static SourceFileNode* findOrConstructSourcefileWithPath(std::string pathArg
                                                            , bool isHeaderFile_arg = false);
    static void printAllSourceFiles();
    static void printAllHeaderFiles();
    std::string getFilePath() const { return sourcefilePath; }

private:
    // Foreløpig: Legg constructor private. Kan endre dette ved behov, men no brukast factory-funksjonen findOrConstructSourcefileWithPath(path).
    SourceFileNode(std::string path);
    SourceFileNode(const SourceFileNode&);              // Not implemented
    SourceFileNode& operator= (const SourceFileNode&);  // Not implemented

    void constructLocalDependencies();
    
    friend struct TESTsourceFileNode;
};



struct TESTsourceFileNode {
    static void testAll();
    static int test_constructLocalDependencies();
    static int test_sourceDependencies();
};



#endif
