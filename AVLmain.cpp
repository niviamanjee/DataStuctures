//
//  main.cpp
//  Nivedita Amanjee
//CISP 430 - LEC 11597
//Assignment : AVL
//Instructions:
//Populate a tree via a text file (input.txt) Make sure that after every insert, the tree is balanced. At the end, display the tree in level format. Make sure to include the height and the balance factor of every node in your output. Redirect the display to  an output file (output.txt)


#include <iostream>
#include <algorithm>
#include <fstream>
#include <stdio.h>

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

struct Tree {
    int value = NULL;
    int height = NULL;
    Tree *left = NULL;
    Tree *right = NULL;
};

struct QueueNode{
    Tree * node = NULL;
    QueueNode * next = NULL;
};

struct Queue {
    QueueNode *  front = NULL;
    QueueNode * rear = NULL;
};


void enQueue(Tree * node, Queue * printQueue){
    QueueNode * treeNode = new QueueNode;
    treeNode->node = node;
    
    if (printQueue-> front == NULL){
        printQueue->front = treeNode;
        printQueue->rear = treeNode;
    }
    else {
        printQueue->rear->next = treeNode;
        printQueue->rear = treeNode;
    }
}

Tree * deQueue(Queue * printQueue){
    Tree * popValue = printQueue->front->node;
    

    if (printQueue->front){
        QueueNode * temp = printQueue->front;
        printQueue->front = printQueue->front->next;
        delete temp;
    }
    else if (!printQueue->front){
        printQueue->rear = printQueue->front;
    }
    return popValue;
}

int getHeight(Tree *child){
    if (child == NULL){
        return -1;
    }
    else {
        
        return child->height;
    }
}

int updateHeight(Tree * node){
    if(node){
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }
    return node->height;
}

int getBalance(Tree *node){
 
    return  getHeight(node->left) - getHeight(node->right);
}
Tree* rotateRight(Tree *x){
    
    Tree * y = x->left;
    Tree * z = y->right;
    
    x->left = z;
    y->right = x;
    x->height = updateHeight(x);
    y->height= updateHeight(y);
    return y;
}

Tree* rotateLeft(Tree *x){
    
    Tree * y = x->right;
    Tree * z = y->left;
    
    x->right = z;
    y->left = x;
    x->height = updateHeight(x);
    y->height= updateHeight(y);
    
    return y;
}


Tree* rebalance(Tree * node){
    node->height = updateHeight(node);
    
    int balance = getBalance(node);

    
  
    if (balance > 1){//if balance is a positive number, it is left heavy
        //right rotate
 
        
        if(getBalance(node->left) < 0){//if the left child is right heavy
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        else{//nodeLeftBalance > 0
            return rotateRight(node);//single rotation
        }
    }
    else if(balance < -1){//if balance is a negative number, it is right heavy
        if(getBalance(node->right) > 0){
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        else {
            return rotateLeft(node);
        }
    }
    
    return node;
}
Tree* newLeaf(int key){
    Tree* node = new Tree;
    node->value = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
    

    return node;
}

Tree * insertLeaf(Tree *&leaf, int key){
    //a recursive function for inserting a node
    //when insert happens, the height is set to 0 for the node
    
 
    if(!leaf){
        leaf = newLeaf(key);
        return leaf;
    }
    else if(key < leaf->value){
        leaf->left = insertLeaf(leaf->left, key);
        
    }
    else if(key > leaf->value){
        leaf->right = insertLeaf(leaf->right, key);
    }
    
    leaf = rebalance(leaf);

    
    return leaf;

}

void printLevels(Tree * root){
    Queue * currQueue = new Queue;
    Queue * nextQueue = new Queue;
    Queue * temp = NULL;
    Tree * displayNode = NULL;

    enQueue(root, currQueue);
    while(currQueue->front){
        displayNode = deQueue(currQueue);
        if (displayNode != NULL){
            output << displayNode->value << "(" << displayNode->height << ", " << getBalance(displayNode) << ")     ";
            enQueue(displayNode->left, nextQueue);
            enQueue(displayNode->right, nextQueue);
        }
        if(!currQueue->front){
            output << endl;
            temp = currQueue;
            currQueue = nextQueue;
            nextQueue = temp;
            temp = NULL;
            
        }
    
    }

    delete currQueue;
    delete nextQueue;


}

void preOrder(Tree * &node){

    if (node != NULL){
        cout << node->value;
        preOrder(node->left);
        preOrder(node->right);
    }
  
}



int main() {
    
    Tree * root = new Tree;
        
    root = NULL;
    char value;
    int nodeCount = 0;
    while (input){ //if the file doesn't exist or isn't found, an output is printed
        while (input.get(value)){ //the file is read character by character
                                              //and each character is added to the string expression
            if (value == ' ' || value== '\n') {break;}//prevents spaces from being passed into isert leaf function
            int number = (int)(value) - 48;
            
            
            cout << number << endl;
            root = insertLeaf(root, number);
            nodeCount++;
          }
          
       
          
    }
    
    input.close();
    cout << "Number of Nodes: " << nodeCount << endl;
    
    output << "AVL Tree (height, balance): \n" << endl;
    output << "Number of Nodes: " << nodeCount << "\n" << endl;
    printLevels(root);
    
    
    preOrder(root);
    output.close();

    return 0;
}
