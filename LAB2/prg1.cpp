/* write a C++ program for implementing the following operations of Stack S and also find the amortized cost if a sequence of n following operations are performed on a data structure 
 i) Push(S,x)
ii) Pop(S)
iii) Multipop(S,k)*/

#include <iostream>

using namespace std;

#define MAX 1000

class Stack {
    int top;

    public:
        int a[MAX];
        Stack(){top= -1;}
        bool push(int x);
        int pop();
        bool multipop(int k);
};

bool Stack::push(int x){
    if(top>=(MAX -1)){
        cout<< "Stack Overflow";
        return false;
    }else{
        a[++top]=x;
        cout<<x<<" pushed into stack\n";
        return true;
    }
}

int Stack::pop(){
    if(top<0){
        cout<<"Stack Underflow\n";
        return 0;
    }else{
        int x=a[top--];
        return x;
    }
}

bool Stack::multipop(int k){
    if(k<=0){
        cout<<"Pop operation cannot be executed\n";
        return false;
    }
    for(int i=0;i<k;i++){
        if(top<0){
            cout<<"Stack Underflow\n";
            return false;
        }
        int x=a[top--];
        cout<< x << " Multi Popped\n";
    }
}

int main(){
    class Stack s;
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);
    s.push(60);
    s.push(70);

    cout<< s.pop() << "Element Popped from the Stack";

    s.multipop(3);

    return 0;
}
