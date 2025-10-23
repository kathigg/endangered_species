#include "BST.hpp"
#include "TNode.hpp"
using namespace std;   

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
    deletionHelper(root); 
    root = nullptr;
}

void BST::deletionHelper(TNode* node){
    if (node == NULL){
        return; 
    }
    // let's do some post-order traversal! (how we do deletion with a BST)
    deletionHelper(node->left);
    deletionHelper(node->right);
    delete node;

}
bool BST::insert(const string sp, const string st, const string inf) {
    root = insertHelper(root, sp, st, inf);
    return true;
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
    printPreHelper(root);
}

void BST::printPreHelper(TNode* node){
    if (node == NULL){
        return;
    }
    cout << node->animal->name << endl;
    printPreHelper(node->left);
    printPreHelper(node->right);
}

void BST::printTreePost() {
    printPostHelper(root);
}

void BST::printPostHelper(TNode* node){
    if (node == NULL){
        return;
    }
    printPostHelper(node->left);
    printPostHelper(node->right);
    cout << node->animal->name << endl;

}

void BST::updateStatus(const string name, const string status){
    TNode* node = find(name);
    if (node != NULL){
        node->animal->status = status;
    }

}

TNode* BST::getSuccessor(TNode* curr) {
    if (curr == nullptr || curr->right == nullptr) return nullptr;
    curr = curr->right;
    while (curr != nullptr && curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

TNode* BST::delNode(TNode* root) {
        // node with 0 or 1 child 
        if (root->left == nullptr) {
            TNode* temp = root->right; 
            if (temp != nullptr) temp->parent = root->parent;
            delete root; 
            return temp;
        }
        if (root->right == nullptr) {
            TNode* temp = root->left;
            if (temp != nullptr) temp->parent = root->parent;
            delete root;
            return temp;
        }

        // Node with two children 
        TNode* succ = getSuccessor(root);
        if (succ == nullptr) return root; 
        *(root->animal) = *(succ->animal);
        root->right = delNode(root->right); 
        return root; 
}


TNode* BST::remove(const string name) {
    TNode* to_delete = find(name);
    if (to_delete == nullptr) return nullptr;
    if (to_delete == root){
        root = delNode(root);
        return root;
    }
    TNode* deleted = delNode(to_delete);
    return deleted;
    /* 
    1. start at the root
    2. do a find for the data you want to remove (go left if less, right if greater, etc)
    if you find the data in the tree, remove it!
    if you don't find the data, you'll reach a null node 

    there are 3 possible cases for removing a node:
    1. the node to be removed has 0 children (is a leaf)
    2. the node to be removed has 1 child
    3. the node to be removed has 2 children
    */



}





