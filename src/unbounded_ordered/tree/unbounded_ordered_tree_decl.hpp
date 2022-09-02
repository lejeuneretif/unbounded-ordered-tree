#ifndef UNBOUNDED_ORDERED_TREE_DECL_HPP
#define UNBOUNDED_ORDERED_TREE_DECL_HPP

#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include "ranged_loop/unbounded_ordered_tree_ranged_loop_decl.hpp"
#include <initializer_list>
#include <iostream>
#include <stdexcept>

#define THROW_ERROR_BEGIN_ITERATOR throw std::out_of_range("The iterator is already at the first node.")
#define THROW_ERROR_END_ITERATOR throw std::out_of_range("The iterator is past the last node.")
#define THROW_ERROR_OOB_ITERATOR throw std::out_of_range("The iterator is out of bounds.")
#define THROW_ERROR_UNKNOWN_STATUS throw std::out_of_range("The iterator is in an unknown status.")

#ifdef UNBOUNDED_ORDERED_TREE_TEST_TRACE
#include <boost/stacktrace.hpp>
#endif // UNBOUNDED_ORDERED_TREE_TEST_TRACE

namespace unbounded_ordered {
#ifdef UNBOUNDED_ORDERED_TREE_TEST_TRACE
  extern std::map<void*, std::string> tree_allocation_debug_stacktrace;
#endif // UNBOUNDED_ORDERED_TREE_TEST_TRACE

  template <typename T>
  class tree {
  protected:
    node<T>* _root;

    tree(node<T>*);

    std::ostream& print_to_stream(std::ostream&) const;

  public:
    // Default constructor
    tree();

    // Creates a tree with only a root
    tree(const T&);

    // Creates a tree with children of the root
    tree(const T&, const std::initializer_list<tree>&);

    // Copy constructor duplicates the whole tree `other`
    tree(const tree&);

    // Move constructor
    tree(tree&&);

    // Copy assignment
    tree& operator=(const tree&);

    // Move assignment operator
    tree& operator=(tree&&);

    // Destructor
    ~tree();

    // Swaps the roots of both trees
    static void swap(tree&, tree&);

    bool is_empty() const;

    // BEGIN Exceptions
    class insert_in_empty_tree : public std::exception {
      const char* what() const throw() {
        return "Cannot insert in empty tree.";
      }
    };
    // END Exceptions

    // BEGIN Operations on the root with move semantics
  private:
    tree& insert_subtree_root(tree&, void (node<T>::*)(node<T>*));

  public:
    tree& insert_first_child(tree&);
    tree& insert_last_child(tree&);
    // END Operations on the root with move semantics

    // BEGIN General iterators
    enum TreeLastMovement {
      TREE_UNDEFINED = 0,
      TREE_TO_ROOT = 1,
      TREE_TO_NEXT_ANCESTOR = 2,
      TREE_TO_PREVIOUS_ANCESTOR = 3,
      TREE_TO_NEXT_LEAF = 4,
      TREE_TO_PREVIOUS_LEAF = 5,
      TREE_TO_PARENT = 6,
      TREE_TO_PREVIOUS_SIBLING = 7,
      TREE_TO_NEXT_SIBLING = 8,
      TREE_TO_FIRST_CHILD = 9,
      TREE_TO_LAST_CHILD = 10,
    };
  
    template <typename T_value>
    class iterator_t;

    template <typename T_value>
    class forward_iterator_t;

    template <typename T_value>
    class bidirectional_iterator_t;

    template <typename T_value>
    class free_iterator_t;
    // END General iterators

    // BEGIN BFS
    template <typename T_value>
    class bfs_iterator_t;

    // BFS iterator
    class bfs_iterator;
    inline bfs_iterator bfs_begin() const {
      return bfs_iterator::begin(_root);
    }
    inline bfs_iterator bfs_after_end() const {
      return bfs_iterator::after_end(_root);
    }
    tree_ranged_loop_bfs<T> bfs() const {
      return tree_ranged_loop_bfs<T>(*this);
    }

    // BFS const iterator
    class bfs_const_iterator;
    inline bfs_const_iterator bfs_cbegin() const {
      return bfs_const_iterator::begin(_root);
    }
    inline bfs_const_iterator bfs_cafter_end() const {
      return bfs_const_iterator::after_end(_root);
    }
    // END BFS

