#include <boost/test/unit_test.hpp>
#include "unbounded_ordered/node/unbounded_ordered_node.hpp"

struct NodeSubtreeInsertTest {
  typedef unbounded_ordered::node<int> nodeint;

  NodeSubtreeInsertTest() {}
  ~NodeSubtreeInsertTest() {}
};

BOOST_FIXTURE_TEST_SUITE( node_subtree_insert_suite, NodeSubtreeInsertTest )

// BEGIN insert previous sibling
BOOST_AUTO_TEST_CASE( insert_previous_sibling_empty_node ) {
  nodeint root = nodeint(0);

  BOOST_CHECK_THROW(root.insert_previous_sibling(nullptr), unbounded_ordered::node_is_null);
}
BOOST_AUTO_TEST_CASE( insert_previous_sibling_root ) {
  nodeint root = nodeint(0);
  nodeint other = nodeint(9);

  BOOST_CHECK_THROW(root.insert_previous_sibling(&other), unbounded_ordered::node_is_root);
}
BOOST_AUTO_TEST_CASE( insert_previous_sibling_as_first_child ) {
  nodeint next_child = nodeint(4);
  nodeint child_first_child = nodeint(2);
  nodeint child_last_child = nodeint(3);
  nodeint child = nodeint(1, {&child_first_child, &child_last_child});
  nodeint root = nodeint(0, {&child, &next_child});

  nodeint other_first_child = nodeint(8);
  nodeint other_last_child = nodeint(7);
  nodeint other = nodeint(9, {&other_first_child, &other_last_child});

  child.insert_previous_sibling(&other);

  // Verifies the newly inserted node.
  BOOST_CHECK_EQUAL(&root, other.get_parent());
  BOOST_CHECK(nullptr == other.get_previous_sibling());
  BOOST_CHECK_EQUAL(&child, other.get_next_sibling());
  BOOST_CHECK_EQUAL(&other_first_child, other.get_first_child());
  BOOST_CHECK_EQUAL(&other_last_child, other.get_last_child());

  // Verifies the child from before insertion.
  BOOST_CHECK_EQUAL(&root, child.get_parent());
  BOOST_CHECK_EQUAL(&other, child.get_previous_sibling());
  BOOST_CHECK_EQUAL(&next_child, child.get_next_sibling());
  BOOST_CHECK_EQUAL(&child_first_child, child.get_first_child());
  BOOST_CHECK_EQUAL(&child_last_child, child.get_last_child());

  // Verifies the root.
  BOOST_CHECK_EQUAL(&other, root.get_first_child());
  BOOST_CHECK_EQUAL(&next_child, root.get_last_child());

  // Verifies the whole structure
  nodeint* expected = new nodeint(0, {
    new nodeint(9, {new nodeint(8), new nodeint(7)}),
    new nodeint(1, {new nodeint(2), new nodeint(3)}),
    new nodeint(4)
  });

  BOOST_CHECK(expected->is_subtree_equal(&root));

  expected->delete_subtree();
}
BOOST_AUTO_TEST_CASE( insert_previous_sibling_as_middle_child ) {
  nodeint last_child_last_child = nodeint(6);
  nodeint last_child_first_child = nodeint(5);
  nodeint last_child = nodeint(4, {&last_child_first_child, &last_child_last_child});
  nodeint first_child_last_child = nodeint(3);
  nodeint first_child_first_child = nodeint(2);
  nodeint first_child = nodeint(1, {&first_child_first_child, &first_child_last_child});
  nodeint root = nodeint(0, {&first_child, &last_child});

  nodeint other_first_child = nodeint(8);
  nodeint other_last_child = nodeint(7);
  nodeint other = nodeint(9, {&other_first_child, &other_last_child});

  last_child.insert_previous_sibling(&other);

  // Verifies the newly inserted node.
  BOOST_CHECK_EQUAL(&root, other.get_parent());
  BOOST_CHECK_EQUAL(&first_child, other.get_previous_sibling());
  BOOST_CHECK_EQUAL(&last_child, other.get_next_sibling());
  BOOST_CHECK_EQUAL(&other_first_child, other.get_first_child());
  BOOST_CHECK_EQUAL(&other_last_child, other.get_last_child());

  // Verifies the children from before insertion.
  BOOST_CHECK_EQUAL(&root, last_child.get_parent());
  BOOST_CHECK_EQUAL(&other, last_child.get_previous_sibling());
  BOOST_CHECK(nullptr == last_child.get_next_sibling());
  BOOST_CHECK_EQUAL(&last_child_first_child, last_child.get_first_child());
  BOOST_CHECK_EQUAL(&last_child_last_child, last_child.get_last_child());

  BOOST_CHECK_EQUAL(&root, first_child.get_parent());
  BOOST_CHECK(nullptr == first_child.get_previous_sibling());
  BOOST_CHECK_EQUAL(&other, first_child.get_next_sibling());
  BOOST_CHECK_EQUAL(&first_child_first_child, first_child.get_first_child());
  BOOST_CHECK_EQUAL(&first_child_last_child, first_child.get_last_child());

  // Verifies the root.
  BOOST_CHECK_EQUAL(&first_child, root.get_first_child());
  BOOST_CHECK_EQUAL(&last_child, root.get_last_child());

  // Verifies the whole structure
  nodeint* expected = new nodeint(0, {
    new nodeint(1, {new nodeint(2), new nodeint(3)}),
    new nodeint(9, {new nodeint(8), new nodeint(7)}),
    new nodeint(4, {new nodeint(5), new nodeint(6)})
  });

  BOOST_CHECK(expected->is_subtree_equal(&root));

  expected->delete_subtree();
}
// END insert previous sibling

