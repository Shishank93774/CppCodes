#include <iostream>
#include <queue>
#include <cstdlib>
#include <list>
#include <stack>
#include "binaryTreeNode.h"

using namespace std;

BinaryTreeNode<int> *takeInputCarefully()
{
    int rootData;
    cout << "Enter Data\n";
    cin >> rootData;
    if (rootData == -1)
    {
        return NULL;
    }
    BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootData);
    BinaryTreeNode<int> *leftChild = takeInputCarefully();
    root->left = leftChild;
    BinaryTreeNode<int> *rightChild = takeInputCarefully();
    root->right = rightChild;
    return root;
}

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

void print(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return;
    }
    if (root != NULL)
    {
        cout << root->data << ": ";
    }
    if (root->left != NULL)
    {
        cout << "L" << root->left->data << " ";
    }
    if (root->right != NULL)
    {
        cout << "R" << root->right->data << " ";
    }
    cout << endl;
    print(root->left);
    print(root->right);
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

int cntNodes(BinaryTreeNode<int> *root)
{
    int ans = 0;
    if (root == NULL)
    {
        return ans;
    }
    else
    {
        ans++;
    }
    ans += cntNodes(root->left);
    ans += cntNodes(root->right);
    return ans;
}

bool isThere(BinaryTreeNode<int> *root, int x)
{
    bool temp = false;
    if (root == NULL)
    {
        return false;
    }
    if (root->data == x)
    {
        return true;
    }
    else
    {
        temp = temp || isThere(root->left, x);
        temp = temp || isThere(root->right, x);
    }
    return temp;
}

int height(BinaryTreeNode<int> *root)
{
    int ans = 0;
    if (root == NULL)
    {
        return 0;
    }
    ans++;
    ans += max(height(root->left), height(root->right));
    return ans;
}

void mirrorTree(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->left != NULL)
    {
        if (root->right != NULL)
        {
            swap(root->left->data, root->right->data);
        }
        else
        {
            swap(root->left, root->right);
        }
    }
    else
    {
        if (root->right != NULL)
        {
            swap(root->left->data, root->right->data);
        }
    }
    mirrorTree(root->left);
    mirrorTree(root->right);
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

void postOrder(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

void inOrder(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return;
    }
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

BinaryTreeNode<int> *treeBuilderHelper(int pre[], int in[], int preS, int preE, int inS, int inE)
{
    if (preS > preE || inS > inE)
    {
        return NULL;
    }
    int rootData = pre[preS];
    BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootData);
    int i = inS, cntNode = 0;
    while (pre[preS] != in[i])
    {
        i++;
        cntNode++;
    }
    int preLS = preS + 1;
    int preLE = preS + cntNode;
    int preRS = preLE + 1;
    int preRE = preE;
    int inLS = inS;
    int inLE = i - 1;
    int inRS = i + 1;
    int inRE = inE;
    root->left = treeBuilderHelper(pre, in, preLS, preLE, inLS, inLE);
    root->right = treeBuilderHelper(pre, in, preRS, preRE, inRS, inRE);
    return root;
}

BinaryTreeNode<int> *treeBuilder(int pre[], int in[], int size)
{
    return treeBuilderHelper(pre, in, 0, size - 1, 0, size - 1);
}

int diameterOfTree(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int ans = height(root->left) + height(root->right);
    ans = max(ans, diameterOfTree(root->left));
    ans = max(ans, diameterOfTree(root->right));
    return ans;
}

pair<int, int> heightDiameter(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return {0, 0};
    }
    pair<int, int> lft = heightDiameter(root->left);
    pair<int, int> rt = heightDiameter(root->right);
    int lh = lft.first;
    int ld = lft.second;
    int rh = rt.first;
    int rd = rt.second;
    int height = 1 + max(lh, rh);
    int diameter = max(lh + rh, max(ld, rd));
    return {height, diameter};
}

pair<int, int> minMax(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return {INT16_MAX, INT16_MIN};
    }
    pair<int, int> lft = minMax(root->left);
    pair<int, int> rt = minMax(root->right);
    return {min(min(root->data, lft.first), rt.first), max(max(root->data, rt.second), rt.second)};
}

bool isBalanced(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return true;
    }
    int lh = height(root->left);
    int rh = height(root->right);
    bool temp = (max(lh, rh) - min(lh, rh) <= 1);
    temp = temp and isBalanced(root->left);
    temp = temp and isBalanced(root->right);
    return temp;
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

