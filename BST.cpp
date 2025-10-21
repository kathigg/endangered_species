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
    root = insertHelper(root, sp, st, inf);
}
TNode* BST::insertHelper(TNode* node, const string sp, const string st, const string inf) {
    if (node == NULL){
        TNode* nnode = new TNode(sp, st, inf);
        return nnode;
    }
    else {
        if (sp < node->animal->name) {
            //insert into left subtree
            if (node->left == NULL){
                TNode *newNode = new TNode(sp, st, inf);
                node->left = newNode;
                newNode->parent = node;
            }
            else {
                //recursive insert into left subtree
                insertHelper(node->left, sp, st, inf);
            }
        if (sp > node->animal->name) {
            // insert into right subtree
            if (node->right == NULL){
                TNode *newNode = new TNode(sp, st, inf);
                node->right = newNode;
                newNode->parent = root;
            }
            else {
                //recursive insert into right subtree
                insertHelper(node->right, sp, st, inf);
            }
        }
        else {
            // species already exists in the tree
        }
        }
    }  
}


TNode* BST::find(const string name) { 
    
}

void BST::PrintTreeIO() {

}

void BST::PrintTreePre() {

}

void BST::PrintTreePost() {

}

void BST::updateStatus(const string name, const string status){

}

TNode* BST::remove(const string name) {

}





