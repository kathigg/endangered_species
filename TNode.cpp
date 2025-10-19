/* 
TNode.cpp
Created on: October 19th, 2025
Authors: Kathleen Higgins and Aastha Desai
*/ 
#include "TNode.hpp"
#include <iostream>

/* default constructor */
TNode::TNode() {
    left = NULL;
    right = NULL; 
    parent = NULL;
    animal = new Species();
    height = 1;
}

/* parameterized constructor */
TNode::TNode(const string sp, const string st, const string inf) {
    left = NULL;
    right = NULL;
    parent = NULL;
    animal = new Species(sp, st, inf);
    height = 1;
}

/* DESTRUCTION TIME!!! */
TNode::~TNode() {
    delete animal;
}

/* print node info */
void TNode::printNode(const bool XtraInfo) {
    std::cout << "\t" << animal->name << std::endl;
    std::cout << "\t" << animal->status << std::endl;
    std::cout << "\t" << animal->info << std::endl;
    if (XtraInfo) {
        std::cout << "\tHeight: " << height << std::endl;
        std::cout << "\tLeft Child: " << (left ? left->animal->name : "NULL") << std::endl;
        std::cout << "\tRight Child " << (right ? right->animal->name : "NULL") << std::endl;
    }
}


