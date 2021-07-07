#include<iostream>
using namespace std;

class Counter{
    public:
        Counter(string word){
            for(int i=0; i<26;i++)
                array[i] = 0;
            for(char c:word)
                array[c-97]++;
        }
        int array[26];
};

string check(string small, string big){
    Counter smallC = Counter(small);
    for(int i=0;i<=big.length()-small.length();i++){
        Counter tmp = Counter(big.substr(i,small.length()));
        bool found = false;
        for(int i=0; i<26;i++){
            if(smallC.array[i]!=tmp.array[i]){
                found = true;
                break;
            }
        }
        if(!found)
            return "YES";
    }
    return "NO";
}

int main(){
    cout<<check("hack","indiahacks")<<endl<<check("code","eddy")<<endl<<check("coder","lamredoc")<<endl;
}