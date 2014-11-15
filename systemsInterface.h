#ifndef SYSTEMSINTERFACE_H
#define SYSTEMSINTERFACE_H

#include <iostream>
#include <vector>
#include <string>

#include "fargar.h"

namespace boost{
    namespace filesystem{
        class path;
    }
}
namespace fs = boost::filesystem;

struct SystemsInterface {
    //static std::vector<std::string> getAllSourcefilePaths(std::string dirPath ="./");
    static std::vector<fs::path> getAllSourcefilePaths(fs::path dirPath);
        // return string-vector of all relevant source files
    static std::vector<fs::path> getLocalDependencies(fs::path filePath);
        // return all included files from file with path [filePath]
    static std::vector<std::string> exec(std::string cmd);
        // execute commmand cmd in shell and return output as a string
};

struct TESTsystemsInterface {
    static void mainTest();
};

#endif
