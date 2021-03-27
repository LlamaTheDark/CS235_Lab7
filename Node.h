#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "NodeInterface.h"

class Node : public NodeInterface {
private:
    int data;
    Node * left = NULL, * right = NULL, * parent = NULL;
    int height = 1;
public:
	Node();
    Node(int);
    Node(int, Node *);
    
	virtual ~Node();

	/*
	* Returns the data that is stored in this node
	*
	* @return the data that is stored in this node.
	*/
	virtual int getData() const;

	/*
	* Returns the left child of this node or null if it doesn't have one.
	*
	* @return the left child of this node or null if it doesn't have one.
	*/
	virtual Node *getLeftChild() const;

	/*
	* Returns the right child of this node or null if it doesn't have one.
	*
	* @return the right child of this node or null if it doesn't have one.
	*/
	virtual Node *getRightChild() const;


    Node *& getLeft();
    Node *& getRight();
    Node *& getParent();

    void loseChildren();

    void setData(int data);



    bool isEmpty() const;

    int getHeight();
    void updateHeight();
    void updateHeight(int&, int);

};

#endif /* NODE_H */