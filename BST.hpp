/* Created by Kathleen Higgins and Aastha Desai
October 21, 2025
BST.hpp
*/
#ifndef BST_HPP_
#define BST_HPP_

#include <iostream>
#include <stdlib.h>
#include "TNode.hpp"

using std::string; 

class BST {
    friend class Interface; 
    TNode* root; 
    bool extraInfo;
public:
    /*
      BST operations:
      - insert: insert a Species (name, status, info)
      - find: return pointer to TNode with given species name
      - remove: remove node with given name (AVL-balanced)
      - updateStatus: change status field of a species
      - printTreeIO / Pre / Post: traversals
    */

    BST(const bool Xtra);
    ~BST();

    int getHeight(TNode* n);
    void updateHeight(TNode* node);
    void updateUpwards(TNode* n);

    bool insert(const string sp, const string st, const string inf);
    TNode* insertHelper(TNode* node, const string sp, const string st, const string inf); 
    TNode* find(const string name);

    void printTreeIO();
    void printTreePre();
    void printTreePost();

    void printIOHelper(TNode* node);
    void printPreHelper(TNode* node);
    void printPostHelper(TNode* node);

    void updateStatus(const string name, const string status);

    TNode* remove(const string name);
    TNode* delNode(TNode* root); 
    TNode* getSuccessor(TNode* curr);

    TNode* deleteMin(TNode* n);
    TNode* minNode(TNode* n);

    // === AVL-specific helpers ===
    int getBalance(TNode* n);
    TNode* rotateLeft(TNode* x);
    TNode* rotateRight(TNode* y);
    TNode* rotateLeftRight(TNode* z);
    TNode* rotateRightLeft(TNode* z);
    TNode* rebalance(TNode* node);
    
    void deletionHelper(TNode* node);
};

#endif /* BST_HPP_ */
