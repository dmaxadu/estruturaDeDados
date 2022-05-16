#include <iostream>
#include <string.h>
#include <stack>
#include <sstream>
#include <stdio.h>

using namespace std;

typedef char itemType;
const int maxItems = 100;

/* stack class declaration */

class Stack{
    private:
        int size;
        itemType* structure;

    public:
        Stack(); /* builder */
        ~Stack(); /* destructor */
        bool isItFull(); /* check if the stack is full */
        bool isItEmpty(); /* check if the stack is empty */
        void pushItem(itemType item); /* add items to the stack */
        itemType popItem(); /* remove items from the stack */
        int stackLenght(); /* return the lenght of the stack */
        void printStack(); /* literally what the name says */
        itemType stackTop(); /* returns the top value of the stack */
};

/* stack's functions declaration */

Stack::Stack(){
    size = 0;
    structure = new itemType[maxItems];
};

Stack::~Stack(){
    delete [] structure;
};

bool Stack::isItFull(){
    if(size == maxItems){
        return true;
    }
    else{
        return false;
    }
    
};

bool Stack::isItEmpty(){
    return(size == 0);
};

void Stack::pushItem(itemType item){
    if(isItFull()){
        cout << "\nThe stack is full, it's not possible to add an element.\n";
    }
    else{
        structure[size] = item;
        size++;
    }
};

itemType Stack::popItem(){
    if(isItEmpty()){
        cout << "\nThe stack is empty, it's not possible to remove a item from nothing :/\n";
        return 0;
    }
    else{
        size--;
        return structure[size];
    }
};

int Stack::stackLenght(){
    return size;
};

void Stack::printStack(){
    cout << "\nStack: \n[";
    for(int i = 0; i < size; i++){
        cout << "Espaco "<< i << ": " << structure[i] << endl; 
    }
    cout << "]\n";
};

itemType Stack::stackTop(){
    return structure[size];
};

bool isOperator(char op){
    if( op >= 'A' && op <= 'Z'){  /* Define the opharaopter in between A to Z. If not, it returns False.*/  
        return true;
    }
    if( op >= 'a' && op <= 'z'){
        return true;  
    } // Define the opharaopter in between a to z. If not, it returns False. */  
    if( op >= '0' && op <= '9'){
        return true;  
    }  // Define the character in between 0 to 9. If not, it returns False. */  
    return false;
}

bool isOperand(char op){
    if( op >= 'A' && op <= 'Z'){
        return true;
    }
    if( op >= 'a' && op <= 'z'){
        return true;
    }
    if( op >= '0' && op <= '9'){
        return true;
    }
    return false;
}

int precedence(char op){
    if(op == '+' || op == '-'){
        return 1;  
    }                   /* it defines the lowest precedence */  
    if (op == '*' || op == '/'){
        return 2; 
    }  
    if(op == '^'){
        return 3;       
    }
    return 0;
}

bool precedenceComparator(char op1, char op2){
    int p1 = precedence(op1);
    int p2 = precedence(op2);

    if(p1 == p2){
        return false;
    }
    if(op1 == '^'){
        return true;
    }

    return(p1 > p2 ? true : false);
}

string convert2Postfix(string infix){
    stack <char> stack1;
    char ch;
    string postfix = "";

    stack1.push('(');
    infix += ')';

    for(int i = 0; i<infix.length(); i++){  
        ch = infix[i];  
  
        if(ch == ' '){
          continue;  
        }  
        else if(ch == '('){
            stack1.push(ch);
        }  
        else if(isOperand(ch)){
            postfix += ch;
        }  
        else if(isOperator(ch)){  
            while(!stack1.empty() && precedenceComparator(stack1.top(), ch)){  
                postfix += stack1.top();  
                stack1.pop();  
            }  
            stack1.push(ch);  
        }  
        else if(ch == ')'){  
            while(!stack1.empty() && stack1.top() != '('){  
                postfix += stack1.top();  
                stack1.pop();  
            }  
            stack1.pop();  
        }  
    } 
    return postfix;
}

int main(){
    string infix, postfix;
    cout << "Insira a expressao: ";
    cin >> infix;
    postfix = convert2Postfix(infix);
    cout << "Expressao em notacao polonesa reversa: " << postfix << endl;
    return 0;
}

//Alteração