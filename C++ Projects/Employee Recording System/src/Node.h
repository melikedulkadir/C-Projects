//
// Created by Melike on 27.11.2021.
//

#ifndef ASSIG2_NODE_H
#define ASSIG2_NODE_H

#include "TemporaryEmployee.h"

//node class for wrapping temporaryEmployee object and its next value
class Node {
private:
    TemporaryEmployee value;
    int next;

public:

    //initializer list constructor
    Node(TemporaryEmployee value, const int& next) : value(value) , next(next) {}
    //default
    Node() = default;


    //getters & setters
    TemporaryEmployee getValue(){
        return this->value;
    }

    int getNext(){
        return this->next;
    }

    void setNext(const unsigned& next){
        this->next = next;
    }
};

#endif //ASSIG2_NODE_H
