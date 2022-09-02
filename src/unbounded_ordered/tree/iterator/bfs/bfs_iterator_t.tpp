#ifndef UNBOUNDED_ORDERED_TREE_BFS_ITERATOR_T_TPP
#define UNBOUNDED_ORDERED_TREE_BFS_ITERATOR_T_TPP

#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include <iterator>
#include "unbounded_ordered/tree/iterator/forward_iterator_t.tpp"
#include <list>
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  template <typename T_value>
  class tree<T>::bfs_iterator_t
      : public std::iterator<std::forward_iterator_tag, T, std::ptrdiff_t, T*, T&>,
        public tree<T>::template forward_iterator_t<T_value> {
  protected:
    // The first node of the heap is the node where the BFS is currently pointing.
    std::list<node<T>*> _heap;

    bfs_iterator_t(node<T>* root) : forward_iterator_t<T_value>(root) {
      this->_current = nullptr;
    }

    bfs_iterator_t(node<T>* root, node<T>* start) : forward_iterator_t<T_value>(root) {
      _heap.push_front(start);
      this->_current = start;
    }

    virtual inline void next() {
      if(! _heap.size()) {
        THROW_ERROR_END_ITERATOR;
      }

      node<T>* current_node = _heap.front();

      if(current_node->get_next_sibling()) {
        _heap.push_front(current_node->get_next_sibling());
      }
      else {
        node<T>* first_node = nullptr;
        node<T>* first_child = nullptr;
        do {
          first_node = _heap.back();
          _heap.pop_back();
          first_child = first_node->get_first_child();
        } while(_heap.size() && ! first_child);

        if(first_child) {
          _heap.push_front(first_child);
        }
      }

      this->_current = _heap.size() ? _heap.front() : nullptr;
    }

  public:
    bfs_iterator_t() : forward_iterator_t<T_value>() {}
  };
};

#endif // UNBOUNDED_ORDERED_TREE_BFS_ITERATOR_T_TPP