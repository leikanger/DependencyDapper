#ifndef SOURCEFILENODE_H
#define SOURCEFILENODE_H

//#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/filesystem.hpp>

// Forward declarations
class SourceFileNode;
namespace boost{
    namespace filesystem{
        class path;
    }
}
namespace fs = boost::filesystem;

// Implementation
class SourceFileNode {
    fs::path sourcefilePath;   
    std::vector<SourceFileNode*> dependencies;
    static std::map<fs::path, SourceFileNode*> allSourceFiles;
    static std::map<fs::path, SourceFileNode*> allHeaderFiles;

public:
    //SourceFileNode* getStaticHeaderFile(std::string pathArg);
    static SourceFileNode* findOrConstructSourcefileWithPath(fs::path pathArg
                                                            , bool isHeaderFile_arg = false);
    static void printAllSourceFiles();
    static void printAllHeaderFiles();
    fs::path getFilePath() const { return sourcefilePath; }

private:
    // Foreløpig: Legg constructor private. Kan endre dette ved behov, men no brukast factory-funksjonen findOrConstructSourcefileWithPath(path).
    SourceFileNode(fs::path path);
    //SourceFileNode(std::string path);
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
