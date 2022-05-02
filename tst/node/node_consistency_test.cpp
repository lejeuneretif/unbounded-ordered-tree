#include <boost/test/unit_test.hpp>
#include "unbounded_ordered/node/unbounded_ordered_node.hpp"

struct NodeConsistencyTest {
  typedef unbounded_ordered::node<int> nodeint;

  NodeConsistencyTest() {}
  ~NodeConsistencyTest() {}
};

BOOST_FIXTURE_TEST_SUITE( node_consistency_suite, NodeConsistencyTest )

BOOST_AUTO_TEST_CASE( internal_consistency_restricted_to_root ) {
  nodeint* root = new nodeint(0);
  
  BOOST_CHECK(root->is_subtree_consistent());
}

BOOST_AUTO_TEST_CASE( internal_consistency_initializer_list ) {
  nodeint* node = new nodeint(5, {new nodeint(6),
    new nodeint(1, {new nodeint(4), new nodeint(3)}), new nodeint(2, {new nodeint(7),
      new nodeint(8, {new nodeint(9)})})});
  
  BOOST_CHECK(node->is_subtree_consistent());
}

BOOST_AUTO_TEST_CASE( internal_consistency_empty_initializer_list ) {
  nodeint* node = new nodeint(5, {});
  
  BOOST_CHECK(node->is_subtree_consistent());
}

BOOST_AUTO_TEST_CASE( internal_consistency_list ) {
  nodeint* node =
  new nodeint(5, std::list<nodeint*>({
    new nodeint(6),
    new nodeint(1, std::list<nodeint*>({
      new nodeint(4),
      new nodeint(3)
    })),
    new nodeint(2, std::list<nodeint*>({
      new nodeint(7),
      new nodeint(8, std::list<nodeint*>({
        new nodeint(9)
      }))
    }))
  }));
  
  BOOST_CHECK(node->is_subtree_consistent());
}

BOOST_AUTO_TEST_CASE( internal_consistency_empty_list ) {
  nodeint* node = new nodeint(5, std::list<nodeint*>());
  
  BOOST_CHECK(node->is_subtree_consistent());
}

BOOST_AUTO_TEST_CASE( internal_consistency_insert_first_child ) {
  nodeint* n0 = new nodeint(0);
  nodeint* n1 = new nodeint(1);
  nodeint* n2 = new nodeint(2);
  nodeint* n3 = new nodeint(3);

  n2->insert_first_child(n3);

  n0->insert_first_child(n2);
  n0->insert_first_child(n1);

  BOOST_CHECK(n0->is_subtree_consistent());

  n0->delete_subtree();
}

BOOST_AUTO_TEST_CASE( internal_consistency_detach ) {
  nodeint* node9 = new nodeint(9);
  nodeint* node8 = new nodeint(8, {node9});
  nodeint* node7 = new nodeint(7);
  nodeint* node2 = new nodeint(2, {node7, node8});
  nodeint* node3 = new nodeint(3);
  nodeint* node4 = new nodeint(4);
  nodeint* node1 = new nodeint(1, {node4, node3});
  nodeint* node6 = new nodeint(6);
  nodeint* node = new nodeint(5, {node6, node1, node2});

  node2->detach();

  BOOST_CHECK(node->is_subtree_consistent());

  BOOST_CHECK(node2->is_root());
  BOOST_CHECK(node2->is_subtree_consistent());

  node->delete_subtree();
  node2->delete_subtree();
}

BOOST_AUTO_TEST_SUITE_END()
