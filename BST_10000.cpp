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

vector<int> getRandInts(vector<int> arr){
  int maxVal = 10000;
  int minVal = 1;
  for(int i =0; i<10000;i++){
      int rando = rand() % maxVal + minVal;
    arr.push_back(rando);
  }
  return arr;
}

Node* findMaxNode(Node* root){
    if(root == NULL){cout <<"No tree.\n";}
    if(root->right == NULL){ return root;} // if right child is null return parent
        return findMaxNode(root->right); // go right  
}

Node* findMinNode(Node* root){
    if(root == NULL){cout <<"No node here.\n";}
         if(root->left == NULL){return root;} // if left child is null return parent
            return findMinNode(root->left); // go left    
}

Node* findNextNode(Node* root, int data){ 
    Node* next = NULL;
    if(root == NULL){cout << "No node"; } // if node does not exist return
    if(isLeaf(root)){return root;}
    if(root->data == data)
         return findMinNode(root->right);// if right child exists, find min if right child
    return root;
    }

Node* findPrevNode(Node* root){// for right child prev = parent
    Node* prev = root->parent;
    if(root == NULL){cout <<"No tree found. "; return root;}
    else if(root->left == NULL){return prev;}
    else {return findMaxNode(root->left); }
        return prev;
}
int height(Node* node)  
{  
    if (node == NULL)  
        return 0;  
    else
    {  
        /* compute the height of each subtree */
        int lheight = height(node->left);  
        int rheight = height(node->right);  
  
        /* use the larger one */
        if (lheight > rheight)  
            return(lheight + 1);  
        else return(rheight + 1);  
    }  
}  

void printGivenLevel(Node* root, int level) 
{ 
    if (root == NULL) 
        return; 
    if (level == 1) 
        cout<< root->data <<" "; 
    else if (level > 1) 
    { 
        printGivenLevel(root->left, level-1); 
        printGivenLevel(root->right, level-1); 
    } 
} 

void printLevelOrder(Node* root) 
{ 
    int h = height(root); 
    int i; 
    for (i=1; i<=h; i++) 
    { 
        printGivenLevel(root, i); 
        cout<<"\n"; 
    } 
} 
  
Node* deleteNode(Node* root, int data){
    Node* parent = root->parent;
    if(root == NULL) {cout<<"There is no tree here.\n"; }
    if(isLeaf(root->left) == true){delete(root->left); return root;}
    else if (data < root->data){
                root->left = deleteNode(root->left, data); 
    }else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    }else if(data == root->data){free(root); root =  findMaxNode(root->left); }
          
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

vector<int> b = {8, 4, 12, 2, 6, 1, 3, 5, 7, 10, 14, 9, 11};

vector<int> c;

//makeTree(b); // insert a vector of ints to create tree

for(auto i: getRandInts(c))
    {
        root = insertNode(root, i);
    }


//root = insertNode(root, 13);
//root = insertNode(root, 15);
Node* min = findMinNode(root);
Node* max = findMaxNode(root);
//Node* prev = findPrevNode(max);
printLevelOrder(root);

//printTree(root);

cout<<"\nMin node is: "<< min->data;

cout<<"\nNext node is: "<< findNextNode(root,10)->data;
//cout<<"\nNext node is: "<< findNextNode(min->right->right)->data;

cout<<"\nMax node is: "<< max->data;

// cout<<"\nPrev node is: "<< prev->data << endl;
return 0;
}
