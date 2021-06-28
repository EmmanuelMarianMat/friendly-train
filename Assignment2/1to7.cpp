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
        }
        TreeNode *left;
        TreeNode *right;
        int data;
        int sum;
        friend class Tree;
};

class Tree{
    public:
        Tree(){
            root = NULL;
        }

        void insert(int value){
            root = insertHelper(root,value);
        }

        void printTree(){
            printTreeHelper(root);
            cout<<endl;
        }

        void printMirrorTree(){
            printMirrorTreeHelper(root);
            cout<<endl;
        }

        void insertParen(string input){
            if(!root){
                int index = 0;
                root = insertParenHelper(input,index,root);
            }
        }

        bool search(int value){
            return searchHelper(root,value)!=NULL;
        }

        int level(int value){
            return levelHelper(root, value, 0);
        }

        int max(){
            TreeNode *ret = maxHelper(root);
            return ret? ret->data: INT_MIN;
        }

        int min(){
            TreeNode *ret = minHelper(root);
            return ret? ret->data: INT_MAX;
        }

        int predecessor(int value){
            TreeNode *ret = predecessorHelper(value);
            return ret? ret->data: INT_MAX;
        }

        int successor(int value){
            TreeNode *ret = successorHelper(value);
            return ret? ret->data: INT_MIN;
        }

        void deleteNode(int value){
            root = deleteNodeHelper(root,value);
        }

        void preorder(){
            preorderHelper(root);
            cout<<endl;
        }
        
        void postorder(){
            postorderHelper(root);
            cout<<endl;
        }

        void inorder(){
            inorderHelper(root);
            cout<<endl;
        }

        void preorderInsert(int arr[], int size){
            if(!root)
                root = preorderInsertHelper(root, arr, 0, size-1);
        }

        int height(){
            return heightHelper(root);
        }

        int path(){
            return pathHelper(root);
        }

        void setSum(){
            root->sum = setSumHelper(root);
        }

        void printSumTree(){
            printSumTreeHelper(root);
            cout<<endl;
        }

        int maxSubTree(){
            int left = getNumberOfNodesHelepr(root->left);
            int right = getNumberOfNodesHelepr(root->right);
            return left>right ? left : right;
        }

        
    private:
        TreeNode *root;

