/* Created by Kathleen Higgins and Aastha Desai
October 21, 2025
BST.hpp
*/
#ifndef BST_HPP_
#define BST_HPP_

#include <iostream>
#include <stdlib.h>
#include "Interface.hpp"

using std::string; 

class BST {
    friend class Interface; 
    class TNode* root; 
    bool extraInfo;
    public:
    /* need at minimum the constructor, find, insert, the 3 print methods, and delete methods */
    /* need printTreeIO(); printTreePre(); printTreePost(); */
    /* update status, find, remove*/
    /* what does find do? 
    TNode *t = tree->find(name); returns a pointer to the TNode with species name
    what does insert do?
    takes in parameters of name, status, and info, and inserts a new TNode with a Species with those fields into the BST
    what does remove do? 
    TNode *t = tree->remove(name); removes the TNode with species name from the BST and returns a pointer to that TNode
    ooh, updateStatus! what does updateStatus do? 
    well, it takes in a name and status, and updates the status field of the Species in the TNode with that name to the new status
    okay, so we need the constructor, the insert, and the 3 print methods. setHeights will be a function we'll need to write after, but originally, all the heights 
    start at 1. 
    for remove, write one genral remove method and 2 helper methods. the general remove methods determines the node to be removed and 
    if the node has 0 children, one child, or 2 children. 
    */
        BST(const bool Xtra); // constructor
        ~BST(); // destructor
        void insert(const string sp, const string st, const string inf);
        class TNode* find(const string name); 
        class Tnode* insert(class TNode* node, const string sp, const string st, const string inf);
        void printTreeIO();
        void printTreePre();
        void printTreePost();

        void updateStatus(const string name, const string status);
        class TNode* remove(const string name);
};
#endif /* BST_HPP_ */
