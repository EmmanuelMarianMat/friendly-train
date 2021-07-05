#include<iostream>
using namespace std;

class Node{

    private:
        Node(string word_){
            word = word_;
            next = NULL;
        }
        string word;
        Node *next;
        friend class Hash;
};

class Hash{
    public:
        Hash(int cap, string sentence_){
            capacity = cap;
            sentence = sentence_;
            
            for(int i=0; i<cap; i++)
                table[i] = NULL;
            
            insertHelper();
        }

        void printTable(){
            for(int i=0; i<capacity; i++){
                if(!table[i])
                    cout<<"NULL";
                else{
                    Node *curr = table[i];
                    while(curr){
                        cout<<curr->word<<" ";
                        curr = curr->next;
                    }
                }
                cout<<endl;
            }
            cout<<endl;
        }

    private:
        int capacity;
        Node* table[100];
        string sentence;

        void insertHelper(){
            int i=0;
            string word;
            
            while(i<sentence.length()&&sentence[i]!='.'){
                word = "";
                while(sentence[i]!=' ' && sentence[i]!='.'){
                    if(isalpha(sentence[i]))
                        word+=sentence[i];
                    i++;
                }
                insertInTable(word);
                i++;
            }
        }

        void insertInTable(string word){
            int index = word.length()%capacity;
            if(table[index]==NULL){
                table[index] = new Node(word);
            }
            else{
                Node *curr=table[index];
                while(curr->next&&curr->word!=word){
                    curr = curr->next;
                }
                if(curr->word!=word)
                    curr->next = new Node(word);
            }
        }
};


int main(){
    string input = "I felt happy because I saw the others were happy and because I knew I should feel happy, but I wasn’t really happy.";
    Hash hash = Hash(4,input);
    // string input = "So I said yes to Thomas Clinton and later thought that I had said yes to God and later still realized I had said yes only to Thomas Clinton.";
    // Hash hash = Hash(10,input);
    hash.printTable();
}