#include <iostream>
#include <string>
#include "AVLTree.h"
#include <iomanip>
#include <queue>
using namespace std;

AVLTree::AVLTree(){
    root = nullptr;
}

AVLTree::~AVLTree(){
    
    
}

AVLNode* AVLTree::getRoot(){
    return root;
}


// search value ss in the AVL tree
bool AVLTree::find(string ss){
    if (root == nullptr) {
        return false;
    }
    
    AVLNode* node = root;
    
    while (node != nullptr) {
        if (ss.compare(node->ssn) == 0) {
            return true;
        }
        if (ss.compare(node->ssn) < 0) {
            node = node->left;
        }
        else{
            node = node->right;
        }
    }
    return false;
}

// return the height of the subtree rooted at node
// if subtree is empty, height is -1
// if subtree has one node, height is 0
int AVLTree::height(AVLNode* node){
    
    if(node != nullptr){
        return node->height;
    }
    else{
        return -1;
    }
}

// return the balance factor of the node
int AVLTree::balanceFactor(AVLNode* node){
    return height(node->left) - height(node->right);
}

// update the height of the node
// this should be done whenever the tree is modified
void AVLTree::updateHeight(AVLNode* node){
    int hl = height(node->left);
    int hr = height(node->right);
    node->height = (hl>hr ? hl : hr) + 1;
}


// rotate right the subtree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::rotateRight(AVLNode* node){
    AVLNode* lp = node->left;      // left child of node
    if (node->parent!=nullptr) {  // node is not root
        if (node->parent->left == node) { // node is a left child
            node->parent->left = lp;
        }else{
            node->parent->right = lp;     // node is a right child
        }
    }
    
    if (lp->right != nullptr) {           // pointer update
        lp->right->parent = node;
    }
    
    lp->parent = node->parent;
    node->left = lp->right;
    lp->right = node;
    node->parent = lp;
    updateHeight(node);                   // after rotation, update height
    updateHeight(lp);                     // after rotation, update height
    if (node == root) {
        root = lp;
    }
    return lp; // lp is the new root of the subtree
}


// rotate left the subtree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::rotateLeft(AVLNode* node){
    AVLNode* rp = node->right;
    if (node->parent!=nullptr) {
        if (node->parent->left == node) {
            node->parent->left = rp;
        }else{
            node->parent->right = rp;
        }
    }
    
    if (rp->left != nullptr) {
        rp->left->parent = node;
    }
    
    rp->parent = node->parent;
    
    node->right = rp->left;
    rp->left = node;
    node->parent = rp;
    node->parent = rp;
    updateHeight(node);
    updateHeight(rp);
    if (node == root) {
        root = rp;
    }
    return rp;
}


// rebalance a tree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::balance(AVLNode* node){
    updateHeight(node);
    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left); // for left right case
        }
        AVLNode* temp = rotateRight(node);
        updateHeight(temp);
        return temp;
    }
    
    if (balanceFactor(node) == -2) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);  // for right left case
        }
        AVLNode* temp2 = rotateLeft(node);
        updateHeight(temp2);
        return temp2;
    }
    return node;
}

// insert a new node with (ss, na) to the AVL tree
// if there exists ss value, return false
// otherwise, insert it, balance the tree, return true
/*use while loop to update height of all nodes except the leaves, may have to include other balance cases like rotate right one and rotate left one (100% correct)*/
bool AVLTree::insert(string ss, string na){
    if(find(ss) == true){
        return false;
    }
    else{
        AVLNode * newnode = new AVLNode(ss, na);
        if(root == nullptr){
            root = newnode;
            newnode->parent = nullptr;
            return true;
        }
        else{
            AVLNode * current = root;
            while(current != nullptr){
                if(ss < current->ssn){
                    if(current->left == nullptr){
                        current->left = newnode;
                        newnode->parent = current;
                        current = nullptr;
                    }
                    else{
                        current = current->left;
                    }}
                else{
                    if(current->right == nullptr){
                        current->right = newnode;
                        newnode->parent = current;
                        current = nullptr;
                    }
                    else{
                        current = current->right;
                    }}}
                AVLNode * parental = root;
                if(parental->ssn == newnode->ssn){
                }
                else{
                    if(parental != nullptr){
                    while(parental->left != newnode && parental->right != newnode){
                        if(newnode->ssn < parental->ssn){
                            parental = parental->left;}
                        else{
                            parental = parental->right;}
                    }
                    }
                }
                newnode = parental;
                while(newnode != nullptr){
                    balance(newnode);
                    parental = root;
                    if(parental->ssn == newnode->ssn){
                        return true;
                    }
                    else{
                        if(parental != nullptr){
                        while(parental->left != newnode && parental->right != newnode){
                            if(newnode->ssn < parental->ssn){
                                if(parental->left == nullptr){
                                    break;       //if bad take out
                                }
                                parental = parental->left;
                            }
                            else{
                                if(parental->right == nullptr){
                                    break;       //if bad take out
                                }
                                parental = parental->right;}
                        }
                        }
                    }
                    newnode = parental;
                }
            }
        }
    
    return true;
}

