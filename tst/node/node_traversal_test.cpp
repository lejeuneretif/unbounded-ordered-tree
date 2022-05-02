#include <boost/test/unit_test.hpp>
#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include <utility>

struct NodeTraversalTest {
  typedef unbounded_ordered::node<int> nodeint;
  nodeint* node;

  typedef nodeint::NodeLastMovement node_last_movement;

  const int count_nodes = 9;
  const int count_leaves = 5;
  const int count_xml_nodes = 13;

  const int dfs_postorder_traversal[9] = {6, 4, 3, 1, 7, 9, 8, 2, 5};
  const node_last_movement dfs_postorder_last_movement[9] = {
    nodeint::NODE_TO_NEXT_LEAF,
    nodeint::NODE_TO_NEXT_LEAF,
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_TO_NEXT_LEAF,
    nodeint::NODE_TO_NEXT_LEAF,
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_TO_PARENT,
  };

  const int dfs_postorder_backwards_traversal[9] = {5, 2, 8, 9, 7, 1, 3, 4, 6};
  const node_last_movement dfs_postorder_backwards_last_movement[9] = {
    nodeint::NODE_TO_LAST_CHILD,
    nodeint::NODE_TO_LAST_CHILD,
    nodeint::NODE_TO_LAST_CHILD,
    nodeint::NODE_TO_PREVIOUS_ANCESTOR,
    nodeint::NODE_TO_PREVIOUS_ANCESTOR,
    nodeint::NODE_TO_LAST_CHILD,
    nodeint::NODE_TO_PREVIOUS_ANCESTOR,
    nodeint::NODE_TO_PREVIOUS_ANCESTOR,
    nodeint::NODE_UNDEFINED,
  };

  const int dfs_preorder_traversal[9] = {5, 6, 1, 4, 3, 2, 7, 8, 9};
  const node_last_movement dfs_preorder_last_movement[9] = {
    nodeint::NODE_TO_FIRST_CHILD,
    nodeint::NODE_TO_NEXT_ANCESTOR,
    nodeint::NODE_TO_FIRST_CHILD,
    nodeint::NODE_TO_NEXT_ANCESTOR,
    nodeint::NODE_TO_NEXT_ANCESTOR,
    nodeint::NODE_TO_FIRST_CHILD,
    nodeint::NODE_TO_NEXT_ANCESTOR,
    nodeint::NODE_TO_FIRST_CHILD,
    nodeint::NODE_UNDEFINED,
  };

  const int dfs_preorder_backwards_traversal[9] = {9, 8, 7, 2, 3, 4, 1, 6, 5};
  const node_last_movement dfs_preorder_backwards_last_movement[9] = {
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_TO_PREVIOUS_LEAF,
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_TO_PREVIOUS_LEAF,
    nodeint::NODE_TO_PREVIOUS_LEAF,
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_TO_PREVIOUS_LEAF,
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_TO_PARENT,
  };

  const int leaf_traversal[5] = {6, 4, 3, 7, 9};
  const node_last_movement leaf_last_movement[5] = {
    nodeint::NODE_TO_NEXT_LEAF,
    nodeint::NODE_TO_NEXT_LEAF,
    nodeint::NODE_TO_NEXT_LEAF,
    nodeint::NODE_TO_NEXT_LEAF,
    nodeint::NODE_UNDEFINED,
  };

  const int leaf_backwards_traversal[5] = {9, 7, 3, 4, 6};
  const node_last_movement leaf_backwards_last_movement[5] = {
    nodeint::NODE_TO_PREVIOUS_LEAF,
    nodeint::NODE_TO_PREVIOUS_LEAF,
    nodeint::NODE_TO_PREVIOUS_LEAF,
    nodeint::NODE_TO_PREVIOUS_LEAF,
    nodeint::NODE_UNDEFINED,
  };

