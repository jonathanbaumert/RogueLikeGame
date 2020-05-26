#ifndef BST_H
# define BST_H

# include <iostream>

using namespace std;

template <class T>
class bst {
 private:
  class bst_node {
  public:
    T data;
    bst_node *left, *right;
    bst_node(T d) : data(d), left(0), right(0) {}
    ~bst_node()
    {
      if (left) {
        delete left;
      }
      if (right) {
        delete right;
      }
    }
    void print_in_order(ostream &o)
    {
      if (left) {
        left->print_in_order(o);
      }
      o << data << " ";
      if (right) {
        right->print_in_order(o);
      }
    }
    void print_pre_order(ostream &o)
    {
      o << data << " ";
      if (left) {
        left->print_pre_order(o);
      }
      if (right) {
        right->print_pre_order(o);
      }
    }
    void print_post_order(ostream &o)
    {
      if (left) {
        left->print_post_order(o);
      }
      if (right) {
        right->print_post_order(o);
      }
      o << data << " ";
    }
  };

  bst_node *root;
  int thesize;

 public:
  bst() : root(NULL), thesize(0) {}
  ~bst()
  {
    if (root) {
      delete root;
    }
  }

  T min() throw (int)
  {
    bst_node *n;
   
    if (!root) {
      throw "Tree is empty!";
    }
 
    for (n = root; n->left; n = n->left)
      ;

    return n->data;
  }

  void insert(T d)
  {
    bst_node *n;
    bool inserted = false;

    if (!root) {
      root = new bst_node(d);
    } else {
      n = root;
      while(!inserted) {
        if (d > n->data) {
          //Go right
          if (!n->right) {
            n->right = new bst_node(d);
            inserted = true;
          } else {
            n = n->right;
          }
        } else {
          //Go left
          if (!n->left) {
            n->left = new bst_node(d);
            inserted = true;
          } else {
            n = n->left;
          }
        }
      }
    }
    thesize++;
  }
  bool find(T d)
  {
    bst_node *n = root;

    while (n) {
      if (n->data == d) {
        return true;
      }
      if (d > n->data) {
        n = n->right;
      } else {
        n = n->left;
      }
    }
    return false;
  }
  void print_in_order(ostream &o)
  {
    if (root) {
      root->print_in_order(o);
    }
  }
  void print_pre_order(ostream &o)
  {
    if (root) {
      root->print_pre_order(o);
    }
  }
  void print_post_order(ostream &o)
  {
    if (root) {
      root->print_post_order(o);
    }
  }
  int size()
  {
    return thesize;
  }

  bool operator>(bst<T> b) {
    return true;
  }

};

#endif
