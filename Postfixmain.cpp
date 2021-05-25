//
//main.cpp
//Nivedita Amanjee
//Student ID: 1595694
//CISP 430 LEC 11597
//Assignment: Postfix Evaluation

//Description: This program reads a postfix expression from a file and evaluates the expression

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

struct node { //a node structure is created that holds an integer and a pointer
                //for the next node address
    int item;
    struct node *next;
};

string readFile(){
    //function that reads a line from a file called input.txt
    
    FILE *file = fopen("input.txt", "r");
    
    string expression = ""; //an empty string is initialized to hold the postfix line
                            //from the file
    
    char c;
    
    
    if (file == NULL){ //if the file doesn't exist or isn't found, an output is printed
           printf("Cannot open file \n");
    }
    
    while ((c = fgetc(file)) != EOF){ //the file is read character by character
                                        //and each character is added to the string expression
        expression+=c;
    }
    
    fclose(file); //the file is closed after being read
    
    return expression;
}

int pop(struct node *&top){ //a pop function for the node stack
    struct node *temp;
    int value;
    if(top){
        temp = top;
        value = temp -> item;
        top = top -> next;
        delete temp;
    }
    
    return value; // it returns the integer value of the popped node
}

void push(int item, struct node *&top){//a push function that adds a node to the stack
    struct node *newNode = new node;
    
    newNode -> item = item;
    newNode->next = top;
    top=newNode;
}

int evaluate(int value1, int value2, char operative){
    //this evaluate function uses a switch operator to check the
    //operator character that is passed in along with the two popped operands from the
    //stack
    int result;
    int x = value1;
    int y = value2;
    
    
    switch (operative){
        case '*':
            result = x * y;
            break;
        case '/':
            result = x / y;
            break;
        case '+':
            result = x + y;
            break;
        case '-':
            result = x - y;
            break;
    }
    
    return result;
}


int main() {
    
    struct node *top = NULL;
    
  
    
    string postfix = readFile();

    cout << "Postfix Expression: " << postfix << endl;
    //loop through the expression string
    
    for (int i = 0; i < postfix.length(); i++){
        
        if (isdigit(postfix[i])){
            push((int)postfix[i]-48, top);
            

        }
        else if (postfix[i]== '*' || postfix[i]== '/' || postfix[i]== '+' || postfix[i]== '-'){
            //create a function that takes in two popped values and an operator and returns the evaluated value
            int value2 = pop(top);

            int value1 = pop(top);
            int answer = evaluate(value1, value2, postfix[i]);


            push(answer, top);
            
        }
    }
    cout << "Evaluated Value: " << pop(top) << endl;

   
    return 0;
}
