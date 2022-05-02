#include <boost/test/unit_test.hpp>
#include "unbounded_ordered_tree.hpp"

struct TreeSubtreeDetachTest {
  typedef unbounded_ordered::tree<int> treeint;

  TreeSubtreeDetachTest() {}
  ~TreeSubtreeDetachTest() {}
};

BOOST_FIXTURE_TEST_SUITE( tree_subtree_detach_suite, TreeSubtreeDetachTest )

BOOST_AUTO_TEST_CASE( detach_root_then_delete ) {
  treeint* tree = new treeint(5, {treeint(6, {treeint(0, {treeint(9)}), treeint(1)}), treeint(11, {treeint(4), treeint(3)}), treeint(2, {treeint(7), treeint(8, {treeint(10)})})});

  treeint::dfs_preorder_iterator it = tree->dfs_preorder_begin();

  treeint* other = tree->detach(it);

  BOOST_CHECK(tree->is_empty());

  delete tree;

  treeint::xml_iterator it2 = other->xml_begin();

  BOOST_CHECK_EQUAL(5, *it2);

  BOOST_CHECK(! other->is_empty());

  delete other;
}

BOOST_AUTO_TEST_CASE( detach_inside_then_delete ) {
  treeint* tree = new treeint(5, {treeint(6, {treeint(0, {treeint(9)}), treeint(1)}), treeint(11, {treeint(4), treeint(3)}), treeint(2, {treeint(7), treeint(8, {treeint(10)})})});

  treeint::dfs_preorder_iterator it = tree->dfs_preorder_begin();

  ++it;
  ++it;
  ++it;
  ++it;
  ++it;

  BOOST_CHECK_EQUAL(11, *it);

  treeint* subtree = tree->detach(it);

  delete tree;

  treeint::dfs_preorder_iterator subit = subtree->dfs_preorder_begin();

  ++subit;

  BOOST_CHECK_EQUAL(4, *subit);

  delete subtree;
}

BOOST_AUTO_TEST_SUITE_END()
