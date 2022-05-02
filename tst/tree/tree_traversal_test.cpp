#include <boost/test/unit_test.hpp>
#include "unbounded_ordered_tree.hpp"

struct TreeTraversalTest {
  typedef unbounded_ordered::tree<int> treeint;
  treeint* tree;

  typedef treeint::TreeLastMovement tree_last_movement;

  const int count_nodes = 9;
  const int count_leaves = 5;
  const int count_xml_nodes = 13;

  const int bfs_traversal[9] = {5, 6, 1, 2, 4, 3, 7, 8, 9};

  const int dfs_postorder_traversal[9] = {6, 4, 3, 1, 7, 9, 8, 2, 5};
  const tree_last_movement dfs_postorder_last_movement[9] = {
    treeint::TREE_UNDEFINED,
    treeint::TREE_TO_NEXT_LEAF,
    treeint::TREE_TO_NEXT_LEAF,
    treeint::TREE_TO_PARENT,
    treeint::TREE_TO_NEXT_LEAF,
    treeint::TREE_TO_NEXT_LEAF,
    treeint::TREE_TO_PARENT,
    treeint::TREE_TO_PARENT,
    treeint::TREE_TO_PARENT,
  };

  const int dfs_postorder_backwards_traversal[9] = {5, 2, 8, 9, 7, 1, 3, 4, 6};
  const tree_last_movement dfs_postorder_backwards_last_movement[9] = {
    treeint::TREE_UNDEFINED,
    treeint::TREE_TO_LAST_CHILD,
    treeint::TREE_TO_LAST_CHILD,
    treeint::TREE_TO_LAST_CHILD,
    treeint::TREE_TO_PREVIOUS_ANCESTOR,
    treeint::TREE_TO_PREVIOUS_ANCESTOR,
    treeint::TREE_TO_LAST_CHILD,
    treeint::TREE_TO_PREVIOUS_ANCESTOR,
    treeint::TREE_TO_PREVIOUS_ANCESTOR,
  };

  const int dfs_preorder_traversal[9] = {5, 6, 1, 4, 3, 2, 7, 8, 9};
  const tree_last_movement dfs_preorder_last_movement[9] = {
    treeint::TREE_UNDEFINED,
    treeint::TREE_TO_FIRST_CHILD,
    treeint::TREE_TO_NEXT_ANCESTOR,
    treeint::TREE_TO_FIRST_CHILD,
    treeint::TREE_TO_NEXT_ANCESTOR,
    treeint::TREE_TO_NEXT_ANCESTOR,
    treeint::TREE_TO_FIRST_CHILD,
    treeint::TREE_TO_NEXT_ANCESTOR,
    treeint::TREE_TO_FIRST_CHILD,
  };

  const int dfs_preorder_backwards_traversal[9] = {9, 8, 7, 2, 3, 4, 1, 6, 5};
  const tree_last_movement dfs_preorder_backwards_last_movement[9] = {
    treeint::TREE_UNDEFINED,
    treeint::TREE_TO_PARENT,
    treeint::TREE_TO_PREVIOUS_LEAF,
    treeint::TREE_TO_PARENT,
    treeint::TREE_TO_PREVIOUS_LEAF,
    treeint::TREE_TO_PREVIOUS_LEAF,
    treeint::TREE_TO_PARENT,
    treeint::TREE_TO_PREVIOUS_LEAF,
    treeint::TREE_TO_PARENT,
  };

  const int leaf_traversal[5] = {6, 4, 3, 7, 9};
  const tree_last_movement leaf_last_movement[5] = {
    treeint::TREE_UNDEFINED,
    treeint::TREE_TO_NEXT_LEAF,
    treeint::TREE_TO_NEXT_LEAF,
    treeint::TREE_TO_NEXT_LEAF,
    treeint::TREE_TO_NEXT_LEAF,
  };

  const int leaf_backwards_traversal[5] = {9, 7, 3, 4, 6};
  const tree_last_movement leaf_backwards_last_movement[5] = {
    treeint::TREE_UNDEFINED,
    treeint::TREE_TO_PREVIOUS_LEAF,
    treeint::TREE_TO_PREVIOUS_LEAF,
    treeint::TREE_TO_PREVIOUS_LEAF,
    treeint::TREE_TO_PREVIOUS_LEAF,
  };

