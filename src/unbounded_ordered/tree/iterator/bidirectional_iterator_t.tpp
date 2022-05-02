#ifndef UNBOUNDED_ORDERED_TREE_BIDIRECTIONAL_ITERATOR_T_TPP
#define UNBOUNDED_ORDERED_TREE_BIDIRECTIONAL_ITERATOR_T_TPP

#include <exception>
#include <iterator>
#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include "unbounded_ordered/tree/iterator/forward_iterator_t.tpp"
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  template <typename T_value>
  class tree<T>::bidirectional_iterator_t
      : public std::iterator<std::bidirectional_iterator_tag, T_value, std::ptrdiff_t, T_value*, T_value&>,
        public tree<T>::template forward_iterator_t<T_value>,
        public tree<T>::template free_iterator_t<T_value> {
  protected:
    enum Status {
      BIDIRECTIONAL_ITERATOR_BEGIN = 0,
      BIDIRECTIONAL_ITERATOR_MIDDLE = 1,
      BIDIRECTIONAL_ITERATOR_END = 2
    };

    bidirectional_iterator_t(node<T>* root, node<T>* current, Status status,
      typename node<T>::NodeLastMovement last_movement)
        : iterator_t<T_value>(root), forward_iterator_t<T_value>(root),
          free_iterator_t<T_value>(root, current, last_movement),
          _status(status) {}

    Status _status;

    virtual inline void previous() {}

  public:
    bidirectional_iterator_t() : iterator_t<T_value>(), forward_iterator_t<T_value>(),
        free_iterator_t<T_value>(), _status(BIDIRECTIONAL_ITERATOR_BEGIN) {}
    
    typename tree<T>::template bidirectional_iterator_t<T_value>& operator--() {
      previous();
      return *this;
    }
    typename tree<T>::template bidirectional_iterator_t<T_value> operator--(int) {
      typename tree<T>::template bidirectional_iterator_t<T_value> tmp = *this;
      --*this;
      return tmp;
    }

    friend class dfs_postorder_const_iterator;
    friend class dfs_postorder_const_reverse_iterator;
    friend class dfs_postorder_iterator;
    friend class dfs_postorder_reverse_iterator;

    friend class dfs_preorder_const_iterator;
    friend class dfs_preorder_const_reverse_iterator;
    friend class dfs_preorder_iterator;
    friend class dfs_preorder_reverse_iterator;

    friend class leaf_const_iterator;
    friend class leaf_const_reverse_iterator;
    friend class leaf_iterator;
    friend class leaf_reverse_iterator;

    friend class xml_const_iterator;
    friend class xml_const_reverse_iterator;
    friend class xml_iterator;
    friend class xml_reverse_iterator;
  };
}

#endif // UNBOUNDED_ORDERED_TREE_BIDIRECTIONAL_ITERATOR_T_TPP