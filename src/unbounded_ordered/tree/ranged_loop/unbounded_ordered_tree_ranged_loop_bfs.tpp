#ifndef UNBOUNDED_ORDERED_TREE_RANGED_LOOP_BFS_TPP
#define UNBOUNDED_ORDERED_TREE_RANGED_LOOP_BFS_TPP

#include "unbounded_ordered/tree/iterator/bfs/bfs_iterator.tpp"
#include "unbounded_ordered_tree_ranged_loop_t.tpp"

namespace unbounded_ordered {
  template <typename T>
  class tree_ranged_loop_bfs : public tree_ranged_loop_t<T> {
  protected:
    tree_ranged_loop_bfs(const tree<T>& t) : tree_ranged_loop_t<T>(t) {}

  public:
    inline typename tree<T>::bfs_iterator begin() const {
      return this->bfs_begin();
    }
    inline typename tree<T>::bfs_iterator end() const {
      return this->bfs_after_end();
    }

    template <typename T_friend>
    friend class tree;
  };
}

#endif // UNBOUNDED_ORDERED_TREE_RANGED_LOOP_BFS_TPP