  const int xml_traversal[13] = {5, 6, 1, 4, 3, 1, 2, 7, 8, 9, 8, 2, 5};
  const tree_last_movement xml_last_movement[13] = {
    treeint::TREE_UNDEFINED,
    treeint::TREE_TO_FIRST_CHILD,
    treeint::TREE_TO_NEXT_SIBLING,
    treeint::TREE_TO_FIRST_CHILD,
    treeint::TREE_TO_NEXT_SIBLING,
    treeint::TREE_TO_PARENT,
    treeint::TREE_TO_NEXT_SIBLING,
    treeint::TREE_TO_FIRST_CHILD,
    treeint::TREE_TO_NEXT_SIBLING,
    treeint::TREE_TO_FIRST_CHILD,
    treeint::TREE_TO_PARENT,
    treeint::TREE_TO_PARENT,
    treeint::TREE_TO_PARENT,
  };

  const int xml_backwards_traversal[13] = {5, 2, 8, 9, 8, 7, 2, 1, 3, 4, 1, 6, 5};
  const tree_last_movement xml_backwards_last_movement[13] = {
    treeint::TREE_UNDEFINED,
    treeint::TREE_TO_LAST_CHILD,
    treeint::TREE_TO_LAST_CHILD,
    treeint::TREE_TO_LAST_CHILD,
    treeint::TREE_TO_PARENT,
    treeint::TREE_TO_PREVIOUS_SIBLING,
    treeint::TREE_TO_PARENT,
    treeint::TREE_TO_PREVIOUS_SIBLING,
    treeint::TREE_TO_LAST_CHILD,
    treeint::TREE_TO_PREVIOUS_SIBLING,
    treeint::TREE_TO_PARENT,
    treeint::TREE_TO_PREVIOUS_SIBLING,
    treeint::TREE_TO_PARENT,
  };

  static std::string last_movement_to_string(tree_last_movement treeLastMovement) {
    switch(treeLastMovement) {
      case treeint::TREE_UNDEFINED: return "TREE_UNDEFINED";
      case treeint::TREE_TO_ROOT: return "TREE_TO_ROOT";
      case treeint::TREE_TO_NEXT_ANCESTOR: return "TREE_TO_NEXT_ANCESTOR";
      case treeint::TREE_TO_PREVIOUS_ANCESTOR: return "TREE_TO_PREVIOUS_ANCESTOR";
      case treeint::TREE_TO_NEXT_LEAF: return "TREE_TO_NEXT_LEAF";
      case treeint::TREE_TO_PREVIOUS_LEAF: return "TREE_TO_PREVIOUS_LEAF";
      case treeint::TREE_TO_PARENT: return "TREE_TO_PARENT";
      case treeint::TREE_TO_PREVIOUS_SIBLING: return "TREE_TO_PREVIOUS_SIBLING";
      case treeint::TREE_TO_NEXT_SIBLING: return "TREE_TO_NEXT_SIBLING";
      case treeint::TREE_TO_FIRST_CHILD: return "TREE_TO_FIRST_CHILD";
      case treeint::TREE_TO_LAST_CHILD: return "TREE_TO_LAST_CHILD";
      default: return "BAD";
    }
  }

  template<class ForwardIterator>
  void test_traversal_forward(const ForwardIterator& start, const ForwardIterator& end,
      const int* const values, int length) {
    int i = 0;
    for(ForwardIterator it = start; it != end; ++it, ++i) {
      BOOST_CHECK_EQUAL(values[i], *it);
    }

    BOOST_CHECK_EQUAL(length, i);
  }

  template<class ForwardIterator>
  void test_traversal_forward_movement(const ForwardIterator& start, const ForwardIterator& end,
      const int* const values, const tree_last_movement* const last_movements, int length) {
    int i = 0;
    for(ForwardIterator it = start; it != end; ++it, ++i) {
      BOOST_CHECK_EQUAL(values[i], *it);
      BOOST_CHECK_EQUAL(last_movements[i], it.get_last_movement());
    }

    BOOST_CHECK_EQUAL(length, i);
  }

  template<class BackwardIterator>
  void test_traversal_backward_movement(const BackwardIterator& start, const BackwardIterator& end,
      const int* const values, const tree_last_movement* const last_movements, int length) {
    int i = 0;
    for(BackwardIterator it = start; it != end; --it, ++i) {
      BOOST_CHECK_EQUAL(values[i], *it);
      BOOST_CHECK_EQUAL(last_movements[i], it.get_last_movement());
    }

    BOOST_CHECK_EQUAL(length, i);
  }

