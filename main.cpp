#include <iostream>
#include <string>


#include "Rope.hpp"

using namespace std;

int main()
{
    //create a rope nodes with strings 
    Rope r1 = Rope(new RopeNode("Hello_"));
    Rope r2 = Rope(new RopeNode("Rope"));
    Rope r3 = Rope(new RopeNode("_Data"));


    // Rope t = Rope(new RopeNode("_structure"));

    //new node to save the result of splitting
    Rope r4 = Rope(new RopeNode());

    r1.concat(r2);
    r1.concat(r3);
    // r1.concat(t);

    // everything after i = 6 (including i)is stored in r4
    r1.split(6, r4);
    r1.print();

    // print the right part of split result
    r4.print();


    return 0;
}
