#include <boost/test/unit_test.hpp>
#include <map>
#include "unbounded_ordered/node/unbounded_ordered_node.hpp"

struct NodeSubtreeEqualTest {
  typedef unbounded_ordered::node<int> nodeint;

  NodeSubtreeEqualTest() {}
  ~NodeSubtreeEqualTest() {}
};

BOOST_FIXTURE_TEST_SUITE( node_subtree_equal_suite, NodeSubtreeEqualTest )

BOOST_AUTO_TEST_CASE( subtree_equal ) {
  nodeint* nodea[12];

  nodea[11] = new nodeint(11);
  nodea[10] = new nodeint(10, {nodea[11]});
  nodea[9] = new nodeint(9);
  nodea[8] = new nodeint(8, {nodea[9]});
  nodea[7] = new nodeint(7);
  nodea[2] = new nodeint(2, {nodea[7], nodea[8]});
  nodea[5] = new nodeint(5);
  nodea[4] = new nodeint(4);
  nodea[3] = new nodeint(3);
  nodea[1] = new nodeint(1, {nodea[4], nodea[3], nodea[10], nodea[5]});
  nodea[6] = new nodeint(6);
  nodea[0] = new nodeint(0, {nodea[6], nodea[1], nodea[2]});

  nodeint* nodeb[12];

  nodeb[11] = new nodeint(11);
  nodeb[10] = new nodeint(10, {nodeb[11]});
  nodeb[9] = new nodeint(9);
  nodeb[8] = new nodeint(8, {nodeb[9]});
  nodeb[7] = new nodeint(7);
  nodeb[2] = new nodeint(2, {nodeb[7], nodeb[8]});
  nodeb[5] = new nodeint(5);
  nodeb[4] = new nodeint(4);
  nodeb[3] = new nodeint(3);
  nodeb[1] = new nodeint(1, {nodeb[4], nodeb[3], nodeb[10], nodeb[5]});
  nodeb[6] = new nodeint(6);
  nodeb[0] = new nodeint(0, {nodeb[6], nodeb[1], nodeb[2]});

  std::map<const nodeint* const, const nodeint* const> m;
  std::map<const nodeint* const, const nodeint* const> m_reverse;

  BOOST_CHECK(nodea[0]->is_subtree_equal(nodeb[0], m, m_reverse));

  for(int i = 0; i < 12; ++i) {
    BOOST_CHECK(m[nodea[i]] == nodeb[i]);
    BOOST_CHECK(nodea[i] == m_reverse[nodeb[i]]);
  }

  nodea[0]->delete_subtree();
  nodeb[0]->delete_subtree();
}

BOOST_AUTO_TEST_CASE( subtree_equal_root_missing_first_child ) {
  nodeint* root = new nodeint(0, {new nodeint(1), new nodeint(2)});

  nodeint* missing_first_child = new nodeint(0, {new nodeint(2)});

  BOOST_CHECK(! root->is_subtree_equal(missing_first_child));

  root->delete_subtree();
  missing_first_child->delete_subtree();
}

BOOST_AUTO_TEST_CASE( subtree_equal_root_missing_middle_child ) {
  nodeint* root = new nodeint(0, {new nodeint(1), new nodeint(2), new nodeint(3)});

  nodeint* missing_middle_child = new nodeint(0, {new nodeint(1), new nodeint(3)});

  BOOST_CHECK(! root->is_subtree_equal(missing_middle_child));

  root->delete_subtree();
  missing_middle_child->delete_subtree();
}

BOOST_AUTO_TEST_CASE( subtree_equal_root_missing_last_child ) {
  nodeint* root = new nodeint(0, {new nodeint(1), new nodeint(2)});

  nodeint* missing_last_child = new nodeint(0, {new nodeint(1)});

  BOOST_CHECK(! root->is_subtree_equal(missing_last_child));

  root->delete_subtree();
  missing_last_child->delete_subtree();
}

BOOST_AUTO_TEST_SUITE_END()