  TreeTraversalTest() {
    tree = new treeint(5, {treeint(6), treeint(1, {treeint(4), treeint(3)}), treeint(2, {treeint(7), treeint(8, {treeint(9)})})});
  }
  ~TreeTraversalTest() {
    delete tree;
  }
};

BOOST_FIXTURE_TEST_SUITE( tree_traversal_suite, TreeTraversalTest )

BOOST_AUTO_TEST_CASE( bfs ) {
  test_traversal_forward<unbounded_ordered::tree<int>::bfs_iterator>(
    tree->bfs_begin(), tree->bfs_after_end(), bfs_traversal, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( const_bfs ) {
  test_traversal_forward<unbounded_ordered::tree<int>::bfs_const_iterator>(
    tree->bfs_cbegin(), tree->bfs_cafter_end(), bfs_traversal, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( dfs_postorder ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::dfs_postorder_iterator>(
    tree->dfs_postorder_begin(), tree->dfs_postorder_after_end(),
    dfs_postorder_traversal, dfs_postorder_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( const_dfs_postorder ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::dfs_postorder_const_iterator>(
    tree->dfs_postorder_cbegin(), tree->dfs_postorder_cafter_end(),
    dfs_postorder_traversal, dfs_postorder_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( reverse_dfs_postorder ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::dfs_postorder_reverse_iterator>(
    tree->dfs_postorder_rbegin(), tree->dfs_postorder_rafter_end(),
    dfs_postorder_backwards_traversal, dfs_postorder_backwards_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( const_reverse_dfs_postorder ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::dfs_postorder_const_reverse_iterator>(
    tree->dfs_postorder_crbegin(), tree->dfs_postorder_crafter_end(),
    dfs_postorder_backwards_traversal, dfs_postorder_backwards_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( dfs_postorder_backwards) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::dfs_postorder_iterator>(
    tree->dfs_postorder_end(), tree->dfs_postorder_before_begin(),
    dfs_postorder_backwards_traversal, dfs_postorder_backwards_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( const_dfs_postorder_backwards ) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::dfs_postorder_const_iterator>(
    tree->dfs_postorder_cend(), tree->dfs_postorder_cbefore_begin(),
    dfs_postorder_backwards_traversal, dfs_postorder_backwards_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( reverse_dfs_postorder_backwards ) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::dfs_postorder_reverse_iterator>(
    tree->dfs_postorder_rend(), tree->dfs_postorder_rbefore_begin(),
    dfs_postorder_traversal, dfs_postorder_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( const_reverse_dfs_postorder_backwards ) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::dfs_postorder_const_reverse_iterator>(
    tree->dfs_postorder_crend(), tree->dfs_postorder_crbefore_begin(),
    dfs_postorder_traversal, dfs_postorder_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( dfs_preorder ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::dfs_preorder_iterator>(
    tree->dfs_preorder_begin(), tree->dfs_preorder_after_end(),
    dfs_preorder_traversal, dfs_preorder_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( const_dfs_preorder ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::dfs_preorder_const_iterator>(
    tree->dfs_preorder_cbegin(), tree->dfs_preorder_cafter_end(),
    dfs_preorder_traversal, dfs_preorder_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( reverse_dfs_preorder ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::dfs_preorder_reverse_iterator>(
    tree->dfs_preorder_rbegin(), tree->dfs_preorder_rafter_end(),
    dfs_preorder_backwards_traversal, dfs_preorder_backwards_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( const_reverse_dfs_preorder ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::dfs_preorder_const_reverse_iterator>(
    tree->dfs_preorder_crbegin(), tree->dfs_preorder_crafter_end(),
    dfs_preorder_backwards_traversal, dfs_preorder_backwards_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( dfs_preorder_backwards ) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::dfs_preorder_iterator>(
    tree->dfs_preorder_end(), tree->dfs_preorder_before_begin(),
    dfs_preorder_backwards_traversal, dfs_preorder_backwards_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( const_dfs_preorder_backwards ) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::dfs_preorder_const_iterator>(
    tree->dfs_preorder_cend(), tree->dfs_preorder_cbefore_begin(),
    dfs_preorder_backwards_traversal, dfs_preorder_backwards_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( reverse_dfs_preorder_backwards ) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::dfs_preorder_reverse_iterator>(
    tree->dfs_preorder_rend(), tree->dfs_preorder_rbefore_begin(),
    dfs_preorder_traversal, dfs_preorder_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( const_reverse_dfs_preorder_backwards ) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::dfs_preorder_const_reverse_iterator>(
    tree->dfs_preorder_crend(), tree->dfs_preorder_crbefore_begin(),
    dfs_preorder_traversal, dfs_preorder_last_movement, count_nodes
  );
}

BOOST_AUTO_TEST_CASE( leaf ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::leaf_iterator>(
    tree->leaf_begin(), tree->leaf_after_end(),
    leaf_traversal, leaf_last_movement, count_leaves
  );
}

BOOST_AUTO_TEST_CASE( const_leaf ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::leaf_const_iterator>(
    tree->leaf_cbegin(), tree->leaf_cafter_end(),
    leaf_traversal, leaf_last_movement, count_leaves
  );
}

BOOST_AUTO_TEST_CASE( reverse_leaf ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::leaf_reverse_iterator>(
    tree->leaf_rbegin(), tree->leaf_rafter_end(),
    leaf_backwards_traversal, leaf_backwards_last_movement, count_leaves
  );
}

BOOST_AUTO_TEST_CASE( const_reverse_leaf ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::leaf_const_reverse_iterator>(
    tree->leaf_crbegin(), tree->leaf_crafter_end(),
    leaf_backwards_traversal, leaf_backwards_last_movement, count_leaves
  );
}

BOOST_AUTO_TEST_CASE( leaf_backwards ) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::leaf_iterator>(
    tree->leaf_end(), tree->leaf_before_begin(),
    leaf_backwards_traversal, leaf_backwards_last_movement, count_leaves
  );
}

BOOST_AUTO_TEST_CASE( const_leaf_backwards ) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::leaf_const_iterator>(
    tree->leaf_cend(), tree->leaf_cbefore_begin(),
    leaf_backwards_traversal, leaf_backwards_last_movement, count_leaves
  );
}

BOOST_AUTO_TEST_CASE( reverse_leaf_backwards ) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::leaf_reverse_iterator>(
    tree->leaf_rend(), tree->leaf_rbefore_begin(),
    leaf_traversal, leaf_last_movement, count_leaves
  );
}

BOOST_AUTO_TEST_CASE( const_reverse_leaf_backwards ) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::leaf_const_reverse_iterator>(
    tree->leaf_crend(), tree->leaf_crbefore_begin(),
    leaf_traversal, leaf_last_movement, count_leaves
  );
}

BOOST_AUTO_TEST_CASE( xml ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::xml_iterator>(
    tree->xml_begin(), tree->xml_after_end(),
    xml_traversal, xml_last_movement, count_xml_nodes
  );
}

BOOST_AUTO_TEST_CASE( const_xml ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::xml_const_iterator>(
    tree->xml_cbegin(), tree->xml_cafter_end(),
    xml_traversal, xml_last_movement, count_xml_nodes
  );
}

BOOST_AUTO_TEST_CASE( reverse_xml ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::xml_reverse_iterator>(
    tree->xml_rbegin(), tree->xml_rafter_end(),
    xml_backwards_traversal, xml_backwards_last_movement, count_xml_nodes
  );
}

BOOST_AUTO_TEST_CASE( const_reverse_xml ) {
  test_traversal_forward_movement<unbounded_ordered::tree<int>::xml_const_reverse_iterator>(
    tree->xml_crbegin(), tree->xml_crafter_end(),
    xml_backwards_traversal, xml_backwards_last_movement, count_xml_nodes
  );
}

BOOST_AUTO_TEST_CASE( xml_backwards ) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::xml_iterator>(
    tree->xml_end(), tree->xml_before_begin(),
    xml_backwards_traversal, xml_backwards_last_movement, count_xml_nodes
  );
}

BOOST_AUTO_TEST_CASE( const_xml_backwards ) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::xml_const_iterator>(
    tree->xml_cend(), tree->xml_cbefore_begin(),
    xml_backwards_traversal, xml_backwards_last_movement, count_xml_nodes
  );
}

BOOST_AUTO_TEST_CASE( reverse_xml_backwards ) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::xml_reverse_iterator>(
    tree->xml_rend(), tree->xml_rbefore_begin(),
    xml_traversal, xml_last_movement, count_xml_nodes
  );
}

BOOST_AUTO_TEST_CASE( const_reverse_xml_backwards ) {
  test_traversal_backward_movement<unbounded_ordered::tree<int>::xml_const_reverse_iterator>(
    tree->xml_crbegin(), tree->xml_crafter_end(),
    xml_traversal, xml_last_movement, count_xml_nodes
  );
}

BOOST_AUTO_TEST_SUITE_END()
