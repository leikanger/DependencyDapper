#include "sourceFileNode.h" 
#include "systemsInterface.h" 
#include "fargar.h"

#include <iostream>
#include <vector>
#include <string>
//#include <algorithm>    // for_each, bl.a.

// Hugs dette: //template<class T> using smartPeikar = typename std::shared_ptr<T>;

using std::cout;
using std::string;
using std::vector;

int main()
{   
    TESTsystemsInterface::mainTest();

    SourceFileNode testObject("main.cpp");
    TESTsourceFileNode::testFindLocalDependencies(&testObject);
}





#if 0
void printFunk(int);
void testeLittTil();

int main() 
{
    std::vector<int> myVector {1,2,3,4,5,5,4,5};

    // C-style løkke:
    cout <<GREENCOLOR <<"C-style løkke:\n" <<DEFAULTCOLOR;

    for (int i = 0; i<myVector.size(); ++i)
        cout<<myVector[i] <<" ";

    // C++-iterator style:
    cout <<GREENCOLOR <<"\nIterator-style:\n" <<DEFAULTCOLOR;

    std::vector<int>::iterator vectorIter;
    for (vectorIter = myVector.begin(); vectorIter != myVector.end(); ++vectorIter)
        cout<<*vectorIter <<" ";

    // C++11-style:
    cout <<GREENCOLOR <<"\nC++11 style:\n" <<DEFAULTCOLOR;

    for (int iter : myVector)   // Her kunne eg også brukt auto i staden for int
        cout<<iter <<" ";

    // for_each style
    cout<<GREENCOLOR <<"\nstd::for_each\n" <<DEFAULTCOLOR;

    std::for_each (myVector.begin(), myVector.end(), &printFunk);

    // for_each style med lambda function:
    cout<<GREENCOLOR <<"\nstd::for_each med lambda funksjon\n" <<DEFAULTCOLOR;

    std::for_each(myVector.begin(), myVector.end(),     [](int i){ cout<<i <<" "; }     );

    cout <<"\n__________________________\n";

    testeLittTil();

    return 0;
}

void printFunk(int iArg) {
    cout<<iArg <<" ";
}

void testeLittTil()
{
    std::vector<double> talliste {1.2, 3.2, 5.2, 7.2, 9.2, 11.2, 13.2 };    
    cout<<YELLOWCOLOR <<"skriv ut original talliste: \n" <<DEFAULTCOLOR; 
    for( auto i : talliste )
        cout<<i <<" ";

    cout<<YELLOWCOLOR <<"\nSå endrer eg litt på den:\n" <<DEFAULTCOLOR;

    std::for_each( talliste.begin(), talliste.end(),    [](double &i){ i = i*2; } );
    for (auto iter : talliste)
        cout <<iter <<" ";
    cout <<"\n\n";
}
#endif
