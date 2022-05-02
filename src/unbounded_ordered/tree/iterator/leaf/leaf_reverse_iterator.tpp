#ifndef UNBOUNDED_ORDERED_TREE_LEAF_REVERSE_ITERATOR_TPP
#define UNBOUNDED_ORDERED_TREE_LEAF_REVERSE_ITERATOR_TPP

#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include "unbounded_ordered/tree/iterator/leaf/leaf_reverse_iterator_t.tpp"
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  class tree<T>::leaf_reverse_iterator
      : public tree<T>::template leaf_reverse_iterator_t<T> {
  protected:
    leaf_reverse_iterator(node<T>* root, node<T>* current,
      typename bidirectional_iterator_t<T>::Status status,
      typename node<T>::NodeLastMovement last_movement)
        : leaf_reverse_iterator_t<T>(root, current, status, last_movement),
          iterator_t<T>(root, current) {}

    inline static typename tree<T>::leaf_reverse_iterator before_begin(node<T>* root) {
      return tree<T>::leaf_reverse_iterator(root, nullptr,
          bidirectional_iterator_t<T>::BIDIRECTIONAL_ITERATOR_BEGIN,
          node<T>::NODE_UNDEFINED);
    }
    inline static typename tree<T>::leaf_reverse_iterator begin(node<T>* root) {
      return tree<T>::leaf_reverse_iterator(root, root->get_rightmost_leaf(),
          bidirectional_iterator_t<T>::BIDIRECTIONAL_ITERATOR_MIDDLE,
          node<T>::NODE_UNDEFINED);
    }
    inline static typename tree<T>::leaf_reverse_iterator end(node<T>* root) {
      return tree<T>::leaf_reverse_iterator(root, root->get_leftmost_leaf(),
          bidirectional_iterator_t<T>::BIDIRECTIONAL_ITERATOR_MIDDLE,
          node<T>::NODE_UNDEFINED);
    }
    inline static typename tree<T>::leaf_reverse_iterator after_end(node<T>* root) {
      return tree<T>::leaf_reverse_iterator(root, nullptr,
          bidirectional_iterator_t<T>::BIDIRECTIONAL_ITERATOR_END,
          node<T>::NODE_UNDEFINED);
    }

  public:
    leaf_reverse_iterator() : leaf_reverse_iterator_t<T>(), iterator_t<T>() {}

    leaf_reverse_iterator(const bidirectional_iterator_t<T>& it)
      : leaf_reverse_iterator_t<T>(it._root, it._current, it._status, it._last_movement),
        iterator_t<T>(it._root, it._current) {
      if(this->_status == bidirectional_iterator_t<T>::BIDIRECTIONAL_ITERATOR_MIDDLE) {
        this->_current = this->_current->get_rightmost_leaf();
      }
    }
    leaf_reverse_iterator(const bidirectional_iterator_t<const T>& it)
      : leaf_reverse_iterator_t<T>(it._root, it._current, it._status, it._last_movement),
        iterator_t<T>(it._root, it._current) {
      if(this->_status == bidirectional_iterator_t<T>::BIDIRECTIONAL_ITERATOR_MIDDLE) {
        this->_current = this->_current->get_rightmost_leaf();
      }
    }

    friend typename unbounded_ordered::tree<T>::leaf_reverse_iterator
        unbounded_ordered::tree<T>::leaf_rbefore_begin() const;
    friend typename unbounded_ordered::tree<T>::leaf_reverse_iterator
        unbounded_ordered::tree<T>::leaf_rbegin() const;
    friend typename unbounded_ordered::tree<T>::leaf_reverse_iterator
        unbounded_ordered::tree<T>::leaf_rend() const;
    friend typename unbounded_ordered::tree<T>::leaf_reverse_iterator
        unbounded_ordered::tree<T>::leaf_rafter_end() const;
  };
}

#endif // UNBOUNDED_ORDERED_TREE_LEAF_REVERSE_ITERATOR_TPP