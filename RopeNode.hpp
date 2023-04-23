#include <string>

using namespace std;


class RopeNode
{
public:
    RopeNode* left;
    RopeNode* right;
    RopeNode* parent;
    string data;
    int weight;

    RopeNode(string s)
    {
        data = s;
        left = right = nullptr;
        weight = s.length();
    }

    RopeNode()
    {
        data = "";
        left = right = nullptr;
        weight = 0;
    }
};