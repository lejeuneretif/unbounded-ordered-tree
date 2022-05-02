#include <boost/test/unit_test.hpp>
#include "unbounded_ordered_tree.hpp"

struct TreeIteratorCastTest {
  typedef unbounded_ordered::tree<int> treeint;
  treeint* tree;

  template <typename it_source, typename it_target>
  void convert_iterators(it_source ita, int na, int va, int nb, int vb) {
    it_source a = ita;
    for(int i = 0; i < na; ++i) ++a;

    it_target b = a;
    BOOST_CHECK_EQUAL(va, *b);

    for(int j = 0; j < nb; ++j) ++b;
    BOOST_CHECK_EQUAL(vb, *b);
  }

  TreeIteratorCastTest() {
    tree = new treeint(5, {treeint(6, {treeint(0, {treeint(9)}), treeint(1)}), treeint(11, {treeint(4), treeint(3)}), treeint(2, {treeint(7), treeint(8, {treeint(10)})})});
  }
  ~TreeIteratorCastTest() {
    delete tree;
  }
};

BOOST_FIXTURE_TEST_SUITE( tree_iterator_cast_suite, TreeIteratorCastTest )

BOOST_AUTO_TEST_CASE( change_data_non_const ) {
  unbounded_ordered::tree<int> t(1);

  unbounded_ordered::tree<int>::dfs_postorder_iterator it = t.dfs_postorder_begin();
  BOOST_CHECK_EQUAL(1, *it);
  *it = 2;

  BOOST_CHECK_EQUAL(2, *(t.dfs_postorder_begin()));
}

BOOST_AUTO_TEST_CASE( cast_dfs_preorder_to_bidirectional ) {
  treeint::dfs_preorder_iterator it = tree->dfs_preorder_begin();

  treeint::bidirectional_iterator_t<int> itb = it;

  BOOST_CHECK_EQUAL(5, *itb);
}

BOOST_AUTO_TEST_CASE( cast_dfs_preorder_to_leaf ) {
  convert_iterators<treeint::dfs_preorder_iterator, treeint::leaf_iterator>(tree->dfs_preorder_begin(), 0, 9, 1, 1);
}

BOOST_AUTO_TEST_SUITE_END()
