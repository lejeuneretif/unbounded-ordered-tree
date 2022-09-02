#ifndef UNBOUNDED_ORDERED_NODE_CONSISTENCY_TPP
#define UNBOUNDED_ORDERED_NODE_CONSISTENCY_TPP

#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"
#include <set>

namespace unbounded_ordered {
  // Used for testing that the pointers between `node` and its children are properly formed.
  // It tests the consistency of the smallest pointer-loops.
  // That way, it ensures the consistency of the bigger pointer-loops, since they all rely on these smaller loops.
  template <typename T>
  bool node<T>::is_small_loop_consistent() const {
    // Asserts that either there is a first child and a last child, or neither.
    // Ie _first_child iff _last_child.
    bool result = ((_first_child == nullptr) == (_last_child == nullptr));

    // If there is a first child, there are chlidren to check the consistency of.
    if(_first_child) {
      // Assert first child does not have previous sibling.
      // Assert last child does not have next sibling.
      result &= ! _first_child->_previous_sibling
              && ! _last_child->_next_sibling;

      // Iterates over the children and checks for loop between the children (there should be none).
      std::set<const node<T>*> visited;

      for(const node<T>* current_child = _first_child;
          current_child != nullptr;
          current_child = current_child->_next_sibling) {
        // Asserts the current child is not already visited.
        // This breaks the for loop if there were a pointer-loop among the children of `this`.
        result &= (visited.find(current_child) == visited.cend());

        // Checks the consistency of the mutual pointers between the current child and its previous sibling, if this one exists.
        if(current_child->_previous_sibling) {
          result &= (current_child == current_child->_previous_sibling->_next_sibling);
        }

        // Checks the parent.
        result &= (this == current_child->_parent);

        if(! current_child->_previous_sibling) {
          // The child without previous sibling should be the first child.
          result &= (current_child == _first_child);
        }

        if(! current_child->_next_sibling) {
          // The child without next sibling should be the last child.
          result &= (current_child == _last_child);
        }

        // The current child is visited.
        visited.insert(current_child);
      }
    }

    return result;
  }

  // Used for testing the small loops in every node below `this`.
  template <typename T>
  bool node<T>::is_big_loop_consistent() const {
    bool result = is_small_loop_consistent();

    if(_next_sibling) {
      result &= _next_sibling->is_big_loop_consistent();
    }

    if(_first_child) {
      result &= _first_child->is_big_loop_consistent();
    }
    else {
      // `this` is a leaf
      result &= ! _last_child;
    }

    return result;
  }

  // Used for testing the small loops and that `node` is the root of a tree.
  template <typename T>
  bool node<T>::is_subtree_consistent() const {
    return !_parent && !_previous_sibling && !_next_sibling && is_big_loop_consistent();
  }
}

#endif // UNBOUNDED_ORDERED_NODE_CONSISTENCY_TPP