#include "Node.h"

#define MAX(a, b) (a > b)?a:b;

/* CONSTRUCTORS */

Node::Node() {}
Node::Node(int data) {
    this->data = data;
}
Node::Node(int data, Node * parent) {
    this->data = data; // not sure which data this will refer to...
    this->parent = parent;
}

/* - - - - - - - - */

/* DESTRUCTORS */

Node::~Node(){
    delete left;
    delete right;
}

/* - - - - - - - - */

/* ACCESSORS */

int Node::getData() const {
    return this->data;
}

Node *Node::getLeftChild() const {
    return this->left;
}
Node *Node::getRightChild() const {
    return this->right;
}

Node *& Node::getLeft() {
    return this->left;
}
Node *& Node::getRight() {
    return this->right;
}
Node *& Node::getParent() {
    return this->parent;
}

/* - - - - - - - - */

/* MUTATORS */

void Node::setData(int data) {
    this->data = data;
}

/* - - - - - - - - */

/* OTHER */

bool Node::isEmpty() const { return this == NULL; }



void Node::loseChildren() {
    left = NULL;
    right = NULL;
}

/* - - - - - - - - */

/* HEIGHT STUFF */

int Node::getHeight() {
    this->updateHeight();
    return this->height;
}

void Node::updateHeight() {
    this->height = 0;
    updateHeight(this->height, 1);
}
void Node::updateHeight(int& height, int depth) {
    if(depth > height){
        height = depth;
        
    }
    if(this->left != NULL){
        this->left->updateHeight(height, depth+1);

    }
    if(this->right != NULL){

        this->right->updateHeight(height, depth+1);

    }
}
/* - - - - - - - - */