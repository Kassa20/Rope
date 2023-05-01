#include <iostream>
#include <string>
#include <stack>

#include "RopeNode.hpp"

using namespace std;

// compare the relevant fields of the two objects
bool operator==(const RopeNode& lhs, const RopeNode& rhs) 
{
    return lhs == rhs;
}

class Rope
{
public:
    RopeNode* root;

    Rope()
    {
        root = new RopeNode("");
    }

    Rope(RopeNode* newNode)
    {
        root = new RopeNode(newNode->data);
    }

    void makeEmpty() {
        root = new RopeNode("");
    }

    // copy function to copy original node to new node to preserve data    
    RopeNode* copyRope(RopeNode* oldRoot, RopeNode* parent)
    {
        if(oldRoot == nullptr)
            return nullptr;

        RopeNode *copy = new RopeNode();
        copy->data = oldRoot->data;
        copy->weight = oldRoot->weight;
        copy->left = copyRope(oldRoot->left, copy);
        copy->right = copyRope(oldRoot->right, copy);
        copy->parent = parent;
        return copy;
    }

    // join two rope nodes
    void concat(Rope &newRope)
    {
        RopeNode* newRoot = new RopeNode();
        RopeNode* right = copyRope(newRope.root, nullptr);
        newRoot->left = this->root;
        newRoot->right = right;
        newRoot->weight = this->root->weight;

        if(this->root->right)
            newRoot->weight += this->root->right->weight;
        
        this->root = newRoot;
        this->root->left->parent = this->root;
        this->root->right->parent = this->root;
    }

    // find the char at index i
    char indexAt(int i)
    {
        RopeNode *p = this->root;
        int k = i;
        while (true) {
            if (p->left) {
                if (k < p->weight) {
                    // follow left subtree
                    p = p->left;
                } else if (k >= p->weight) {
                    // follow right subtree and adjust index
                    k -= p->weight;
                    p = p->right;
                }
            } else {
                // leaf node
                return p->data[k];
            }
        }
    }

    void print() 
    {
        cout << endl;
        printRope(root);
        cout << endl;
        cout << endl;
    }

    // recursive print function 
    void printRope(RopeNode* r) {
        if (r != nullptr) {
            printRope(r->left);
            if (!r->data.empty())
                cout << r->data;
            printRope(r->right);
        }
    }

    
    // recursively walk down the right
    RopeNode* isChild(RopeNode* walk)
    {
        if(walk->right == nullptr)
            return walk;

        return isChild(walk->right);
        
    }


    //The first i characters should stay in the current rope, while a new
    // Rope (newRope) should contain the remaining characters.
    Rope* split(int index, Rope &newRope)
    {
        if(index <= 0)
        {
            return nullptr;
        }

        else
        {
            RopeNode* tmp = root;
            int index_helper = index;

            //find the index to split
            while (tmp->left || tmp->right)
            {
                if(index_helper < tmp->weight)
                {
                    tmp = tmp->left;
                }

                else
                {
                    index_helper -= tmp->weight;
                    tmp = tmp->right;
                }
            }

            // // Edge case*
		    // if index_helper is in the middle of a node's value
		    // split Rope into Ro & pe for example
            if(index_helper != 0)
            {
                string tmp_str1, tmp_str2;

                // copy string upto index_helper
                for(int i = 0; i < index_helper; i++)
                {
                    tmp_str1 += tmp->data[i];
                }

                //copy string after index_helper
                for(int i = index_helper; i < tmp->weight; i++)
                {
                    tmp_str2 += tmp->data[i];
                }


                //Creating pointers for new nodes to store split result
                tmp->left =  new RopeNode();
                tmp->right = new RopeNode();

                // left node
                tmp->left->data = tmp_str1;
                tmp->left->weight = tmp_str1.length();
                tmp->left->parent = tmp;

                //right node
                tmp->right->data = tmp_str2;
                tmp->right->weight = tmp_str2.length();
                tmp->right->parent = tmp;

                //clear parent data
                tmp->data = "";
                tmp->weight = tmp->left->weight;

                if(index_helper < tmp->weight)
                    tmp = tmp->left;
                else
                {
                    index_helper -= tmp->weight;               
                    tmp = tmp->right;
                }

            }
            // end of edge case 
            
            RopeNode* newRoot = new RopeNode();
            RopeNode* walk = this->root;
            newRoot->left = tmp;
            tmp->parent = newRoot;
            this->root->weight -= tmp->weight;

            // check if tmp is right most child, to prevent duplication(edge case)
            if(isChild(walk) != tmp)
            {
                newRoot->right = this->root->right;
                this->root->right->parent = newRoot;
            }
            
            newRope.root = newRoot;
        }

        return &newRope;

    }

};