// BEGIN insert next sibling
BOOST_AUTO_TEST_CASE( insert_next_sibling_empty_node ) {
  nodeint root = nodeint(0);

  BOOST_CHECK_THROW(root.insert_next_sibling(nullptr), unbounded_ordered::node_is_null);
}
BOOST_AUTO_TEST_CASE( insert_next_sibling_root ) {
  nodeint root = nodeint(0);
  nodeint other = nodeint(9);

  BOOST_CHECK_THROW(root.insert_next_sibling(&other), unbounded_ordered::node_is_root);
}
BOOST_AUTO_TEST_CASE( insert_next_sibling_as_last_child ) {
  nodeint child_first_child = nodeint(2);
  nodeint child_last_child = nodeint(3);
  nodeint child = nodeint(1, {&child_first_child, &child_last_child});
  nodeint previous_child = nodeint(4);
  nodeint root = nodeint(0, {&previous_child, &child});

  nodeint other_first_child = nodeint(8);
  nodeint other_last_child = nodeint(7);
  nodeint other = nodeint(9, {&other_first_child, &other_last_child});

  child.insert_next_sibling(&other);

  // Verifies the newly inserted node.
  BOOST_CHECK_EQUAL(&root, other.get_parent());
  BOOST_CHECK_EQUAL(&child, other.get_previous_sibling());
  BOOST_CHECK(nullptr == other.get_next_sibling());
  BOOST_CHECK_EQUAL(&other_first_child, other.get_first_child());
  BOOST_CHECK_EQUAL(&other_last_child, other.get_last_child());

  // Verifies the child from before insertion.
  BOOST_CHECK_EQUAL(&root, child.get_parent());
  BOOST_CHECK_EQUAL(&previous_child, child.get_previous_sibling());
  BOOST_CHECK_EQUAL(&other, child.get_next_sibling());
  BOOST_CHECK_EQUAL(&child_first_child, child.get_first_child());
  BOOST_CHECK_EQUAL(&child_last_child, child.get_last_child());

  // Verifies the root.
  BOOST_CHECK_EQUAL(&previous_child, root.get_first_child());
  BOOST_CHECK_EQUAL(&other, root.get_last_child());

  // Verifies the whole structure
  nodeint* expected = new nodeint(0, {
    new nodeint(4),
    new nodeint(1, {new nodeint(2), new nodeint(3)}),
    new nodeint(9, {new nodeint(8), new nodeint(7)})
  });

  BOOST_CHECK(expected->is_subtree_equal(&root));

  expected->delete_subtree();
}
BOOST_AUTO_TEST_CASE( insert_next_sibling_as_middle_child ) {
  nodeint last_child_last_child = nodeint(6);
  nodeint last_child_first_child = nodeint(5);
  nodeint last_child = nodeint(4, {&last_child_first_child, &last_child_last_child});
  nodeint first_child_last_child = nodeint(3);
  nodeint first_child_first_child = nodeint(2);
  nodeint first_child = nodeint(1, {&first_child_first_child, &first_child_last_child});
  nodeint root = nodeint(0, {&first_child, &last_child});

  nodeint other_first_child = nodeint(8);
  nodeint other_last_child = nodeint(7);
  nodeint other = nodeint(9, {&other_first_child, &other_last_child});

  first_child.insert_next_sibling(&other);

  // Verifies the newly inserted node.
  BOOST_CHECK_EQUAL(&root, other.get_parent());
  BOOST_CHECK_EQUAL(&first_child, other.get_previous_sibling());
  BOOST_CHECK_EQUAL(&last_child, other.get_next_sibling());
  BOOST_CHECK_EQUAL(&other_first_child, other.get_first_child());
  BOOST_CHECK_EQUAL(&other_last_child, other.get_last_child());

  // Verifies the children from before insertion.
  BOOST_CHECK_EQUAL(&root, last_child.get_parent());
  BOOST_CHECK_EQUAL(&other, last_child.get_previous_sibling());
  BOOST_CHECK(nullptr == last_child.get_next_sibling());
  BOOST_CHECK_EQUAL(&last_child_first_child, last_child.get_first_child());
  BOOST_CHECK_EQUAL(&last_child_last_child, last_child.get_last_child());

  BOOST_CHECK_EQUAL(&root, first_child.get_parent());
  BOOST_CHECK(nullptr == first_child.get_previous_sibling());
  BOOST_CHECK_EQUAL(&other, first_child.get_next_sibling());
  BOOST_CHECK_EQUAL(&first_child_first_child, first_child.get_first_child());
  BOOST_CHECK_EQUAL(&first_child_last_child, first_child.get_last_child());

  // Verifies the root.
  BOOST_CHECK_EQUAL(&first_child, root.get_first_child());
  BOOST_CHECK_EQUAL(&last_child, root.get_last_child());

  // Verifies the whole structure
  nodeint* expected = new nodeint(0, {
    new nodeint(1, {new nodeint(2), new nodeint(3)}),
    new nodeint(9, {new nodeint(8), new nodeint(7)}),
    new nodeint(4, {new nodeint(5), new nodeint(6)})
  });

  BOOST_CHECK(expected->is_subtree_equal(&root));

  expected->delete_subtree();
}
// END insert next sibling

