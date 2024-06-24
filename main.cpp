//
//  main.cpp
//  Project 3b
//
//  Created by Kc Ashiogwu

#include <fstream>
#include <iostream>
#include "SplayTree.h"
#include "BinarySearchTree.h"
#include <vector>
#include <chrono>

using namespace std;

int main(int argc, char ** argv) {
    fstream FileofIntegers("/Users/kcashiogwu/Downloads/p3_test0.txt");//argv[1]);
    //BinarySearchTreeNode* root = NULL;
    if(!FileofIntegers){
        cout << "Error opening file ";
        return 1;
    }
    else {
        cout << "File Opened" << endl;
        vector<int> Integers; //this should be your binary search tree object
       int ToLoadIntegers;
        //idk if this while loop should be in the else statement
        BST theTree;
        
        //for the splay tree methods
        ST SplayTree;
        vector<int> values;
       int valuesLoaded;
        
        
        //implement time here
        chrono::steady_clock::time_point t3 = chrono::steady_clock::now();
        cout << "building the tree. inserting everything..." << endl;
        while (FileofIntegers >> valuesLoaded){
            SplayTree.insert(valuesLoaded);
            //cout << ToLoadIntegers << " ";
            //cout << "\n";
        }
        chrono::steady_clock::time_point t4 = chrono::steady_clock::now();
        
        SplayTree.print();
        
        cout << endl << endl << endl;
        
        //cout << theTree.root;
        
        FileofIntegers.clear();
        char dollar1;
        
        //read the dollar sign
        FileofIntegers >> dollar1;
        
        cout << "searching the Splay tree for things" << endl;
        
        //searching for the elements withing the tree
        while (FileofIntegers >> valuesLoaded){
            cout << "searching for " << valuesLoaded << ": ";
            SplayTree.search(valuesLoaded);
    
        }
        
        FileofIntegers.clear();
        //char dollar;
        
        //read the dollar sign
        FileofIntegers >> dollar1;
        
        cout << "removing the Splay tree for things" << endl;
        
        //searching for the elements withing the tree
        while (FileofIntegers >> valuesLoaded){
            cout << "removing " << valuesLoaded << endl;
            SplayTree.remove(valuesLoaded);
    
        }
       
        SplayTree.print();

       
    
    
    unsigned long SplayTree_insertTime = chrono::duration_cast<chrono::nanoseconds>(t4-t3).count();
        
        FileofIntegers.close(); //file is closed
        
       
       // FileofIntegers.clear();
        FileofIntegers.open("/Users/kcashiogwu/Downloads/p3_test0.txt");
        //binary tree
        //implement time here
        chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
        cout << "building the tree. inserting everything..." << endl;
        while (FileofIntegers >> ToLoadIntegers){
            theTree.Insert(ToLoadIntegers);
            //cout << ToLoadIntegers << " ";
            //cout << "\n";
        }
        chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
        
        theTree.PrintTree();
        
        cout << endl << endl << endl;
        
        //cout << theTree.root;
        
        FileofIntegers.clear();
        char dollar;
        
        //read the dollar sign
        FileofIntegers >> dollar;
        
        cout << "searching the tree for things" << endl;
        
        //searching for the elements withing the tree
        while (FileofIntegers >> ToLoadIntegers){
            cout << "searching for " << ToLoadIntegers << ": ";
            cout << theTree.Search(ToLoadIntegers) << endl;
    
        }
        
        FileofIntegers.clear();
        //char dollar;
        
        //read the dollar sign
        FileofIntegers >> dollar;
        
        cout << "removing the tree for things" << endl;
        
        //searching for the elements withing the tree
        while (FileofIntegers >> ToLoadIntegers){
            cout << "removing " << ToLoadIntegers << endl;
            theTree.Remove(ToLoadIntegers);
    
        }
       
        theTree.PrintTree();

       
    
    
    unsigned long Tree_insertTime = chrono::duration_cast<chrono::nanoseconds>(t2-t1).count();
        
        FileofIntegers.close(); //close file
    
    //Integers.search();
        
    
    cout << "\n" << "Time to Construct Binary Tree: " << Tree_insertTime << endl;
    
    
    
    cout << "\n" << "The Traversal Count for the Binary Search tree was: " << theTree.getCount() << endl;
    
    cout << "\n" << "Time to Construct Binary Tree: " << SplayTree_insertTime << endl;
        
    cout << "\n" << "The Traversal Count for the Binary Search tree was: " << SplayTree.getCount() << endl;
        
        
    
    }


}
