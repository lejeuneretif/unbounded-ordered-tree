#ifndef UNBOUNDED_ORDERED_TREE_DFS_POSTORDER_CONST_REVERSE_ITERATOR_TPP
#define UNBOUNDED_ORDERED_TREE_DFS_POSTORDER_CONST_REVERSE_ITERATOR_TPP

#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include "unbounded_ordered/tree/iterator/dfs/postorder/dfs_postorder_reverse_iterator_t.tpp"
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  class tree<T>::dfs_postorder_const_reverse_iterator
      : public tree<T>::template dfs_postorder_reverse_iterator_t<const T> {
  protected:
    dfs_postorder_const_reverse_iterator(node<T>* root, node<T>* current,
      typename dfs_postorder_reverse_iterator_t<const T>::Status status,
      typename node<T>::NodeLastMovement last_movement)
        : dfs_postorder_reverse_iterator_t<const T>(root, current, status, last_movement),
          iterator_t<const T>(root, current) {}

    inline static typename tree<T>::dfs_postorder_const_reverse_iterator before_begin(node<T>* root) {
      return tree<T>::dfs_postorder_const_reverse_iterator(root, nullptr,
          dfs_postorder_reverse_iterator_t<const T>::BIDIRECTIONAL_ITERATOR_BEGIN,
          node<T>::NODE_UNDEFINED);
    }
    inline static typename tree<T>::dfs_postorder_const_reverse_iterator begin(node<T>* root) {
      return tree<T>::dfs_postorder_const_reverse_iterator(root, root,
          dfs_postorder_reverse_iterator_t<const T>::BIDIRECTIONAL_ITERATOR_MIDDLE,
          node<T>::NODE_UNDEFINED);
    }
    inline static typename tree<T>::dfs_postorder_const_reverse_iterator end(node<T>* root) {
      return tree<T>::dfs_postorder_const_reverse_iterator(root, root->get_leftmost_leaf(),
          dfs_postorder_reverse_iterator_t<const T>::BIDIRECTIONAL_ITERATOR_MIDDLE,
          node<T>::NODE_UNDEFINED);
    }
    inline static typename tree<T>::dfs_postorder_const_reverse_iterator after_end(node<T>* root) {
      return tree<T>::dfs_postorder_const_reverse_iterator(root, nullptr,
          dfs_postorder_reverse_iterator_t<const T>::BIDIRECTIONAL_ITERATOR_END,
          node<T>::NODE_UNDEFINED);
    }

  public:
    dfs_postorder_const_reverse_iterator() : dfs_postorder_reverse_iterator_t<const T>(), iterator_t<const T>() {}

    dfs_postorder_const_reverse_iterator(const bidirectional_iterator_t<T>& it)
      : dfs_postorder_reverse_iterator_t<const T>(it._root, it._current, it._status, it._last_movement),
        iterator_t<const T>(it._root, it._current) {}
    dfs_postorder_const_reverse_iterator(const bidirectional_iterator_t<const T>& it)
      : dfs_postorder_reverse_iterator_t<const T>(it._root, it._current, it._status, it._last_movement),
        iterator_t<const T>(it._root, it._current) {}

    friend typename unbounded_ordered::tree<T>::dfs_postorder_const_reverse_iterator
        unbounded_ordered::tree<T>::dfs_postorder_crbefore_begin() const;
    friend typename unbounded_ordered::tree<T>::dfs_postorder_const_reverse_iterator
        unbounded_ordered::tree<T>::dfs_postorder_crbegin() const;
    friend typename unbounded_ordered::tree<T>::dfs_postorder_const_reverse_iterator
        unbounded_ordered::tree<T>::dfs_postorder_crend() const;
    friend typename unbounded_ordered::tree<T>::dfs_postorder_const_reverse_iterator
        unbounded_ordered::tree<T>::dfs_postorder_crafter_end() const;
  };
}

#endif // UNBOUNDED_ORDERED_TREE_DFS_POSTORDER_CONST_REVERSE_ITERATOR_TPP