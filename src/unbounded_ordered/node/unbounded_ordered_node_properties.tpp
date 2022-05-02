#ifndef UNBOUNDED_ORDERED_NODE_PROPERTIES_TPP
#define UNBOUNDED_ORDERED_NODE_PROPERTIES_TPP

#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  bool node<T>::is_leaf() const { return !_first_child; }

  template <typename T>
  bool node<T>::is_root() const { return !_parent; }

  template <typename T>
  std::size_t node<T>::count_children() const {
    std::size_t result = 0;

    for(node<T>* child = _first_child; child; child = child->_next_sibling) {
      ++result;
    }

    return result;
  }
}

#endif // UNBOUNDED_ORDERED_NODE_PROPERTIES_TPP