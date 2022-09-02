#include <boost/test/unit_test.hpp>
#include "unbounded_ordered_tree.hpp"

struct TreeSubtreeCopyTest {
  TreeSubtreeCopyTest() {}
  ~TreeSubtreeCopyTest() {}
};

BOOST_FIXTURE_TEST_SUITE( tree_subtree_copy_suite, TreeSubtreeCopyTest )

BOOST_AUTO_TEST_CASE( copy_then_delete ) {
  typedef unbounded_ordered::tree<int> treeint;

  treeint* tree = new treeint(5, {treeint(6, {treeint(0, {treeint(9)}), treeint(1)}), treeint(11, {treeint(4), treeint(3)}), treeint(2, {treeint(7), treeint(8, {treeint(10)})})});

  treeint::dfs_preorder_iterator it = tree->dfs_preorder_begin();

  ++it;
  ++it;
  ++it;
  ++it;
  ++it;

  BOOST_CHECK_EQUAL(11, *it);

  treeint* subtree = tree->subtree_copy(it);

  delete tree;

  treeint::dfs_preorder_iterator subit = subtree->dfs_preorder_begin();

  ++subit;

  BOOST_CHECK_EQUAL(4, *subit);

  delete subtree;
}

BOOST_AUTO_TEST_SUITE_END()
