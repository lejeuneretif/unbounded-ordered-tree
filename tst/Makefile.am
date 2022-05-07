bin_PROGRAMS = unit-test

unit_test_SOURCES = unit-tests.cpp \
  \
  node/node_lca_test.cpp \
  node/node_apply_test.cpp \
  node/node_consistency_test.cpp \
  node/node_subtree_copy_test.cpp \
  node/node_subtree_delete_test.cpp \
  node/node_subtree_equal_test.cpp \
  node/node_subtree_insert_test.cpp \
  node/node_traversal_test.cpp \
  node/node_properties_test.cpp \
  \
  tree/tree_change_data_test.cpp \
  tree/tree_ctor_dtor_test.cpp \
  tree/tree_iterator_cast_test.cpp \
  tree/tree_ranged_loop_test.cpp \
  tree/tree_subtree_copy_test.cpp \
  tree/tree_subtree_detach_test.cpp \
  tree/tree_subtree_insert_test.cpp \
  tree/tree_traversal_test.cpp

unit_test_CXXFLAGS = -g -ggdb -no-pie -fno-pie -rdynamic -fno-omit-frame-pointer \
                      $(TEST_FLAGS) \
                      -Iunbounded_ordered \
                      -Iboost \
                      -DBOOST_TEST_NO_MAIN -DBOOST_TEST_ALTERNATIVE_INIT_API \
                      -DBOOST_STACKTRACE_LINK -DBOOST_STACKTRACE_USE_ADDR2LINE -DBOOST_STACKTRACE_USE_BACKTRACE

unit_test_LDADD = -lboost_unit_test_framework \
                  -lboost_stacktrace_backtrace -lboost_stacktrace_addr2line -lboost_stacktrace_basic -lbacktrace -ldl
