#ifndef UNBOUNDED_ORDERED_NODE_PRINT_TPP
#define UNBOUNDED_ORDERED_NODE_PRINT_TPP

#include <iostream>
#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  std::ostream& node<T>::print_to_stream(std::ostream& s) const {
    s << _data;

    if(_first_child) {
      s << "( ";

      node<T>* current_node = _first_child;
      while(current_node != _last_child) {
        current_node->print_to_stream(s);
        s << ", ";
        current_node = current_node->_next_sibling;
      }

      _last_child->print_to_stream(s);

      s << " )";
    }

    return s;
  }
}

#endif // UNBOUNDED_ORDERED_NODE_PRINT_TPP
