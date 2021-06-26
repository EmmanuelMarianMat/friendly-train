#include<iostream>
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
        friend class LinkedList;
};

class LinkedList{
    public:
        LinkedList(){
            head = NULL;
            len = 0;
        }

        void insert(int value){
            Node* newNode = new Node(value);
            len+=1;
            int j = (len-1)/2;
            Node *curr = head, *prev = NULL;
            while(j--){
                prev = curr;
                curr = curr->next;
            }
            newNode->next = curr;

            if(prev){
                prev->next = newNode;
            }
            else{
                head = newNode;
            }
        }

        void deleteMid(){
            if(head == NULL){
                cout<<"Empty List; Can't delete"<<endl;
                return;
            }
            int j = (len-1)/2;
            Node *curr = head, *prev = NULL;
            while(j--){
                prev = curr;
                curr = curr->next;
            }
            if(!prev)
                head = curr->next;
            else
                prev->next = curr->next;

            len-=1;
            delete curr;
        }

        void insertionSort(){
            if(head==NULL||head->next==NULL){
                return;
            }
            Node *curr = head->next;
            while(curr){
                Node* curr2 = head;
                bool found = false;
                int tmp = curr->data;
                while(curr2!=curr){
                    if(!found){
                        if(curr2->data>curr->data){
                            found = true;
                            tmp = curr2->data;
                            curr2->data = curr->data;
                        }
                    }
                    else{
                        tmp = curr2->data^tmp;
                        curr2->data = curr2->data^tmp;
                        tmp = curr2->data^tmp;
                    }
                    curr2 = curr2->next;
                }
                
                curr->data = tmp;
                curr = curr->next;
            }
        }

        bool searchHelper(Node *node, int value){
            if(node==NULL)
                return false;
            return node->data==value? true: searchHelper(node->next,value);
        }

        bool search(int value){
            return searchHelper(head,value);
        }

        int kthLastHelper(Node* node,int param){
            if(param==0){
                return node->data;
            }
            return kthLastHelper(node->next,param-1);
        }

        int kthLast(int k){
            return kthLastHelper(head,len-k);
        }
        
        void printList(){
            Node *curr = head;
            while(curr){
                cout<<curr->data<<" -> ";
                curr = curr->next;
            }
            cout<<"NULL"<<endl;
        }

    private:
        int len = 0;
        Node *head;

};


int main(){
    LinkedList list;
    list.insert(1);
    //list.printList();
    list.insert(2);
    //list.printList();
    list.insert(3);
    //list.printList();
    list.insert(4);
    //list.printList();
    list.insert(5);
    //list.printList();
    list.insert(6);
    //list.printList();
    list.insert(7);
    //list.printList();
    list.insert(8);
    //list.printList();
    list.insert(9);
    //list.printList();
    list.insert(10);
    //list.printList();
    list.insert(11);
    //list.printList();
    list.insert(12);
    //list.printList();
    list.insert(13);
    //list.printList();
    list.insert(14);
    //list.printList();
    list.insert(15);
    //list.printList();
    list.insert(16);
    //list.printList();
    list.insert(17);
    //list.printList();
    list.insert(18);
    //list.printList();
    list.insert(19);
    //list.printList();
    list.insert(20);
    //list.printList();
    list.insert(21);
    //list.printList();
    list.insert(22);
    //list.printList();
    list.insert(23);
    //list.printList();
    list.insert(24);
    //list.printList();
    list.insert(25);
    //list.printList();
    list.insert(26);
    //list.printList();
    list.insert(27);
    //list.printList();
    list.insert(28);
    //list.printList();
    list.insert(29);
    //list.printList();
    list.insert(30);
    //list.printList();
    //list.printList();
    list.insertionSort();
    //list.printList();

    for(int i=1; i<=30; i++){
        if(!list.search(i)){
            cout<<"Error at "<<i<<endl;
        }
    }
    for(int i=31; i<=1000; i++){
        if(list.search(i)){
            cout<<"Error at "<<i<<endl;
        }
    }

    // for(int i=1;i<=30;i++){
    //     cout<<list.kthLast(i)<<" ";
    // }

    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    list.deleteMid();
    //list.printList();
    return 0;
}
