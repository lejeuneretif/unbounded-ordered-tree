#ifndef UNBOUNDED_ORDERED_TREE_RANGED_ITERATOR_TPP
#define UNBOUNDED_ORDERED_TREE_RANGED_ITERATOR_TPP

#include "unbounded_ordered_tree.hpp"

namespace unbounded_ordered {
  // BEGIN Like std::begin, std::end and variations.
  // BFS iterators
  template<typename T>
  constexpr auto bfs_begin(tree<T>& t) -> decltype(t.bfs_begin()) { return t.bfs_begin(); }
  template<typename T>
  constexpr auto bfs_begin(const tree<T>& t) -> decltype(t.bfs_cbegin()) { return t.bfs_cbegin(); }
  template<typename T>
  constexpr auto bfs_cbegin(const tree<T>& t) noexcept -> decltype(bfs_begin(t)) { return bfs_begin(t); }

  template<typename T>
  constexpr auto bfs_after_end(tree<T>& t) -> decltype(t.bfs_after_end()) { return t.bfs_after_end(); }
  template<typename T>
  constexpr auto bfs_after_end(const tree<T>& t) -> decltype(t.bfs_cafter_end()) { return t.bfs_cafter_end(); }
  template<typename T>
  constexpr auto bfs_cafter_end(const tree<T>& t) noexcept -> decltype(bfs_after_end(t)) { return bfs_after_end(t); }
  // END BFS

  // BEGIN DFS postorder
  // DFS postorder iterator
  template<typename T>
  constexpr auto dfs_postorder_before_begin(tree<T>& t) -> decltype(t.dfs_postorder_before_begin()) { return t.dfs_postorder_before_begin(); }
  template<typename T>
  constexpr auto dfs_postorder_before_begin(const tree<T>& t) -> decltype(t.dfs_postorder_cbefore_begin()) { return t.dfs_postorder_cbefore_begin(); }
  template<typename T>
  constexpr auto dfs_postorder_cbefore_begin(const tree<T>& t) noexcept -> decltype(dfs_postorder_before_begin(t)) { return dfs_postorder_before_begin(t); }
  
  template<typename T>
  constexpr auto dfs_postorder_begin(tree<T>& t) -> decltype(t.dfs_postorder_begin()) { return t.dfs_postorder_begin(); }
  template<typename T>
  constexpr auto dfs_postorder_begin(const tree<T>& t) -> decltype(t.dfs_postorder_cbegin()) { return t.dfs_postorder_cbegin(); }
  template<typename T>
  constexpr auto dfs_postorder_cbegin(const tree<T>& t) noexcept -> decltype(dfs_postorder_begin(t)) { return dfs_postorder_begin(t); }

  template<typename T>
  constexpr auto dfs_postorder_end(tree<T>& t) -> decltype(t.dfs_postorder_end()) { return t.dfs_postorder_end(); }
  template<typename T>
  constexpr auto dfs_postorder_end(const tree<T>& t) -> decltype(t.dfs_postorder_cend()) { return t.dfs_postorder_cend(); }
  template<typename T>
  constexpr auto dfs_postorder_cend(const tree<T>& t) noexcept -> decltype(dfs_postorder_end(t)) { return dfs_postorder_end(t); }

  template<typename T>
  constexpr auto dfs_postorder_after_end(tree<T>& t) -> decltype(t.dfs_postorder_after_end()) { return t.dfs_postorder_after_end(); }
  template<typename T>
  constexpr auto dfs_postorder_after_end(const tree<T>& t) -> decltype(t.dfs_postorder_cafter_end()) { return t.dfs_postorder_cafter_end(); }
  template<typename T>
  constexpr auto dfs_postorder_cafter_end(const tree<T>& t) noexcept -> decltype(dfs_postorder_after_end(t)) { return dfs_postorder_after_end(t); }

