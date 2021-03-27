#include "AVL.h"

#define NULLTEST(a) (a==NULL)?NULL:a;

AVL::AVL(){}
AVL::~AVL(){
    delete root;
}

Node *  AVL::getRootNode() const { return root; }
Node *& AVL::getRoot    ()       { return root; }
void AVL:: setRoot(Node * new_root)    { root = new_root; }


bool AVL::add(int data) {
    bool result = add(data, root);
    if(result){
        std::cout << "SUCCESSFULLY ADDED NODE" << std::endl;
    }
    rebalance(this->getRoot());
    return result;
}
bool AVL::add(int data, Node *& subroot){
    // this->getRoot()->setHeight(0);

    if(subroot->isEmpty()){
        subroot = new Node(data);
        return true;
    }

    if(data == subroot->getData()) {
        return false;
    }

    bool result;

    if(data < subroot->getData()) {
        result = add(data, subroot->getLeft());
        // return add(data, subroot->getLeft());
    } else {
        result = add(data, subroot->getRight());
        // return add(data, subroot->getRight());
    }
    if(result /*&& subroot != this->getRootNode()*/){
        subroot->updateHeight();
        rebalance(subroot);
        // std::cout << "poopoopeepee" << std::endl;

    }


    
    // int balanceFactor = subroot->getRight()->getHeight() - subroot->getLeft()->getHeight();
    return result;
}

bool AVL::remove(int data) {

    if(this->getRoot()->getData() == data && this->getRoot()->getLeft()->isEmpty() && this->getRoot()->getRight()->isEmpty()){
        this->clear();
        return true;
    }else{
        bool result = remove(data, root);
        rebalance(this->getRoot());
        return result;
    }
}
bool AVL::remove(int data, Node *& subroot) {
    std::cout << "- - - REMOVING NODE WITH DATA: " << data << std::endl;
    if(subroot->isEmpty()){
        return false;
    }


    // std:cout << "currently looking at node with data: " << subroot->getData() << std::endl;
    bool result;

    if(data < subroot->getData()) {
        
        result = remove(data, subroot->getLeft());

        // return remove(data, subroot->getLeft());
    } else if(subroot->getData() < data) {

        result = remove(data, subroot->getRight());

        // return remove(data, subroot->getRight());
    } else {
        
        // s< "does it have empty children?" << std::endl;
        if (subroot->getLeft()->isEmpty()) {
            
            // std::cut << "\tnow replacing this node with node @" << subroot->getRight() << std::endl;
            Node * tmp = subroot;
            subroot = subroot->getRight();
            tmp->loseChildren();
            delete tmp;


            // std::cut << "sucess!" << std::endl;
        } else if(subroot->getRight()->isEmpty()) {

            Node * tmp = subroot;
            subroot = subroot->getLeft();
            tmp->loseChildren();
            delete tmp;


        } else {

            // std: * oldroot = subroot;

            replaceParent(subroot, subroot->getLeft());

            // ollete oldroot;


        }

        // return true;
        result = true;
    }

    if(result && !subroot->isEmpty()){
        subroot->updateHeight();
        rebalance(subroot);
    }

    return result;
}

void AVL::replaceParent(Node *& oldRoot, Node *& localRoot) {
    // find thmove on the left subtree of oldRoot to delete the local root node.
    if(!localRoot->getRight()->isEmpty()){
        replaceParent(oldRoot, localRoot->getRight());
    } else {
        oldRoot->setData(localRoot->getData());
        remove(localRoot->getData(), oldRoot->getLeft());

        // delete localRoot;
    }
}



void AVL::clear() {
    delete root;
    root = NULL;
}

void AVL::traverse() {
    traverse(root);
}

void AVL::traverse(Node *& subroot) {
    
    if(!subroot->isEmpty()){
        // std::cout << "left-";
        traverse(subroot->getLeft());
        std::cout << subroot->getData() << ", height: " << subroot->getHeight() << std::endl;
        if(subroot->getLeft() != NULL) {
            std::cout << "\tleft: " << subroot->getLeft()->getData();
        }else{
            std::cout << "\tleft: NULL";
        }
        if(subroot->getRight() != NULL){
            std::cout << ", right: " << subroot->getRight()->getData() << std::endl;
        }else{
            std::cout << ", right: NULL" << std::endl;
        }
        traverse(subroot->getRight());
    }
}

void AVL::breadthTraverse(){
    for(int i = this->getRoot()->getHeight(); i > 0; i--){
        std::cout << "row " << this->getRoot()->getHeight()+1 - i << ": " << std::flush;
        breadthTraverse(this->getRoot(), i);
        std::cout << std::endl;
    }
}
void AVL::breadthTraverse(Node *& subroot, int b){
    if(!subroot->isEmpty()){
        if(!subroot->isEmpty()){
            // std::cout << "left-";
            breadthTraverse(subroot->getLeft(), b);
            if(b == subroot->getHeight()){
                std::cout << subroot->getData() << " ";
            }
            breadthTraverse(subroot->getRight(), b);
        }
    }
}

/* REBALANCING */

// bool AVL::rebalance(){
//     std::cout << "##### tree status pre-rotation: #####" << std::endl;
//     this->traverse();
//     // test left tree for rebalance

//     if(this->getRootNode()->getLeft() != NULL){
//         std::cout << "testing left tree of root (" << this->getRoot()->getData() << ") for balance: " << std::endl;
//         rebalance(this->getRoot()->getLeft());
//     }

//     // test right tree for rebalance

