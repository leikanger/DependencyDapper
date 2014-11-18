#ifndef SUBARCHITECTURE_H
#define SUBARCHITECTURE_H

#include "sourceFileNode.h"
#include <vector>
#include <map>

// forward declarations
struct TESTsubArchitecture;

//implementation
class SubArchitecture {
    fs::path subArchPath;
    //SubArchitecture* SuperArchitecture;                 -  for later
    std::vector<SourceFileNode*> sourceFiles;
    static std::map<fs::path, SourceFileNode*> allHeaderFiles;
    

public:
    SubArchitecture(fs::path path); //KANSKJE legge til default argument  ="." ?
    static const SourceFileNode* getStaticHeaderFile(fs::path pathArg);
    
protected:
    void findRelevantSourceFiles();
    
friend struct TESTsubArchitecture;
};

// TEST klasse:
struct TESTsubArchitecture {
    static void testAll() {
        constructor();
        findRelevantSourceFiles();
    }
    static void constructor();
    static void findRelevantSourceFiles() { /* TODO */ };
};



    /******************** TIDLIGARE PLANAR:
     * Konstruerer SourceNode:
     *   - har en factoryFunk som finn path til alle dependencies til SourceNode'n
     *      * Desse lagres i medlemsvariabel, for seinare å kunne nyttast til oppslag frå SubArch
     *          objektet som held SourceNode.
     *      * Medlemsvariabel (vector<string>) returneres
     *
     *
     */

    /********************* DÅRLIG: VIL IKKJE FUNKE ***********************
     * void findDependenciesForSourcefiles()  
     * LOKAL VARIABEL: vector<string> unhandledPaths;
     * DESIGNVALG: Skiller klart mellom filde- og headerfiler, dvs at en cpp ikkje kan inkluderes
     *   -> Kall constructAllSourefiles() og legg til returvectoren i unhandledPaths.
     *   -> while (!unhandledPaths.empty() )
     *      * sjekk om headerfila eksisterer i static-medlemsvariabelen   allHeaderFiles
     *          TRUE: 
     *      og plasserer desse i auto vector<string> variable: sourcefilePaths
     *  *  For kvar av desse, 
     *  -> Lager og går gjennom unhandledPaths, som er alle uhandterte paths.
     *  ->
     *
     *
     *   constructAllSourefiles()
     *      -> Lagar og går gjennom alle kildefilende 
     *          - Lager ved å kalle systemsInterface.getAllSourceFilePth() 
     *          - Går gjennom alle filene, og søker etter lokale #include "" statements
     *              Navnet på alle dependencies lagrast i vector<string>, som returneres fra funk.
     *      -> Return: dependencyPaths (sjå førre linja)
     */

#endif
