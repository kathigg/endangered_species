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