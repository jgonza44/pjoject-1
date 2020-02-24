#include<bits/stdc++.h>
#include<vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

};

Node* createNode(int data){
    Node* node = new Node();
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;

}

void printArray(const vector<int>& arr) {
    for (auto val : arr) {
    cout << val << " ";
    }
}

class CompleteTree{
    vector<vector<int> > Array;
    private:
        Node* root;

        int parent(int i) {return (i - 1) / 2; }
        int left(int i) {return 2 * i + 1;}
        int right(int i) {return 2 * i + 2;}

    public:

    void fromArray(vector<int> list) {
        vector<Node*> nodes;

        for (int value : list) {
        Node* node = createNode(value);
        nodes.push_back(node);
        }
    }


};

int main()
{
    CompleteTree MyTree;

    vector<int> myvec;
    int elem;
    cin >> elem;
    myvec.push_back(elem);
    MyTree.fromArray(myvec);
    printArray(myvec);

    return 0;
}