  const int xml_traversal[13] = {5, 6, 1, 4, 3, 1, 2, 7, 8, 9, 8, 2, 5};
  const node_last_movement xml_last_movement[13] = {
    nodeint::NODE_TO_FIRST_CHILD,
    nodeint::NODE_TO_NEXT_SIBLING,
    nodeint::NODE_TO_FIRST_CHILD,
    nodeint::NODE_TO_NEXT_SIBLING,
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_TO_NEXT_SIBLING,
    nodeint::NODE_TO_FIRST_CHILD,
    nodeint::NODE_TO_NEXT_SIBLING,
    nodeint::NODE_TO_FIRST_CHILD,
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_UNDEFINED,
  };

  const int xml_backwards_traversal[13] = {5, 2, 8, 9, 8, 7, 2, 1, 3, 4, 1, 6, 5};
  const node_last_movement xml_backwards_last_movement[13] = {
    nodeint::NODE_TO_LAST_CHILD,
    nodeint::NODE_TO_LAST_CHILD,
    nodeint::NODE_TO_LAST_CHILD,
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_TO_PREVIOUS_SIBLING,
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_TO_PREVIOUS_SIBLING,
    nodeint::NODE_TO_LAST_CHILD,
    nodeint::NODE_TO_PREVIOUS_SIBLING,
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_TO_PREVIOUS_SIBLING,
    nodeint::NODE_TO_PARENT,
    nodeint::NODE_UNDEFINED,
  };

  static std::string last_movement_to_string(node_last_movement last_movement) {
    switch(last_movement) {
      case nodeint::NODE_UNDEFINED: return "NODE_UNDEFINED";
      case nodeint::NODE_TO_ROOT: return "NODE_TO_ROOT";
      case nodeint::NODE_TO_NEXT_ANCESTOR: return "NODE_TO_NEXT_ANCESTOR";
      case nodeint::NODE_TO_PREVIOUS_ANCESTOR: return "NODE_TO_PREVIOUS_ANCESTOR";
      case nodeint::NODE_TO_NEXT_LEAF: return "NODE_TO_NEXT_LEAF";
      case nodeint::NODE_TO_PREVIOUS_LEAF: return "NODE_TO_PREVIOUS_LEAF";
      case nodeint::NODE_TO_PARENT: return "NODE_TO_PARENT";
      case nodeint::NODE_TO_PREVIOUS_SIBLING: return "NODE_TO_PREVIOUS_SIBLING";
      case nodeint::NODE_TO_NEXT_SIBLING: return "NODE_TO_NEXT_SIBLING";
      case nodeint::NODE_TO_FIRST_CHILD: return "NODE_TO_FIRST_CHILD";
      case nodeint::NODE_TO_LAST_CHILD: return "NODE_TO_LAST_CHILD";
      default: return "BAD";
    }
  }

  NodeTraversalTest() {
    nodeint* node9 = new nodeint(9);
    nodeint* node8 = new nodeint(8, {node9});
    nodeint* node7 = new nodeint(7);
    nodeint* node2 = new nodeint(2, {node7, node8});
    nodeint* node3 = new nodeint(3);
    nodeint* node4 = new nodeint(4);
    nodeint* node1 = new nodeint(1, {node4, node3});
    nodeint* node6 = new nodeint(6);

    node = new nodeint(5, {node6, node1, node2});
  }
  ~NodeTraversalTest() {
    node->delete_subtree();
  }
};

BOOST_FIXTURE_TEST_SUITE( node_traversal_suite, NodeTraversalTest )

BOOST_AUTO_TEST_CASE( dfs_postorder ) {
  nodeint* current = node->get_leftmost_leaf();
  int i = 0;

  while(current) {
    BOOST_CHECK_EQUAL(dfs_postorder_traversal[i], current->get_data());

    std::pair<nodeint*, node_last_movement> p = current->dfs_postorder_next();
    current = p.first;

    BOOST_CHECK_EQUAL(dfs_postorder_last_movement[i], p.second);

    ++i;
  }

  BOOST_CHECK_EQUAL(count_nodes, i);
}
BOOST_AUTO_TEST_CASE( dfs_postorder_backwards ) {
  nodeint* current = node;
  int i = 0;

  while(current) {
    BOOST_CHECK_EQUAL(dfs_postorder_backwards_traversal[i], current->get_data());

    std::pair<nodeint*, node_last_movement> p = current->dfs_postorder_previous();
    current = p.first;

    BOOST_CHECK_EQUAL(dfs_postorder_backwards_last_movement[i], p.second);

    ++i;
  }

  BOOST_CHECK_EQUAL(count_nodes, i);
}

