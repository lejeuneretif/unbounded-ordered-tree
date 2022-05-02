#include <boost/test/unit_test.hpp>
#include "unbounded_ordered/node/unbounded_ordered_node.hpp"

struct NodeSubtreeDeleteTest {
  typedef unbounded_ordered::node<int> nodeint;

  NodeSubtreeDeleteTest() {}
  ~NodeSubtreeDeleteTest() {}
};

BOOST_FIXTURE_TEST_SUITE( node_subtree_delete_suite, NodeSubtreeDeleteTest )

BOOST_AUTO_TEST_CASE( subtree_delete ) {
  typedef unbounded_ordered::node<int> nodeint;

  nodeint* nodea[12];

  nodea[11] = new nodeint(11);
  nodea[10] = new nodeint(10, {nodea[11]});
  nodea[9] = new nodeint(9);
  nodea[8] = new nodeint(8, {nodea[9]});
  nodea[7] = new nodeint(7);
  nodea[6] = new nodeint(6);
  nodea[5] = new nodeint(5);
  nodea[4] = new nodeint(4);
  nodea[3] = new nodeint(3);
  nodea[2] = new nodeint(2, {nodea[7], nodea[8]});
  nodea[1] = new nodeint(1, {nodea[4], nodea[3], nodea[10], nodea[5]});
  nodea[0] = new nodeint(0, {nodea[6], nodea[1], nodea[2]});

  nodeint* nodeb[12];

  nodeb[11] = new nodeint(11);
  nodeb[10] = new nodeint(10, {nodeb[11]});
  nodeb[6] = new nodeint(6);
  nodeb[5] = new nodeint(5);
  nodeb[4] = new nodeint(4);
  nodeb[3] = new nodeint(3);
  nodeb[1] = new nodeint(1, {nodeb[4], nodeb[3], nodeb[10], nodeb[5]});
  nodeb[0] = new nodeint(0, {nodeb[6], nodeb[1]});

  nodea[2]->delete_subtree();

  BOOST_CHECK(nodea[0]->is_subtree_consistent());

  BOOST_CHECK(nodeb[0]->is_subtree_equal(nodea[0]));

  nodea[0]->delete_subtree();
  nodeb[0]->delete_subtree();
}

BOOST_AUTO_TEST_SUITE_END()
