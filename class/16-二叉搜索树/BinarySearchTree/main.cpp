/*
 * FILE: CANTOR FRACTALS
 * ---------------------
 * This program draws a Cantor Fractal of a constant depth on the screen.
 * A Cantor fractal of depth N is a thick horizontal line on top, with
 * a depth N-1 Cantor fractal below the left third, and a depth N-1 Cantor
 * fractal below the right third, of the drawn line.
 */

#include <iostream>

#include "console.h"
using namespace std;

struct Node {
    string key;
    Node *left;
    Node *right;
};

// binary search
Node *findNode(Node *root, const string &key) {
    // edge case: empty link
    if (root == nullptr)
        return nullptr;
    // base case: find key
    if (key == root->key)
        return root;

    // recursive case
    if (key < root->key) {
        return findNode(root->left, key);
    } else {
        return findNode(root->right, key);
    }
}

// binary search itr
Node *findNodeItr(Node *root, const string &key) {
    while (true) {
        if (root == nullptr)
            return nullptr;
        if (key == root->key)
            return root;

        if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
}

// insert node
void insertNode(Node *&root, const string &key) {
    if (root == nullptr) {
        root = new Node{key, nullptr, nullptr};
        cout << root->key << endl;
    } else {
        // key should be unique
        if (key < root->key) {
            insertNode(root->left, key);
        } else if (key > root->key) {
            insertNode(root->right, key);
        }
    }
}

// delete tree
void deleteTree(Node *root) {
    // base case
    if (root == nullptr)
        return;
    // recursive case
    deleteTree(root->right);
    deleteTree(root->left);
    cout << root->key << endl;
    delete root;
}

// display tree
void displayTree(Node *root) {
    if (root != nullptr) {
        displayTree(root->left);
        cout << root->key << endl;
        displayTree(root->right);
    }
}

int main() {
    Node *root = nullptr;

    cout << "Insertt node: " << endl;
    insertNode(root, "Cat");
    insertNode(root, "Dog");
    insertNode(root, "Pig");
    cout << endl;

    cout << "Display tree inorder: " << endl;
    displayTree(root);
    cout << endl;

    Node *pig = findNode(root, "Pig");
    cout << "Find node: " << pig->key << endl << endl;

    cout << "Delete tree postorder: " << endl;
    deleteTree(root);

    return 0;
}
