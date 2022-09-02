#define BOOST_TEST_MODULE "Unit-tests of unbounded_ordered_tree."
#include <boost/test/included/unit_test.hpp>
#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include "unbounded_ordered/unbounded_ordered_tree.hpp"

std::map<void*, std::string> unbounded_ordered::node_allocation_debug_stacktrace;
std::map<void*, std::string> unbounded_ordered::tree_allocation_debug_stacktrace;

int main(int argc, char** argv) {
  int boost_unit_tests = boost::unit_test::unit_test_main( &init_unit_test, argc, argv );

  if(unbounded_ordered::node_allocation_debug_stacktrace.size()
      || unbounded_ordered::tree_allocation_debug_stacktrace.size()) {
    std::cout << "List of memory leaks:" << std::endl;

    for(auto it : unbounded_ordered::node_allocation_debug_stacktrace) {
      std::cout << "node " << it.first << " not freed, allocated at" << std::endl
                << it.second << std::endl;
    }

    for(auto it : unbounded_ordered::tree_allocation_debug_stacktrace) {
      std::cout << "tree " << it.first << " not freed, allocated at" << std::endl
                << it.second << std::endl;
    }
  }
  else {
    std::cout << "No memory leak." << std::endl;
  }
}
