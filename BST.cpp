#include "BST.hpp"
#include "TNode.hpp"

/* constructor! */
BST::BST(const bool Xtra) {
    root = NULL; 
    extraInfo = Xtra; 
}
/* destructor! */
BST::~BST() {
    // Destruction method to free all nodes in the tree
    // fun fact---this is being implemented using post-order traversal,
    // the method that works by recusively doing a post-order traversal of the 
    // left subtree and the right subtree, followed by a visit to the root node. 
    // As Professor Yarrington always says, you have to kill the children before 
    // you kill the parents! 
}
void BST::insert(const string sp, const string st, const string inf) {
    
}
TNode* BST::find(const string name) { 

}




