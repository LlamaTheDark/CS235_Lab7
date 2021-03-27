#ifndef AVL_H
#define AVL_H

#include "AVLInterface.h"
#include "Node.h"

using namespace std;

class AVL : public AVLInterface {
private:
    Node *root = NULL;
    
public:
	AVL();
	virtual ~AVL();

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	virtual Node * getRootNode() const;
    Node *& getRoot();
    void setRoot(Node * new_root);

	/*
	* Attempts to add the given int to the AVL tree
	* Rebalances the tree if data is successfully added
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	virtual bool add(int data);
    bool add(int data, Node *& subroot);

	/*
	* Attempts to remove the given int from the AVL tree
	* Rebalances the tree if data is successfully removed
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	virtual bool remove(int data);
    bool remove(int data, Node *& subroot);

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	virtual void clear();

    void traverse();
    void traverse(Node *& subroot);
    void breadthTraverse();
    void breadthTraverse(Node *&, int);

    int getBalanceFactor();
    int getBalanceFactor(Node * root);

    void replaceParent (Node *&, Node *&);


    /* REBALANCING */

    bool rebalance();
    bool rebalance(Node *&);
    int BF(Node *&);

    Node * rotateLeft(Node *&);
    Node * rotateRight(Node *&);

    /* - - - - - - - - */
};

#endif /* AVL_H */