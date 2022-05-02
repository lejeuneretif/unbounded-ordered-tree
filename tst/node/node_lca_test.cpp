#include <boost/test/unit_test.hpp>
#include <iostream>
#include <list>
#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include <utility>

struct NodeLcaTest {
  typedef unbounded_ordered::node<int> nodeint;

  nodeint* nodes[12];

  NodeLcaTest() {
    nodes[11] = new nodeint(11);
    nodes[10] = new nodeint(10, {nodes[11]});
    nodes[9] = new nodeint(9);
    nodes[8] = new nodeint(8, {nodes[9]});
    nodes[7] = new nodeint(7);
    nodes[6] = new nodeint(6);
    nodes[5] = new nodeint(5);
    nodes[4] = new nodeint(4);
    nodes[3] = new nodeint(3);
    nodes[2] = new nodeint(2, {nodes[7], nodes[8]});
    nodes[1] = new nodeint(1, {nodes[4], nodes[3], nodes[10], nodes[5]});
    nodes[0] = new nodeint(0, {nodes[6], nodes[1], nodes[2]});
  }

  ~NodeLcaTest() {
    nodes[0]->delete_subtree();
  }
};

BOOST_FIXTURE_TEST_SUITE( node_lca_suite, NodeLcaTest )

BOOST_AUTO_TEST_CASE( ancestors ) {
  int ancestors0[1] = {0};
  int ancestors1[2] = {0, 1};
  int ancestors2[2] = {0, 2};
  int ancestors3[3] = {0, 1, 3};
  int ancestors4[3] = {0, 1, 4};
  int ancestors5[3] = {0, 1, 5};
  int ancestors6[2] = {0, 6};
  int ancestors7[3] = {0, 2, 7};
  int ancestors8[3] = {0, 2, 8};
  int ancestors9[4] = {0, 2, 8, 9};
  int ancestors10[3] = {0, 1, 10};
  int ancestors11[4] = {0, 1, 10, 11};

  std::pair<int, int*> ancestors[12] = {
    std::pair<int, int*>(1, ancestors0),
    std::pair<int, int*>(2, ancestors1),
    std::pair<int, int*>(2, ancestors2),
    std::pair<int, int*>(3, ancestors3),
    std::pair<int, int*>(3, ancestors4),
    std::pair<int, int*>(3, ancestors5),
    std::pair<int, int*>(2, ancestors6),
    std::pair<int, int*>(3, ancestors7),
    std::pair<int, int*>(3, ancestors8),
    std::pair<int, int*>(4, ancestors9),
    std::pair<int, int*>(3, ancestors10),
    std::pair<int, int*>(4, ancestors11),
  };

  for(int i = 0; i < 12; ++i) {
    std::list<const nodeint*> ancestor = nodes[i]->ancestors();
    int j = 0;
    for(std::list<const nodeint*>::const_iterator it = ancestor.cbegin(); it != ancestor.cend(); ++it) {
      BOOST_CHECK(*it == nodes[ancestors[i].second[j]]);
      ++j;
    }

    BOOST_CHECK_EQUAL(ancestors[i].first, j);
  }
}

BOOST_AUTO_TEST_CASE( lowest_common_ancestor ) {
  int lcas[12][12] =
  {          // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
      /* 0 */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0 },
      /* 1 */ { 0, 1, 0, 1, 1, 1, 0, 0, 0, 0,  1,  1 },
      /* 2 */ { 0, 0, 2, 0, 0, 0, 0, 2, 2, 2,  0,  0 },
      /* 3 */ { 0, 1, 0, 3, 1, 1, 0, 0, 0, 0,  1,  1 },
      /* 4 */ { 0, 1, 0, 1, 4, 1, 0, 0, 0, 0,  1,  1 },
      /* 5 */ { 0, 1, 0, 1, 1, 5, 0, 0, 0, 0,  1,  1 },
      /* 6 */ { 0, 0, 0, 0, 0, 0, 6, 0, 0, 0,  0,  0 },
      /* 7 */ { 0, 0, 2, 0, 0, 0, 0, 7, 2, 2,  0,  0 },
      /* 8 */ { 0, 0, 2, 0, 0, 0, 0, 2, 8, 8,  0,  0 },
      /* 9 */ { 0, 0, 2, 0, 0, 0, 0, 2, 8, 9,  0,  0 },
      /*10 */ { 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 10, 10 },
      /*11 */ { 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 10, 11 },
  };

  for(int i = 0; i < 12; ++i) {
    for(int j = 0; j < 12; ++j) {
      BOOST_CHECK(nodes[lcas[i][j]] == nodes[i]->lowest_common_ancestor(nodes[j]));
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()
