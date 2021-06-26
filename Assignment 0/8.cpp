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
            head = NULL;
        }

        bool isEmpty(){
            return head==NULL;
        }

        void enqueue(int value){
            Node *newNode = new Node(value);
            Node *prev=NULL, *curr=head;
            
            while(curr&&curr->data>=value){
                prev = curr;
                curr = curr->next;
            }

            if(!prev)
                head = newNode;
            else
                prev->next = newNode;

            newNode->next = curr;
        }

        int dequeue(){
            if(isEmpty()){
                return INT_MIN;
            }
            else{
                int ret = head->data;
                Node *curr = head;
                head = head->next;
                delete curr;
                return ret;
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
        Node *head;
};

int main(){
    PriorityQueue queue;
    
    srand(time(0));
    for(int i=0;i<30;i++){
        queue.enqueue(rand());
    }
    
    for(int i=0;i<30;i++){
        cout<<queue.dequeue()<<" ";
    }
    
    cout<<endl;
}
