#include <boost/test/unit_test.hpp>
#include "unbounded_ordered_tree.hpp"

struct TreeSubtreeInsertTest {
  typedef unbounded_ordered::tree<int> treeint;

  TreeSubtreeInsertTest() {}
  ~TreeSubtreeInsertTest() {}
};

BOOST_FIXTURE_TEST_SUITE( tree_subtree_insert_suite, TreeSubtreeInsertTest )

BOOST_AUTO_TEST_CASE( insert_previous_sibling ) {
  treeint* tree = new treeint(5, {
    treeint(6, {
      treeint(0, {treeint(9)}),
      treeint(1)
    }),
    treeint(11, {treeint(4), treeint(3)})
  });

  treeint::dfs_preorder_iterator it = tree->dfs_preorder_begin();

  ++it;
  ++it;
  ++it;
  ++it;

  BOOST_CHECK_EQUAL(1, *it);

  treeint* other = new treeint(2, {treeint(7), treeint(8, {treeint(10)})});

  treeint* expected = new treeint(5, {
    treeint(6, {
      treeint(0, {treeint(9)}),
      treeint(2, {treeint(7), treeint(8, {treeint(10)})}),
      treeint(1)
    }),
    treeint(11, {treeint(4), treeint(3)})
  });

  tree->insert_previous_sibling_move(it, *other);

  BOOST_CHECK(treeint::is_consistent(*tree));

  BOOST_CHECK(treeint::assert_isomorphic(*expected, *tree));

  delete tree;
  delete other;
  delete expected;
}

BOOST_AUTO_TEST_SUITE_END()