// BEGIN insert first child
BOOST_AUTO_TEST_CASE( insert_first_child_empty_node ) {
  nodeint root = nodeint(0);

  BOOST_CHECK_THROW(root.insert_first_child(nullptr), unbounded_ordered::node_is_null);
}
BOOST_AUTO_TEST_CASE( insert_first_child_alone ) {
  nodeint root = nodeint(0);

  nodeint other = nodeint(9);

  root.insert_first_child(&other);

  // Verifies the newly inserted node.
  BOOST_CHECK_EQUAL(&root, other.get_parent());
  BOOST_CHECK(nullptr == other.get_previous_sibling());
  BOOST_CHECK(nullptr == other.get_next_sibling());
  BOOST_CHECK(nullptr == other.get_first_child());
  BOOST_CHECK(nullptr == other.get_last_child());

  // Verifies the root.
  BOOST_CHECK(nullptr == root.get_parent());
  BOOST_CHECK(nullptr == root.get_previous_sibling());
  BOOST_CHECK(nullptr == root.get_next_sibling());
  BOOST_CHECK_EQUAL(&other, root.get_first_child());
  BOOST_CHECK_EQUAL(&other, root.get_last_child());

  nodeint* expected = new nodeint(0, {new nodeint(9)});

  BOOST_CHECK(expected->is_subtree_equal(&root));

  expected->delete_subtree();
}
BOOST_AUTO_TEST_CASE( insert_first_child_with_other_child ) {
  nodeint last_child = nodeint(1);
  nodeint root = nodeint(0, {&last_child});

  nodeint other = nodeint(9);

  root.insert_first_child(&other);

  // Verifies the newly inserted node.
  BOOST_CHECK_EQUAL(&root, other.get_parent());
  BOOST_CHECK(nullptr == other.get_previous_sibling());
  BOOST_CHECK_EQUAL(&last_child, other.get_next_sibling());
  BOOST_CHECK(nullptr == other.get_first_child());
  BOOST_CHECK(nullptr == other.get_last_child());

  BOOST_CHECK_EQUAL(&root, last_child.get_parent());
  BOOST_CHECK_EQUAL(&other, last_child.get_previous_sibling());
  BOOST_CHECK(nullptr == last_child.get_next_sibling());
  BOOST_CHECK(nullptr == last_child.get_first_child());
  BOOST_CHECK(nullptr == last_child.get_last_child());

  // Verifies the root.
  BOOST_CHECK(nullptr == root.get_parent());
  BOOST_CHECK(nullptr == root.get_previous_sibling());
  BOOST_CHECK(nullptr == root.get_next_sibling());
  BOOST_CHECK_EQUAL(&other, root.get_first_child());
  BOOST_CHECK_EQUAL(&last_child, root.get_last_child());

  nodeint* expected = new nodeint(0, {new nodeint(9), new nodeint(1)});

  BOOST_CHECK(expected->is_subtree_equal(&root));

  expected->delete_subtree();
}
// END insert first child