  // DFS postorder reverse iterator
  template<typename T>
  constexpr auto dfs_postorder_rbefore_begin(tree<T>& t) -> decltype(t.dfs_postorder_rbefore_begin()) { return t.dfs_postorder_rbefore_begin(); }
  template<typename T>
  constexpr auto dfs_postorder_rbefore_begin(const tree<T>& t) -> decltype(t.dfs_postorder_crbefore_begin()) { return t.dfs_postorder_crbefore_begin(); }
  template<typename T>
  constexpr auto dfs_postorder_crbefore_begin(const tree<T>& t) noexcept -> decltype(dfs_postorder_rbefore_begin(t)) { return dfs_postorder_rbefore_begin(t); }
  
  template<typename T>
  constexpr auto dfs_postorder_r_begin(tree<T>& t) -> decltype(t.dfs_postorder_rbegin()) { return t.dfs_postorder_rbegin(); }
  template<typename T>
  constexpr auto dfs_postorder_rbegin(const tree<T>& t) -> decltype(t.dfs_postorder_crbegin()) { return t.dfs_postorder_crbegin(); }
  template<typename T>
  constexpr auto dfs_postorder_crbegin(const tree<T>& t) noexcept -> decltype(dfs_postorder_rbegin(t)) { return dfs_postorder_rbegin(t); }

  template<typename T>
  constexpr auto dfs_postorder_rend(tree<T>& t) -> decltype(t.dfs_postorder_rend()) { return t.dfs_postorder_rend(); }
  template<typename T>
  constexpr auto dfs_postorder_rend(const tree<T>& t) -> decltype(t.dfs_postorder_crend()) { return t.dfs_postorder_crend(); }
  template<typename T>
  constexpr auto dfs_postorder_crend(const tree<T>& t) noexcept -> decltype(dfs_postorder_rend(t)) { return dfs_postorder_rend(t); }

  template<typename T>
  constexpr auto dfs_postorder_rafter_end(tree<T>& t) -> decltype(t.dfs_postorder_rafter_end()) { return t.dfs_postorder_after_rend(); }
  template<typename T>
  constexpr auto dfs_postorder_rafter_end(const tree<T>& t) -> decltype(t.dfs_postorder_crafter_end()) { return t.dfs_postorder_cafter_rend(); }
  template<typename T>
  constexpr auto dfs_postorder_crafter_end(const tree<T>& t) noexcept -> decltype(dfs_postorder_rafter_end(t)) { return dfs_postorder_after_rend(t); }
  // END DFS postorder

  // BEGIN DFS preorder
  // DFS preorder iterator
  template<typename T>
  constexpr auto dfs_preorder_before_begin(tree<T>& t) -> decltype(t.dfs_preorder_before_begin()) { return t.dfs_preorder_before_begin(); }
  template<typename T>
  constexpr auto dfs_preorder_before_begin(const tree<T>& t) -> decltype(t.dfs_preorder_cbefore_begin()) { return t.dfs_preorder_cbefore_begin(); }
  template<typename T>
  constexpr auto dfs_preorder_cbefore_begin(const tree<T>& t) noexcept -> decltype(dfs_preorder_before_begin(t)) { return dfs_preorder_before_begin(t); }
  
  template<typename T>
  constexpr auto dfs_preorder_begin(tree<T>& t) -> decltype(t.dfs_preorder_begin()) { return t.dfs_preorder_begin(); }
  template<typename T>
  constexpr auto dfs_preorder_begin(const tree<T>& t) -> decltype(t.dfs_preorder_cbegin()) { return t.dfs_preorder_cbegin(); }
  template<typename T>
  constexpr auto dfs_preorder_cbegin(const tree<T>& t) noexcept -> decltype(dfs_preorder_begin(t)) { return dfs_preorder_begin(t); }

