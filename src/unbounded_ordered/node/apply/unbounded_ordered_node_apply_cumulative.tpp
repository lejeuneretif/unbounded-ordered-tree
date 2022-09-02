#ifndef UNBOUNDED_ORDERED_NODE_APPLY_CUMULATIVE_TPP
#define UNBOUNDED_ORDERED_NODE_APPLY_CUMULATIVE_TPP

#include <list>
#include <map>
#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"
#include <utility>

namespace unbounded_ordered {
  template<typename T>
  template<typename U>
  U node<T>::cumulative(U (*fun)(const T&, const std::list<U>&)) const {
    // partial_results is a fifo of the results.
    // At each step, the last items in partial_results are replaced with the result of the call to fun.
    std::list<U> partial_results;

    const node<T>* current = get_leftmost_leaf();
    while(current) {
      std::list<U> arguments;
      for(node<T>* child = current->_first_child; child; child = child->_next_sibling) {
        U value = partial_results.back();
        partial_results.pop_back();
        arguments.push_front(value);
      }

      partial_results.push_back(fun(current->get_data(), arguments));

      current = current->dfs_postorder_next().first;
    }

    return partial_results.back();
  }

  template<typename T>
  template<typename U, typename Context>
  U node<T>::cumulative(U (*fun)(Context&, const T&, const std::list<U>&), Context& context) const {
    // partial_results is a fifo of the results.
    // At each step, the last items in partial_results are replaced with the result of the call to fun.
    std::list<U> partial_results;

    const node<T>* current = get_leftmost_leaf();
    while(current) {
      std::list<U> arguments;
      for(node<T>* child = current->_first_child; child; child = child->_next_sibling) {
        U value = partial_results.back();
        partial_results.pop_back();
        arguments.push_front(value);
      }

      partial_results.push_back(fun(context, current->get_data(), arguments));

      current = current->dfs_postorder_next().first;
    }

    return partial_results.back();
  }
}

#endif // UNBOUNDED_ORDERED_NODE_APPLY_CUMULATIVE_TPP