// BEGIN insert last child
BOOST_AUTO_TEST_CASE( insert_last_child_empty_node ) {
  nodeint root = nodeint(0);

  BOOST_CHECK_THROW(root.insert_last_child(nullptr), unbounded_ordered::node_is_null);
}
BOOST_AUTO_TEST_CASE( insert_last_child_alone ) {
  nodeint root = nodeint(0);

  nodeint other = nodeint(9);

  root.insert_last_child(&other);

  // Verifies the newly inserted node.
  BOOST_CHECK_EQUAL(&root, other.get_parent());
  BOOST_CHECK(nullptr == other.get_previous_sibling());
  BOOST_CHECK(nullptr == other.get_next_sibling());
  BOOST_CHECK(nullptr == other.get_first_child());
  BOOST_CHECK(nullptr == other.get_last_child());

  // Verifies the root.
  BOOST_CHECK(nullptr == root.get_parent());
  BOOST_CHECK(nullptr == root.get_previous_sibling());
  BOOST_CHECK(nullptr == root.get_next_sibling());
  BOOST_CHECK_EQUAL(&other, root.get_first_child());
  BOOST_CHECK_EQUAL(&other, root.get_last_child());

  nodeint* expected = new nodeint(0, {new nodeint(9)});

  BOOST_CHECK(expected->is_subtree_equal(&root));

  expected->delete_subtree();
}
BOOST_AUTO_TEST_CASE( insert_last_child_with_other_child ) {
  nodeint first_child = nodeint(1);
  nodeint root = nodeint(0, {&first_child});

  nodeint other = nodeint(9);

  root.insert_last_child(&other);

  // Verifies the newly inserted node.
  BOOST_CHECK_EQUAL(&root, other.get_parent());
  BOOST_CHECK_EQUAL(&first_child, other.get_previous_sibling());
  BOOST_CHECK(nullptr == other.get_next_sibling());
  BOOST_CHECK(nullptr == other.get_first_child());
  BOOST_CHECK(nullptr == other.get_last_child());

  BOOST_CHECK_EQUAL(&root, first_child.get_parent());
  BOOST_CHECK(nullptr == first_child.get_previous_sibling());
  BOOST_CHECK_EQUAL(&other, first_child.get_next_sibling());
  BOOST_CHECK(nullptr == first_child.get_first_child());
  BOOST_CHECK(nullptr == first_child.get_last_child());

  // Verifies the root.
  BOOST_CHECK(nullptr == root.get_parent());
  BOOST_CHECK(nullptr == root.get_previous_sibling());
  BOOST_CHECK(nullptr == root.get_next_sibling());
  BOOST_CHECK_EQUAL(&first_child, root.get_first_child());
  BOOST_CHECK_EQUAL(&other, root.get_last_child());

  nodeint* expected = new nodeint(0, {new nodeint(1), new nodeint(9)});

  BOOST_CHECK(expected->is_subtree_equal(&root));

  expected->delete_subtree();
}
// END insert last child

BOOST_AUTO_TEST_SUITE_END()
