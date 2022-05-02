#ifndef UNBOUNDED_ORDERED_NODE_CTOR_TPP
#define UNBOUNDED_ORDERED_NODE_CTOR_TPP

#include <list>
#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"

namespace unbounded_ordered {
// BEGIN ctors
  template <typename T>
  node<T>::node()
    : _parent(nullptr), _previous_sibling(nullptr), _next_sibling(nullptr),
      _first_child(nullptr), _last_child(nullptr) {}

  template <typename T>
  node<T>::node(const T& data, node<T>* parent, node<T>* previous_sibling, node<T>* next_sibling,
                node<T>* first_child, node<T>* last_child)
    : _parent(parent), _data(data), _previous_sibling(previous_sibling), _next_sibling(next_sibling),
      _first_child(first_child), _last_child(last_child) {}

  template <typename T>
  node<T>::node(const T& data, const std::list<node<T>*>& l)
      : _parent(nullptr), _data(data), _previous_sibling(nullptr), _next_sibling(nullptr),
        _first_child(nullptr), _last_child(nullptr) {
    if(! l.empty()) {
      typename std::list<node<T>*>::const_iterator iterator_current_node = l.begin();

      _first_child = *iterator_current_node;

      node<T>* previous_node = nullptr;
      for(; iterator_current_node != l.end(); ++iterator_current_node) {
        (*iterator_current_node)->_parent = this;

        if(previous_node) {
          previous_node->_next_sibling = *iterator_current_node;
          (*iterator_current_node)->_previous_sibling = previous_node;
        }

        previous_node = *iterator_current_node;
      }

      _last_child = previous_node;
    }
  }

  template <typename T>
  node<T>::node(const T& data, const std::initializer_list<node<T>*>& l)
      : _parent(nullptr), _data(data), _previous_sibling(nullptr), _next_sibling(nullptr),
        _first_child(nullptr), _last_child(nullptr) {
    if(l.size()) {
      typename std::initializer_list<node<T>*>::const_iterator iterator_current_node = l.begin();

      _first_child = *iterator_current_node;

      node<T>* previous_node = nullptr;
      for(; iterator_current_node != l.end(); ++iterator_current_node) {
        (*iterator_current_node)->_parent = this;

        if(previous_node) {
          previous_node->_next_sibling = *iterator_current_node;
          (*iterator_current_node)->_previous_sibling = previous_node;
        }

        previous_node = *iterator_current_node;
      }

      _last_child = previous_node;
    }
  }
// END ctors

// BEGIN getter setter
  template <typename T>
  const T& node<T>::get_data() const { return _data; }
  template <typename T>
  T& node<T>::get_data() { return _data; }

  template <typename T>
  node<T>* node<T>::get_parent() const { return _parent; }
  template <typename T>
  node<T>* node<T>::get_previous_sibling() const { return _previous_sibling; }
  template <typename T>
  node<T>* node<T>::get_next_sibling() const { return _next_sibling; }
  template <typename T>
  node<T>* node<T>::get_first_child() const { return _first_child; }
  template <typename T>
  node<T>* node<T>::get_leftmost_leaf() const {
    const node<T>* result = this;
    while(result->_first_child) result = result->_first_child;

    return const_cast<node<T>*>(result);
  }
  template <typename T>
  node<T>* node<T>::get_last_child() const { return _last_child; }
  template <typename T>
  node<T>* node<T>::get_rightmost_leaf() const {
    const node<T>* result = this;
    while(result->_last_child) result = result->_last_child;

    return const_cast<node<T>*>(result);
  }

  template <typename T>
  void node<T>::set_data(const T& data) { _data = data; }
// END getter setter

  // The dtor blanks the pointers to avoid bad access to memory once the nodes are deleted.
  template <typename T>
  node<T>::~node() {
    _parent = _previous_sibling = _next_sibling = _first_child = _last_child = nullptr;
  }
}

#endif // UNBOUNDED_ORDERED_NODE_CTOR_TPP
