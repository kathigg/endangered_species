#include "BST.hpp"
#include "TNode.hpp"
using namespace std;   

int BST::getHeight(TNode* n) {
    return n ? n->height : 0;
}

void BST::updateHeight(TNode* node){
    if (!node) return;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = 1 + std::max(leftHeight, rightHeight);
}

void BST::updateUpwards(TNode* n) {
    while (n) {
        updateHeight(n);
        n = n->parent;
    }
}

// Leftmost in a subtree (successor helper)
TNode* BST::minNode(TNode* n) {
    if (!n) return nullptr;
    while (n->left) n = n->left;
    return n;
}

// Delete the leftmost node from a subtree and return the new subtree root.
// Maintains parent pointers.
TNode* BST::deleteMin(TNode* n) {
    if (!n) return nullptr;
    if (!n->left) {
        TNode* r = n->right;
        if (r) r->parent = n->parent;
        delete n;
        return r;
    }
    n->left = deleteMin(n->left);
    if (n->left) n->left->parent = n;
    updateHeight(n);
    return n;
}

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
    if (!node) return new TNode(sp, st, inf);

    if (sp < node->animal->name) {
        node->left = insertHelper(node->left, sp, st, inf);
        node->left->parent = node;
    } else if (sp > node->animal->name) {
        node->right = insertHelper(node->right, sp, st, inf);
        node->right->parent = node;
    } else {
        // duplicate: no-op (or update info if desired)
        return node;
    }

    updateHeight(node);
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
    if (!root) return nullptr;

    // 0 or 1 child — return the replacement and fix parent
    if (!root->left) {
        TNode* temp = root->right;
        if (temp) temp->parent = root->parent;
        delete root;
        return temp;
    }
    if (!root->right) {
        TNode* temp = root->left;
        if (temp) temp->parent = root->parent;
        delete root;
        return temp;
    }

    // 2 children:
    // 1) find successor (min of right subtree)
    TNode* succ = minNode(root->right);         // never null here
    // 2) copy full payload (not just name)
    *(root->animal) = *(succ->animal);
    // 3) delete the successor node specifically
    root->right = deleteMin(root->right);       // removes that exact node
    if (root->right) root->right->parent = root;

    updateHeight(root);
    return root;
}

TNode* BST::remove(const string name) {
    TNode* target = find(name);
    if (!target) return nullptr;

    TNode* parent = target->parent;

    if (target == root) {
        root = delNode(root);               // delNode returns new subtree root
        if (root) root->parent = nullptr;
        // After root replacement, update heights upward from new root
        updateUpwards(root);
        return root;
    }

    // Decide which side to replace on parent
    TNode* replacement = delNode(target);   // returns new subtree head at that spot
    if (parent->left == target) {
        parent->left = replacement;
    } else {
        parent->right = replacement;
    }
    if (replacement) replacement->parent = parent;

    // Recompute heights up to the root
    updateUpwards(parent);

    return parent;
}





