//Make Tree
#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    Node* parent;
    /*bool visited; //Maybe I will use this*/
};
Node* root = nullptr; // my tree is empty

bool isLeaf(Node* node){
    if(node->left == NULL && node->right == NULL){
        //cout <<"it is a leaf ";
        return true;
    }
    //cout <<"it is not a leaf ";
    return false;
}

Node* makeNode(int data){
    Node* temp;
    temp = new Node();
    temp->data = data;
    temp->left = nullptr;
    temp->right = nullptr;
    temp->parent = nullptr;
    return temp;
}

Node* insertNode(Node* root, int data){
    
    if(root == NULL){root = makeNode(data);} // creat the node in the tree
    else if(data < root->data ){ // check if node is smaller
         root->left = insertNode(root->left, data);
         root->left->parent = root;
    }else if(data > root->data ){ // check if node is greater
         root->right = insertNode(root->right, data);
         root->right->parent = root;
    }
    return root;
}

Node* findMaxNode(Node* root){
    if(root == NULL){cout <<"No tree.\n";}
    if(root->right == NULL){ return root;} // if right child is null return parent
        return findMaxNode(root->right); // go right  
}

Node* findMinNode(Node* root){
    if(root == NULL){cout <<"No tree.\n";}
         if(root->left == NULL){return root;} // if left child is null return parent
            return findMinNode(root->left); // go left    
}

Node* findNextNode(Node* root){
    if (root == NULL){cout << "No node";}
    else if(root->right == NULL){return root;}
         return findMinNode(root->right);
}

Node* findPrevNode(Node* root){
    Node* prev = root->parent;
    if(root == NULL){cout <<"No tree found. "; return root;}
    else if(root->left == NULL){return prev;}
    else {return findMaxNode(root->left); }
        return prev;
}

Node* deleteNode(Node* root, int data){
    if (root == NULL) {return root; }
    if(isLeaf(root) == true){
        free(root); return findMaxNode(root);
    }
    if (data < root->data){
                root->left = deleteNode(root->left, data); 
    }else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    }else if(data == root->data){}
          
    return root;
}

void makeTree(vector<int> ints){
    for(auto i: ints){
        root = insertNode(root, i);
    }
}

// void printTree(Node* root){
    
//     cout <<"My tree nodes are: "<< root->data << endl;
// }

int main(){

vector<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

makeTree(b); // insert a vector of ints to create tree

root = insertNode(root, 14);
root = insertNode(root, 15);
Node* min = findMinNode(root);
Node* max = findMaxNode(root);
Node* prev = findPrevNode(max);

//printTree(root);

cout<<"\nMin node is: "<< min->data;

cout<<"\nNext node is: "<< findNextNode(min)->data;
cout<<"\nNext node is: "<< findNextNode(min->right)->data;
cout<<"\nNext node is: "<< findNextNode(min->right->right)->data;

cout<<"\nMax node is: "<< max->data;

//cout<<"\n"<< isLeaf(min);

cout<<"\nPrev node is: "<< prev->data;

return 0;
}
