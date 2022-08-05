//
// Created by Melike on 26.11.2021.
//

#ifndef ASSIG2_LINKEDLIST_H
#define ASSIG2_LINKEDLIST_H

#include "Node.h"
#include <vector>
const int SIZE = 20;


class CircularArrayLinkedList{

private:
    int avail;
    int head;
    int tail;
    Node list[SIZE]; // node class array for saving temporaryEmployee nodes.

public:

    CircularArrayLinkedList() {
        this->avail = 0;
        this->head = 0;
        this->tail = 0;
        for(int i = 0; i != SIZE-1; ++i){
            this->list[i].setNext(-1);
        }
    }

    // check function for controlling is given employee exist or not
    bool isExist(int empNum){
        for (int i = 0; i < SIZE; ++i) {
            if(list[i].getValue().getEmployeeNumber()==empNum)
                return true;
        }return false;
    }

    // finds the employee with empNum and returns it
    TemporaryEmployee findEmployee(int empNum){
        int i = head;
        while(list[i].getNext() != head){
            if(list[i].getValue().getEmployeeNumber()==empNum){
                return list[i].getValue();
            }
        }
        if (list[i].getNext() == head){
            if(list[i].getValue().getEmployeeNumber()==empNum){
                return list[i].getValue();
            }
        }TemporaryEmployee temporaryEmployee;
    }

    // finding available place in the array for inserting value
    int findAvail(){
        for(int i = 0 ; i != SIZE ; ++i){
            if(list[i].getNext() == -1){
                return i;
            }
        }
        return -1;
    }

    // insertion function after finding suitable place
    bool insert(TemporaryEmployee temp){

        int suit = findSuitable(temp);
        int avail = findAvail();
        if(suit == -1){
            return false;
        }

        //first value to an empty list
        if(avail == 0){
            Node newNode(temp,head);
            this->list[head] = newNode;
            head = 0;
            tail = 0;
            return true;
        }

        else if(suit == head){
            if (head == tail && suit==0){     // insert second elem
                Node newNode(temp,head);
                list[avail] = newNode;
                list[head].setNext(avail);
               if(temp.getEmployeeNumber()<list[head].getValue().getEmployeeNumber())   // if smaller head become new node
                   head = avail;
               else
                   tail = avail;

            }else{
                Node newNode(temp,list[suit].getNext());
                list[avail] = newNode;
                list[suit].setNext(avail);
            } return true;
        }

        //adding the last element to the list
        else if(suit == tail){
            Node newNode(temp,head);
            list[suit].setNext(avail);
            tail = avail;
            return true;
        }

        //any value to a somewhat filled list
        Node newNode(temp,list[suit].getNext());
        list[avail] = newNode;
        list[suit].setNext(avail);
        return true;


    }

    // finding suitable place for inserting value to the list
    int findSuitable(TemporaryEmployee temp){
        if(findAvail() == -1){
            return -1;
        }

        int i = head;
        int last = head;

        while(list[i].getNext() != head){

            if(list[i].getValue().getEmployeeNumber()==0){
                return last;
            }

            if(temp.getEmployeeNumber() > list[i].getValue().getEmployeeNumber()){
                last = i;
                i = list[i].getNext();
            }
            else if(temp.getEmployeeNumber() < list[i].getValue().getEmployeeNumber()){
                return last;
            }

        }

        if (list[i].getNext() == head) {
            if(temp.getEmployeeNumber() > list[i].getValue().getEmployeeNumber()){
                last = tail;
            }
            else if(temp.getEmployeeNumber() < list[i].getValue().getEmployeeNumber()){
                last = head;
            }
        }

        return last;
    }

    // delete function for permanentEmployee
    void deleteTemployee(TemporaryEmployee temp){
        for (int i = 0; i < SIZE; ++i) {
            if(list[i].getValue().getEmployeeNumber()==temp.getEmployeeNumber()){
                int curr = list[i].getNext();
                for (int j = 0; j < SIZE; ++j) {
                    if(i==list[j].getNext()){
                        list[j].setNext(curr);
                        // if deleting item is head
                        if(head == i){
                            head = curr;
                         // if deleting item is tail
                        }else if(tail==i){
                            tail = j;
                        }
                    }
                }

            }
            list[i] = Node();
            list[i].setNext(-1);
        }
    }

    //update function for temporaryEmployee
    void update(TemporaryEmployee temp,string title,float salary_coef){
        for (int i = 0; i < SIZE; ++i) {
            if(list[i].getValue().getEmployeeNumber()==temp.getEmployeeNumber()){
                list[i].getValue().setTitle(title);
                list[i].getValue().setSalaryCoefficient(salary_coef);
            }
        }
    }

    void addEmployee(vector<Employee>& employeeList) {
        int i = head;
        while(list[i].getNext() != head){
            if(list[i].getValue().getEmployeeNumber()==0){
                return;
            }
            employeeList.push_back(list[i].getValue());
            i = list[i].getNext();
        }
        if (list[i].getNext() == head){
            employeeList.push_back(list[i].getValue());
        }
    }
};

#endif //ASSIG2_LINKEDLIST_H
