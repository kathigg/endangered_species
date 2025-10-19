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