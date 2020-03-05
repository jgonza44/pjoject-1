// avl tree notes from class Monday 03/02/2020
// height of current = height of current.left and current.right (greater) + 1
// to figure out bal
// start at node
// traceback ancestors untilwe get node with bf -2 or + 2 or get to root
// if grandparent bf is less than -1 bf of parent = -1
// right right inbalalnce
// if bf of parent = 1
// rl inbalance
// gp > 1 LR
// pa = 1
// RL
// old gans = 10
// old parent = 13 and old node = 18
// old parent.left = oldgrand
// old parent.right = old node
// keep track of ancestry chain

#include <bits/stdc++.h>
using namespace std;

struct Node // create a node with all its attributes
{
	int data;
	Node* left;
	Node* right;
	Node* parent;
	int height;
};

bool isLeaf(Node* node){
    if(node->left == NULL && node->right == NULL){return true;}
    return false;
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

int height(Node* node) // keep track of nodes heights
{
	if (node == NULL)
	{
		return 0;
	}
	return node->height;
}

int max(int a, int b)
{if (a > b){return a;} return b;}

Node* makeNode(int data)
{
	Node* node;
	node = new Node();	node->data = data;
	node->left = NULL;	node->right = NULL;
	node->parent = NULL;  node->height = 1;
	return node;
}

Node* rightRotate(Node* curr)
{
	Node* temp = curr->left;
	curr->left = temp->right;
	temp->right = curr;

	curr->height = max(height(curr->left), height(curr->right)) + 1;
	temp->height = max(height(temp->left), height(temp->right)) + 1;

	return temp;
}

Node* leftRotate(Node* curr)
{
	Node* temp = curr->right;
	Node* temp1 = temp->left;
	temp->left = curr;
	curr->right = temp1;

	curr->height = max(height(curr->left), height(curr->right)) + 1;
	temp->height = max(height(temp->left), height(temp->right)) + 1;

	return temp;
}

int getBalance(Node* node)
{
	if (node == NULL)
		return 0;
	return height(node->left) - height(node->right);
}

Node* insert(Node* node, int data)
{
	if (node == NULL)	{return makeNode(data);}
	if (data < node->data)	{node->left = insert(node->left, data);}
	else if (data > node->data)	{node->right = insert(node->right, data);}
	else  {	return node;}

	node->height = 1 + max(height(node->left), height(node->right));
	int bal = getBalance(node);

	// left left
	if (bal > 1 && data < node->left->data){return rightRotate(node);}

	// right right
	if (bal < -1 && data > node->right->data){return leftRotate(node);}

	// left right Case
	if (bal > 1 && data > node->left->data)	{node->left = leftRotate(node->left);
		return rightRotate(node);}

	if (bal < -1 && data < node->right->data) {node->right = rightRotate(node->right);
		return leftRotate(node);}

	return node;
}

void printLevel(Node* root, int level)
{
	if (root == NULL){return;}
	if (level == 1)	{cout << "(" << root->data << ") ";}
	else if (level > 1)
	{
		printLevel(root->left, level - 1);
		printLevel(root->right, level - 1);
	}
}

void print(Node* root)
{
	int h = height(root);
	int i;
	for (i = 1; i <= h; i++)
	{
		printLevel(root, i);
		cout << "\n";
	}
}

Node* search(Node* root, int data) 
{ 
    if (root == NULL || root->data == data) 
       return root; 
    if (data > root->data) 
       return search(root->right, data); 
    return search(root->left, data); 
} 

Node* findMinNode(Node* node)
{
	// find the left-most child
	while (node->left)
	{
		node = node->left;
	}
	return node;
}

// Node* findMinNode(Node* root){
//     if(root == NULL){cout <<"No node here.\n";}
//          if(root->left == NULL){return root;} // if left child is null return parent
//             return findMinNode(root->left); // go left
// }

Node* findMaxNode(Node* node)
{
  if(!(node->right)){return node;}
	while (node->right)
	{
		node = node->right;
	}
	return node;
}

Node* findNextNode(Node* root, int data)
    { 
      Node* parent = search(root, data);
      if(parent == NULL){return root;}
      if(parent->right != NULL){return findMinNode(parent->right);}
      else{
        Node* next = NULL;
        Node* ancestor = root;
        while(ancestor != parent) {
          if(parent->data < ancestor->data) {
            next = ancestor; // so far this is the deepest node for which current node is in left
            next = ancestor->left;
            ancestor = ancestor->left;
            }
            else {next = ancestor->right;}
          }
		return next;
      }
      
     }

Node* findPrevNode(Node* root, int data){// for right child prev = parent
    Node* parent = search(root, data);
    // if node does not exist return
    if(parent == NULL){cout << "\nNo node";return parent;} 
    if(parent->left){return findMaxNode(parent->left);}
    return parent;
}

Node* deleteNode(Node* root, int data)
{
	if (root == NULL)
	{
		return root;
	}
	if (data < root->data)
	{
		root->left = deleteNode(root->left, data);
	}
	else if (data > root->data)
	{
		root->right = deleteNode(root->right, data);
	}
	else
	{
		if ((root->left == NULL) || (root->right == NULL))
		{
			Node* temp = root->left ? root->left : root->right;
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
			{
				*root = *temp;
				delete (temp);
			}
		}
		else
		{
			Node* temp = findMinNode(root->right);
			root->data = temp->data;
			root->right = deleteNode(root->right, temp->data);
		}
	}

	if (root == NULL)
	{
		return root;
	}

	root->height = 1 + max(height(root->left), height(root->right));

	int bal = getBalance(root);

	if (bal > 1 && getBalance(root->left) >= 0)
	{
		return rightRotate(root);
	}

	if (bal > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if (bal < -1 && getBalance(root->right) <= 0)
	{
		return leftRotate(root);
	}

	// right left case
	if (bal < -1 && getBalance(root->right) > 0)
	{ // root->right = rightChild
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}


int main()
{
	Node* root = NULL;
	int num, newint, com;
	//com = 0;
	vector<int> b = {};
	
	clock_t time_req;

    time_req = clock();

	// cout << "How many nodes will you enter?\n";
	// cin >> num;
	// cout << "Please enter one integer at a time.\n";

	// while (com < num)
	// {
	// 	cin >> newint;
	// 	b.push_back(newint);
	// 	com++;
	// 	cout << "Please enter an integer.\n";
	// }
	// // add to tree
	for (auto i : getRandInts(b))
	{
		root = insert(root, i);
	}

    cout << "\nAVL tree is \n";
	print(root);
	
	time_req = clock() - time_req;
	//deleteNode(root, 4);
	//cout << "\nAVL tree after delete \n";
	//print(root);
	
    cout<< "\nThe max node is "<<findMaxNode(root)->data;
    cout<< "\nThe min node is "<<findMinNode(root)->data;
    cout<< "\nThe next node is "<<findNextNode(root,5387)->data;
    cout<< "\nThe prev node is "<<findPrevNode(root,5387)->data;
    cout<< "\nThe time is "<< findPrevNode(root,5387)->data;
    cout << "\nAVL time is " << (float)time_req/CLOCKS_PER_SEC << " seconds" << endl;


	return 0;
}

