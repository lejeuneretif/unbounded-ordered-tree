#define BOOST_TEST_MODULE "Unit-tests of unbounded_ordered_tree."
#include <boost/test/included/unit_test.hpp>
#include "unbounded_ordered/node/unbounded_ordered_node.hpp"

std::map<void*, std::string> unbounded_ordered::debug_stacktrace;

int main(int argc, char** argv) {
  int boost_unit_tests = boost::unit_test::unit_test_main( &init_unit_test, argc, argv );

  if(unbounded_ordered::debug_stacktrace.size()) {
    std::cout << "List of memory leaks:" << std::endl;
    for(auto it : unbounded_ordered::debug_stacktrace) {
      std::cout << "node " << it.first << " not freed, allocated at" << std::endl
                << it.second << std::endl;
    }
  }
  else {
    std::cout << "No memory leak." << std::endl;
  }
}
