#ifndef UNBOUNDED_ORDERED_NODE_DECL_HPP
#define UNBOUNDED_ORDERED_NODE_DECL_HPP

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <typeinfo>

#ifdef TEST_TRACE
#include <boost/stacktrace/stacktrace.hpp>
#endif

namespace unbounded_ordered {
#ifdef TEST_TRACE
  static long mem_used = 0;
  static std::map<void*, std::string> debug_stacktrace;
#endif

  template <typename T>
  class node {
  public:
    // Traversals
    enum NodeLastMovement {
      NODE_UNDEFINED = 0,
      NODE_TO_ROOT = 1,
      NODE_TO_NEXT_ANCESTOR = 2,
      NODE_TO_PREVIOUS_ANCESTOR = 3,
      NODE_TO_NEXT_LEAF = 4,
      NODE_TO_PREVIOUS_LEAF = 5,
      NODE_TO_PARENT = 6,
      NODE_TO_PREVIOUS_SIBLING = 7,
      NODE_TO_NEXT_SIBLING = 8,
      NODE_TO_FIRST_CHILD = 9,
      NODE_TO_LAST_CHILD = 10,
    };

  private:
    node* _parent;
    T _data;
    node* _previous_sibling;
    node* _next_sibling;
    node* _first_child;
    node* _last_child;

  public:
    node();
    node(const T&, node* = nullptr, node* = nullptr, node* = nullptr, node* = nullptr, node* = nullptr);
    node(const T&, const std::list<node*>&);
    node(const T&, const std::initializer_list<node*>&);
    ~node();

    const T& get_data() const;
    T& get_data();

    node* get_parent() const;
    node* get_previous_sibling() const;
    node* get_next_sibling() const;
    node* get_first_child() const;
    node* get_leftmost_leaf() const;
    node* get_last_child() const;
    node* get_rightmost_leaf() const;

    bool is_leaf() const;
    bool is_root() const;

    std::size_t count_children() const;

    NodeLastMovement last_movement() const;

    void set_data(const T&);

    // BEGIN subtree operations
    node* copy_subtree() const;
    void delete_subtree();

    void insert_previous_sibling(node*);
    void insert_next_sibling(node*);
    void insert_first_child(node*);
    void insert_last_child(node*);

    void detach();
    // END subtree operations

    // DFS postorder
    std::pair<node*, NodeLastMovement> dfs_postorder_next() const;
    std::pair<node*, NodeLastMovement> dfs_postorder_previous() const;
    // DFS preorder
    std::pair<node*, NodeLastMovement> dfs_preorder_next() const;
    std::pair<node*, NodeLastMovement> dfs_preorder_previous() const;
    // Leaf
    std::pair<node*, NodeLastMovement> leaf_next() const;
    std::pair<node*, NodeLastMovement> leaf_previous() const;
    // XML
    std::pair<node*, NodeLastMovement> xml_next(NodeLastMovement) const;
    std::pair<node*, NodeLastMovement> xml_previous(NodeLastMovement) const;

    std::ostream& print_to_stream(std::ostream&) const;


  private:
    bool is_subtree_equal_aux(
      const node* const,
      std::map<const node* const, const node* const>&
    ) const;

    bool is_subtree_equal_bijection(
      const node* const,
      std::map<const node* const, const node* const>&,
      std::map<const node* const, const node* const>&
    ) const;

  public:
    // Used for testing that replicating a tree rooted in this was done properly.
    bool is_subtree_equal(
      const node* const,
      std::map<const node* const, const node* const>&,
      std::map<const node* const, const node* const>&,
      const std::string& = ""
    ) const;

    bool is_subtree_equal(
      const node* const,
      const std::string& = ""
    ) const;


    std::list<const node*> ancestors() const;
    const node* lowest_common_ancestor(const node*) const;


  private:
    // Used for testing that the pointers between `node` and its children are properly formed.
    // It tests the consistency of the smallest pointer-loops.
    // That way, it ensures the consistency of the bigger pointer-loops, since they all rely on these smaller loops.
    bool is_small_loop_consistent() const;

    // Used for testing the small loops in every node below `n`.
    bool is_big_loop_consistent() const;

  public:
    // Used for testing the small loops and that `node` is the root of a tree.
    bool is_subtree_consistent() const;


    template<typename U>
    U cumulative(U (*fun)(const T&, const std::list<U>&)) const;

    template<typename U, typename Context>
    U cumulative(U (*fun)(Context&, const T&, const std::list<U>&), Context&) const;


    template<typename U>
    node<U>* morphism(U (*fun)(const T&, const std::list<U>&)) const;

    template<typename U, typename Context>
    node<U>* morphism(U (*fun)(Context&, const T&, const std::list<U>&), Context& context) const;

    #ifdef TEST_TRACE
    void* operator new(size_t s) {
      ++mem_used;
      void* p = malloc(s);
      // std::cout << "New node " << typeid(T).name() << " at " << p << std::endl;
      // std::stringstream ss;
      // ss << boost::stacktrace::stacktrace();
      // debug_stacktrace[p] = ss.str();
      return p;
    }

    void operator delete(void* p) {
      // std::cout << "Delete node " << typeid(T).name() << " at " << p << std::endl;
      --mem_used;
      // debug_stacktrace.erase(p);
      free(p);
    }
    #endif
  };
}

#endif // UNBOUNDED_ORDERED_NODE_DECL_HPP