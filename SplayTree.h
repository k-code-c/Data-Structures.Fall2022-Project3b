#include <iostream>
#include<list>
#include<cstring>
#include<fstream>

using namespace std;

//the tree node
class node
{
public:
    int key;
    node* left;
    node* right;
    node* parent;
    
    node();
    node(int key); //overloaded constrcutor
};

class ST{
private:
    // node* insert();
    node * root;
    node *SplaySearch(node *node, int key);
    void leftRotate(node *x);
    void rightRotate(node *x);
    node *splay(node *);
    node * insert(node *, int);
    void privatePrint(node *);
    void DeleteRecursive(node *);
    node * findMax(node *);
    int count;
public:
    
    void insert(int);
    void remove(int);
    void search(int);
    void print();
    int getCount();
    ST();
    ~ST();
    
    
};
int ST::getCount(){
    return count;
}
node::node(){ //constructor for BinarySearchTreeNode
    left=right=parent=NULL;
}

node::node(int key){
    left=right=parent=NULL;
    this->key = key;
}

ST::ST() {
    root = NULL;
    count = 0;
}

ST::~ST() {
    DeleteRecursive(root);
}

void ST::DeleteRecursive(node* LocalRoot){
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
//this will allocate a new node with the given key and NULL for the left and right pointers

//a utility function for right rotating a y-rooted subtree.
void ST::rightRotate(node *x){
    //TODO: implenent
    node *y = x->left;
    x->left = y->right;
    if(y->right != NULL){
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL){
        root = y;
    }
    else if(x == x->parent->right){
        x->parent->right = y;
    }
    else{
        x->parent->left = y;
    }
    //update parent right or left child
    //parent->right = x->left; //this is not right
    //make y's right child x
    y->right = x;
    x->parent = y;
}

void ST::leftRotate(node *x){ //a utility function for right rotating a x-rooted subtree
    //TODO: implenent
    node *y = x->right;
    x->right = y->left;
    if(y->left != NULL){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL){
        root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    //update parent right or left child
    //parent->right = x->left; //this is not right
    //make y's right child x
    y->left = x;
    x->parent = y;
}

//1. if the key is present in the tree, move it to the root
//2. if the key is not present, return the last item accessed by the root
//3. this function modifies the tree and returns the modifeid root

node * ST::splay(node *toBeSplayed){
    while(toBeSplayed->parent != NULL){
        if(toBeSplayed->parent->parent == NULL){
            if(toBeSplayed == toBeSplayed->parent->left){
                //rotate right
                rightRotate(toBeSplayed->parent);
            }
            
            else{
                //roate left
                leftRotate(toBeSplayed->parent);
            }
        }
        else if(toBeSplayed == toBeSplayed->parent->left && toBeSplayed->parent == toBeSplayed->parent->parent->left){ //idk why parent is not declared
            rightRotate(toBeSplayed->parent->parent);
            rightRotate(toBeSplayed->parent);
            
        }
        
        else if(toBeSplayed == toBeSplayed->parent->right && toBeSplayed->parent == toBeSplayed->parent->parent->right){
            leftRotate(toBeSplayed->parent->parent);
            leftRotate(toBeSplayed->parent);
            
        }
       else {
            rightRotate(toBeSplayed->parent);
            leftRotate(toBeSplayed->parent);
            
        }
    }
    //while toBeSplayed is not the root
    //check to see if toBeSplayed is one level below the root.
    //if toBeSplayed is a left child, zig (rotate right)
    //else zag (rotateLeft)
    //check to see if toBeSplayed is a left child, and its parent is ALSO a left child
    //perform a zig zig (2 rotate rights)
    //check to see if toBeSplayed is a right child, and its parent is ALSO a right child
    //perform zag zag (2 rotate lefts)
    //check to see if toBeSplayed is a right child and its parent is a left child
    //perform a zig zag (left THEN right)
    //check to see if toBeSplayed is a left child and its parent is a right child
    //perform a zag zig (right THEN left)
    return NULL;
    
}

node *ST::SplaySearch(node* node, int key){
    //1. if the given key is not in the node return NULL
    //2. if the given key is found return the node
    //3. if the given key is greater than the current nodes key and same thing with the smaller node
   /* if(Givenkey == node->Key){
        return NULL;
    }*/
    if(node == NULL){
        return NULL; //might have to flip the true and the false around
        count++;
    }
    if(node->key == key){
            return node;
        }
    else if(node->key > key){
        count++;
        return SplaySearch(node->left, key);

            }
    else{
        count++;
        return SplaySearch(node->right, key);
            }
}

void ST::search(int key){
    node * target = SplaySearch(root, key);
    splay(target);
} //review


void ST::privatePrint(node *node){
    if(root == NULL){
        cout << "[" << "]" ;
        return;
    }
    if(node != NULL){
        cout << "[" << node->key;//idk if it should be Key
        if(node->left != NULL || node->right != NULL){
            privatePrint(node->left);
            privatePrint(node->right);
            
        }
        cout << "]";
        
    }
    
}

void ST::print(){
    //cout << "I work";
    privatePrint(root);
}


node * ST::insert(node *localRoot, int Givenkey){
    if(localRoot == NULL){
        node* NewNode = new node();
        NewNode->key = Givenkey;
        localRoot = NewNode;
        count++;
        return NewNode;
    }
    else if (localRoot->key < Givenkey){
        //case 1: right is null pointer
        //case 2: right is another subtree
        if(localRoot->right == NULL){
            node* NewNode = new node();
            NewNode->key = Givenkey;
            localRoot->right = NewNode;
            NewNode->parent = localRoot;
            count++;
        }
        else{
            return insert(localRoot->right, Givenkey);
            count++;
            
        }
    }
    
    //go to the left subtree if the given key is smaller thab the nodes key
    else{
        if(localRoot->left == NULL){
            node* NewNode = new node();
            NewNode->key = Givenkey;
            localRoot->left = NewNode;
            NewNode->parent = localRoot;
            count++;
        }
        else{
            return insert(localRoot->left, Givenkey);
            count++;
            
        }
        
    }
    return NULL;
}

void ST::insert(int Givenkey){
    //passing root node and given key
    node *added = insert(root, Givenkey);
    splay(added);
}

node * ST::findMax(node *node){
    if(node != NULL){
        if(node->right == NULL){
            return node;
        }
        else{
            return findMax(node->right);
        }
    }
    else{
        return NULL;
    }
}// implement

void ST::remove(int key){
    search(key); //node that we are removing is at the root
    
    
    //case 0: node is the last node in the tree
        //just delete the root and set it to nullpointer
    
    if(root->left == NULL && root->right == NULL){
        delete root;
        root = NULL;
    }
    
    //case 1: root only has a left subtree
        //make left child the new root
    
    else if (root->left != NULL && root->right == NULL) {
        node * temp = root;
        root = root->left;
        root->parent = NULL;
        delete temp;
    
    }
    
    //case 2: root only has a right subtree
        //make right child the new root
    else if (root->left == NULL && root->right != NULL) {
        node * temp = root;
        root = root->right;
        root->parent = NULL;
        delete temp;
    
    }
    //case 3: root has both subtrees
        //we need to join the two subtrees
        //find the largest node in the left tree, splay it, then create new root with right subtree
    
    else{
        node * temp = root;
        node * right = root->right;
        node * left = findMax(root->left);
        splay(left);
        root->right = right;
        right->parent = root;
        delete temp;
    }
} // implement

