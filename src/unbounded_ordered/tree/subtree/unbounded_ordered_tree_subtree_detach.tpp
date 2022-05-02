#ifndef UNBOUNDED_ORDERED_TREE_SUBTREE_DETACH_TPP
#define UNBOUNDED_ORDERED_TREE_SUBTREE_DETACH_TPP

#include "unbounded_ordered/tree/iterator/iterator_t.tpp"
#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  template <typename T_value>
  tree<T>* tree<T>::detach(const iterator_t<T_value>& it) {
    if(_root == it._current) {
      _root = nullptr;
    }

    // Detaches the node pointed by the iterator.
    it._current->detach();

    // Wraps the node pointed by the iterator into a tree.
    return new tree<T>(it._current);
  }
}

#endif // UNBOUNDED_ORDERED_TREE_SUBTREE_DETACH_TPP