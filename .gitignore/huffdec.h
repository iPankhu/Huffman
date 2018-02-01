// Code for Huffman tree
#include <iostream>
#include <string>
using namespace std;

struct Node {
    struct Node *right = NULL;
    struct Node *left = NULL;
    int va;
    bool isLeaf = false;
};

class Decode {
private:
    Node* root;
public:
    Node* rootget();
    void leafadd(int va, string bina);
    int getnow(string bina){
Node *t;
    t = root;

    for (int i = 0; i < bina.length(); i++) {
        if (t == NULL) {
            return -1;
        }
        else if (bina.at(i) == '0') {
            t = t->left;
        }
        else if (bina.at(i) == '1') {
            t = t->right;
        }
    }
    if (t->isLeaf == true) {
        return t->va;
    }
    else {
        return -1;
    }
    };

    Decode() {
        root = new (struct Node);
    }
};



