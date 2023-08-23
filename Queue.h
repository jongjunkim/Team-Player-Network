#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Player.h"


class Queue{
    private: 
        class Node{
            public: 
                Player data;
                Node *next;

                Node(){
                    data = Player();
                    next = nullptr;
                }

                Node(const Player &data){
                    this->data = data;
                    next = nullptr;
                }


        };

        Node *head, *tail;
        unsigned num_elements;

    public:
        Queue(){head = tail = nullptr; num_elements=0;};
        ~Queue();
        void enQueue(const Player &data);
        void deQueue();
        bool empty();
        int getNum(){
            return num_elements;
        }
        Player getFrontPlayer(){
            return head->data;
        }



};

#endif
 