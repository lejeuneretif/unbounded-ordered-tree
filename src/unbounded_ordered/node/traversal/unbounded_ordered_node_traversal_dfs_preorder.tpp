#ifndef UNBOUNDED_ORDERED_NODE_TRAVERSAL_DFS_PREORDER_TPP
#define UNBOUNDED_ORDERED_NODE_TRAVERSAL_DFS_PREORDER_TPP

#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"

namespace unbounded_ordered {
  template<typename T>
  std::pair<node<T>*, enum node<T>::NodeLastMovement> node<T>::dfs_preorder_next() const {
    if(_first_child) {
      return std::pair<node<T>*, enum node<T>::NodeLastMovement>(_first_child, NODE_TO_FIRST_CHILD);
    }

    const node<T>* current = this;
    while(current && ! current->_next_sibling) {
      current = current->_parent;
    }

    if(current) {
      return std::pair<node<T>*, enum node<T>::NodeLastMovement>(current->_next_sibling, NODE_TO_NEXT_ANCESTOR);
    }
    else {
      return std::pair<node<T>*, enum node<T>::NodeLastMovement>(nullptr, NODE_UNDEFINED);
    }
  }

  template<typename T>
  std::pair<node<T>*, enum node<T>::NodeLastMovement> node<T>::dfs_preorder_previous() const {
    if(_previous_sibling) {
      return std::pair<node<T>*, enum node<T>::NodeLastMovement>(_previous_sibling->get_rightmost_leaf(), NODE_TO_PREVIOUS_LEAF);
    }
    else {
      return std::pair<node<T>*, enum node<T>::NodeLastMovement>(_parent, NODE_TO_PARENT);
    }
  }
}

#endif // UNBOUNDED_ORDERED_NODE_TRAVERSAL_DFS_PREORDER_TPP