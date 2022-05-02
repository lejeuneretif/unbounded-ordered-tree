#ifndef UNBOUNDED_ORDERED_NODE_DETACH_TPP
#define UNBOUNDED_ORDERED_NODE_DETACH_TPP

#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"

namespace unbounded_ordered {
  // Detaches the subtree rooted at `this` from the global tree
  template <typename T>
  void node<T>::detach() {
    if(_parent) {
      // Its first child might change
      if(_parent->_first_child == this) {
        _parent->_first_child = _next_sibling;
      }

      // Its last child might change
      if(_parent->_last_child == this) {
        _parent->_last_child = _previous_sibling;
      }
    }

    // Now, detach the node
    _parent = nullptr;

    node<T>* old_previous_sibling = _previous_sibling;
    node<T>* old_next_sibling = _next_sibling;

    if(old_previous_sibling) {
      old_previous_sibling->_next_sibling = old_next_sibling;
    }

    if(old_next_sibling) {
      old_next_sibling->_previous_sibling = old_previous_sibling;
    }

    _previous_sibling = nullptr;
    _next_sibling = nullptr;
  }
}

#endif // UNBOUNDED_ORDERED_NODE_DETACH_TPP