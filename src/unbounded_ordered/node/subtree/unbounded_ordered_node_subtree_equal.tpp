#ifndef UNBOUNDED_ORDERED_NODE_SUBTREE_EQUAL_TPP
#define UNBOUNDED_ORDERED_NODE_SUBTREE_EQUAL_TPP

#include <map>
#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  bool node<T>::is_subtree_equal_aux(
    const node<T>* const rhs,
    std::map<const node<T>* const, const node<T>* const>& m
  ) const {
    typename std::map<const node<T>* const, const node<T>* const>::const_iterator this_it = m.find(this);

    if(this_it == m.cend()) {
      // The pair of nodes was not visited so far.
      // They need to be added.
#ifdef LEVEL_DEBUG
      std::cout << "Mapping " << this << " -> " << rhs << std::endl;
#endif // LEVEL_DEBUG
      m.insert(typename std::map<const node<T>* const, const node<T>* const>::value_type(this, rhs));
      //m[this] = rhs;
      return true;
    }
    else {
      // The node this was visited.
      // Need to assert that it is mapped to the same node as required by the argument given to the method.
#ifdef LEVEL_DEBUG
      std::cout << "Checking " << this_it->second << " == " << rhs << std::endl;
#endif // LEVEL_DEBUG
      return this_it->second == rhs;
    }
  }

  template <typename T>
  bool node<T>::is_subtree_equal_bijection(
    const node<T>* const rhs,
    std::map<const node<T>* const, const node<T>* const>& m,
    std::map<const node<T>* const, const node<T>* const>& m_reverse
  ) const {
    return is_subtree_equal_aux(rhs, m) && rhs->is_subtree_equal_aux(this, m_reverse);
  }

  // Used for testing that replicating a tree rooted in this was done properly.
  template <typename T>
  bool node<T>::is_subtree_equal(
    const node<T>* const rhs,
    std::map<const node<T>* const, const node<T>* const>& m,
    std::map<const node<T>* const, const node<T>* const>& m_reverse,
    const std::string& path
  ) const {
#ifdef LEVEL_DEBUG
    std::cout << "Checking " << path << " " << this << ", " << rhs << std::endl;
#endif // LEVEL_DEBUG
    bool result = rhs
                  && is_subtree_equal_aux(rhs, m)
                  && rhs->is_subtree_equal_aux(this, m_reverse);

#ifdef LEVEL_DEBUG
    std::cout << "Checking " << path << ",data " << _data << " == " << rhs->_data << std::endl;
#endif // LEVEL_DEBUG
    result &= (_data == rhs->_data);

#ifdef LEVEL_DEBUG
    std::cout << "Checking " << path << ",parent " << _parent << ", " << rhs->_parent << std::endl;
#endif // LEVEL_DEBUG
    if(result && _parent) result &= _parent->is_subtree_equal_bijection(rhs->_parent, m, m_reverse);

#ifdef LEVEL_DEBUG
    std::cout << "Checking " << path << ",last child " << _last_child << ", " << rhs->_last_child << std::endl;
#endif // LEVEL_DEBUG
    if(result && _last_child) result &= _last_child->is_subtree_equal_bijection(rhs->_last_child, m, m_reverse);

#ifdef LEVEL_DEBUG
    std::cout << "Checking " << path << ",previous sibling " << _previous_sibling << ", " << rhs->_previous_sibling << std::endl;
#endif // LEVEL_DEBUG
    if(result && _previous_sibling) result &= _previous_sibling->is_subtree_equal_bijection(rhs->_previous_sibling, m, m_reverse);

#ifdef LEVEL_DEBUG
    std::cout << "Checking " << path << ",next sibling " << _next_sibling << ", " << rhs->_next_sibling << std::endl;
#endif // LEVEL_DEBUG
    // Recursion needs to be done on the next sibling.
    if(result && _next_sibling) result &= _next_sibling->is_subtree_equal(rhs->_next_sibling, m, m_reverse, path + ",next sibling");

#ifdef LEVEL_DEBUG
    std::cout << "Checking " << path << ",first child " << _first_child << ", " << rhs->_first_child << std::endl;
#endif // LEVEL_DEBUG
    // Recursion needs to be done on the first child.
    if(result && _first_child) result &= _first_child->is_subtree_equal(rhs->_first_child, m, m_reverse, path + ",first child");

    return result;
  }

  template <typename T>
  bool node<T>::is_subtree_equal(
    const node<T>* const rhs,
    const std::string& path
  ) const {
    std::map<const node<T>* const, const node<T>* const> m;
    std::map<const node<T>* const, const node<T>* const> m_reverse;

    return is_subtree_equal(rhs, m, m_reverse, path);
  }
}

#endif // UNBOUNDED_ORDERED_NODE_SUBTREE_EQUAL_TPP