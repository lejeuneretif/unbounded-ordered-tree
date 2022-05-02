#ifndef UNBOUNDED_ORDERED_TREE_ITERATOR_T_HPP
#define UNBOUNDED_ORDERED_TREE_ITERATOR_T_HPP

#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  template <typename T_value>
  class tree<T>::iterator_t {
  protected:
    node<T>* _root;
    node<T>* _current;

    iterator_t(node<T>* root, node<T>* current = nullptr) : _root(root), _current(current) {}

  public:
    iterator_t() : _root(nullptr), _current(nullptr) {}

    T_value& operator*() const {
      if(! _current) THROW_ERROR_OOB_ITERATOR;

      return _current->get_data();
    }
    T_value* operator->() const {
      if(! _current) THROW_ERROR_OOB_ITERATOR;

      return &(_current->get_data());
    }

    bool is_leaf() const { return _current->is_leaf(); }
    bool is_root() const { return _current->is_root(); }

    inline bool operator==(const iterator_t& rhs) const {
      return _current == rhs._current;
    }
    inline bool operator!=(const iterator_t& rhs) const {
      return !this->operator==(rhs);
    }

    inline bool operator< (const iterator_t& rhs) const {
      return _current < rhs._current;
    }
    inline bool operator> (const iterator_t& rhs) const {
      return  rhs.operator<(*this);
    }
    inline bool operator<=(const iterator_t& rhs) const {
      return !this->operator>(rhs);
    }
    inline bool operator>=(const iterator_t& rhs) const {
      return !this->operator<(rhs);
    }

    friend class tree<T>;
  };
}


#endif // UNBOUNDED_ORDERED_TREE_ITERATOR_T_HPP