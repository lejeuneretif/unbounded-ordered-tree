#ifndef UNBOUNDED_ORDERED_NODE_INSERT_SUBTREE_TPP
#define UNBOUNDED_ORDERED_NODE_INSERT_SUBTREE_TPP

#include <exception>
#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"

namespace unbounded_ordered {
  class node_is_root : public std::exception {
    const char* what() const throw() {
      return "Root node cannot have sibling.";
    }
  };

  class node_is_null : public std::exception {
    const char* what() const throw() {
      return "Node is null.";
    }
  };

  // The caller should make sure that node is detached
  template <typename T>
  void node<T>::insert_previous_sibling(node<T>* n) {
    if(! n) throw node_is_null();

    if(!_parent) throw node_is_root();

    n->_parent = _parent;

    if(_previous_sibling) {
      _previous_sibling->_next_sibling = n;
    }

    n->_previous_sibling = _previous_sibling;
    n->_next_sibling = this;

    _previous_sibling = n;

    if(_parent->_first_child == this) {
      // Parent's first child changed
      _parent->_first_child = n;
    }
  }

  // The caller should make sure that n is detached
  template <typename T>
  void node<T>::insert_next_sibling(node<T>* n) {
    if(! n) throw node_is_null();

    if(!_parent) throw node_is_root();

    n->_parent = _parent;

    if(_next_sibling) {
      _next_sibling->_previous_sibling = n;
    }

    n->_next_sibling = _next_sibling;

    n->_previous_sibling = this;
    _next_sibling = n;

    if(_parent->_last_child == this) {
      // Parent's last child changed
      _parent->_last_child = n;
    }
  }

  // The caller should make sure that n is detached
  template <typename T>
  void node<T>::insert_first_child(node<T>* n) {
    if(! n) throw node_is_null();

    n->_parent = this;

    if(_first_child) {
      _first_child->_previous_sibling = n;
    }

    n->_next_sibling = _first_child;

    _first_child = n;

    if(!_last_child) {
      // Now, there is a last child
      _last_child = n;
    }
  }

  // The caller should make sure that n is detached
  template <typename T>
  void node<T>::insert_last_child(node<T>* n) {
    if(! n) throw node_is_null();
    
    n->_parent = this;

    if(_last_child) {
      _last_child->_next_sibling = n;
    }

    n->_previous_sibling = _last_child;

    _last_child = n;

    if(!_first_child) {
      // Now there is a first child
      _first_child = n;
    }
  }
}

#endif // UNBOUNDED_ORDERED_NODE_INSERT_SUBTREE_TPP