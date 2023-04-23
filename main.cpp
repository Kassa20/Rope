#include <iostream>
#include <string>
#include <stack>

#include "Rope.hpp"

using namespace std;

int main()
{
    Rope r1 = Rope(new RopeNode());
    r1.root->data = "Hello_";
    r1.root->weight = 6;

    Rope r2 = Rope(new RopeNode());
    r2.root->data = "Rope";
    r2.root->weight = 4;

    Rope r3 = Rope(new RopeNode());
    r3.root->data = "_Data";
    r3.root->weight = 5;

    // Rope t = Rope(new RopeNode());
    // t.root->data = "_structure";
    // t.root->weight = 10;


    Rope r4 = Rope(new RopeNode());

    r1.concat(r2);
    r1.concat(r3);
    // r1.concat(t);

    r1.split(12, r4);
    r1.print();
    r4.print();


    return 0;
}