//     if(this->getRootNode()->getRight() != NULL){
//         std::cout << "testing right tree of root (" << this->getRoot()->getData() << ") for balance: " << std::endl;
//         rebalance(this->getRoot()->getRight());

//     }
//     // test root for rebalance

//     std::cout << "testing root (" << this->getRoot()->getData() << ") for balance: " << std::endl;
//     int balance = BF(this->getRoot());
//     std::cout << "\tbf: " << balance << std::endl;
//     switch(balance){
//         case 2: {
//             // Node *& root = this->getRoot();
            
//             if(!this->getRoot()->getRight()->isEmpty() && BF(this->getRoot()->getRight()) < 0){
//                 // right child is left-heavy: Right Left Tree
//                 this->getRoot()->getRight() = rotateRight(this->getRoot()->getRight());
//             }

//             this->setRoot(rotateLeft(this->getRoot()));

//         }   break;
//         case -2: {
//             if(!this->getRoot()->getLeft()->isEmpty() && BF(this->getRoot()->getLeft()) > 0){
//                 // left child is right heavy right-heavy: Left Right Tree
//                 this->getRoot()->getLeft() = rotateLeft(this->getRoot()->getLeft());
//             }
//             // Node *& root = this->getRoot();
//             this->setRoot(rotateRight(this->getRoot()));
            
//         }   break;
//         default:
//             break;
//     }
//     this->getRoot()->updateHeight();
//     //      this will include tests for LL, LR, RR, & RL trees

//     std::cout << "post-rotation: " << std::endl;
//     this->traverse();

//     return true;
// }



// bool AVL::rebalance(Node *& old_root){ // returns new_root
//     int bf = BF(old_root);
//     std::cout << "\tdata: " << old_root->getData() << std::endl;
//     std::cout << "\tbf: " << bf << std::endl;
//     switch(bf){
//         case 2:
//             // rotate_left
//             std::cout << "rebalancing " << old_root->getData() << " with left-rotation" << std::endl;
//             old_root = rotateLeft(old_root);
//             break;
//         case -2:
//             // rotate_right
//             std::cout << "rebalancing " << old_root->getData() << " with right-rotation" << std::endl;
//             old_root = rotateRight(old_root);
//             break;
//         default:
//             // jack squat
//             break;
//     }
//     old_root->updateHeight();

//     return true;
// }


Node * AVL::rotateLeft(Node *& old_root){ // returns new_root
    std::cout << "reached rotateLeft(" << old_root->getData() << ")" << std::endl;

    // Node * tmp = old_root;

    Node * new_root = old_root->getRight();

    old_root->getRight() = new_root->getLeft();
    new_root->getLeft() = old_root;

    new_root->updateHeight();
    old_root->updateHeight();

    return new_root;
}
Node * AVL::rotateRight(Node *& old_root){
    std::cout << "reached rotateRight(" << old_root->getData() << ")" << std::endl;

    // Node * tmp = old_root;
    Node * new_root = old_root->getLeft();

    old_root->getLeft() = new_root->getRight();
    new_root->getRight() = old_root;

    new_root->updateHeight();
    old_root->updateHeight();

    return new_root;
}

int AVL::BF(Node *& subroot){
    int height_r = 0, height_l = 0;
    if(!subroot->getRight()->isEmpty()){
        height_r = subroot->getRight()->getHeight();
    }
    if(!subroot->getLeft()->isEmpty()){
        height_l = subroot->getLeft()->getHeight();
    }

    std::cout << "\t### BF calculation for node (" << subroot->getData() << ") ###" << std::endl;
    std::cout << "\t" << height_r << " - " << height_l << std::endl;
    return height_r - height_l;
    // rebalance(subroot, height_r - height_l);
}




















bool AVL::rebalance(Node *& subroot){
    std::cout << "##### tree status pre-rotation: #####" << std::endl;
    // this->traverse();
    // // test left tree for rebalance

    // if(subroot->getLeft() != NULL){
    //     std::cout << "testing left tree of root (" << subroot->getData() << ") for balance: " << std::endl;
    //     rebalance(subroot->getLeft());
    // }

    // // test right tree for rebalance

    // if(subroot->getRight() != NULL){
    //     std::cout << "testing right tree of root (" << subroot->getData() << ") for balance: " << std::endl;
    //     rebalance(subroot->getRight());

    // }
    // // test root for rebalance

    std::cout << "testing root (" << subroot->getData() << ") for balance: " << std::endl;
    int balance = BF(subroot);
    std::cout << "\tbf: " << balance << std::endl;
    switch(balance){
        case 2: {
            // Node *& root = this->getRoot();
            
            if(!subroot->getRight()->isEmpty() && BF(subroot->getRight()) < 0){
                // right child is left-heavy: Right Left Tree
                subroot->getRight() = rotateRight(subroot->getRight());
            }

            if(this->getRoot() == subroot){
                this->setRoot(rotateLeft(subroot));
            }else{
                subroot = rotateLeft(subroot);
            }

        }   break;
        case -2: {
            if(!subroot->getLeft()->isEmpty() && BF(subroot->getLeft()) > 0){
                // left child is right heavy right-heavy: Left Right Tree
                subroot->getLeft() = rotateLeft(subroot->getLeft());
            }
            // Node *& root = this->getRoot();
            if(this->getRoot() == subroot){
                this->setRoot(rotateRight(subroot));
            }else{
                subroot = rotateRight(subroot);
            }
            
        }   break;
        default:
            break;
    }
    subroot->updateHeight();
    //      this will include tests for LL, LR, RR, & RL trees

    std::cout << "post-rotation: " << std::endl;
    // this->traverse();

    return true;
}