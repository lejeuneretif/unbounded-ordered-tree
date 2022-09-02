#include <boost/test/unit_test.hpp>
#include "unbounded_ordered_tree.hpp"

struct TreeChangeDataTest {
  TreeChangeDataTest() {}
  ~TreeChangeDataTest() {}
};

BOOST_FIXTURE_TEST_SUITE( tree_change_data_suite, TreeChangeDataTest )

BOOST_AUTO_TEST_CASE( change_data_non_const ) {
  unbounded_ordered::tree<int> t(1);

  unbounded_ordered::tree<int>::dfs_postorder_iterator it = t.dfs_postorder_begin();
  BOOST_CHECK_EQUAL(1, *it);
  *it = 2;

  BOOST_CHECK_EQUAL(2, *(t.dfs_postorder_begin()));
}

BOOST_AUTO_TEST_SUITE_END()
