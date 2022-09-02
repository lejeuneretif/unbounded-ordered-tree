#ifndef UNBOUNDED_ORDERED_TREE_BFS_CONST_ITERATOR_TPP
#define UNBOUNDED_ORDERED_TREE_BFS_CONST_ITERATOR_TPP

#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include "unbounded_ordered/tree/iterator/bfs/bfs_iterator_t.tpp"
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  class tree<T>::bfs_const_iterator : public tree<T>::template bfs_iterator_t<const T> {
  private:
    bfs_const_iterator(node<T>* root) : bfs_iterator_t<const T>(root) {}

    bfs_const_iterator(node<T>* root, node<T>* start)
        : bfs_iterator_t<const T>(root, start) {}

    inline static typename tree<T>::bfs_const_iterator begin(node<T>* root) {
      return tree<T>::bfs_const_iterator(root, root);
    }
    inline static typename tree<T>::bfs_const_iterator after_end(node<T>* root) {
      return tree<T>::bfs_const_iterator(root);
    }

  public:
    bfs_const_iterator() : bfs_iterator_t<const T>() {}

    friend typename unbounded_ordered::tree<T>::bfs_const_iterator
        unbounded_ordered::tree<T>::bfs_cbegin() const;
    friend typename unbounded_ordered::tree<T>::bfs_const_iterator
        unbounded_ordered::tree<T>::bfs_cafter_end() const;
  };
};

#endif // UNBOUNDED_ORDERED_TREE_BFS_CONST_ITERATOR_TPP