//
//main.cpp
//CISP 430 | LEC 11597
//Assignment: Merge Sort
//This program sorts the values of an array using the merge sort algorirthm by implementing a singly linked lists.
//

#include <iostream>
#include <stdio.h>

using namespace std;

//Algorithm
//function1: populate a linked list with array values
//function2: traverse the linked list and count the length of the nodes
//if head == NULL: return Null
//if head->next == NULL : return head
//function3: split the linked list into 2 halves; null terminated lists using node count
//function4: merge sort- sort each half (sort by passing in each half separately)
//function5: merge the sorted lists together and update the head pointer


struct node {
    int value;
    node* next = NULL;
};



void printList(node* head){
    

    cout << "{";
    while (head){
        cout <<to_string(head->value) << ", ";
        head = head->next;
    }
    cout << "}"<< endl;
    cout << "=========================================\n\n" << endl;
}
void insertNode(node* &head, int number){
    node * newNode = new node;
    newNode->value = number;
  
    
    if(head == NULL){//if the list is empty
        head = newNode;
        
        return;
        
    }
    node* current = head;
    while(current->next){
       
        current = current->next;
    }
    current->next = newNode;//insert the new node where the list ends
        

}

void populateList(node* &head){
    int randomIntArray[]= {3, 5, 1, 9, 7, 2, 8, 6, 0, 4};
    for (int i = 0; i < 10 ; i++){
        
        insertNode(head, randomIntArray[i]);
        
        
    }
}

void splitList(node* head, node* &leftHalf, node* &rightHalf){
    
    int listLength= 1;

    node* current = head;

    
    while(current->next){
        listLength++;
        current = current->next;
    }
    
    int midpoint = listLength/2;
    current = head;
    
    for (int i = 0; i < midpoint; i++){//split the list at the first half
        insertNode(leftHalf, current->value);
        current = current->next;
    }
    for(int j = midpoint; j < listLength; j++ ){//split the list at the second half
        insertNode(rightHalf, current->value);
        current = current->next;
    }
    

}

node* merge(node* left, node* right){
    node* joinedList = NULL;
    
    if(left == NULL){
        return right;
    }
    if(right == NULL){
        return left;
    }
    
    if(left->value <= right->value){
        insertNode(joinedList, left->value);
        joinedList->next = merge(left->next, right);
    }
    else{
        insertNode(joinedList, right->value);
        joinedList->next = merge(left, right->next);
    }
    
    return joinedList;
}
node* mergeSort(node* &head){
    

    if (head == NULL){
        return NULL;
    }
    if(head->next == NULL){
        return head;
    }
    
    node* leftHalf = NULL;
    node* rightHalf = NULL;
    splitList(head, leftHalf, rightHalf);
    leftHalf = mergeSort(leftHalf);
    rightHalf = mergeSort(rightHalf);
    node* sortedList = merge(leftHalf, rightHalf);
    
    //printList(sortedList);
    return sortedList;
    
    
    
}


int main() {

    node* head = NULL;
    
    populateList(head);
    
    cout << " Unsorted List: \n" << endl;
    printList(head);
 
    node* resultList = mergeSort(head);
    
    cout << "Sorted List: \n" << endl;
    printList(resultList);
    return 0;
}
