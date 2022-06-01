/* 
 * Programa: stackCalculator.cpp;
 * Autor: Daniel Machado;
 * DRE: 121046088;
 * Descrição: Utiliza a pilha pra calcular expressões;
 */
#include <iostream>
#include <string.h>
#include <sstream>

#define ERROR cout << "\nThe operation can't be executed by one of the following reasons:\n1 - The stack is empty\n2 - The stack is full\nTry again" << endl; return 0;

using namespace std;

typedef char itemType;

const int maxItems = 100;

class Stack{
    private:
    int top;
    int size;
    itemType* structure;

    public:
    Stack();
    ~Stack();
    bool full();
    bool empty();
    int push(itemType item);
    itemType pop();
    int peek();
    void print();

};

Stack::Stack(){
    size = 0;
    top = 0;
    structure = new itemType[maxItems];
}

Stack::~Stack(){
    delete [] structure;
}

bool Stack::full(){
    if(size == maxItems){
        return true;
    }
    return false;
}

bool Stack::empty(){
    if(size == 0){
        return true;
    }
    else{
        return false;
    }
}

int Stack::push(itemType item){
    if(!full()){
        structure[size] = item;
        size++;
    }
    else{
        cout << "Erro no push";
        ERROR;
    }

    return 0;
};

itemType Stack::pop(){
    if(empty()){
        cout << "Erro no pop";
        ERROR;
    
    }
    else{
        size--;
        return structure[size];
    }
    return 0;
}

int Stack::peek(){
    if(empty()){
        cout << "Erro no peek";
        ERROR;
        exit(EXIT_FAILURE);
    }
    else{
        return structure[size - 1];
    }
    return 0;
}

void Stack::print(){
    cout << "\n[ ";
    for(int i = 0; i < size; i++){
        cout << structure[i] << " ";
    }
    cout << "]\n";
}

bool isOperator(char op){
    if(op == '-' || op == '+' || op == '*' || op == '/' || op == '^'){
        return 1;
    }
    return 0;
}

bool isOperand(char op){
    if(op >= 'A' && op <= 'Z'){
        return 1;
    }
    if(op >= 'a' && op <= 'z'){
        return 1;
    }
    if(op >= '0' && op <= '9'){
        return 1;
    }
    return 0;
}

int precedence(char op){
    if(op == '+' || op == '-'){
        return 1;  
    }
    if (op == '*' || op == '/'){
        return 2; 
    }  
    if(op == '^'){
        return 3;       
    }
    return 0; 
}

bool eqlOrhigher (char op1, char op2){  
    int p1 = precedence(op1);  
    int p2 = precedence(op2);  
    if (p1 == p2){  
        return false;  
    }
    if (op1 == '^' ){
        return true;  
    }
    return  (p1>p2 ? true : false);  
}; 

string convert(string infix){  
    Stack stack1;  
    string postfix ="";    
    char op;  
  
    stack1.push( '(' );  
    infix += ')';  
  
    for(int i = 0; i<infix.length(); i++){  
        op = infix[i];  
  
        if(op == ' '){
          continue;  
        }  
        else if(op == '('){
            stack1.push(op);
        }  
        else if(isOperand(op)){
            postfix += op;
            if(isOperator(infix[i + 1])){
                postfix += ' ';
            }
        }  
        else if(isOperator(op)){  
            while(!stack1.empty() && eqlOrhigher(stack1.peek(), op)){  
                postfix += stack1.peek();  
                stack1.pop();  
            }  
            stack1.push(op);  
        }  
        else if(op == ')'){  
            while(!stack1.empty() && stack1.peek() != '('){  
                postfix += stack1.peek();  
                stack1.pop();  
            }  
            stack1.pop();  
        }  
    }
return postfix;  
}; 

int main(){
    Stack stack1;
    int newNumber;
    string number = "";
    string infix_expression, postfix_expression;

    cout << "\033[31;1mInsira a expressão: \033[m";
    cin >> infix_expression;
    postfix_expression = convert(infix_expression);
    
    cout << postfix_expression;
    return 0;
}