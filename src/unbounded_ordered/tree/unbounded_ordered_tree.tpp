#ifndef UNBOUNDED_ORDERED_TREE_TPP
#define UNBOUNDED_ORDERED_TREE_TPP

#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  // Default constructor
  template <typename T>
  tree<T>::tree() : _root(nullptr) {}

  template <typename T>
  tree<T>::tree(node<T>* root) : _root(root) {}

  // Creates a tree with only a root
  template <typename T>
  tree<T>::tree(const T& data) : _root(new node<T>(data)) {}

  template <typename T>
  tree<T>::tree(const T& data, const std::initializer_list<tree>& il) {
    std::list<node<T>*> children;
    for(typename std::initializer_list<tree>::const_iterator it = il.begin(); it != il.end(); ++it) {
      children.push_back(it->_root->copy_subtree());
    }

    _root = new node<T>(data, children);
  }

  // Copy constructor duplicates the whole tree `other`
  template <typename T>
  tree<T>::tree(const tree& other) : _root(node<T>::copy_subtree(other._root)) {}

  // Move constructor
  template <typename T>
  tree<T>::tree(tree&& other) : _root(other._root) { other._root = nullptr; }

  // Copy assignment
  template <typename T>
  tree<T>& tree<T>::operator=(const tree& other) {
    if(this == &other) {
      return *this;
    }

    // Copy the other tree
    node<T>* new_root = node<T>::copy_subtree(other._root);

    // Delete the tree currently rooted at _root
    _root->delete_subtree();

    // Define the new root at the current tree
    _root = new_root;

    return *this;
  }

  // Move assignment operator
  template <typename T>
  tree<T>& tree<T>::operator=(tree&& other) {
    // Delete the tree currently rooted at _root
    _root->delete_subtree();

    _root = other._root;
    other._root = nullptr;

    return *this;
  }

  // Destructor
  template <typename T>
  tree<T>::~tree() {
    if(_root) {
      _root->delete_subtree();
      _root = nullptr;
    }
  }

  // Swaps the roots of both trees
  template <typename T>
  void tree<T>::swap(tree& lhs, tree& rhs) {
    node<T>* tmp = rhs._root;
    rhs._root = lhs._root;
    lhs._root = tmp;
  }

  template <typename T>
  bool tree<T>::is_empty() const { return !_root; }

  template <typename T>
  void tree<T>::insert_first_child(const tree& new_first_child) {
    _root->insert_first_child(node<T>::copy_subtree(new_first_child._root));
  }

  // Used for testing that the trees are isomorphic
  template <typename T>
  bool tree<T>::assert_isomorphic(const tree<T>& lhs, const tree<T>& rhs) {
    std::map<const node<T>* const, const node<T>* const> m;
    std::map<const node<T>* const, const node<T>* const> m_reverse;
    return lhs._root->is_subtree_equal(rhs._root, m, m_reverse, "root");
  }

  // Used for testing the small loops and that it is a subtree
  template <typename T>
  bool tree<T>::is_consistent(const tree<T>& t) {
    return t._root->is_subtree_consistent();
  }

  template <typename T>
  std::ostream& tree<T>::print_to_stream(std::ostream& s) const {
    return _root->print_to_stream(s);
  }
}

template <typename T>
std::ostream& operator<<(std::ostream& s, const typename unbounded_ordered::tree<T>& t) {
  return t.print_to_stream(s);
}

#endif // UNBOUNDED_ORDERED_TREE_TPP