  template<typename T>
  constexpr auto dfs_preorder_end(tree<T>& t) -> decltype(t.dfs_preorder_end()) { return t.dfs_preorder_end(); }
  template<typename T>
  constexpr auto dfs_preorder_end(const tree<T>& t) -> decltype(t.dfs_preorder_cend()) { return t.dfs_preorder_cend(); }
  template<typename T>
  constexpr auto dfs_preorder_cend(const tree<T>& t) noexcept -> decltype(dfs_preorder_end(t)) { return dfs_preorder_end(t); }

  template<typename T>
  constexpr auto dfs_preorder_after_end(tree<T>& t) -> decltype(t.dfs_preorder_after_end()) { return t.dfs_preorder_after_end(); }
  template<typename T>
  constexpr auto dfs_preorder_after_end(const tree<T>& t) -> decltype(t.dfs_preorder_cafter_end()) { return t.dfs_preorder_cafter_end(); }
  template<typename T>
  constexpr auto dfs_preorder_cafter_end(const tree<T>& t) noexcept -> decltype(dfs_preorder_after_end(t)) { return dfs_preorder_after_end(t); }

  // DFS preorder reverse iterator
  template<typename T>
  constexpr auto dfs_preorder_rbefore_begin(tree<T>& t) -> decltype(t.dfs_preorder_rbefore_begin()) { return t.dfs_preorder_rbefore_begin(); }
  template<typename T>
  constexpr auto dfs_preorder_rbefore_begin(const tree<T>& t) -> decltype(t.dfs_preorder_crbefore_begin()) { return t.dfs_preorder_crbefore_begin(); }
  template<typename T>
  constexpr auto dfs_preorder_crbefore_begin(const tree<T>& t) noexcept -> decltype(dfs_preorder_rbefore_begin(t)) { return dfs_preorder_rbefore_begin(t); }
  
  template<typename T>
  constexpr auto dfs_preorder_r_begin(tree<T>& t) -> decltype(t.dfs_preorder_rbegin()) { return t.dfs_preorder_rbegin(); }
  template<typename T>
  constexpr auto dfs_preorder_rbegin(const tree<T>& t) -> decltype(t.dfs_preorder_crbegin()) { return t.dfs_preorder_crbegin(); }
  template<typename T>
  constexpr auto dfs_preorder_crbegin(const tree<T>& t) noexcept -> decltype(dfs_preorder_rbegin(t)) { return dfs_preorder_rbegin(t); }

  template<typename T>
  constexpr auto dfs_preorder_rend(tree<T>& t) -> decltype(t.dfs_preorder_rend()) { return t.dfs_preorder_rend(); }
  template<typename T>
  constexpr auto dfs_preorder_rend(const tree<T>& t) -> decltype(t.dfs_preorder_crend()) { return t.dfs_preorder_crend(); }
  template<typename T>
  constexpr auto dfs_preorder_crend(const tree<T>& t) noexcept -> decltype(dfs_preorder_rend(t)) { return dfs_preorder_rend(t); }

  template<typename T>
  constexpr auto dfs_preorder_rafter_end(tree<T>& t) -> decltype(t.dfs_preorder_rafter_end()) { return t.dfs_preorder_after_rend(); }
  template<typename T>
  constexpr auto dfs_preorder_rafter_end(const tree<T>& t) -> decltype(t.dfs_preorder_crafter_end()) { return t.dfs_preorder_cafter_rend(); }
  template<typename T>
  constexpr auto dfs_preorder_crafter_end(const tree<T>& t) noexcept -> decltype(dfs_preorder_rafter_end(t)) { return dfs_preorder_after_rend(t); }
  // END DFS preorder

  // BEGIN Leaf
  // Leaf iterator
  template<typename T>
  constexpr auto leaf_before_begin(tree<T>& t) -> decltype(t.leaf_before_begin()) { return t.leaf_before_begin(); }
  template<typename T>
  constexpr auto leaf_before_begin(const tree<T>& t) -> decltype(t.leaf_cbefore_begin()) { return t.leaf_cbefore_begin(); }
  template<typename T>
  constexpr auto leaf_cbefore_begin(const tree<T>& t) noexcept -> decltype(leaf_before_begin(t)) { return leaf_before_begin(t); }
  
