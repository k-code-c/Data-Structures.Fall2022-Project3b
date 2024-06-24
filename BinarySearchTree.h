/* //in this implementation we will be creating a binary search tree that will allow us to add different methods.
 //we will be implementing a search method, insert method, remove and display*/
/* //To construct such a print statement, perform a Depth First Traversal and 1.) print an open bracket when traversing down 1 depth to a child node, 2.) print the key for that node (or nothing, if null) and 3.) print a close bracket for each depth retreated. For leaf nodes, the program should not print its null children (it should only print a null node if it’s a null child of a
 parent with one non-null child. */

/* //The first line of the input file will contain all the integer numbers to store, separated by spaces.
 //Using this input, the program should initialize the tree structure. This line will be followed by a new
 //line character. The second line—which serves to separate the initialization values from the search
 //values—has just a single symbol, dollar sign ($), followed by a new line character. The third line
 //contains the sequence of search values. For each of these integers, the program should search for
 //the value from the tree (if the tree, in fact, contains the value). This line will be followed by a new
 //line character. The fourth line—which serves to separate the search values from the removal
 //values—has just a single symbol, dollar sign ($), followed by a new line character. The fifth line
 //contains the sequence of search values. For each of these integers, the program should remove the
// value from the tree (if the tree, in fact, contains the value). */
#include <iostream>
#include<list>
#include<cstring>
#include<fstream>

using namespace std;


class BinarySearchTreeNode{
    //the elements of operation for our search tree
    public:
    int Key;
    BinarySearchTreeNode* left; //left side of the tree
    BinarySearchTreeNode* parent; //parent node
    BinarySearchTreeNode* right; //right side of the tree
    
    BinarySearchTreeNode();
    BinarySearchTreeNode(int key); //overloaded constrcutor
    
   
};

class BST{
private:
  //  BinarySearchTreeNode * root;
//protected:
    
   BinarySearchTreeNode* Insert(BinarySearchTreeNode* node, int Givenkey);
    bool Search(BinarySearchTreeNode* node, int Givenkey);
   void PrintTree(BinarySearchTreeNode* node);
    void DeleteRecursive(BinarySearchTreeNode* LocalRoot);
    void Remove(int r,BinarySearchTreeNode* LocalRoot, BinarySearchTreeNode* Caller);
    BinarySearchTreeNode* RemoveMin( BinarySearchTreeNode* Parent,  BinarySearchTreeNode* node);
    int count;
    
public:
    BinarySearchTreeNode * root;
    BST(); //constrcutor
    ~BST();
    
    void Insert(int Givenkey);
    bool Search(int Givenkey);
    void Remove(int r);
    void PrintTree();
    int getCount();

};

int BST::getCount(){
    return count;
}

BinarySearchTreeNode::BinarySearchTreeNode(){ //constructor for BinarySearchTreeNode
    left=right=NULL;
    
}

BinarySearchTreeNode::BinarySearchTreeNode(int key){
    left=right=NULL;
    Key = key;
}

BST::BST() {
    root = NULL;
    count = 0;
}

BST::~BST() {
    DeleteRecursive(root);
}

void BST::DeleteRecursive(BinarySearchTreeNode* LocalRoot){
    //case 1: tree is empty, just return
    if(LocalRoot == NULL){
        return;
        
    }
    //case 2: do all of this:
        //recursively call this method with localRoot -> right
        //recursively call this method with localRoot -> left
        //delete localRoot
    
    DeleteRecursive(LocalRoot->right);
    DeleteRecursive(LocalRoot->left);
    delete LocalRoot;
    
};


BinarySearchTreeNode* BST::Insert(BinarySearchTreeNode* node, int Givenkey){
    //for this insert function we will be adding a new node based on the behavior of the BST
    //in order to insert a key we need to compare it with the root key(if there is no root key, the node being inserted becomes the root) and check if it is greater or smaller than the root key
    if(node == NULL){
        BinarySearchTreeNode* NewNode = new BinarySearchTreeNode();
        NewNode->Key = Givenkey;
        node = NewNode;
        count++;
    }
    else if (node->Key < Givenkey){
        //case 1: right is null pointer
        //case 2: right is another subtree
        if(node->right == NULL){
            BinarySearchTreeNode* NewNode = new BinarySearchTreeNode();
            NewNode->Key = Givenkey;
            node->right = NewNode;
            count++;
        }
        else{
         Insert(node->right, Givenkey);
        node->right->parent = node;
            count++;
        }
    }
    
    //go to the left subtree if the given key is smaller thab the nodes key
    else{
        if(node->left == NULL){
            BinarySearchTreeNode* NewNode = new BinarySearchTreeNode();
            NewNode->Key = Givenkey;
            node->left = NewNode;
            count++;
        }
        else{
         Insert(node->left, Givenkey);
        node->left->parent = node;
            count++;
        }
    }
    return node;
}

