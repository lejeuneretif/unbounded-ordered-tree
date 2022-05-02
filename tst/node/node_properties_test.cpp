#include <boost/test/unit_test.hpp>
#include "unbounded_ordered/node/unbounded_ordered_node.hpp"

struct NodePropertiesTest {
  typedef unbounded_ordered::node<int> nodeint;

  NodePropertiesTest() {}
  ~NodePropertiesTest() {}
};

BOOST_FIXTURE_TEST_SUITE( node_properties_suite, NodePropertiesTest )

BOOST_AUTO_TEST_CASE( count_children ) {
  nodeint* node[12];

  node[11] = new nodeint(11);
  node[10] = new nodeint(10, {node[11]});
  node[9] = new nodeint(9);
  node[8] = new nodeint(8, {node[9]});
  node[7] = new nodeint(7);
  node[6] = new nodeint(6);
  node[5] = new nodeint(5);
  node[4] = new nodeint(4);
  node[3] = new nodeint(3);
  node[2] = new nodeint(2, {node[7], node[8]});
  node[1] = new nodeint(1, {node[4], node[3], node[10], node[5]});
  node[0] = new nodeint(0, {node[6], node[1], node[2]});

  std::size_t result[12] = {3, 4, 2, 0, 0, 0, 0, 0, 1, 0, 1, 0};

  for(int i = 0; i < 12; ++i) {
    BOOST_CHECK(result[i] == node[i]->count_children());
  }

  node[0]->delete_subtree();
}

BOOST_AUTO_TEST_SUITE_END()
