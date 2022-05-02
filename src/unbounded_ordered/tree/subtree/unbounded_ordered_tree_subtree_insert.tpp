#ifndef UNBOUNDED_ORDERED_TREE_SUBTREE_INSERT_TPP
#define UNBOUNDED_ORDERED_TREE_SUBTREE_INSERT_TPP

#include <exception>
#include "unbounded_ordered/tree/iterator/iterator_t.tpp"
#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  class insert_in_empty_tree : public std::exception {
    const char* what() const throw() {
      return "Cannot insert in empty tree.";
    }
  };

  template <typename T>
  template <typename T_value>
  void tree<T>::insert_subtree_move(const iterator_t<T_value>& it, tree<T>& t, void (node<T>::*insert)(node<T>*)) const {
    if(! _root) throw insert_in_empty_tree();

    if(t._root) (it._current->*insert)(t._root);

    t._root = nullptr;
  }

  template <typename T>
  template <typename T_value>
  void tree<T>::insert_previous_sibling_move(const iterator_t<T_value>& it, tree<T>& t) const {
    insert_subtree_move(it, t, &node<T>::insert_previous_sibling);
  }

  template <typename T>
  template <typename T_value>
  void tree<T>::insert_next_sibling_move(const iterator_t<T_value>& it, tree<T>& t) const {
    insert_subtree_move(it, t, &node<T>::insert_next_sibling);
  }

  template <typename T>
  template <typename T_value>
  void tree<T>::insert_first_child_move(const iterator_t<T_value>& it, tree<T>& t) const {
    insert_subtree_move(it, t, &node<T>::insert_first_child);
  }

  template <typename T>
  template <typename T_value>
  void tree<T>::insert_last_child_move(const iterator_t<T_value>& it, tree<T>& t) const {
    insert_subtree_move(it, t, &node<T>::insert_last_child);
  }
}

#endif // UNBOUNDED_ORDERED_TREE_SUBTREE_INSERT_TPP