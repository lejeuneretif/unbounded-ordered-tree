#include <boost/test/unit_test.hpp>
#include "unbounded_ordered_tree.hpp"

struct TreeSubtreeRangedLoopTest {
  typedef unbounded_ordered::tree<int> treeint;

  const int count_nodes = 9;

  const int bfs_traversal[9] = {5, 6, 1, 2, 4, 3, 7, 8, 9};

  TreeSubtreeRangedLoopTest() {}
  ~TreeSubtreeRangedLoopTest() {}
};

BOOST_FIXTURE_TEST_SUITE( tree_subtree_ranged_loop_suite, TreeSubtreeRangedLoopTest )

BOOST_AUTO_TEST_CASE( ranged_loop_bfs ) {
  treeint tree = treeint(5, {treeint(6), treeint(1, {treeint(4), treeint(3)}), treeint(2, {treeint(7), treeint(8, {treeint(9)})})});

  int i = 0;
  for(auto a : tree.bfs()) {
    BOOST_CHECK_EQUAL(bfs_traversal[i], a);
    ++i;
  }
  BOOST_CHECK_EQUAL(count_nodes, i);
}

BOOST_AUTO_TEST_SUITE_END()
