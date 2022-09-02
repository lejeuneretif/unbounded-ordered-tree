#ifndef UNBOUNDED_ORDERED_TREE_RANGED_LOOP_T_TPP
#define UNBOUNDED_ORDERED_TREE_RANGED_LOOP_T_TPP

#include "unbounded_ordered_tree_ranged_loop_decl.hpp"
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  class tree_ranged_loop_t : public tree<T> {
  protected:
    tree_ranged_loop_t(const tree<T>& t) : tree<T>(t._root) {}

    // Need to overwrite the 5-rule operators on the parent class tree<T> which copies subtrees.
    // The current class is a view on the existing parent tree.
    tree_ranged_loop_t() : tree<T>(nullptr) {}
    tree_ranged_loop_t(const tree_ranged_loop_t& other) : tree<T>(other._root) {}
    tree_ranged_loop_t(tree_ranged_loop_t&& other) : tree<T>(other._root) {
      other._root = nullptr;
    }

    tree_ranged_loop_t& operator=(const tree_ranged_loop_t& other) {
      if(this == &other) {
        return *this;
      }

      // Define the new root at the current tree
      this->_root = other._root;

      return *this;
    }

    tree_ranged_loop_t& operator=(tree_ranged_loop_t&& other) {
      this->_root = other._root;
      other._root = nullptr;

      return *this;
    }

  public:
    ~tree_ranged_loop_t() {
      this->_root = nullptr;
    }

    template <typename T_friend>
    friend class tree;
  };
}

#endif // UNBOUNDED_ORDERED_TREE_RANGED_LOOP_T_TPP