// Code for Huffman tree
#include <iostream>
#include <string>
#include "huffdec.h"

using namespace std;

void Decode::leafadd(int va, string bina) {
    Node *t;
    t = root;
    for (int i = 0; i < bina.length(); i++) {
        if (bina.at(i) == '0') {
            if (t->left == NULL) {
                Node* newNode = new (struct Node);
                t->left = newNode;
            }
            t = t->left;
        }
        else if (bina.at(i) == '1') {
            if (t->right == NULL) {
                Node* newNode = new (struct Node);
                t->right = newNode;
            }
            t = t->right;
        }
    }
    t->va = va;
    t->isLeaf = true;
}
Node* Decode::rootget() {
    return root;
}