  template<typename T>
  constexpr auto leaf_begin(tree<T>& t) -> decltype(t.leaf_begin()) { return t.leaf_begin(); }
  template<typename T>
  constexpr auto leaf_begin(const tree<T>& t) -> decltype(t.leaf_cbegin()) { return t.leaf_cbegin(); }
  template<typename T>
  constexpr auto leaf_cbegin(const tree<T>& t) noexcept -> decltype(leaf_begin(t)) { return leaf_begin(t); }

  template<typename T>
  constexpr auto leaf_end(tree<T>& t) -> decltype(t.leaf_end()) { return t.leaf_end(); }
  template<typename T>
  constexpr auto leaf_end(const tree<T>& t) -> decltype(t.leaf_cend()) { return t.leaf_cend(); }
  template<typename T>
  constexpr auto leaf_cend(const tree<T>& t) noexcept -> decltype(leaf_end(t)) { return leaf_end(t); }

  template<typename T>
  constexpr auto leaf_after_end(tree<T>& t) -> decltype(t.leaf_after_end()) { return t.leaf_after_end(); }
  template<typename T>
  constexpr auto leaf_after_end(const tree<T>& t) -> decltype(t.leaf_cafter_end()) { return t.leaf_cafter_end(); }
  template<typename T>
  constexpr auto leaf_cafter_end(const tree<T>& t) noexcept -> decltype(leaf_after_end(t)) { return leaf_after_end(t); }

  // Leaf reverse iterator
  template<typename T>
  constexpr auto leaf_rbefore_begin(tree<T>& t) -> decltype(t.leaf_rbefore_begin()) { return t.leaf_rbefore_begin(); }
  template<typename T>
  constexpr auto leaf_rbefore_begin(const tree<T>& t) -> decltype(t.leaf_crbefore_begin()) { return t.leaf_crbefore_begin(); }
  template<typename T>
  constexpr auto leaf_crbefore_begin(const tree<T>& t) noexcept -> decltype(leaf_rbefore_begin(t)) { return leaf_rbefore_begin(t); }
  
  template<typename T>
  constexpr auto leaf_r_begin(tree<T>& t) -> decltype(t.leaf_rbegin()) { return t.leaf_rbegin(); }
  template<typename T>
  constexpr auto leaf_rbegin(const tree<T>& t) -> decltype(t.leaf_crbegin()) { return t.leaf_crbegin(); }
  template<typename T>
  constexpr auto leaf_crbegin(const tree<T>& t) noexcept -> decltype(leaf_rbegin(t)) { return leaf_rbegin(t); }

  template<typename T>
  constexpr auto leaf_rend(tree<T>& t) -> decltype(t.leaf_rend()) { return t.leaf_rend(); }
  template<typename T>
  constexpr auto leaf_rend(const tree<T>& t) -> decltype(t.leaf_crend()) { return t.leaf_crend(); }
  template<typename T>
  constexpr auto leaf_crend(const tree<T>& t) noexcept -> decltype(leaf_rend(t)) { return leaf_rend(t); }

  template<typename T>
  constexpr auto leaf_rafter_end(tree<T>& t) -> decltype(t.leaf_rafter_end()) { return t.leaf_after_rend(); }
  template<typename T>
  constexpr auto leaf_rafter_end(const tree<T>& t) -> decltype(t.leaf_crafter_end()) { return t.leaf_cafter_rend(); }
  template<typename T>
  constexpr auto leaf_crafter_end(const tree<T>& t) noexcept -> decltype(leaf_rafter_end(t)) { return leaf_after_rend(t); }
  // END Leaf