    // BEGIN DFS postorder
    // DFS postorder iterator
    template <typename T_value>
    class dfs_postorder_iterator_t;

    class dfs_postorder_iterator;
    inline dfs_postorder_iterator dfs_postorder_before_begin() const {
      return dfs_postorder_iterator::before_begin(_root);
    }
    inline dfs_postorder_iterator dfs_postorder_begin() const {
      return dfs_postorder_iterator::begin(_root);
    }
    inline dfs_postorder_iterator dfs_postorder_end() const {
      return dfs_postorder_iterator::end(_root);
    }
    inline dfs_postorder_iterator dfs_postorder_after_end() const {
      return dfs_postorder_iterator::after_end(_root);
    }

    // DFS postorder const iterator
    class dfs_postorder_const_iterator;
    inline dfs_postorder_const_iterator dfs_postorder_cbefore_begin() const {
      return dfs_postorder_const_iterator::before_begin(_root);
    }
    inline dfs_postorder_const_iterator dfs_postorder_cbegin() const {
      return dfs_postorder_const_iterator::begin(_root);
    }
    inline dfs_postorder_const_iterator dfs_postorder_cend() const {
      return dfs_postorder_const_iterator::end(_root);
    }
    inline dfs_postorder_const_iterator dfs_postorder_cafter_end() const {
      return dfs_postorder_const_iterator::after_end(_root);
    }

    // DFS postorder reverse iterator
    template <typename T_value>
    class dfs_postorder_reverse_iterator_t;

    class dfs_postorder_reverse_iterator;
    inline dfs_postorder_reverse_iterator dfs_postorder_rbefore_begin() const {
      return dfs_postorder_reverse_iterator::before_begin(_root);
    }
    inline dfs_postorder_reverse_iterator dfs_postorder_rbegin() const {
      return dfs_postorder_reverse_iterator::begin(_root);
    }
    inline dfs_postorder_reverse_iterator dfs_postorder_rend() const {
      return dfs_postorder_reverse_iterator::end(_root);
    }
    inline dfs_postorder_reverse_iterator dfs_postorder_rafter_end() const {
      return dfs_postorder_reverse_iterator::after_end(_root);
    }

    // DFS postorder const reverse iterator
    class dfs_postorder_const_reverse_iterator;
    inline dfs_postorder_const_reverse_iterator dfs_postorder_crbefore_begin() const {
      return dfs_postorder_const_reverse_iterator::before_begin(_root);
    }
    inline dfs_postorder_const_reverse_iterator dfs_postorder_crbegin() const {
      return dfs_postorder_const_reverse_iterator::begin(_root);
    }
    inline dfs_postorder_const_reverse_iterator dfs_postorder_crend() const {
      return dfs_postorder_const_reverse_iterator::end(_root);
    }
    inline dfs_postorder_const_reverse_iterator dfs_postorder_crafter_end() const {
      return dfs_postorder_const_reverse_iterator::after_end(_root);
    }
    // END DFS postorder

    // BEGIN DFS preorder
    // DFS preorder iterator
    template <typename T_value>
    class dfs_preorder_iterator_t;

    class dfs_preorder_iterator;
    inline dfs_preorder_iterator dfs_preorder_before_begin() const {
      return dfs_preorder_iterator::before_begin(_root);
    }
    inline dfs_preorder_iterator dfs_preorder_begin() const {
      return dfs_preorder_iterator::begin(_root);
    }
    inline dfs_preorder_iterator dfs_preorder_end() const {
      return dfs_preorder_iterator::end(_root);
    }
    inline dfs_preorder_iterator dfs_preorder_after_end() const {
      return dfs_preorder_iterator::after_end(_root);
    }

    // DFS preorder const iterator
    class dfs_preorder_const_iterator;
    inline dfs_preorder_const_iterator dfs_preorder_cbefore_begin() const {
      return dfs_preorder_const_iterator::before_begin(_root);
    }
    inline dfs_preorder_const_iterator dfs_preorder_cbegin() const {
      return dfs_preorder_const_iterator::begin(_root);
    }
    inline dfs_preorder_const_iterator dfs_preorder_cend() const {
      return dfs_preorder_const_iterator::end(_root);
    }
    inline dfs_preorder_const_iterator dfs_preorder_cafter_end() const {
      return dfs_preorder_const_iterator::after_end(_root);
    }

