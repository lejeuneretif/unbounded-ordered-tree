#define BOOST_TEST_MODULE "Unit-tests of unbounded_ordered_tree."
#include <boost/test/included/unit_test.hpp>
#include "unbounded_ordered/node/unbounded_ordered_node.hpp"

int main(int argc, char** argv) {
  std::cout << "Blip!!!" << std::endl;

  int boost_unit_tests = boost::unit_test::unit_test_main( &init_unit_test, argc, argv );

  std::cout << "Blop!!!" << std::endl;

  std::cout << unbounded_ordered::mem_used << std::endl;
}
