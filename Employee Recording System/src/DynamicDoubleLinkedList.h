//
// Created by Melike on 28.11.2021.
//

#ifndef ASSIG2_DYNAMICDOUBLELINKEDLIST_H
#define ASSIG2_DYNAMICDOUBLELINKEDLIST_H
#include <vector>
#include "PermanentEmployee.h"
using namespace std;

class DynamicDoubleLinkedList {
public:
    DynamicDoubleLinkedList() {}


// A doubly linked list node for saving permanentEmployee object and its pointers
    struct Node {
        PermanentEmployee data;
        struct Node *next;
        struct Node *prev;
    };
    struct Node *head = nullptr;
    struct Node* last = nullptr;

    // check function for controlling is given employee exist or not
    bool isExist(int empNum){
        struct Node* node = head;
        while (node != nullptr) {
            if(node->data.getEmployeeNumber()==empNum){
                return true;
            }node = node->next;
        }return false;
    }

    // finds the employee with empNum and returns it
    PermanentEmployee findEmployee(int empNum){
        struct Node* node = head;
        while (node != nullptr) {
            if(node->data.getEmployeeNumber()==empNum){
                return node->data;
            }node = node->next;
        }PermanentEmployee permanentEmployee;
    }

    // insertion function after finding suitable place
    void insert(PermanentEmployee permEmp) {
        struct Node *newNode = new Node;
        newNode->data = permEmp;
        // insert first node
        struct Node *suit = findSuit(permEmp, head);
        if (head == nullptr) {
            head = newNode;
            last = newNode;
            newNode->next= nullptr;
            newNode->prev= nullptr;
            return;
        }

        // insert front
        else if (suit == nullptr) {
            newNode->next = head;
            newNode->prev = nullptr;

            if (head != nullptr){
                head->prev = newNode;
                head = newNode;
            }

        }else{
            newNode->prev = suit;
            if (suit->next != nullptr){
                newNode->next = suit->next;
                suit->next = newNode;
                newNode->next->prev = newNode;
            }
            else{
                newNode->prev->next=newNode;
                newNode->next = nullptr;
                last = newNode;
            }
        }
    }

    // finding suitable place for inserting value
    struct Node* findSuit(PermanentEmployee permEmp,struct Node* node){
        if(head== nullptr)
            return head;
        while (node != nullptr) {
            if(node->data.getDateOfAppointment()<permEmp.getDateOfAppointment()){
                node = node->next;
                if(node->next== nullptr)
                    return node;
            }else if(node->data.getDateOfAppointment()>permEmp.getDateOfAppointment()){
                if(node==head)
                    return nullptr;
                return node->prev;
            }
        }
        return node->prev;
    }

    //update function for permanentEmployee
    bool update(PermanentEmployee permEmp,string title,float salary_coef){
        struct Node* node = head;
        while (node != nullptr) {
            if(node->data.getEmployeeNumber()==permEmp.getEmployeeNumber()){
                node->data.setTitle(title);
                node->data.setSalaryCoefficient(salary_coef);
                return true;
            }node = node->next;
        }
        return true;
    }

    // remove function for permanentEmployee
    void remove(PermanentEmployee permEmp){
        struct Node* node = head;
        while (node != nullptr) {
            if(node->data.getEmployeeNumber()==permEmp.getEmployeeNumber()){
                if(node==head){
                    if(node->next== nullptr){
                        head= nullptr;
                        last= nullptr;
                        return;
                    }
                    node->next->prev = nullptr;
                    head = node->next;
                }else if(node->next== nullptr){
                    node->prev->next = nullptr;
                    last = node->prev;
                }else{
                    node->prev->next= node->next;
                    node->next->prev = node->prev;
                }
            }node = node->next;
        }
    }
    void addEmployee(vector<Employee>& employeeList){
        struct Node* node = head;
        while (node != nullptr) {
            employeeList.push_back(node->data);
            node = node->next;
        }
    }

};



#endif //ASSIG2_DYNAMICDOUBLELINKEDLIST_H