    // DFS preorder reverse iterator
    template <typename T_value>
    class dfs_preorder_reverse_iterator_t;

    class dfs_preorder_reverse_iterator;
    inline dfs_preorder_reverse_iterator dfs_preorder_rbefore_begin() const {
      return dfs_preorder_reverse_iterator::before_begin(_root);
    }
    inline dfs_preorder_reverse_iterator dfs_preorder_rbegin() const {
      return dfs_preorder_reverse_iterator::begin(_root);
    }
    inline dfs_preorder_reverse_iterator dfs_preorder_rend() const {
      return dfs_preorder_reverse_iterator::end(_root);
    }
    inline dfs_preorder_reverse_iterator dfs_preorder_rafter_end() const {
      return dfs_preorder_reverse_iterator::after_end(_root);
    }

    // DFS preorder const reverse iterator
    class dfs_preorder_const_reverse_iterator;
    inline dfs_preorder_const_reverse_iterator dfs_preorder_crbefore_begin() const {
      return dfs_preorder_const_reverse_iterator::before_begin(_root);
    }
    inline dfs_preorder_const_reverse_iterator dfs_preorder_crbegin() const {
      return dfs_preorder_const_reverse_iterator::begin(_root);
    }
    inline dfs_preorder_const_reverse_iterator dfs_preorder_crend() const {
      return dfs_preorder_const_reverse_iterator::end(_root);
    }
    inline dfs_preorder_const_reverse_iterator dfs_preorder_crafter_end() const {
      return dfs_preorder_const_reverse_iterator::after_end(_root);
    }
    // END DFS preorder

    // BEGIN Leaf
    // Leaf iterator
    template <typename T_value>
    class leaf_iterator_t;

    class leaf_iterator;
    inline leaf_iterator leaf_before_begin() const {
      return leaf_iterator::before_begin(_root);
    }
    inline leaf_iterator leaf_begin() const {
      return leaf_iterator::begin(_root);
    }
    inline leaf_iterator leaf_end() const {
      return leaf_iterator::end(_root);
    }
    inline leaf_iterator leaf_after_end() const {
      return leaf_iterator::after_end(_root);
    }

    // Leaf const iterator
    class leaf_const_iterator;
    inline leaf_const_iterator leaf_cbefore_begin() const {
      return leaf_const_iterator::before_begin(_root);
    }
    inline leaf_const_iterator leaf_cbegin() const {
      return leaf_const_iterator::begin(_root);
    }
    inline leaf_const_iterator leaf_cend() const {
      return leaf_const_iterator::end(_root);
    }
    inline leaf_const_iterator leaf_cafter_end() const {
      return leaf_const_iterator::after_end(_root);
    }

    // Leaf reverse iterator
    template <typename T_value>
    class leaf_reverse_iterator_t;

    class leaf_reverse_iterator;
    inline leaf_reverse_iterator leaf_rbefore_begin() const {
      return leaf_reverse_iterator::before_begin(_root);
    }
    inline leaf_reverse_iterator leaf_rbegin() const {
      return leaf_reverse_iterator::begin(_root);
    }
    inline leaf_reverse_iterator leaf_rend() const {
      return leaf_reverse_iterator::end(_root);
    }
    inline leaf_reverse_iterator leaf_rafter_end() const {
      return leaf_reverse_iterator::after_end(_root);
    }

    // Leaf const reverse iterator
    class leaf_const_reverse_iterator;
    inline leaf_const_reverse_iterator leaf_crbefore_begin() const {
      return leaf_const_reverse_iterator::before_begin(_root);
    }
    inline leaf_const_reverse_iterator leaf_crbegin() const {
      return leaf_const_reverse_iterator::begin(_root);
    }
    inline leaf_const_reverse_iterator leaf_crend() const {
      return leaf_const_reverse_iterator::end(_root);
    }
    inline leaf_const_reverse_iterator leaf_crafter_end() const {
      return leaf_const_reverse_iterator::after_end(_root);
    }
    // END Leaf

    // BEGIN XML
    // XML iterator
    template <typename T_value>
    class xml_iterator_t;

