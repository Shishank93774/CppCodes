#include <iostream>
#include <queue>
#include<list>
#include "BST.h"
using namespace std;

BinaryTreeNode<int> *takeInput()
{
    int rootData;
    cout << "Enter Data\n";
    cin >> rootData;
    if (rootData == -1)
    {
        return NULL;
    }
    BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootData);
    queue<BinaryTreeNode<int> *> qu;
    qu.push(root);
    while (!qu.empty())
    {
        BinaryTreeNode<int> *front = qu.front();
        int leftData;
        cout << "Enter Left Data of " << front->data << "\n";
        cin >> leftData;
        if (leftData != -1)
        {
            BinaryTreeNode<int> *leftChild = new BinaryTreeNode<int>(leftData);
            front->left = leftChild;
            qu.push(leftChild);
        }
        int rightData;
        cout << "Enter Right Data of " << front->data << "\n";
        cin >> rightData;
        if (rightData != -1)
        {
            BinaryTreeNode<int> *rightChild = new BinaryTreeNode<int>(rightData);
            front->right = rightChild;
            qu.push(rightChild);
        }
        qu.pop();
    }
    return root;
}

BinaryTreeNode<int> *bSearch(BinaryTreeNode<int> *root, int x)
{
    BinaryTreeNode<int> *temp = NULL;
    if (root == NULL)
    {
        return NULL;
    }
    if (root->data == x)
    {
        return root;
    }
    else if (x < root->data)
    {
        temp = bSearch(root->left, x);
    }
    else
    {
        temp = bSearch(root->right, x);
    }
    return temp;
}

void printInRange(BinaryTreeNode<int> *root, int a, int b)
{
    if (root == NULL)
    {
        return;
    }
    if (root->data >= a)
    {
        if (root->data >= b)
        {
            cout << root->data << " ";
            printInRange(root->left, a, b);
        }
        else
        {
            printInRange(root->left, a, root->data);
            cout << root->data << " ";
            printInRange(root->right, root->data, b);
        }
    }
    else
    {
        printInRange(root->right, a, b);
    }
}

int maxElmntInTree(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return INT32_MIN;
    }
    return max(root->data, max(maxElmntInTree(root->left), maxElmntInTree(root->right)));
}

int minElmntInTree(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return INT32_MAX;
    }
    return min(root->data, min(minElmntInTree(root->left), minElmntInTree(root->right)));
}

void levelOrderPrint(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return;
    }
    queue<BinaryTreeNode<int> *> qu;
    qu.push(root);
    qu.push(NULL);
    while (!qu.empty())
    {
        BinaryTreeNode<int> *front = qu.front();
        qu.pop();
        if (front != NULL)
        {
            cout << front->data << " ";
            if (front->left != NULL)
            {
                qu.push(front->left);
            }
            if (front->right != NULL)
            {
                qu.push(front->right);
            }
        }
        else
        {
            if (qu.empty())
            {
                break;
            }
            cout << endl;
            qu.push(NULL);
        }
    }
}

void printLevelWise(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return;
    }
    queue<BinaryTreeNode<int> *> qu;
    qu.push(root);
    while (!qu.empty())
    {
        BinaryTreeNode<int> *front = qu.front();
        cout << front->data << ":";
        if (front->left != NULL)
        {
            cout << " L" << front->left->data;
            qu.push(front->left);
        }
        if (front->right != NULL)
        {
            cout << " R" << front->right->data;
            qu.push(front->right);
        }
        qu.pop();
        cout << endl;
    }
}

void preOrder(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return;
    }
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

bool isBST(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return true;
    }
    int lmax = maxElmntInTree(root->left);
    int rmin = minElmntInTree(root->right);
    bool temp = (root->data > lmax) && (root->data <= rmin) && isBST(root->left) && isBST(root->right);
    return temp;
}

pair<pair<int, int>, bool> minMaxIsBST(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return {{INT32_MAX, INT32_MIN}, true};
    }
    pair<pair<int, int>, bool> lft = minMaxIsBST(root->left);
    pair<pair<int, int>, bool> rt = minMaxIsBST(root->right);
    int mx = max(root->data, max(rt.first.second, lft.first.second));
    int mn = min(root->data, min(rt.first.first, lft.first.first));
    bool chk = (root->data > lft.first.second) && (root->data <= rt.first.first) && (lft.second) && (rt.second);
    return {{mn, mx}, chk};
}

