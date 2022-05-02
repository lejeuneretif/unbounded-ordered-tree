#ifndef UNBOUNDED_ORDERED_TREE_FORWARD_ITERATOR_T_HPP
#define UNBOUNDED_ORDERED_TREE_FORWARD_ITERATOR_T_HPP

#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include "unbounded_ordered/tree/iterator/iterator_t.tpp"
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  template <typename T_value>
  class tree<T>::forward_iterator_t : virtual public tree<T>::template iterator_t<T_value> {
  protected:
    forward_iterator_t(node<T>* root) : iterator_t<T_value>(root) {}

    virtual inline void next() {}

  public:
    forward_iterator_t() : iterator_t<T_value>(nullptr) {}

    typename tree<T>::template forward_iterator_t<T_value>& operator++() {
      next();
      return *this;
    }
    typename tree<T>::template forward_iterator_t<T_value> operator++(int) {
      typename tree<T>::template forward_iterator_t<T_value> tmp = *this;
      ++*this;
      return tmp;
    }
  };
}

#endif // UNBOUNDED_ORDERED_TREE_FORWARD_ITERATOR_T_HPP