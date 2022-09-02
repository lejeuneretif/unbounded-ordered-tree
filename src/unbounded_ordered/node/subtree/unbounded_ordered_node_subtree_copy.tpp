#ifndef UNBOUNDED_ORDERED_NODE_COPY_SUBTREE_TPP
#define UNBOUNDED_ORDERED_NODE_COPY_SUBTREE_TPP

#include <cstddef>
#include <list>
#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  node<T>* node<T>::copy_subtree() const {
    const node<T>* current_original = this;

    node<T>* current_copy = new node<T>(_data);

    node<T>* result = current_copy;

    bool subtree_under_current_copy_already_copied = false;

    do {
      if(! subtree_under_current_copy_already_copied && current_original->_first_child) {
        // Copy the first child of the original node.
        // The pointers created are 2 between parent and first child.
        current_original = current_original->_first_child;

        node<T>* copy_first_child = new node<T>(current_original->_data, current_copy);
        current_copy->_first_child = copy_first_child;

        current_copy = copy_first_child;
      }
      else if(current_original->_next_sibling) {
        // Copy the next sibling of the original node.
        // The pointers created are 3: child-to-parent, between siblings.
        current_original = current_original->_next_sibling;

        node<T>* copy_next_sibling = new node<T>(
          current_original->_data,
          current_copy->_parent,
          current_copy
        );
        current_copy->_next_sibling = copy_next_sibling;

        current_copy = copy_next_sibling;
        subtree_under_current_copy_already_copied = false;
      }
      else if(current_original->_parent) {
        // current_original is the last child of its parent.
        // Create the pointer to the last child.
        current_original = current_original->_parent;

        node<T>* copy_parent = current_copy->_parent;
        copy_parent->_last_child = current_copy;

        current_copy = copy_parent;
        subtree_under_current_copy_already_copied = true;
      }
    } while(current_original != this);

    return result;
  }
}

#endif // UNBOUNDED_ORDERED_NODE_COPY_SUBTREE_TPP