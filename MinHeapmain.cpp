//
//  main.cpp
//  Nivedita Amanjee | SID: 1595694
// CISP 430 | LEC 11597
// Assignment: Min-heap
//
//Instructions:
//Insert 10 values into a min-heap from a file.  Display the data, level by level.Then delete 5 items. After each delete, display the heap, level by level.

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ifstream input("input.txt");
int heapArray[20];
int indexCount = 0;

void swap(int a, int b){
    
    //cout << "Swap Values before: (a) " << heapArray[a] << " (b) " << heapArray[b] << endl;
    int temp = heapArray[a];
    heapArray[a] = heapArray[b];
    heapArray[b] = temp;
    //cout << "Swap Values after: (a) " << heapArray[a] << " (b) " << heapArray[b] << endl;
    
}

void reheapUp(int index){
    
    int parentIndex = (index-1)/2;
    int parentValue = heapArray[parentIndex];
    int insertedValue = heapArray[index];
    
 
    if (index < 1){
        return;
    }
  
    if(parentValue >= insertedValue){
        swap(parentIndex, index);
        reheapUp(parentIndex);
    }


}
void insert(int value){
    heapArray[indexCount] = value;
    reheapUp(indexCount);
    indexCount++;
    
}



void printHeapArray(int maxSize){
    
    cout << "Heap: ";
    for(int i = 0; i < maxSize; i++){
        cout << heapArray[i] << " ";
    }
    cout << endl;
}
void reheapDown(int root){
    int parent = heapArray[root];
   
    
    int leftChild = heapArray[2*root+1];
    int rightChild = heapArray[2*root+2];
    int leftChildIndex = 2*root+1;
    int rightChildIndex = 2*root+2;
    
    int smallerChild;
    int smallerChildIndex;
    
    if(leftChildIndex > indexCount || rightChildIndex > indexCount){return;};
    if(rightChildIndex == indexCount){
        smallerChild = leftChild;
        smallerChildIndex = leftChildIndex;
    }
    else{

        smallerChild = (leftChild<rightChild) ? leftChild : rightChild;
        smallerChildIndex = (leftChild<rightChild) ? leftChildIndex : rightChildIndex;
    };
    //cout << "Left Child: " << leftChild << " | " << "Right Child: " << rightChild << endl;
    //cout << "Smaller Child: " << smallerChild << endl;
   //swap with the smaller child
   if(parent > smallerChild ){
       swap(root, smallerChildIndex);
       reheapDown(smallerChildIndex);
   }



}

void popArray(){

    if (indexCount < 0){return;}

    indexCount--;
    swap(0, indexCount);
 
    reheapDown(0);
    
}

void printLevels(){
    int level = 1;
    int count = 0;

    while(count < indexCount){
        
        int nodesPerLevel = pow(2, level-1);
        cout << "Level " << level << ": ";
        while (count < indexCount && nodesPerLevel > 0){
            cout << heapArray[count++] << " ";
            nodesPerLevel--;
        }
        cout << endl;
        level++;
        
    }
    cout << "\n" << endl;
    
}



int main() {
  
    int value;

    
    
    while (input){ //if the file doesn't exist or isn't found, an output is printed
        while (input >> value){ //the file is read until whitespace is found

            insert(value);
       
          }
          
    }
    
    printHeapArray(indexCount);
    printLevels();
    
    for (int i = 0; i < 5; i++){
        cout << "Delete " << i+1 << " value: " << heapArray[0] << endl; //pop function that replaces the index 0 value with the
                        //value of the last index
                        //and returns the popped value
        popArray();
        printHeapArray(indexCount);
        printLevels();
        
    }
    return 0;
}
