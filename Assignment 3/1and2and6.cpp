#include<iostream>
#include<algorithm>
using namespace std;

class TreeNode
{
    private:
        TreeNode(int x){
            data = x;
            left = NULL;
            right = NULL;
            height = 1;
            count = 1;
        }
        TreeNode *left;
        TreeNode *right;
        int data;
        int sum;
        int height;
        int count;
        friend class Tree;
};

class Tree{
    public:
        Tree(){
            root = NULL;
        }

        void insertNode(int value){
            root = insertNodeHelper(root,value);
        }

        void deleteNode(int value){
            root = deleteNodeHelper(root,value);
        }

        void printTree(){
            printTreeHelper(root);
            cout<<endl;
            int height;
            bool avl = isAVLHelper(root,&height) && isBST(root);
            cout<<"AVL? "<< avl;
            cout<<endl;
        }

        void deleteTree(){
            deleteTreeHelper(root);
            root = NULL;
        }

        void insertParen(string input){
            if(!root){
                int index = 0;
                root = insertParenHelper(input,index,root);
            }
        }

        void sortAVL(int* arr, int length){
            for(int i=0; i<length; i++)
                root = insertNodeHelper2(root,arr[i]);
            
            int count=0;
            sortHelper(root, arr, &count);
        }


    private:
        void sortHelper(TreeNode *tree, int arr[], int *count){
            if(tree){
                sortHelper(tree->left,arr,count);
                for(int i=0; i<tree->count; i++)
                    arr[(*count)++] = tree->data;
                sortHelper(tree->right,arr,count);
            }
        }

        bool isBST(TreeNode *tree){
            if(!tree || !(tree->left||tree->right)){
                return true;
            }
            bool left=true,right=true;

            if(tree->left){
                if(tree->left->data>=tree->data){
                    return false;
                }
                else
                    left = isBST(tree->left);
            }

            if(tree->right){
                if(tree->right->data<tree->data)
                    return false;
                else
                    right = isBST(tree->right);
            }

            return left&&right;
        }

        TreeNode* insertParenHelper(string input, int &index, TreeNode *tree){
            index++;
            if(index==input.length()||input[index]==41)
                return NULL;
            
            int data = 0;
            bool negative = false;
            if(input[index]==45)
            {
                index++;
                negative = true;
            }
            while(input[index]>=48 && input[index]<=57){
                data = data*10 + (input[index]-48);
                index++;
            }

            data = negative? -data : data;
            tree = new TreeNode(data);
            tree->left = insertParenHelper(input,index,tree->left);
            index++;
            tree->right = insertParenHelper(input,index,tree->right);
            index++;
            return tree;
        }

        void deleteTreeHelper(TreeNode *tree){
            if(tree==NULL)
                return;
            deleteTreeHelper(tree->left);
            deleteTreeHelper(tree->right);
            //cout<<tree->data<<endl;
            delete tree;
        }

        bool isAVLHelper(TreeNode *tree, int *height){
            if(tree==NULL){
                *height = 0;
                return true;
            }

            int lh,rh;

            bool l = isAVLHelper(tree->left, &lh);
            bool r = isAVLHelper(tree->right, &rh);

            *height = 1+max(lh,rh);

            return lh-rh>=-1 && lh-rh<=1 && l && r;
            
        }

        void printTreeHelper(TreeNode *tree){
            cout<<"(";
            if(tree)
            {
                cout<<tree->data;
                printTreeHelper(tree->left);
                printTreeHelper(tree->right);
            }
            cout<<")";
        }

        TreeNode* insertNodeHelper2(TreeNode *tree, int value){
            if(tree==NULL)
                return new TreeNode(value);
            else if(tree->data>value)
                tree->left = insertNodeHelper(tree->left,value);
            else if(tree->data<value)
                tree->right = insertNodeHelper(tree->right,value);
            else{
                tree->count++;
                return tree;
            }

            updateHeights(tree);
            
            int balance = getBalance(tree);

            if(balance>1 && tree->left->data>value)
                return rightRotate(tree);
            
            if(balance>1 && tree->left->data<=value){
                tree->left = leftRotate(tree->left);
                return rightRotate(tree);
            }

            if(balance<-1 && tree->right->data<=value)
                return leftRotate(tree);
            
            if(balance<-1 && tree->right->data>value){
                tree->right = rightRotate(tree->right);
                return leftRotate(tree);
            }

            return tree;
        }

