#include<iostream>
#include "binaryTreeNode.h"
#include <iostream>
using namespace std;

class BST
{
private:
    BinaryTreeNode<int> *root;

public:
    BST();
    ~BST();
    bool hasData(int) const;
    void insert(int);
    void insertAVLly(int);
    void deleteData(int);
    BinaryTreeNode<int> * getRoot(){
        return root;
    }
private:
    bool hasData(int, BinaryTreeNode<int> *) const;
    BinaryTreeNode<int> *insert(int, BinaryTreeNode<int> *);
    BinaryTreeNode<int> *insert(BinaryTreeNode<int> *, BinaryTreeNode<int> *);
    BinaryTreeNode<int> *deleteData(int, BinaryTreeNode<int> *);
    int minElement(BinaryTreeNode<int> *node){
        int mn = INT32_MAX;
        if(node == NULL){
            return mn;
        }
        mn = min(node->data, min(minElement(node->left), minElement(node->right)));
        return mn;
    }
    int maxElement(BinaryTreeNode<int> *node){
        int mx = INT32_MIN;
        if(node == NULL){
            return mx;
        }
        mx = max(node->data, max(maxElement(node->left), maxElement(node->right)));
        return mx;
    }
    int height(BinaryTreeNode<int> *node){
        if(node == NULL){
            return 0;
        }
        return 1 +  max(height(node->left), height(node->right));
    }
    BinaryTreeNode<int> *rightRotate(BinaryTreeNode<int> *r){
         BinaryTreeNode<int> *temp = r;
         r = r->left;
         temp->left = r->right;
         r->right = temp;
         return r;
    }
    BinaryTreeNode<int> *leftRotate(BinaryTreeNode<int> *r){
         BinaryTreeNode<int> *temp = r;
         r = r->right;
         temp->right = r->left;
         r->left = temp;
         return r;
    }
};

BST::BST()
{
    root = NULL;
}

BST::~BST()
{
    delete root;
}

bool BST::hasData(int data) const
{
    return hasData(data, root);
}

bool BST::hasData(int data, BinaryTreeNode<int> *node) const
{
    if  (node == NULL)
    {
        return false;
    }
    if  (node->data == data)
    {
        return true;
    }
    bool chk;
    if (data < node->data)
    {
        chk = hasData(data, node->left);
    }
    else
    {
        chk = hasData(data, node->right);
    }
    return chk;
}

void BST::insert(int data){
    root = insert(data, root);
}

void BST::insertAVLly(int data){
    BinaryTreeNode<int> * node = new BinaryTreeNode<int>(data);
    root = insert(node, root);
}

BinaryTreeNode<int> *BST::insert(int data, BinaryTreeNode<int> *node){
     if(node == NULL){
         node = new BinaryTreeNode<int>(data);
         return node;
     }
     if(data < node->data){
        node->left =  insert(data, node->left);
     }else{
        node->right = insert(data, node->right);
     }
     return node;
}

BinaryTreeNode<int> *BST::insert(BinaryTreeNode<int> *node, BinaryTreeNode<int> *r){
     if(r == NULL){
         r = node;
         return r;
     }
     if(node->data < r->data){
         r->left = insert(node, r->left);
     }else if(node->data > r->data){
         r->right = insert(node, r->right);
     }
     int bf = height(r->left) - height(r->right);
     if(bf>1){
       if(r->left->data > node->data){
           r = rightRotate(r);
       }else{
          r->left = leftRotate(r->left);
          r = rightRotate(r);
       }
     }else if(bf < -1){
       if(r->right->data < node->data){
           r = leftRotate(r);
       }else{
          r->right = rightRotate(r->right);
          r = leftRotate(r);
       }
     }
     return r;
}

void BST:: deleteData(int data){
     deleteData(data, root);
} 

BinaryTreeNode<int> * BST::deleteData(int data, BinaryTreeNode<int> *node){
    if(node == NULL){
        return NULL;
    }
    if(data < node->data){
       node->left = deleteData(data, node->left);
    }else if(data > node->data){
       node->right = deleteData(data, node->right);
    }else{
       if(node->left == NULL and node->right == NULL){
           delete node;
           return NULL;
       }
       if(node->left == NULL){
           return node->right;
       }else{
           if(node->right == NULL){
               return node->left;
           }else{
              int replace = minElement(node->right);
              data = replace;
              node->data = replace;
              deleteData(data, node->right);
           }
       }
    }
    return node;
}
