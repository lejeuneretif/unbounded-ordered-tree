#ifndef UNBOUNDED_ORDERED_TREE_BFS_ITERATOR_TPP
#define UNBOUNDED_ORDERED_TREE_BFS_ITERATOR_TPP

#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include "unbounded_ordered/tree/iterator/bfs/bfs_iterator_t.tpp"
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  class tree<T>::bfs_iterator : public tree<T>::template bfs_iterator_t<T> {
  private:
    bfs_iterator(node<T>* root) : bfs_iterator_t<T>(root) {}

    bfs_iterator(node<T>* root, node<T>* start) : bfs_iterator_t<T>(root, start) {}

    inline static typename tree<T>::bfs_iterator begin(node<T>* root) {
      return tree<T>::bfs_iterator(root, root);
    }
    inline static typename tree<T>::bfs_iterator after_end(node<T>* root) {
      return tree<T>::bfs_iterator(root);
    }

  public:
    bfs_iterator() : bfs_iterator_t<T>() {}

    friend typename unbounded_ordered::tree<T>::bfs_iterator
        unbounded_ordered::tree<T>::bfs_begin() const;
    friend typename unbounded_ordered::tree<T>::bfs_iterator
        unbounded_ordered::tree<T>::bfs_after_end() const;
  };
};

#endif // UNBOUNDED_ORDERED_TREE_BFS_ITERATOR_TPP