        TreeNode* insertNodeHelper(TreeNode *tree, int value){
            if(tree==NULL)
                return new TreeNode(value);
            else if(tree->data>value)
                tree->left = insertNodeHelper(tree->left,value);
            else
                tree->right = insertNodeHelper(tree->right,value);

            updateHeights(tree);
            
            int balance = getBalance(tree);

            if(balance>1 && tree->left->data>value)
                return rightRotate(tree);
            
            if(balance>1 && tree->left->data<=value){
                tree->left = leftRotate(tree->left);
                return rightRotate(tree);
            }

            if(balance<-1 && tree->right->data<=value)
                return leftRotate(tree);
            
            if(balance<-1 && tree->right->data>value){
                tree->right = rightRotate(tree->right);
                return leftRotate(tree);
            }

            return tree;
        }

        TreeNode* deleteNodeHelper(TreeNode *tree, int value){
            if(tree==NULL)
                return NULL;
            
            else if(tree->data==value){
                if(tree->left&&tree->right){
                    tree->data = minHelper(tree->right)->data;
                    tree->right = deleteNodeHelper(tree->right, tree->data);
                    return tree;
                }
                else 
                    return tree->left?tree->left:tree->right;
            }

            else if(tree->data>value)
                tree->left = deleteNodeHelper(tree->left,value);
            else
                tree->right = deleteNodeHelper(tree->right,value);

            updateHeights(tree);
            
            int balance = getBalance(tree);

            if(balance>1 && getBalance(tree->left)>0)
                return rightRotate(tree);
            
            if(balance>1 && getBalance(tree->left)<0){
                tree->left = leftRotate(tree->left);
                return rightRotate(tree);
            }

            if(balance<-1 && getBalance(tree->right)<0)
                return leftRotate(tree);
            
            if(balance<-1 && getBalance(tree->right)>0){
                tree->right = rightRotate(tree->right);
                return leftRotate(tree);
            }

            return tree;
        }

        TreeNode* minHelper(TreeNode *tree){
            if(!tree)
                return NULL;
            TreeNode* curr=tree;
            while(curr->left){
                curr = curr->left;
            }
            return curr;
        }

        TreeNode* leftRotate(TreeNode *x){
            TreeNode *y = x->right;
            x->right = y->left;
            y->left = x;
            updateHeights(x);
            updateHeights(y);
            return y;
        }

        TreeNode* rightRotate(TreeNode *x){
            TreeNode *y = x->left;
            x->left = y->right;
            y->right = x;
            updateHeights(x);
            updateHeights(y);
            return y;
        }

        void updateHeights(TreeNode *x){
            x->height = 1 + max(height(x->left),height(x->right));
        }

        int getBalance(TreeNode *x){
            return height(x->left) - height(x->right);
        }

        int height(TreeNode *x){
            if(x==NULL)
                return 0;
            return x->height;
        }

        TreeNode *root;
};

void sort(int *arr, int length){
    Tree tree;
    tree.sortAVL(arr,length);
    tree.deleteTree();
}

int main(){
    Tree tree;
    tree.insertNode(4);
    tree.insertNode(6);
    tree.insertNode(3);
    tree.insertNode(2);
    tree.insertNode(1);
    tree.deleteNode(3);
    tree.printTree();
    tree.deleteTree();
    tree.insertParen("(10(15()())(20()()))");
    tree.printTree();
    tree.deleteTree();
    tree.insertParen("(12(8(5(4()())())(11()()))(18(17()())()))");
    tree.printTree();
    tree.deleteTree();
    int arr[] = {100,12,100,1,1,12,100,1,12,100,1,1};
    sort(arr,12);
    for(int i=0; i<12; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}