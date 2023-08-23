#include <iostream>
using namespace std;
#include "Queue.h"



 Queue::~Queue(){

     Node* newnode = head;

     while(head != nullptr){
         newnode = head;
         head = head->next;
         delete newnode;
     }


 }


void Queue::enQueue(const Player &data){

    Node *newnode = new Node(data);

    if(tail == nullptr){
        head = tail = newnode;
        num_elements++;
        return;
    }

    tail->next = newnode;
    tail = newnode;
    num_elements++;

}



void Queue::deQueue(){

    if(head == nullptr)
        return;

    Node *newnode = head;
    head = head->next;

    if(head == nullptr)
        tail = nullptr;

    num_elements--;
    delete(newnode);

}

bool Queue::empty(){

    if(num_elements == 0)
        return true;
    
    return false;
}