        TreeNode *insertHelper(TreeNode *node, int value){
            if(node==NULL)
                return new TreeNode(value);
            if(value<node->data)
                node->left = insertHelper(node->left,value);
            else
                node->right = insertHelper(node->right,value);
            return node;
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

        void printMirrorTreeHelper(TreeNode *tree){
            cout<<"(";
            if(tree)
            {
                cout<<tree->data;
                printMirrorTreeHelper(tree->right);
                printMirrorTreeHelper(tree->left);
            }
            cout<<")";
        }


        TreeNode* searchHelper(TreeNode *tree, int value){
            if(tree==NULL)
                return NULL;
            else if (tree->data == value)
                return tree;

            else if(tree->data>value)
                return searchHelper(tree->left,value);
            else
                return searchHelper(tree->right,value);
        }

        int levelHelper(TreeNode *tree, int value, int level){
            if(!tree)
                return -1;
            else if(tree->data==value)
                return level;
            else if(tree->data>value)
                return levelHelper(tree->left, value, level+1);
            else
                return levelHelper(tree->right, value, level+1);
        }

        TreeNode* maxHelper(TreeNode *tree){
            if(!tree)
                return NULL;
            TreeNode* curr=tree;
            while(curr->right){
                curr = curr->right;
            }
            return curr;
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

        TreeNode* predecessorHelper(int value){
            if(root){
                TreeNode *curr = root, *lastRight = NULL;
                while(curr){
                    if(curr->data == value){
                        if(curr->left)
                            return maxHelper(curr->left);
                        return lastRight? lastRight: NULL;
                    }
                    else if(curr->data<value){
                        lastRight = curr;
                        curr = curr->right;
                    }
                    else    
                        curr = curr->left;
                }
            }
            return NULL;
            
        }

        TreeNode* successorHelper(int value){
            if(root){
                TreeNode *curr = root, *lastLeft = NULL;
                while(curr){
                    if(curr->data == value){
                        if(curr->right)
                            return minHelper(curr->right);
                        return lastLeft? lastLeft: NULL;
                    }
                    else if(curr->data<value)
                        curr = curr->right;
                    else{
                        lastLeft = curr;    
                        curr = curr->left;
                    }
                }
            }
            return NULL;
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

        TreeNode *deleteNodeHelper(TreeNode *tree, int value){
            if(tree==NULL)
            {
                cout<<"No such value to delete"<<endl;
                return NULL;
            }
            if(tree->data == value){
                
                if(tree->left&&tree->right){
                    tree->data = minHelper(tree->right)->data;
                    tree->right = deleteNodeHelper(tree->right, tree->data);
                    return tree;
                }
                else 
                    return tree->left?tree->left:tree->right; 
            }
            else if(tree->data < value)
                tree->right = deleteNodeHelper(tree->right, value);
            else
                tree->left = deleteNodeHelper(tree->left, value);

            return tree;
        }

        void preorderHelper(TreeNode *tree){
            if(tree){
                cout<<tree->data<<" ";
                preorderHelper(tree->left);
                preorderHelper(tree->right);
            }
        }

        void postorderHelper(TreeNode *tree){
            if(tree){
                postorderHelper(tree->left);
                postorderHelper(tree->right);
                cout<<tree->data<<" ";
            }
        }

        void inorderHelper(TreeNode *tree){
            if(tree){
                inorderHelper(tree->left);
                cout<<tree->data<<" ";
                inorderHelper(tree->right);
            }
        }

        TreeNode* preorderInsertHelper(TreeNode *tree, int arr[], int beg, int end){
            if(beg<=end){
                int elem = arr[beg];
                tree = new TreeNode(elem);
                int i;
                for(i=beg+1; i<=end; i++){
                    if(arr[i]>elem)
                        break;
                }
                tree->left = preorderInsertHelper(tree->left, arr, beg+1, i-1);
                tree->right = preorderInsertHelper(tree->right, arr, i,end);
                return tree;
            }
            return NULL;
        }

        int heightHelper(TreeNode *tree){
            if(tree==NULL)
                return -1;
            int left = heightHelper(tree->left);
            int right = heightHelper(tree->right);
            return left>right? 1+left : 1+right;
        }

        int pathHelper(TreeNode *tree){
            if(tree){
                int d = heightHelper(tree->left)+heightHelper(tree->right)+2;
                int ld = pathHelper(tree->left);
                int rd = pathHelper(tree->right);
                if(d>ld)
                    if(d>rd)
                        return d;
                    else
                        return rd;
                else
                    return ld>rd? ld:rd;
            }
            return 0;
        }

        int setSumHelper(TreeNode *tree){
            if(tree){
                int sum = 0;
                if(tree->left)
                    sum += (tree->left->sum = setSumHelper(tree->left));
                if(tree->right)
                    sum += (tree->right->sum = setSumHelper(tree->right));
                return sum+tree->data;
            }
            else
                return 0;
            
        }

        void printSumTreeHelper(TreeNode *tree){
            cout<<"(";
            if(tree)
            {
                cout<<tree->sum;
                printSumTreeHelper(tree->left);
                printSumTreeHelper(tree->right);
            }
            cout<<")";
        }

        int getNumberOfNodesHelepr(TreeNode *tree){
            if(tree){
                return 1+getNumberOfNodesHelepr(tree->left)+getNumberOfNodesHelepr(tree->right);
            }
            return 0;
        }

};

int main(){
    Tree tree;

    // FIRST TEST - for parentheses format insert

    // string input = "(43(60(82()(70()()))(50()()))(15(30(35()())(20()()))(8()())))";
    // tree.insertParen(input);
    // cout<<input<<endl;
    // tree.printTree();


    // SECOND TEST - to test pred, succ, min, max, insert, mirrortree and a bunch of stuff idek but not delete

    // cout<<tree.min()<<" "<<tree.max()<<endl;
    // cout<<tree.predecessor(43)<<" "<<tree.predecessor(15)<<" "<<tree.predecessor(8)<<" "<<tree.predecessor(30)<<" "<<tree.predecessor(20)<<" "<<tree.predecessor(35)<<" "<<tree.predecessor(60)<<" "<<tree.predecessor(50)<<" "<<tree.predecessor(82)<<" "<<tree.predecessor(70)<<" "<<tree.predecessor(722)<<endl;
    // cout<<tree.successor(43)<<" "<<tree.successor(15)<<" "<<tree.successor(8)<<" "<<tree.successor(30)<<" "<<tree.successor(20)<<" "<<tree.successor(35)<<" "<<tree.successor(60)<<" "<<tree.successor(50)<<" "<<tree.successor(82)<<" "<<tree.successor(70)<<" "<<tree.successor(722)<<endl;
    // tree.insert(43);
    // cout<<tree.min()<<" "<<tree.max()<<endl;
    // cout<<tree.predecessor(43)<<" "<<tree.predecessor(15)<<" "<<tree.predecessor(8)<<" "<<tree.predecessor(30)<<" "<<tree.predecessor(20)<<" "<<tree.predecessor(35)<<" "<<tree.predecessor(60)<<" "<<tree.predecessor(50)<<" "<<tree.predecessor(82)<<" "<<tree.predecessor(70)<<" "<<tree.predecessor(722)<<endl;
    // cout<<tree.successor(43)<<" "<<tree.successor(15)<<" "<<tree.successor(8)<<" "<<tree.successor(30)<<" "<<tree.successor(20)<<" "<<tree.successor(35)<<" "<<tree.successor(60)<<" "<<tree.successor(50)<<" "<<tree.successor(82)<<" "<<tree.successor(70)<<" "<<tree.successor(722)<<endl;
    // tree.insert(15);
    // tree.insert(8);
    // tree.insert(30);
    // tree.insert(20);
    // tree.insert(35);
    // tree.insert(60);
    // tree.insert(50);
    // tree.insert(82);
    // tree.insert(70);
    // tree.printTree();
    // cout<<tree.level(43)<<" "<<tree.level(15)<<" "<<tree.level(8)<<" "<<tree.level(30)<<" "<<tree.level(20)<<" "<<tree.level(35)<<" "<<tree.level(60)<<" "<<tree.level(50)<<" "<<tree.level(82)<<" "<<tree.level(70)<<" "<<tree.level(722)<<endl;
    // cout<<tree.search(43)<<" "<<tree.search(15)<<" "<<tree.search(8)<<" "<<tree.search(30)<<" "<<tree.search(20)<<" "<<tree.search(35)<<" "<<tree.search(60)<<" "<<tree.search(50)<<" "<<tree.search(82)<<" "<<tree.search(70)<<" "<<tree.search(722)<<endl;
    // tree.printMirrorTree();
    // cout<<tree.min()<<" "<<tree.max()<<endl;
    // cout<<tree.predecessor(43)<<" "<<tree.predecessor(15)<<" "<<tree.predecessor(8)<<" "<<tree.predecessor(30)<<" "<<tree.predecessor(20)<<" "<<tree.predecessor(35)<<" "<<tree.predecessor(60)<<" "<<tree.predecessor(50)<<" "<<tree.predecessor(82)<<" "<<tree.predecessor(70)<<" "<<tree.predecessor(722)<<endl;
    // cout<<tree.successor(43)<<" "<<tree.successor(15)<<" "<<tree.successor(8)<<" "<<tree.successor(30)<<" "<<tree.successor(20)<<" "<<tree.successor(35)<<" "<<tree.successor(60)<<" "<<tree.successor(50)<<" "<<tree.successor(82)<<" "<<tree.successor(70)<<" "<<tree.successor(722)<<endl;
    // tree.printTree();
    // tree.inorder();


    // THIRD TEST - test the pred, succ,max, min, etc. and DELETE ig?

    // cout<<tree.search(25)<<" "<<tree.min()<<" "<<tree.max()<<" "<<tree.predecessor(25)<<" "<<tree.successor(25)<<" "<<endl;
    // tree.insert(25);
    // cout<<tree.search(25)<<" "<<tree.min()<<" "<<tree.max()<<" "<<tree.predecessor(25)<<" "<<tree.successor(25)<<" "<<endl;
    // tree.insert(13);
    // tree.insert(50);
    // tree.insert(45);
    // tree.insert(55);
    // tree.insert(18);
    // cout<<tree.search(10)<<endl;
    // tree.inorder();
    // tree.preorder();
    // tree.postorder();
    // tree.printTree();
    // tree.deleteNode(55);
    // tree.deleteNode(13);
    // tree.deleteNode(25);
    // cout<<tree.min()<<" "<<tree.max()<<endl;


    // FOURTH TEST - for mirror tree

    // tree.insertParen("(31(16(7()())(24(19()())(29()())))(45()()))");
    // cout<<"(31(16(7()())(24(19()())(29()())))(45()()))"<<endl;
    // tree.printTree();
    // tree.printMirrorTree();

    // FIFTH TEST - test pre order insert

    // int arr[10] = {43,15,8,30,20,35,60,50,82,70};
    // tree.preorderInsert(arr, 10);
    // tree.printTree();
    // cout<<tree.height()<<" "<<tree.path()<<endl;

    // SIXTH TEST - test height and path

    // int arr[6] = {25, 13, 18, 50, 45, 55};
    // tree.preorderInsert(arr, 6);
    // tree.printTree();
    // cout<<tree.height()<<" "<<tree.path()<<endl;

    // SEVENTH TEST - test height and path

    // tree.insert(43);
    // tree.insert(15);
    // tree.insert(8);
    // tree.insert(30);
    // tree.insert(20);
    // tree.insert(35);
    // tree.insert(60);
    // tree.insert(50);
    // tree.insert(82);
    // tree.insert(70);
    // tree.insert(25);
    // tree.insert(27);
    // tree.insert(5);
    // tree.insert(6);
    // tree.insert(7);
    // cout<<tree.height()<<" "<<tree.path()<<endl;

    // EIGHTH TEST - test sum

    // string input = "(10(-2(8()())(-4()()))(6(7()())(5()())))";
    // tree.insertParen(input);
    // tree.setSum();
    // tree.printSumTree();

    // NINETH TEST - max subtree

    // string input = "(10(40(20()())(60()()))(30(90()())()))";
    // tree.insertParen(input);
    // cout<<tree.maxSubTree()<<endl;

    // TENTH TEST - max subtree
    
    tree.insert(5);
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(10);
    tree.insert(7);
    tree.insert(15);
    tree.insert(11);
    tree.insert(20);
    cout<<tree.maxSubTree()<<endl;


    return 0;
}