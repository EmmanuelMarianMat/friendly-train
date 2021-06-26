#include<iostream>
#include<time.h>
using namespace std;

class Node
{
    public:
        Node(int x){
            data = x;
            next = NULL;
        }

    private:
        Node *next;
        int data;
        friend class PriorityQueue;
};

class PriorityQueue{
    public:
        PriorityQueue(){
            head = tail = NULL;
        }

        bool isEmpty(){
            return head==NULL;
        }

    void enqueue(int value){
        Node *newNode = new Node(value);

        if(head==NULL){
            head = tail = newNode;
            return;    
        }

    }

    void printQueue(){
            Node *curr = head;
            while(curr){
                cout<<curr->data<<" -> ";
                curr = curr->next;
            }
            cout<<"NULL"<<endl;
        }

    private:
        Node *head, *tail;

};