    class xml_iterator;
    inline xml_iterator xml_before_begin() const {
      return xml_iterator::before_begin(_root);
    }
    inline xml_iterator xml_begin() const {
      return xml_iterator::begin(_root);
    }
    inline xml_iterator xml_end() const {
      return xml_iterator::end(_root);
    }
    inline xml_iterator xml_after_end() const {
      return xml_iterator::after_end(_root);
    }

    // XML const iterator
    class xml_const_iterator;
    inline xml_const_iterator xml_cbefore_begin() const {
      return xml_const_iterator::before_begin(_root);
    }
    inline xml_const_iterator xml_cbegin() const {
      return xml_const_iterator::begin(_root);
    }
    inline xml_const_iterator xml_cend() const {
      return xml_const_iterator::end(_root);
    }
    inline xml_const_iterator xml_cafter_end() const {
      return xml_const_iterator::after_end(_root);
    }

    // XML reverse iterator
    template <typename T_value>
    class xml_reverse_iterator_t;

    class xml_reverse_iterator;
    inline xml_reverse_iterator xml_rbefore_begin() const {
      return xml_reverse_iterator::before_begin(_root);
    }
    inline xml_reverse_iterator xml_rbegin() const {
      return xml_reverse_iterator::begin(_root);
    }
    inline xml_reverse_iterator xml_rend() const {
      return xml_reverse_iterator::end(_root);
    }
    inline xml_reverse_iterator xml_rafter_end() const {
      return xml_reverse_iterator::after_end(_root);
    }

    // XML const reverse iterator
    class xml_const_reverse_iterator;
    inline xml_const_reverse_iterator xml_crbefore_begin() const {
      return xml_const_reverse_iterator::before_begin(_root);
    }
    inline xml_const_reverse_iterator xml_crbegin() const {
      return xml_const_reverse_iterator::begin(_root);
    }
    inline xml_const_reverse_iterator xml_crend() const {
      return xml_const_reverse_iterator::end(_root);
    }
    inline xml_const_reverse_iterator xml_crafter_end() const {
      return xml_const_reverse_iterator::after_end(_root);
    }
    // END XML

    // BEGIN subtree operations
    template <typename T_value>
    tree<T>* detach(const iterator_t<T_value>&);

    template <typename T_value>
    tree<T>* subtree_copy(const iterator_t<T_value>&) const;

  private:
    template <typename T_value>
    void insert_subtree_move(const iterator_t<T_value>&, tree<T>&, void (node<T>::*)(node<T>*)) const;

  public:
    template <typename T_value>
    void insert_previous_sibling_move(const iterator_t<T_value>&, tree<T>&) const;

    template <typename T_value>
    void insert_next_sibling_move(const iterator_t<T_value>&, tree<T>&) const;

    template <typename T_value>
    void insert_first_child_move(const iterator_t<T_value>&, tree<T>&) const;

    template <typename T_value>
    void insert_last_child_move(const iterator_t<T_value>&, tree<T>&) const;
    // END subtree operations

    // Used for testing that the trees are the same.
    static bool assert_isomorphic(const tree<T>&, const tree<T>&);

    // Used for testing the small loops and that it is a subtree.
    static bool is_consistent(const tree<T>&);

    template <typename T_value>
    friend class iterator_t;

    template <typename T_friend>
    friend class tree_ranged_loop_t;

    template <typename T_friend>
    friend class tree_ranged_loop_bfs;

    template <typename T_friend>
    friend std::ostream& operator<<(std::ostream&, const tree<T_friend>&);

#ifdef UNBOUNDED_ORDERED_TREE_TEST_TRACE
    void* operator new(size_t s) {
      void* p = malloc(s);
      tree_allocation_debug_stacktrace[p] = boost::stacktrace::to_string( boost::stacktrace::stacktrace() );
      return p;
    }

    void operator delete(void* p) {
      free(p);
      tree_allocation_debug_stacktrace.erase(p);
    }
#endif // UNBOUNDED_ORDERED_TREE_TEST_TRACE
  };
}

template <typename T>
std::ostream& operator<<(std::ostream&, const typename unbounded_ordered::tree<T>&);

#endif // UNBOUNDED_ORDERED_TREE_DECL_HPP