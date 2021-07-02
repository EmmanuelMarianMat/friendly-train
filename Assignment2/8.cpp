#include<iostream>
using namespace std;

class TreeNode
{
    public:
        TreeNode(int x){
            letter = 48;
            freq = x;
            code = "";
            left = NULL;
            right = NULL;
        }

        TreeNode(int x, char c){
            letter = c;
            code = "";
            freq = x;
            left = NULL;
            right = NULL;
        }

        int freq;
        char letter;
        string code;
    private:
        TreeNode *left;
        TreeNode *right;
        
        friend class HuffManTree;
};

class Node
{
    public:
        Node(int x, char c){
            data = x;
            letter = c;
            next = NULL;
        }

        Node(TreeNode *n){
            node = n;
            next = NULL;
        }

    private:
        Node *next;
        int data;
        char letter;
        TreeNode *node;
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

        void enqueue(int value, char c){
            Node *newNode = new Node(value,c);
            Node *prev=NULL, *curr=head;
            
            while(curr&&curr->data<value){
                prev = curr;
                curr = curr->next;
            }

            if(!prev)
                head = newNode;
            else
                prev->next = newNode;

            newNode->next = curr;
        }

        void enqueue(TreeNode *node){
            Node *newNode = new Node(node);
            Node *prev=NULL, *curr=head;
            
            while(curr&&curr->node->freq<=node->freq){
                prev = curr;
                curr = curr->next;
            }

            if(!prev)
                head = newNode;
            else
                prev->next = newNode;

            newNode->next = curr;
        }

        TreeNode* dequeue(){
            if(isEmpty()){
                return NULL;
            }
            else{
                TreeNode *tmp = head->node;
                Node *curr = head;
                head = head->next;
                delete curr;
                return tmp;
            }
        }

        void printQueue(){
            Node *curr = head;
            while(curr){
                cout<<'('<<curr->node->letter<<","<<curr->node->freq<<')'<<" -> ";
                curr = curr->next;
            }
            cout<<"NULL"<<endl;
        }

    private:
        Node *head;
};

class HuffManTree{
    public:
        HuffManTree(string word_){
            root = NULL;
            word = word_;
            for(int i=0; i<26;i++)
                count[i] = 0;
            for(auto c:word)
                count[c-97]+=1;
            TreeNode *tmp;
            for(int i=0;i<26;i++){
                if(count[i]){
                    tmp = new TreeNode(count[i],97+i);
                    queue.enqueue(tmp);
                }
            }
            
            while(true){
                TreeNode *node1 = queue.dequeue();
                TreeNode *node2 = queue.dequeue();
                if(node2==NULL){
                    root = node1;
                    break;
                }
                TreeNode *newNode = new TreeNode(node1->freq+node2->freq);
                if(node1->freq>node2->freq){
                    newNode->left = node2;
                    newNode->right = node1;
                }
                else{
                    newNode->left = node1;
                    newNode->right = node2;
                }
                queue.enqueue(newNode);
            }
        }

        void findCodes(){
            setCodes(root,"");
            for(char letter:word)
                cout<<codes[letter-97]<<" ";
            cout<<endl;
        }

        void printTree(){
            printTreeHelper(root);
            cout<<endl;
        }

    private:
        TreeNode *root;
        string word;
        int count[26];
        PriorityQueue queue;
        string codes[26];

        void printTreeHelper(TreeNode *tree){
            cout<<"(";
            if(tree)
            {
                cout<<tree->freq;
                printTreeHelper(tree->left);
                printTreeHelper(tree->right);
            }
            cout<<")";
        }

        void setCodes(TreeNode *tree,string str){
            if(!tree)
                return;
            if(tree->left||tree->right){
                setCodes(tree->left,str+"0");
                setCodes(tree->right,str+"1");
            }
            else
                codes[tree->letter-97] = str;
        }
        
};
/*

                        58
                       /  \
                     25     33
                    /  \   /  \
                 12i  13s 15e  18
                               / \
                              8   10a
                             / \
                           4u   4
                               / \
                             1t   3o

*/



int main(){
    string word = "aaaaaaaaaaeeeeeeeeeeeeeeeiiiiiiiiiiiiooouuuussssssssssssst";
    HuffManTree tree = HuffManTree(word);
    tree.printTree();
    tree.findCodes();
}
