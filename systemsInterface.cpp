#include "systemsInterface.h"
#include <boost/filesystem.hpp>

#include <fstream>
#include <cstdlib>

using std::cout;
using std::string;
using std::vector;

namespace fs = boost::filesystem;

#if 0
class myException : std::exception {
    std::string description;
public:
    myException(std::string desc) : description(desc) {}
    virtual const char* what() noexcept {return description.c_str(); }
};
#endif

vector<fs::path> SystemsInterface::getAllSourcefilePaths(fs::path dirPath)
{   
    // Lets try to make it with boost::filesystem
    try {
        // Check whether path is a valid directory
        if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
            cout<<"Error: directory with supplied path does not exist or is not directory\n";
            throw("Directory path is not path to a valid directory");
        }
    } 
    catch (fs::filesystem_error const & e) {
        std::cerr<<e.what() <<'\n';
    }

    vector<fs::path> returnVector;
    // Iterate through directory. Add element ti returnVector if valid
    for( fs::directory_iterator file(dirPath) ;
          file != fs::directory_iterator();   //Default ctor gives end-iterator
          ++file) {
        try {
            if (fs::is_directory(*file))
                continue;

            cout<<"File paht: " <<file->path() <<'\n';    
            returnVector.push_back(*file);
        }
        catch (fs::filesystem_error const & e) {
            std::cerr <<e.what() <<'\n';
        }
    }

    return returnVector;
}

#if 0 //Gammel variant:
vector<fs::path> SystemsInterface::getAllSourcefilePaths(fs::path dirPath)
{   
    string shellCommandToExecute = "ls " + dirPath + "*cpp";
    vector<string> returnFromSystemCmd = exec(shellCommandToExecute.c_str());
    cout<<"HER\n\n";
    if (returnFromSystemCmd.size() == 1 && 
            returnFromSystemCmd.front().find("No such file or directory") == std::string::npos) {
        // String does not contain tested line
        cout<<"Folder contains no .cpp files.\n";
        return vector<string>();
    } else {
        return returnFromSystemCmd;
    }
}
#endif

/***********************************************************
 * systemsInterface::getLocalDependencies(string filePath)
 * return: vector<string> of all PATHs included by local include statement: # include " PATH "
 *     -> that is dependencies that are supplied by relative path.
 *
 **********************************************************/
vector<fs::path> SystemsInterface::getLocalDependencies(fs::path filePath)
{
    string shellCommand = "cat " + filePath.string() + " | grep \'#include \"\'";

    vector<string> systemOutput = exec(shellCommand);

    vector<fs::path> returnDep = vector<fs::path>();

    // Extract the text between the mark " in the include statements: 
    //   e.g. systemsInterface.h in this components  # include " systemsInterface.h "
    for (vector<string>::iterator it = systemOutput.begin(); it!=systemOutput.end(); ++it) {
        // Find first and last position of the mark " in order to extract name of included file.
        std::size_t firstPos= it->find_first_of("\"");
        std::size_t lastPos = it->find_last_of("\"");
        *it = it->substr(firstPos+1, lastPos-firstPos-1); 
        returnDep.push_back(fs::path(*it));
    }
    return returnDep;
}

vector<string> SystemsInterface::exec(string cmd)
{
    vector<string> result;

    string tempFileName = "cmd_output.temp";
    string shellCommand = cmd + " > " + tempFileName;
    //  Error-check!
    int returnFromSystemCmd = std::system(shellCommand.c_str());
    if (returnFromSystemCmd) { // Check for error value : return 0 on sucess
        cout <<"Could not find any local includes in the source file\n"; //return vector<string>();
        return result;
        //throw "Function exec(std::string): std::system(-) command returned error. Terminate program\n";
    }

    // Go through all the local header files (include "" - commands)
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
    /*
    cout<<"Get source files:\n\n";
    vector<fs::path> sourceFiles = SystemsInterface::getAllSourcefilePaths("./");

    for (auto iter : sourceFiles) {
        vector<string> dependencies = SystemsInterface::getLocalDependencies(iter);
        cout<<"Dependencies of file " <<iter <<std::endl;
        for (auto dependencyIter : dependencies) {
            cout<<GREENCOLOR <<dependencyIter <<DEFAULTCOLOR <<"\n";
        }
    }
    */
}
