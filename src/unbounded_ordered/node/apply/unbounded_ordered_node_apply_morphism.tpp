#ifndef UNBOUNDED_ORDERED_NODE_APPLY_MORPHISM_TPP
#define UNBOUNDED_ORDERED_NODE_APPLY_MORPHISM_TPP

#include <list>
#include <map>
#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"
#include <utility>

namespace unbounded_ordered {
  template<typename T>
  template<typename U>
  node<U>* node<T>::morphism(U (*fun)(const T&, const std::list<U>&)) const {
    // partial_results is a fifo of the results.
    // At each step, the last items in partial_results are replaced with the result of the call to fun.
    std::list<node<U>*> partial_results;

    const node<T>* current = get_leftmost_leaf();
    while(current) {
      std::list<U> arguments;
      std::list<node<U>*> image_children;
      for(node<T>* child = current->_first_child; child; child = child->_next_sibling) {
        node<U>* image_child = partial_results.back();
        partial_results.pop_back();
        arguments.push_front(image_child->get_data());
        image_children.push_front(image_child);
      }

      partial_results.push_back(new node<U>(fun(current->get_data(), arguments), image_children));

      current = current->dfs_postorder_next().first;
    }

    return partial_results.back();
  }

  template<typename T>
  template<typename U, typename Context>
  node<U>* node<T>::morphism(U (*fun)(Context&, const T&, const std::list<U>&), Context& context) const {
    // partial_results is a fifo of the results.
    // At each step, the last items in partial_results are replaced with the result of the call to fun.
    std::list<node<U>*> partial_results;

    const node<T>* current = get_leftmost_leaf();
    while(current) {
      std::list<U> arguments;
      std::list<node<U>*> image_children;
      for(node<T>* child = current->_first_child; child; child = child->_next_sibling) {
        node<U>* image_child = partial_results.back();
        partial_results.pop_back();
        arguments.push_front(image_child->get_data());
        image_children.push_front(image_child);
      }

      partial_results.push_back(new node<U>(fun(context, current->get_data(), arguments), image_children));

      current = current->dfs_postorder_next().first;
    }

    return partial_results.back();
  }
}

#endif // UNBOUNDED_ORDERED_NODE_APPLY_MORPHISM_TPP