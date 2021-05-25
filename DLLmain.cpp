//
//main.cpp
//Nivedita Amanjee
//Student ID : 1595694
//CISP 430 | LEC 11597
//Program that reads in a collection of names from a file and ouputs a list of the correctly sorted names onto a file

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

ifstream inFile("input.txt");
ofstream outFile("output.txt");

struct node {
    string name;
    node *next;
    node *prev;
};

struct nodeList{
    node *head;
    node *tail;
};


void traverseBegToEnd(nodeList &list){
    node * current = list.head;
    outFile << "List from Beginning to End: " << endl;
    while (current != NULL){
        outFile << current -> name << endl;
        current = current -> next;
    }
    
    outFile << "=======================================================================" << endl;
}

void traverseEndToBeg(nodeList &list){
    node * current = list.tail;
    
    outFile << "List from End to Beginning: " << endl;
    while (current != NULL){
        outFile << current -> name << endl;
        current = current -> prev;
    }
}
node * searchList(nodeList &list, string name){
    node * resultNode=list.head;


        if (!list.head){
            return NULL;
        }
    
    while (resultNode->next){

            if(resultNode->name == name){
                break;
            }

            resultNode = resultNode->next;

       
    }
    
        if(resultNode->name != name){
                resultNode = NULL;
        }

return resultNode;
}
//delete function:
void deleteNode(nodeList &list, string name){

    node * matchingNode = searchList(list, name);
    if (matchingNode){
        if(matchingNode == list.head){
            list.head = list.head->next;
        }
        else{
            matchingNode->prev->next = matchingNode->next;
        }

        if(matchingNode == list.tail){
            list.tail = list.tail->prev;
        }
        else{
            matchingNode->next->prev = matchingNode->prev;
        }
    }
    delete matchingNode;
}

void insertNode(nodeList &list, string name){
    node * newNode = new node;
    newNode->name= name;
    newNode->prev = NULL;
    newNode->next = NULL;

    cout << "Name to be inserted: " << name << endl;

    if(list.head == NULL && list.tail == NULL){//if the list is empty:
            list.tail = newNode;
            list.head = newNode;
            return;
    }
    cout << "Head's name is: " << list.head->name << endl;
    cout << "Tail's name is: " << list.tail->name << endl;

    cout << "search list returns: " << searchList(list, newNode->name) << endl;
    if(!searchList(list, name)){//if the duplicate is not found:
    cout << "the name isn't on the list" << endl;
        if(newNode->name < list.head->name){//if the name to be inserted is smaller than the head
            newNode->next = list.head;
            list.head->prev = newNode;
            list.head = newNode;
            newNode->prev = NULL;
        }
        else if(newNode->name > list.tail->name){//if the name is larger than the tail
                newNode-> prev = list.tail;
                list.tail->next = newNode;
    
                list.tail = newNode;
                newNode->next = NULL;
        }
        else {//if the name is somewhere in the middle
            node * current = list.head;//current node is created to search through the list
            while (name > current->name){//while loop that searches for location of insertion
                current = current->next;
            }
                current->prev->next = newNode;
                newNode->prev = current->prev;
                newNode->next = current;
                current->prev = newNode;
        }
    }

    cout<< "List.head->name: " << list.head->name << endl;
    cout<< "List.tail->name: " << list.tail->name << endl;
}




int main() {
    
    nodeList list; //list that holds the head and tail pointers
    list.head = NULL;
    list.tail = NULL;

    string line;

    while (inFile){
                line = "";
        inFile >> line;
     
            cout << line << "\n\n";
            
            
            if (line == "delete"){
            
                    inFile >> line;
                    cout << "Name to be deleted: " << line <<endl;
                    deleteNode(list, line);
            }

            else if (line != "") {
                
                insertNode(list, line);
                
            }
            
            
        }
   
  
    
    traverseBegToEnd(list);
    traverseEndToBeg(list);
    inFile.close();
    outFile.close();

    
    
    return 0;
}
