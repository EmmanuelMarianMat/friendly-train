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

        bool isFull(){
            return len==cap;
        }

        int pop(){
            if(isEmpty()){
                return INT_MIN;
            }
            return ptr[--len];
        }

        void push(int value){
            if(isFull())
                resize();
            ptr[len++] = value;
        }
    
    private:
        int *ptr;
        int len;
        int cap;

        void resize(){
            cap*=2;
            int* ptrTemp = new int[cap];
            for(int i=0;i<len;i++)
                ptrTemp[i] = ptr[i];
            delete ptr;
            ptr = ptrTemp;
        }
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
    stk.push(11);
    stk.push(21);
    stk.push(31);
    stk.push(41);
    stk.push(15);
    stk.push(16);
    stk.push(17);
    stk.push(18);
    //cout<<stk.isEmpty()<<" "<<stk.isFull()<<endl;
    cout<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl;
    cout<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl<<stk.pop()<<endl;
    //cout<<stk.isEmpty()<<" "<<stk.isFull()<<endl;
    return 0;
}