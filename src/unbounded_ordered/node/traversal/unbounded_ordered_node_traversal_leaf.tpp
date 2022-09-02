#ifndef UNBOUNDED_ORDERED_NODE_TRAVERSAL_LEAF_TPP
#define UNBOUNDED_ORDERED_NODE_TRAVERSAL_LEAF_TPP

#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"

namespace unbounded_ordered {
  template<typename T>
  std::pair<node<T>*, enum node<T>::NodeLastMovement> node<T>::leaf_next() const {
    const node<T>* current = this;
    while(current && ! current->_next_sibling) {
      current = current->_parent;
    }

    if(current) {
      return std::pair<node<T>*, enum node<T>::NodeLastMovement>(current->_next_sibling->get_leftmost_leaf(), NODE_TO_NEXT_LEAF);
    }
    else {
      return std::pair<node<T>*, enum node<T>::NodeLastMovement>(nullptr, NODE_UNDEFINED);
    }
  }

  template<typename T>
  std::pair<node<T>*, enum node<T>::NodeLastMovement> node<T>::leaf_previous() const {
    const node<T>* current = this;
    while(current && ! current->_previous_sibling) {
      current = current->_parent;
    }

    if(current) {
      return std::pair<node<T>*, enum node<T>::NodeLastMovement>(current->_previous_sibling->get_rightmost_leaf(), NODE_TO_PREVIOUS_LEAF);
    }
    else {
      return std::pair<node<T>*, enum node<T>::NodeLastMovement>(nullptr, NODE_UNDEFINED);
    }
  }
}

#endif // UNBOUNDED_ORDERED_NODE_TRAVERSAL_LEAF_TPP