  // BEGIN XML
  // XML iterator
  template<typename T>
  constexpr auto xml_before_begin(tree<T>& t) -> decltype(t.xml_before_begin()) { return t.xml_before_begin(); }
  template<typename T>
  constexpr auto xml_before_begin(const tree<T>& t) -> decltype(t.xml_cbefore_begin()) { return t.xml_cbefore_begin(); }
  template<typename T>
  constexpr auto xml_cbefore_begin(const tree<T>& t) noexcept -> decltype(xml_before_begin(t)) { return xml_before_begin(t); }
  
  template<typename T>
  constexpr auto xml_begin(tree<T>& t) -> decltype(t.xml_begin()) { return t.xml_begin(); }
  template<typename T>
  constexpr auto xml_begin(const tree<T>& t) -> decltype(t.xml_cbegin()) { return t.xml_cbegin(); }
  template<typename T>
  constexpr auto xml_cbegin(const tree<T>& t) noexcept -> decltype(xml_begin(t)) { return xml_begin(t); }

  template<typename T>
  constexpr auto xml_end(tree<T>& t) -> decltype(t.xml_end()) { return t.xml_end(); }
  template<typename T>
  constexpr auto xml_end(const tree<T>& t) -> decltype(t.xml_cend()) { return t.xml_cend(); }
  template<typename T>
  constexpr auto xml_cend(const tree<T>& t) noexcept -> decltype(xml_end(t)) { return xml_end(t); }

  template<typename T>
  constexpr auto xml_after_end(tree<T>& t) -> decltype(t.xml_after_end()) { return t.xml_after_end(); }
  template<typename T>
  constexpr auto xml_after_end(const tree<T>& t) -> decltype(t.xml_cafter_end()) { return t.xml_cafter_end(); }
  template<typename T>
  constexpr auto xml_cafter_end(const tree<T>& t) noexcept -> decltype(xml_after_end(t)) { return xml_after_end(t); }

  // XML reverse iterator
  template<typename T>
  constexpr auto xml_rbefore_begin(tree<T>& t) -> decltype(t.xml_rbefore_begin()) { return t.xml_rbefore_begin(); }
  template<typename T>
  constexpr auto xml_rbefore_begin(const tree<T>& t) -> decltype(t.xml_crbefore_begin()) { return t.xml_crbefore_begin(); }
  template<typename T>
  constexpr auto xml_crbefore_begin(const tree<T>& t) noexcept -> decltype(xml_rbefore_begin(t)) { return xml_rbefore_begin(t); }
  
  template<typename T>
  constexpr auto xml_r_begin(tree<T>& t) -> decltype(t.xml_rbegin()) { return t.xml_rbegin(); }
  template<typename T>
  constexpr auto xml_rbegin(const tree<T>& t) -> decltype(t.xml_crbegin()) { return t.xml_crbegin(); }
  template<typename T>
  constexpr auto xml_crbegin(const tree<T>& t) noexcept -> decltype(xml_rbegin(t)) { return xml_rbegin(t); }

  template<typename T>
  constexpr auto xml_rend(tree<T>& t) -> decltype(t.xml_rend()) { return t.xml_rend(); }
  template<typename T>
  constexpr auto xml_rend(const tree<T>& t) -> decltype(t.xml_crend()) { return t.xml_crend(); }
  template<typename T>
  constexpr auto xml_crend(const tree<T>& t) noexcept -> decltype(xml_rend(t)) { return xml_rend(t); }

  template<typename T>
  constexpr auto xml_rafter_end(tree<T>& t) -> decltype(t.xml_rafter_end()) { return t.xml_after_rend(); }
  template<typename T>
  constexpr auto xml_rafter_end(const tree<T>& t) -> decltype(t.xml_crafter_end()) { return t.xml_cafter_rend(); }
  template<typename T>
  constexpr auto xml_crafter_end(const tree<T>& t) noexcept -> decltype(xml_rafter_end(t)) { return xml_after_rend(t); }
  // END XML
  // END Like std::begin, std::end and variations.
}

#endif // UNBOUNDED_ORDERED_TREE_RANGED_ITERATOR_TPP