#ifndef UNBOUNDED_ORDERED_NODE_DELETE_SUBTREE_TPP
#define UNBOUNDED_ORDERED_NODE_DELETE_SUBTREE_TPP

#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  void node<T>::delete_subtree() {
    detach();

    node<T>* dfs_postorder_previous = nullptr;
    node<T>* dfs_postorder_current = get_leftmost_leaf();

    while(dfs_postorder_current) {
      dfs_postorder_previous = dfs_postorder_current;
      dfs_postorder_current = dfs_postorder_current->dfs_postorder_next().first;
      delete dfs_postorder_previous;
    }
  }
}

#endif // UNBOUNDED_ORDERED_NODE_DELETE_SUBTREE_TPP