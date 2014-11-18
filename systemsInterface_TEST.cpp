#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SystemsInterface test
#include <boost/test/unit_test.hpp>
#include "systemsInterface.h"
#include <boost/filesystem.hpp>
#include "fargar.h"

#define GREENTEXT(text) <<GREENCOLOR <<text <<DEFAULTCOLOR
#define REDTEXT(text) <<REDCOLOR <<text <<DEFAULTCOLOR

using std::cout;
using std::vector;
using std::string;

namespace fs = boost::filesystem;
using boost::filesystem::path;

BOOST_AUTO_TEST_CASE( getAllSourceFilesPaths )
{
    BOOST_CHECK( SystemsInterface::getAllSourcefilePaths("./testFolder/newFolder/").size() == 0 ); 
    vector<fs::path> allSourefilePaths = SystemsInterface::getAllSourcefilePaths("./testFolder/");
    for (auto iter : allSourefilePaths)
        cout<<"Item: " <<iter <<'\n';

    cout<<"\n\n\nTest "<<YELLOWCOLOR <<"SystemsInterface" <<DEFAULTCOLOR <<'\n';
    BOOST_CHECK( SystemsInterface::getAllSourcefilePaths("./testFolder/").size() == 4);

    allSourefilePaths = SystemsInterface::getAllSourcefilePaths("./testFolder/");
    for (auto iter : allSourefilePaths)
        cout<<"Item: " <<iter <<std::endl;
}

#if 0
BOOST_AUTO_TEST_CASE( getAllSourceFilesPaths )
{
    cout<<"Starting boost test case\n";

    cout<<"Checking path ./testFolder/newFolder/ \n";
    vector<string> testVector1 = SystemsInterface::getAllSourcefilePaths("./testFolder/newFolder/");
    /* This folder does not contain any cpp source files */
    BOOST_CHECK( testVector1.empty() );


    string test1 = "Trallala, dette går bra";
    if (test1.find("Trallala, dette går bra") == string::npos)
        cout<<REDCOLOR <<"Fann 'an ikkje\n\n\n\n\n" <<DEFAULTCOLOR;
    else
        cout<<GREENCOLOR <<"Fann 'an\n" <<DEFAULTCOLOR;


    SystemsInterface::getAllSourcefilePaths(path("./");


    cout<<"Testing path ./testFolder/: \n";
    vector<string> testVector2 = SystemsInterface::getAllSourcefilePaths("./testFolder/");
    for (auto iter : testVector2)
        cout<<"\tElement: " <<iter <<"\n";

    /* This folder should only contain the (cpp) source file testFolder/source1.cpp */
    BOOST_CHECK( testVector2.size() == 1 );
    cout<<"Size: " <<testVector2.size() <<"\n";
    BOOST_CHECK_EQUAL( testVector2.front(), "testFolder/source1.cpp");
}
#endif