BOOST_AUTO_TEST_CASE( dfs_preorder ) {
  nodeint* current = node;
  int i = 0;

  while(current) {
    BOOST_CHECK_EQUAL(dfs_preorder_traversal[i], current->get_data());

    std::pair<nodeint*, node_last_movement> p = current->dfs_preorder_next();
    current = p.first;

    BOOST_CHECK_EQUAL(dfs_preorder_last_movement[i], p.second);

    ++i;
  }

  BOOST_CHECK_EQUAL(count_nodes, i);
}
BOOST_AUTO_TEST_CASE( dfs_preorder_backwards ) {
  nodeint* current = node->get_rightmost_leaf();
  int i = 0;

  while(current) {
    BOOST_CHECK_EQUAL(dfs_preorder_backwards_traversal[i], current->get_data());

    std::pair<nodeint*, node_last_movement> p = current->dfs_preorder_previous();
    current = p.first;

    BOOST_CHECK_EQUAL(dfs_preorder_backwards_last_movement[i], p.second);

    ++i;
  }

  BOOST_CHECK_EQUAL(count_nodes, i);
}

BOOST_AUTO_TEST_CASE( leaf ) {
  nodeint* current = node->get_leftmost_leaf();
  int i = 0;

  while(current) {
    BOOST_CHECK_EQUAL(leaf_traversal[i], current->get_data());

    std::pair<nodeint*, node_last_movement> p = current->leaf_next();
    current = p.first;

    BOOST_CHECK_EQUAL(leaf_last_movement[i], p.second);

    ++i;
  }

  BOOST_CHECK_EQUAL(count_leaves, i);
}
BOOST_AUTO_TEST_CASE( leaf_backwards ) {
  nodeint* current = node->get_rightmost_leaf();
  int i = 0;

  while(current) {
    BOOST_CHECK_EQUAL(leaf_backwards_traversal[i], current->get_data());

    std::pair<nodeint*, node_last_movement> p = current->leaf_previous();
    current = p.first;

    BOOST_CHECK_EQUAL(leaf_backwards_last_movement[i], p.second);

    ++i;
  }

  BOOST_CHECK_EQUAL(count_leaves, i);
}

BOOST_AUTO_TEST_CASE( xml ) {
  nodeint* current = node;
  node_last_movement last_movement = nodeint::NODE_UNDEFINED;
  int i = 0;

  while(current) {
    BOOST_CHECK_EQUAL(xml_traversal[i], current->get_data());

    std::pair<nodeint*, node_last_movement> p = current->xml_next(last_movement);
    current = p.first;
    last_movement = p.second;

    BOOST_CHECK_EQUAL(xml_last_movement[i], p.second);

    ++i;
  }

  BOOST_CHECK_EQUAL(count_xml_nodes, i);
}
BOOST_AUTO_TEST_CASE( xml_backwards ) {
  nodeint* current = node;
  node_last_movement last_movement = nodeint::NODE_UNDEFINED;
  int i = 0;

  while(current) {
    BOOST_CHECK_EQUAL(xml_backwards_traversal[i], current->get_data());

    std::pair<nodeint*, node_last_movement> p = current->xml_previous(last_movement);
    current = p.first;
    last_movement = p.second;

    BOOST_CHECK_EQUAL(xml_backwards_last_movement[i], p.second);

    ++i;
  }

  BOOST_CHECK_EQUAL(count_xml_nodes, i);
}

BOOST_AUTO_TEST_SUITE_END()
