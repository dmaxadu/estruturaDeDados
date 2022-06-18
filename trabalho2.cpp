/* 
 * Programa: stackCalculator.cpp;
 * Autor: Daniel Machado;
 * DRE: 121046088;
 * Descrição: Utiliza a pilha pra calcular expressões;
 */

//A expressão deve ser inserida com espaço entre os números diferentes e os operadores, exemplo: 100 * ( 2 + 12 )

#include <iostream>
#include <string.h>
#include <math.h>
#include <sstream>
#include <ctype.h>
#include <bits/stdc++.h>

#define ERROR cout << "\nThe operation can't be executed by one of the following reasons:\n1 - The stack is empty\n2 - The stack is full\nTry again" << endl; return 0;

using namespace std;

const int maxItems = 100;

class StackChar{
    private:
    int top;
    int size;
    char* structure;

    public:
    StackChar();
    ~StackChar();
    bool full();
    bool empty();
    int push(char item);
    char pop();
    int peek();
    void print();

};

StackChar::StackChar(){
    size = 0;
    top = 0;
    structure = new char[maxItems];
}

StackChar::~StackChar(){
    delete [] structure;
}

bool StackChar::full(){
    if(size == maxItems){
        return true;
    }
    return false;
}

bool StackChar::empty(){
    if(size == 0){
        return true;
    }
    else{
        return false;
    }
}

int StackChar::push(char item){
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

char StackChar::pop(){
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

int StackChar::peek(){
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

void StackChar::print(){
    cout << "\n[ ";
    for(int i = 0; i < size; i++){
        cout << structure[i] << " ";
    }
    cout << "]\n";
}

class StackInt{
    private:
    int top;
    int size;
    int* structure;

    public:
    StackInt();
    ~StackInt();
    bool full();
    bool empty();
    int push(int item);
    int pop();
    int peek();
    void print();

};

StackInt::StackInt(){
    size = 0;
    top = 0;
    structure = new int[maxItems];
}

StackInt::~StackInt(){
    delete [] structure;
}

bool StackInt::full(){
    if(size == maxItems){
        return true;
    }
    return false;
}

bool StackInt::empty(){
    if(size == 0){
        return true;
    }
    else{
        return false;
    }
}

int StackInt::push(int item){
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

int StackInt::pop(){
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

int StackInt::peek(){
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

void StackInt::print(){
    cout << "\n[ ";
    for(int i = 0; i < size; i++){
        cout << structure[i] << " ";
    }
    cout << "]\n";
}

int precedence(char op){ 
    if(op == '+'||op == '-') 
        return 1; 
    if(op == '*'||op == '/') 
        return 2; 
    return 0; 
} 
  
int applyOp(int a, int b, char op){ 
    switch(op){ 
        case '+': 
            return a + b; 
        case '-': 
            return a - b; 
        case '*': 
            return a * b; 
        case '/': 
            return a / b; 
    }
    return 0; 
} 
  
int evaluate(string tokens){ 
    int i; 
      
    StackInt values; 
      
    StackChar ops; 
      
    for(i = 0; i < tokens.length(); i++){ 
          
        if(tokens[i] == ' ') 
            continue; 
          
        else if(tokens[i] == '('){ 
            ops.push(tokens[i]); 
        } 
          
        else if(isdigit(tokens[i])){ 
            int val = 0; 
              
            while(i < tokens.length() && isdigit(tokens[i])){ 
                val = (val*10) + (tokens[i]-'0'); 
                i++; 
            } 
              
            values.push(val); 
        } 
          
        else if(tokens[i] == ')'){ 
            
            while(!ops.empty() && ops.peek() != '('){ 
                int val2 = values.peek(); 
                values.pop(); 
                  
                int val1 = values.peek(); 
                values.pop(); 
                  
                char op = ops.peek(); 
                ops.pop(); 
                  
                values.push(applyOp(val1, val2, op)); 
            } 
              
            if(!ops.empty()) 
               ops.pop(); 
        } 
          
        else{ 
            while(!ops.empty() && precedence(ops.peek()) >= precedence(tokens[i])){ 
                int val2 = values.peek(); 
                values.pop(); 
                  
                int val1 = values.peek(); 
                values.pop(); 
                  
                char op = ops.peek(); 
                ops.pop(); 
                  
                values.push(applyOp(val1, val2, op)); 
            } 
              
            ops.push(tokens[i]); 
        } 
    } 
      
    while(!ops.empty()){ 
        int val2 = values.peek(); 
        values.pop(); 
                  
        int val1 = values.peek(); 
        values.pop(); 
                  
        char op = ops.peek(); 
        ops.pop(); 
                  
        values.push(applyOp(val1, val2, op)); 
    } 
      
    return values.peek(); 
} 
  
int main(){ 
    string exp;
    cout << "Insira a expressão: ";
    while(getline(cin, exp)){
        if(exp != ""){
          break;
        }
    }
    cout << evaluate(exp) << endl; 
    
    return 0; 
}