bool isBST3(BinaryTreeNode<int> *root, int mn = INT32_MIN, int mx = INT32_MAX)
{
    if (root == NULL)
    {
        return true;
    }
    if (root->data <= mn or root->data > mx)
    {
        return false;
    }
    bool chk = isBST3(root->left, mn, root->data) && isBST3(root->right, root->data, mx - 1);
    return chk;
}

BinaryTreeNode<int> *makeTreeFromSortedArray(int arr[], int st = 0, int lst = INT32_MAX)
{
    if(st>lst){
        return NULL;
    }
    int md = (lst - st) / 2 + st;
    BinaryTreeNode<int> *root = new BinaryTreeNode<int>(arr[md]);
    root->left = makeTreeFromSortedArray(arr, st, md-1);
    root->right = makeTreeFromSortedArray(arr, md+1, lst);
    return root;
}

void SortedLlFromBST(BinaryTreeNode<int> *root, list<BinaryTreeNode<int> *> &lst){
    if(root == NULL){
         return;
    }
    SortedLlFromBST(root->left, lst);
    lst.push_back(root);
    SortedLlFromBST(root->right, lst);
}

vector<int> * pathToRoot(BinaryTreeNode<int> *root, int x){
    if(root == NULL){
        return NULL;
    }
    if(root->data == x){
        vector<int> *arr = new vector<int>;
        arr->push_back(root->data);
        return arr;
    }
    vector<int> *vec = new vector<int>;
    vec = pathToRoot(root->left, x);
    if(vec == NULL){
        vec = pathToRoot(root->right, x);
        if(vec == NULL){
           return NULL;
        }else{
           vec->push_back(root->data);
           return vec;
        }
    }
    vec->push_back(root->data);
    return vec;
}

int main()
{
     BST b;
     b.insertAVLly(30);
     b.insertAVLly(100);
     b.insertAVLly(90);
     b.insertAVLly(80);
     b.insertAVLly(70);
     b.insertAVLly(60);
     b.insertAVLly(50);
     b.insertAVLly(40);
     system("cls");
     BinaryTreeNode<int> *root = b.getRoot();
     printLevelWise(root);
     cout<<endl;
     b.insertAVLly(35);
     b.insertAVLly(32);
     b.insertAVLly(22);
     printLevelWise(root);
    //  b.deleteData(25);
    //  b.deleteData(40);
    //  cout<<endl;
    //  printLevelWise(root);
    
   
    
    // BinaryTreeNode<int> *root = takeInput();
    // 40 20 60 10 30 50 70 -1 -1 -1 -1 -1 -1 -1 -1
    // int x;
    // cin>>x;
    // BinaryTreeNode<int> *res = bSearch(root, x);
    // if(res == NULL){
    //     cout<<x<<" not found!\n";
    // }else{
    //     cout<<x<<" found!\n";
    // }
    // int a, b;
    // cin >> a >> b; // b >= a   always
    // printInRange(root, a, b);
    // cout << isBST(root);
    // pair<pair<int, int>, bool> pr = minMaxIsBST(root);
    // cout<<pr.first.first<<" "<<pr.first.second<<" "<<pr.second;
    // cout<<isBST3(root);
    // int arr[] = {1, 2, 3, 4, 5, 7, 89, 90, 91, 101, 145, 172, 199, 400, 1000, 2000, 2312, 5432};
    // int sz = sizeof(arr) / sizeof(arr[0]);
    // printLevelWise(root);
    // int n;
    // cin>>n;
    // int *arr = new int[n];
    // for(int i = 0; i<n; i++){
    //     cin>>arr[i];
    // }
    // BinaryTreeNode<int> *root = makeTreeFromSortedArray(arr, 0, n-1);
    // preOrder(root);
    // list<BinaryTreeNode<int> *> lst;
    // SortedLlFromBST(root, lst);
    // for(auto it: lst){
    //     cout<<it->data<<" ";
    // }
    // int x;
    // cin>>x;
    // vector<int>* vec = pathToRoot(root, x);
    // for(int i = 0; i<vec->size(); i++){
    //     cout<<vec->at(i)<<" ";
    // }
    // delete root;
    return 0;
}