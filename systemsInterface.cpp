#include "systemsInterface.h"

#include <fstream>
#include <cstdlib>

using std::cout;
using std::string;
using std::vector;

vector<string> systemsInterface::getSourceFiles()
{   
    return exec("ls *cpp");
}

/***********************************************************
 * systemsInterface::getLocalDependencies(string filePath)
 * return: vector<string> of all PATHs included by local include statement: # include " PATH "
 *     -> that is dependencies that are supplied by relative path.
 *
 **********************************************************/
vector<string> systemsInterface::getLocalDependencies(string filePath)
{
    string shellCommand = "cat " + filePath + " | grep \'#include \"\'";

    vector<string> systemOutput = exec(shellCommand);

    // Extract the text between the mark " in the include statements: e.g. systemsInterface.h in this components  # include " systemsInterface.h "
    for (vector<string>::iterator it = systemOutput.begin(); it!=systemOutput.end(); ++it) {
        // Find first and last position of the mark " in order to extract name of included file.
        std::size_t firstPos= it->find_first_of("\"");
        std::size_t lastPos = it->find_last_of("\"");
        *it = it->substr(firstPos+1, lastPos-firstPos-1); // TODO Check if there is more intuitive (easily understandable) ways of doing this!
    }
    return systemOutput;
}

vector<string> systemsInterface::exec(string cmd)
{
    vector<string> result;

    string tempFileName = "cmd_output.temp";
    string shellCommand = cmd + " > " + tempFileName;
    //  Error-check!
    int returnFromSystemCmd = std::system(shellCommand.c_str());
    if (returnFromSystemCmd)
        throw "Function exec(std::string): std::system(-) command returned error. Terminate program\n";

    std::string output = "";
    std::ifstream fileStream(tempFileName, std::ifstream::in);

    while ( std::getline(fileStream, output) ) {
        result.push_back(output);
    }

    fileStream.close();
    shellCommand = "rm " + tempFileName;
    std::system(shellCommand.c_str());

    return result;
}




/* TEST Component */
void TESTsystemsInterface::mainTest()
{
    cout<<"Get source files:\n\n";
    vector<string> sourceFiles = systemsInterface::getSourceFiles();

    for (auto iter : sourceFiles) {
        vector<string> dependencies = systemsInterface::getLocalDependencies(iter);
        cout<<"Dependencies of file " <<iter <<std::endl;
        for (auto dependencyIter : dependencies) {
            cout<<GREENCOLOR <<dependencyIter <<DEFAULTCOLOR <<"\n";
        }
    }
}
