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
        }
        else if (sp > node->animal->name) {
            // insert into right subtree
            if (node->right == NULL){
                TNode *newNode = new TNode(sp, st, inf);
                node->right = newNode;
                newNode->parent = node;
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
    return node; 
}

TNode* BST::find(const string name) { 
    TNode* current = root;
    while (current != NULL) {
        if (name == current->animal->name) {
            return current;
        }
        else {
            if (name < current->animal->name) {
                current = current->left;
            }
            else {
                current = current->right; 
            } 
            } 
        }  
    return NULL;
}

void BST::printTreeIO() {
    //ok, so printing a tree in order means that you go all the way down to the 
    //bottom of the left subtree, and move from there. 
    /* 1. visit left node 
    2. print root
    3. visit right node */
    printIOHelper(root);
}

void BST::printIOHelper(TNode* node){
    if (node == NULL){
        return;
    }
    printIOHelper(node->left);
    cout << node->animal->name << endl;
    printIOHelper(node->right);
}

void BST::printTreePre() {

}

void BST::printTreePost() {

}

void BST::updateStatus(const string name, const string status){

}

TNode* BST::remove(const string name) {

}