void BST::Insert(int Givenkey){
    //passing root node and given key
     root = Insert(root, Givenkey);
}

bool BST::Search(BinarySearchTreeNode* node, int Givenkey){
    //1. if the given key is not in the node return NULL
    //2. if the given key is found return the node
    //3. if the given key is greater than the current nodes key and same thing with the smaller node
   /* if(Givenkey == node->Key){
        return NULL;
    }*/
    if(node == NULL){
        return false; //might have to flip the true and the false around
        count++; //just added the count for the traversal count
    }
    if(node->Key == Givenkey){
            return true;
        }
    else if(node->Key > Givenkey){
        count++;
        return Search(node->left, Givenkey);

            }
    else{
        count++;
        return Search(node->right, Givenkey);
            }
    }

bool BST::Search(int Givenkey){
    //if the key is found return true else return false
    //cout << root;
    //BinarySearchTreeNode* result = Search(root, Givenkey);
    if(root == NULL){
        return false; //might have to flip the true and the false around
    }
    return Search(root,Givenkey);
}


void BST::Remove(int Givenkey){
     Remove(Givenkey, root, root);
}

void BST::PrintTree(BinarySearchTreeNode* node){
    if(root == NULL){
        cout << "[" << "]" ;
        return;
    }
    if(node != NULL){
        cout << "[" << node->Key;//idk if it should be Key
        if(node->left != NULL || node->right != NULL){
            PrintTree(node->left);
            PrintTree(node->right);
            
        }
        cout << "]";
        
    }
}

void BST::PrintTree(){
    //cout << "I work";
    PrintTree(root);
}

void BST::Remove(int r,BinarySearchTreeNode* LocalRoot, BinarySearchTreeNode* Caller){
    if(LocalRoot != NULL){
        if(LocalRoot->Key < r){
            //go to right subtree
            count++;
            Remove(r, LocalRoot->right,LocalRoot);
        }
        else if(LocalRoot->Key > r){
            //go to left subtree
            Remove(r, LocalRoot->left,LocalRoot);
            
        }
        else if(LocalRoot->left != NULL && LocalRoot->right!= NULL){
            //node found, it has 2 children
            //so, we need to remove the minimum node of the right subtree & copy to root
            
            BinarySearchTreeNode* MinRight = RemoveMin(LocalRoot, LocalRoot->right);
            int temp = LocalRoot->Key;
            count++;
            LocalRoot->Key = MinRight->Key;
            count++;
            MinRight->Key = temp;
            count++;
            Remove(temp,LocalRoot->right, LocalRoot);
        }
        else{
        
            //we found the node, and it has either 0 or 1 child
            //so, we just need to delete it and reconnect the pointers
            
            BinarySearchTreeNode* Trash = LocalRoot;
            count = count + 3;
            if(Caller->left == LocalRoot){
                if(LocalRoot->left == NULL && LocalRoot->right == NULL){
                    Caller->left = NULL;
                }
                else if(LocalRoot->left != NULL){
                    Caller->left = LocalRoot->left;
                }
                else{
                    Caller->left = LocalRoot->right;

                }
            }
            else if(Caller->right == LocalRoot){
                if(LocalRoot->left == NULL && LocalRoot->right == NULL){
                    Caller->right = NULL;
                }
                else if(LocalRoot->left != NULL){
                    Caller->right = LocalRoot->left;
                }
                else{
                    Caller->right = LocalRoot->right;

                }
            }
            //delete the node we removed;
            
            //if statement to set root to null if we just deleted the last node (aid destructor)
            delete Trash;
            if(Caller == LocalRoot){
                root = NULL;
            }
            
        }
        
       
    }
}

BinarySearchTreeNode* BST:: RemoveMin( BinarySearchTreeNode* Parent,  BinarySearchTreeNode* node){
    if(node != NULL){
        if(node->left == NULL){
            return node;
        }
        else{
            return RemoveMin(node, node->left);
        }
    }
    else{
        return NULL;
    }
}





