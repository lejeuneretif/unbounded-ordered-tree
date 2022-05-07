#include <boost/test/unit_test.hpp>
#include "unbounded_ordered_tree.hpp"

struct TreeCtorDtorTest {
  typedef unbounded_ordered::tree<int> treeint;

  TreeCtorDtorTest() {}
  ~TreeCtorDtorTest() {}
};

BOOST_FIXTURE_TEST_SUITE( tree_ctor_dtor_suite, TreeCtorDtorTest )

BOOST_AUTO_TEST_CASE( root ) {
    treeint t(1);
}

BOOST_AUTO_TEST_CASE( children ) {
    treeint t(1, {treeint(2), treeint(3)});
}

BOOST_AUTO_TEST_CASE( assign_root ) {
    treeint t = treeint(1);
}

BOOST_AUTO_TEST_CASE( assign_children ) {
    treeint t = treeint(1, {treeint(2), treeint(3)});
}

BOOST_AUTO_TEST_CASE( new_root ) {
    treeint* t = new treeint(1);

    delete t;
}

BOOST_AUTO_TEST_CASE( new_children ) {
    treeint* t = new treeint(1, {treeint(2), treeint(3)});

    delete t;
}

BOOST_AUTO_TEST_SUITE_END()
