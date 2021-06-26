#include<iostream>
using namespace std;

class Stack{
    public:
        Stack(){
            cap = 8;
            ptr = new int[cap];
            len = 0;
        }

        bool isEmpty(){
            return len==0;
        }

        void push(int value){
            if(isFull())
                cout<<"Full stack"<<endl;
            else
                ptr[len++] = value;
        }

        int pop(){
            if(isEmpty()){
                cout<<"Empty stack"<<endl;
                return INT_MIN;
            }
            return ptr[--len];
        }

        bool isFull(){
            return len==cap;
        }

    private:
        int *ptr;
        int len;
        int cap;
};


int main(){
    Stack stk;
    stk.push(1);
    stk.push(2);
    stk.push(3);
    stk.push(4);
    stk.push(5);
    stk.push(6);
    stk.push(7);
    stk.push(8);
    stk.push(8);
    //cout<<stk.isEmpty()<<" "<<stk.isFull()<<endl;
    cout<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl;
    //cout<<stk.isEmpty()<<" "<<stk.isFull()<<endl;

}