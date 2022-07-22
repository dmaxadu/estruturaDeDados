/* 
 * Programa: stackCalculator.cpp;
 * Autor: Daniel Machado;
 * DRE: 121046088;
 * Descrição: Utiliza a pilha pra calcular expressões;
 */

//A expressão deve ser inserida com espaço entre os números diferentes e os operadores, exemplo: 100 * ( 2 + 12 ).

#include <iostream>
#include <string.h>
#include <math.h>
#include <sstream>
#include <ctype.h>
#include <bits/stdc++.h>

#define ERROR cout << "\nThe operation can't be executed by one of the following reasons:\n1 - The stack is empty\n2 - The stack is full\nTry again" << endl; return 0;

using namespace std;

const int maxItems = 100;

/* Stack de Char */

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

/* Stack de Inteiros */

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

/* Funções necessárias para o cálculo da expressão */

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

/* Função que faz o parse da expressão para que ela seja calculada */

int evaluate(string exp){ 
    int i; 
      
    StackInt numbers; 
      
    StackChar operators; 
      
    for(i = 0; i < exp.length(); i++){ 
          
        if(exp[i] == ' ') 
            continue; 
          
        else if(exp[i] == '('){ 
            operators.push(exp[i]); 
        } 
          
        else if(isdigit(exp[i])){ 
            int val = 0; 
              
            while(i < exp.length() && isdigit(exp[i])){ 
                val = (val*10) + (exp[i]-'0'); 
                i++; 
            } 
              
            numbers.push(val); 
        } 
          
        else if(exp[i] == ')'){ 
            
            while(!operators.empty() && operators.peek() != '('){ 
                int val2 = numbers.peek(); 
                numbers.pop(); 
                  
                int val1 = numbers.peek(); 
                numbers.pop(); 
                  
                char op = operators.peek(); 
                operators.pop(); 
                  
                numbers.push(applyOp(val1, val2, op)); 
            } 
              
            if(!operators.empty()) 
               operators.pop(); 
        } 
          
        else{ 
            while(!operators.empty() && precedence(operators.peek()) >= precedence(exp[i])){ 
                int val2 = numbers.peek(); 
                numbers.pop(); 
                  
                int val1 = numbers.peek(); 
                numbers.pop(); 
                  
                char op = operators.peek(); 
                operators.pop(); 
                  
                numbers.push(applyOp(val1, val2, op)); 
            } 
              
            operators.push(exp[i]); 
        } 
    } 
      
    while(!operators.empty()){ 
        int val2 = numbers.peek(); 
        numbers.pop(); 
                  
        int val1 = numbers.peek(); 
        numbers.pop(); 
                  
        char op = operators.peek(); 
        operators.pop(); 
                  
        numbers.push(applyOp(val1, val2, op)); 
    } 
      
    return numbers.peek(); 
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
