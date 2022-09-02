#ifndef UNBOUNDED_ORDERED_NODE_TRAVERSAL_DFS_POSTORDER_TPP
#define UNBOUNDED_ORDERED_NODE_TRAVERSAL_DFS_POSTORDER_TPP

#include <utility>
#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"

namespace unbounded_ordered {
  template<typename T>
  std::pair<node<T>*, enum node<T>::NodeLastMovement> node<T>::dfs_postorder_next() const {
    if(_next_sibling) {
      return std::pair<node<T>*, NodeLastMovement>(_next_sibling->get_leftmost_leaf(), NODE_TO_NEXT_LEAF);
    }
    else {
      return std::pair<node<T>*, NodeLastMovement>(_parent, NODE_TO_PARENT);
    }
  }

  template<typename T>
  std::pair<node<T>*, enum node<T>::NodeLastMovement> node<T>::dfs_postorder_previous() const {
    if(_last_child) {
      return std::pair<node<T>*, NodeLastMovement>(_last_child, NODE_TO_LAST_CHILD);
    }

    const node<T>* current = this;
    while(current && ! current->_previous_sibling) {
      current = current->_parent;
    }

    if(current) {
      return std::pair<node<T>*, NodeLastMovement>(current->_previous_sibling, NODE_TO_PREVIOUS_ANCESTOR);
    }
    else {
      return std::pair<node<T>*, NodeLastMovement>(nullptr, NODE_UNDEFINED);
    }
  }
}

#endif // UNBOUNDED_ORDERED_NODE_TRAVERSAL_DFS_POSTORDER_TPP