AVLNode* AVLTree::maxOfSubtree(AVLNode* node){
    if (node == nullptr) {
        return nullptr;
    }
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

// delete the node containing value ss
// if there is not such node, return false
// otherwise, delete the node, balance the tree, return true
 /* include area where the node gets reattached to part of a tree node, this function currently just deletes a node rather than fixing the area where it was deleted then balancing it */
//put if not nullptrs around the while loop in parental function include for deletion as well
bool AVLTree::deleteNode(string ss){
    if(root == nullptr){
        return false;
    }
    if(find(ss) == false){
       // cout << "not found" << endl;
        return false;
    }
    else{
    AVLNode * current = root;
        while(current->ssn != ss){
            if(ss < current->ssn){
                current = current->left;        //this code puts current as the node to be deleted
        }
            if(ss > current->ssn){
                current = current->right;
        }
    }
        if(current->left == nullptr && current->right == nullptr){      //if it is a leaf being deleted
           // cout << "leaf" << endl;
            AVLNode * parental = root;
            if(parental->ssn == current->ssn){
               }
            else{
                while(parental->left != current && parental->right != current){
                    if(current->ssn < parental->ssn){
                        parental = parental->left;}
                    else{
                        parental = parental->right;}
                }
                
            }
            if(parental->left == current){
                parental->left = nullptr;
            }
            else{
                parental->right = nullptr;
            }
             //rebalancing time
            current = parental;
            while(current != nullptr){
                balance(current);
                parental = root;
                if(parental->ssn == current->ssn){
                    parental = nullptr;}
                else{
                    while(parental->left != current && parental->right != current){
                        if(current->ssn < parental->ssn){
                            if(parental->left == nullptr){
                                break;       //if bad take out
                            }
                            parental = parental->left;}
                        else{
                            if(parental->right == nullptr){
                                break;       //if bad take out
                            }
                            parental = parental->right;}
                    }
                    
                }
                current = parental;
            }
            return true;
        }
    if((current->left == nullptr && current->right != nullptr) || (current->left != nullptr && current->right == nullptr)){
        AVLNode * parental = root;    //if there is only one child
       // cout << "one child" << endl;
        if(parental->ssn == current->ssn){
            }
        else{
            while(parental->left != current && parental->right != current){
                if(current->ssn < parental->ssn){
                    parental = parental->left;}
                else{
                    parental = parental->right;}
            }
            
        }
        if(current->left != nullptr){
            current->ssn = current->left->ssn;
            current->left = nullptr;
        }
        else{
            current->ssn = current->right->ssn;
            current->right = nullptr;
        }
        // rebalancing time
        current = parental;
        
        while(current != nullptr){
            balance(current);
            parental = root;
            if(parental->ssn == current->ssn){
                parental = nullptr;}
            else{
                while(parental->left != current && parental->right != current){
                    if(current->ssn < parental->ssn){
                        if(parental->left == nullptr){
                            break;       //if bad take out
                        }
                        parental = parental->left;}
                    else{
                        if(parental->right == nullptr){
                            break;       //if bad take out
                        }
                        parental = parental->right;}
                }
                
            }
            current = parental;
        }
        return true;
        }
        
        if(current->right != nullptr && current->left != nullptr){   //if there are two children
          //  cout << "two kids" << endl;
            AVLNode * succnode = current->right;
            while(succnode->left!=nullptr){
                succnode = succnode->left;
            }
            current->ssn = succnode->ssn;
            succnode = nullptr;
            return true;
            
        }
    return true;
    
}
}

// internal function
// do not call it directly
void AVLTree::print(AVLNode* x, int indent){
    if(x == nullptr) return;
    if (x->right != nullptr) {
        print(x->right, indent+4);
    }
    
    if (indent != 0) {
        cout << std::setw(indent) << ' ';
    }
    
    if(x->right != nullptr){
        cout << " /\n" << std::setw(indent) << ' ';
    }
    
    cout << x->ssn << endl;
    
    if (x->left != nullptr) {
        cout << std::setw(indent) << ' ' <<" \\\n";
        print(x->left, indent+4);
    }
    
}

// print out the structure of the binary tree
// use it for debugging, I love this function
void AVLTree::print(){
    int count = 0;
    print(root, count);
}


// it does not level order traversal
// it prints out the number of node
// use it mainly for debugging
//works 100%
void AVLTree::levelOrder(){
    if(root == nullptr){
        return;
    }
    queue<AVLNode*> qu;
    int total = 0;
    qu.push(root);
    while(qu.size() > 0){
        AVLNode * box = qu.front();
        qu.pop();
        if(box != nullptr){
            total++;
            qu.push(box->left);
            qu.push(box->right);
            
        }
        
    }
    cout << total << endl;
}

 /*
  
  simply extra code in this comment for previous insert function
  
  bool AVLTree::insert(string ss, string na){
  if(find(ss) == true){
  return false;
  }
  else{
  AVLNode * newnode = new AVLNode(ss, na);
  if(root == nullptr){
  root = newnode;
  newnode->parent = nullptr;
  return true;
  }
  else{
  AVLNode * current = root;
  while(current != nullptr){
  if(ss < current->ssn){
  if(current->left == nullptr){
  current->left = newnode;
  newnode->parent = current
  current = nullptr;
  }
  else{
  current = current->left;
  }}
  else{
  if(current->right == nullptr){
  current->right = newnode;
  newnode->parent = current;
  current = nullptr;
  }
  else{
  current = current->right;
  }}
  AVLNode * parental = root;
  if(parental->ssn == current->ssn){
  }
  else{
  while(parental->left != current && parental->right != current){
  if(current->ssn < parental->ssn){
  parental = parental->left;}
  else{
  parental = parental->right;}
  }
  
  }
  newnode = parental;
  while(newnode != nullptr){
  balance(newnode);
  parental = root;
  if(parental->ssn == current->ssn){
  }
  else{
  while(parental->left != current && parental->right != current){
  if(current->ssn < parental->ssn){
  parental = parental->left;}
  else{
  parental = parental->right;}
  }
  
  }
  }
  return true;
  }
  
  */
 
 


