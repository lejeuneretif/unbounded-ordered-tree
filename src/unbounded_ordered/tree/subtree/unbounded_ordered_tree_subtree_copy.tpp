#ifndef UNBOUNDED_ORDERED_TREE_SUBTREE_COPY_TPP
#define UNBOUNDED_ORDERED_TREE_SUBTREE_COPY_TPP

#include "unbounded_ordered/tree/iterator/iterator_t.tpp"
#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  template <typename T_value>
  tree<T>* tree<T>::subtree_copy(const iterator_t<T_value>& it) const {
    // Copies the subtree of the node pointed by the iterator then wraps the copy into a tree.
    return new tree<T>(it._current->copy_subtree());
  }
}

#endif // UNBOUNDED_ORDERED_TREE_SUBTREE_COPY_TPP