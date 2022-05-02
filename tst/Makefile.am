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
  tree/tree_iterator_cast_test.cpp \
  tree/tree_subtree_copy_test.cpp \
  tree/tree_subtree_detach_test.cpp \
  tree/tree_subtree_insert_test.cpp \
  tree/tree_traversal_test.cpp

unit_test_CXXFLAGS = -g $(TEST_FLAGS) -Iunbounded_ordered -Iboost \
                      -DBOOST_TEST_NO_MAIN -DBOOST_TEST_ALTERNATIVE_INIT_API -DBOOST_STACKTRACE_LINK
unit_test_LDADD = -lboost_unit_test_framework
