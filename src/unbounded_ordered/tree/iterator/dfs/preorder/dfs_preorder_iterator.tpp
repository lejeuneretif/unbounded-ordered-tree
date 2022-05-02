#ifndef UNBOUNDED_ORDERED_TREE_DFS_PREORDER_ITERATOR_TPP
#define UNBOUNDED_ORDERED_TREE_DFS_PREORDER_ITERATOR_TPP

#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include "unbounded_ordered/tree/iterator/dfs/preorder/dfs_preorder_iterator_t.tpp"
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  class tree<T>::dfs_preorder_iterator
      : public tree<T>::template dfs_preorder_iterator_t<T> {
  protected:
    dfs_preorder_iterator(node<T>* root, node<T>* current,
      typename bidirectional_iterator_t<T>::Status status,
      typename node<T>::NodeLastMovement last_movement)
        : dfs_preorder_iterator_t<T>(root, current, status, last_movement),
          iterator_t<T>(root, current) {}

    inline static typename tree<T>::dfs_preorder_iterator before_begin(node<T>* root) {
      return tree<T>::dfs_preorder_iterator(root, nullptr,
          bidirectional_iterator_t<T>::BIDIRECTIONAL_ITERATOR_BEGIN,
          node<T>::NODE_UNDEFINED);
    }
    inline static typename tree<T>::dfs_preorder_iterator begin(node<T>* root) {
      return tree<T>::dfs_preorder_iterator(root, root,
          bidirectional_iterator_t<T>::BIDIRECTIONAL_ITERATOR_MIDDLE,
          node<T>::NODE_UNDEFINED);
    }
    inline static typename tree<T>::dfs_preorder_iterator end(node<T>* root) {
      return tree<T>::dfs_preorder_iterator(root, root->get_rightmost_leaf(),
          bidirectional_iterator_t<T>::BIDIRECTIONAL_ITERATOR_MIDDLE,
          node<T>::NODE_UNDEFINED);
    }
    inline static typename tree<T>::dfs_preorder_iterator after_end(node<T>* root) {
      return tree<T>::dfs_preorder_iterator(root, nullptr,
          bidirectional_iterator_t<T>::BIDIRECTIONAL_ITERATOR_END,
          node<T>::NODE_UNDEFINED);
    }

  public:
    dfs_preorder_iterator() : bidirectional_iterator_t<T>(), iterator_t<T>() {}

    dfs_preorder_iterator(const bidirectional_iterator_t<T>& it)
      : dfs_preorder_iterator_t<T>(it._root, it._current, it._status, it._last_movement),
        iterator_t<T>(it._root, it._current) {}
    dfs_preorder_iterator(const bidirectional_iterator_t<const T>& it)
      : dfs_preorder_iterator_t<T>(it._root, it._current, it._status, it._last_movement),
        iterator_t<T>(it._root, it._current) {}

    friend typename unbounded_ordered::tree<T>::dfs_preorder_iterator
        unbounded_ordered::tree<T>::dfs_preorder_before_begin() const;
    friend typename unbounded_ordered::tree<T>::dfs_preorder_iterator
        unbounded_ordered::tree<T>::dfs_preorder_begin() const;
    friend typename unbounded_ordered::tree<T>::dfs_preorder_iterator
        unbounded_ordered::tree<T>::dfs_preorder_end() const;
    friend typename unbounded_ordered::tree<T>::dfs_preorder_iterator
        unbounded_ordered::tree<T>::dfs_preorder_after_end() const;
  };
}

#endif // UNBOUNDED_ORDERED_TREE_DFS_PREORDER_ITERATOR_TPP