BinaryTreeNode<int> *leafNodeRemoval(BinaryTreeNode<int> *root)
{
    if (root->left == NULL and root->right == NULL)
    {
        return NULL;
    }
    if (root->left != NULL)
    {
        root->left = leafNodeRemoval(root->left);
    }
    if (root->right != NULL)
    {
        root->right = leafNodeRemoval(root->right);
    }
    return root;
}

void leveleWiseLl(BinaryTreeNode<int> *root, list<BinaryTreeNode<int> *> arr[], int sz)
{
    if (root == NULL)
    {
        return;
    }
    queue<BinaryTreeNode<int> *> qu;
    qu.push(root);
    qu.push(NULL);
    int i = 0;
    while (!qu.empty())
    {
        BinaryTreeNode<int> *front = qu.front();
        qu.pop();
        if (front != NULL)
        {
            arr[i].push_back(front);
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
            i++;
            qu.push(NULL);
        }
    }
}

// BUG HERE ---
//            |
//            V

/*
void levelOrderZigZagPrint(BinaryTreeNode<int> *root)
{
    if (root == NULL)
    {
        return;
    }
    stack<BinaryTreeNode<int> *> *MS = new stack<BinaryTreeNode<int> *>();
    stack<BinaryTreeNode<int> *> *CS = new stack<BinaryTreeNode<int> *>();
    int level = 1;
    MS->push(root);
    while (!MS->empty())
    {
        BinaryTreeNode<int> *strt = MS->top();
        cout << strt->data << " ";
        if (level % 2)
        {
            if (strt->left != NULL)
            {
                CS->push(root->left);
            }
            if (strt->right != NULL)
            {
                CS->push(root->right);
            }
        }
        else
        {
            if (strt->right != NULL)
            {
                CS->push(root->right);
            }
            if (strt->left != NULL)
            {
                CS->push(root->left);
            }
        }
        MS->pop();
        if (MS->empty())
        {
            *MS = *CS;
            CS = new stack<BinaryTreeNode<int> * >();
            cout << endl;
            level++;
        }
    }
}

*/

//             ^
//             |
// BUG ABOVE ---


int main()
{
    BinaryTreeNode<int> *root = takeInput();
    // 1 2 3 4 5 6 7 -1 -1 -1 -1 8 9 -1 -1 -1 -1 -1 -1
    // 1 2 3 4 5 6 7 -1 -1 -1 -1 8 9 -1 -1 -1 -1 10 -1 -1 -1
    // int pre[] = {1, 2, 4, 5, 3, 6, 8, 9, 7};
    // int in[] = {4, 2, 5, 1, 8, 6, 9, 3, 7};
    // BinaryTreeNode<int> *root = treeBuilder(pre, in, 9);
    // system("cls");
    // printLevelWise(root);

    // levelOrderZigZagPrint(root);               // BUG :(

    // levelOrderPrint(root);
    // cout << endl;
    // cout << endl;
    // root = leafNodeRemoval(root);
    // levelOrderPrint(root);
    // int sz = height(root);
    // list<BinaryTreeNode<int> *> arr[sz];
    // leveleWiseLl(root, arr, sz);
    // cout << endl;
    // cout << endl;
    // for (int i = 0; i < sz; i++)
    // {
    //     for (auto it : arr[i])
    //     {
    //         cout << it->data << " ";
    //     }
    //     cout << endl;
    // }
    // printLevelWise(root);
    // cout<<isBalanced(root);
    // cout << cntNodes(root);
    // cout << endl;
    // cout<<diameterOfTree(root);
    // pair<int, int> reciver = heightDiameter(root);
    // cout<<"Height: "<<reciver.first<<endl;
    // cout<<"Diameter: "<<reciver.second<<endl;
    // pair<int, int> reciver = minMax(root);
    // cout<<"MIN: "<<reciver.first<<endl;
    // cout<<"MAX: "<<reciver.second<<endl;
    // int x;;
    // cin >> x;
    // if (isThere(root, x))
    //     cout << "true\n";
    // else
    //     cout << "false\n";
    // cout << height(root);
    // mirrorTree(root);
    // cout<<"PRE: ";
    // preOrder(root);
    // cout<<endl;
    // cout<<"POST: ";
    // postOrder(root);
    // cout<<endl;
    // cout<<"IN: ";
    // inOrder(root);
    // cout<<endl;
    
    delete root;
    return 0;
}