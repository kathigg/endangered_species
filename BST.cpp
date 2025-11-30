#include "BST.hpp"
#include "TNode.hpp"
using namespace std;


int BST::getHeight(TNode* n) {
    return n ? n->height : 0;
}

void BST::updateHeight(TNode* node) {
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


TNode* BST::minNode(TNode* n) {
    if (!n) return nullptr;
    while (n->left) n = n->left;
    return n;
}

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
    return rebalance(n);
}


TNode* BST::rotateLeft(TNode* x) {
    TNode* y = x->right;
    TNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    if (T2) T2->parent = x;

    y->parent = x->parent;
    x->parent = y;

    updateHeight(x);
    updateHeight(y);

    return y;
}

TNode* BST::rotateRight(TNode* y) {
    TNode* x = y->left;
    TNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    if (T2) T2->parent = y;

    x->parent = y->parent;
    y->parent = x;

    updateHeight(y);
    updateHeight(x);

    return x;
}

TNode* BST::rebalance(TNode* node) {
    updateHeight(node);

    int balance = getHeight(node->left) - getHeight(node->right);

    if (balance > 1) {
        if (getHeight(node->left->right) > getHeight(node->left->left)) {
            node->left = rotateLeft(node->left);
            if (node->left) node->left->parent = node;
        }
        return rotateRight(node);
    }

    if (balance < -1) {
        if (getHeight(node->right->left) > getHeight(node->right->right)) {
            node->right = rotateRight(node->right);
            if (node->right) node->right->parent = node;
        }
        return rotateLeft(node);
    }

    return node;
}


BST::BST(const bool Xtra) {
    root = NULL;
    extraInfo = Xtra;
}

BST::~BST() {
    deletionHelper(root);
    root = nullptr;
}

void BST::deletionHelper(TNode* node) {
    if (!node) return;
    deletionHelper(node->left);
    deletionHelper(node->right);
    delete node;
}


bool BST::insert(const string sp, const string st, const string inf) {
    root = insertHelper(root, sp, st, inf);
    if (root) root->parent = nullptr;
    return true;
}

TNode* BST::insertHelper(TNode* node, const string sp, const string st, const string inf) {
    if (!node) {
        return new TNode(sp, st, inf);
    }

    if (sp < node->animal->name) {
        node->left = insertHelper(node->left, sp, st, inf);
        if (node->left) node->left->parent = node;
    }
    else if (sp > node->animal->name) {
        node->right = insertHelper(node->right, sp, st, inf);
        if (node->right) node->right->parent = node;
    }
    else {
        return node;
    }

    updateHeight(node);
    return rebalance(node);
}

// -------------------- FIND --------------------

TNode* BST::find(const string name) {
    TNode* current = root;
    while (current != nullptr) {
        if (name == current->animal->name) return current;

        if (name < current->animal->name)
            current = current->left;
        else
            current = current->right;
    }
    return NULL;
}


void BST::printTreeIO() {
    printIOHelper(root);
}

void BST::printIOHelper(TNode* node) {
    if (!node) return;
    printIOHelper(node->left);
    cout << node->animal->name << endl;
    printIOHelper(node->right);
}

void BST::printTreePre() {
    printPreHelper(root);
}

void BST::printPreHelper(TNode* node) {
    if (!node) return;
    cout << node->animal->name << endl;
    printPreHelper(node->left);
    printPreHelper(node->right);
}

void BST::printTreePost() {
    printPostHelper(root);
}

void BST::printPostHelper(TNode* node) {
    if (!node) return;
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


TNode* BST::delNode(TNode* root) {
    if (!root) return nullptr;

    // 0 or 1 child
    if (!root->left || !root->right) {
        TNode* child = root->left ? root->left : root->right;
        if (child) child->parent = root->parent;
        delete root;
        return child;
    }

    // 2 children
    TNode* succ = minNode(root->right);
    *(root->animal) = *(succ->animal); // Copy data

    root->right = deleteMin(root->right);
    if (root->right) root->right->parent = root;

    updateHeight(root);
    return rebalance(root);
}

TNode* BST::remove(const string name) {
    TNode* target = find(name);
    if (!target) return nullptr;

    TNode* parent = target->parent;

    // Removing the root
    if (target == root) {
        root = delNode(root);
        if (root) root->parent = nullptr;
        return root;
    }

    TNode* replacement = delNode(target);

    if (parent->left == target)
        parent->left = replacement;
    else
        parent->right = replacement;

    if (replacement) replacement->parent = parent;

    return rebalance(parent);
}
