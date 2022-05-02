#include <boost/test/unit_test.hpp>
#include <string>
#include "unbounded_ordered/node/unbounded_ordered_node.hpp"

struct NodeApplyFixture {
  static std::string concat(const int& parent, const std::list<std::string>& children) {
    std::string result = std::to_string(parent);

    std::list<std::string>::const_iterator it = children.cbegin();
    if(it != children.cend()) {
      result += "( " + *it;
      ++it;
      for(; it != children.cend(); ++it) result += ", " + *it;
      result += " )";
    }

    return result;
  }

  typedef unbounded_ordered::node<int> nodeint;
  nodeint* nodea[12];

  typedef unbounded_ordered::node<std::string> nodestr;
  nodestr* nodeb[12];

  NodeApplyFixture() {
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

    nodeb[11] = new nodestr("11");
    nodeb[10] = new nodestr("10( 11 )", {nodeb[11]});
    nodeb[9] = new nodestr("9");
    nodeb[8] = new nodestr("8( 9 )", {nodeb[9]});
    nodeb[7] = new nodestr("7");
    nodeb[6] = new nodestr("6");
    nodeb[5] = new nodestr("5");
    nodeb[4] = new nodestr("4");
    nodeb[3] = new nodestr("3");
    nodeb[2] = new nodestr("2( 7, 8( 9 ) )", {nodeb[7], nodeb[8]});
    nodeb[1] = new nodestr("1( 4, 3, 10( 11 ), 5 )", {nodeb[4], nodeb[3], nodeb[10], nodeb[5]});
    nodeb[0] = new nodestr("0( 6, 1( 4, 3, 10( 11 ), 5 ), 2( 7, 8( 9 ) ) )", {nodeb[6], nodeb[1], nodeb[2]});
  }

  ~NodeApplyFixture() {
    nodea[0]->delete_subtree();
    nodeb[0]->delete_subtree();
  }
};

BOOST_FIXTURE_TEST_SUITE( node_apply_suite, NodeApplyFixture )

BOOST_AUTO_TEST_CASE( cumulative_no_context ) {
  std::string expected = "0( 6, 1( 4, 3, 10( 11 ), 5 ), 2( 7, 8( 9 ) ) )";

  std::string result = nodea[0]->cumulative<std::string>(&NodeApplyFixture::concat);

  BOOST_CHECK_EQUAL(expected, result);
}

BOOST_AUTO_TEST_CASE( morphism_no_context ) {
  nodestr* result = nodea[0]->morphism<std::string>(&NodeApplyFixture::concat);

  BOOST_CHECK(nodeb[0]->is_subtree_equal(result));

  result->delete_subtree();
}

BOOST_AUTO_TEST_SUITE_END()
