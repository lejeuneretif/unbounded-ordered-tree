#ifndef UNBOUNDED_ORDERED_NODE_TRAVERSAL_XML_TPP
#define UNBOUNDED_ORDERED_NODE_TRAVERSAL_XML_TPP

#include <utility>
#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"

namespace unbounded_ordered {
  template<typename T>
  std::pair<node<T>*, enum node<T>::NodeLastMovement> node<T>::xml_next(node<T>::NodeLastMovement last_movement) const {
    node<T>* result;
    node<T>::NodeLastMovement next_movement;

    if(last_movement != node<T>::NodeLastMovement::NODE_TO_PARENT && _first_child) {
      result = _first_child;
      next_movement = NODE_TO_FIRST_CHILD;
    }
    else if(_next_sibling) {
      result = _next_sibling;
      next_movement = NODE_TO_NEXT_SIBLING;
    }
    else if(_parent) {
      result = _parent;
      next_movement = NODE_TO_PARENT;
    }
    else {
      result = nullptr;
      next_movement = NODE_UNDEFINED;
    }

    return std::pair<node<T>*, NodeLastMovement>(result, next_movement);
  }

  template<typename T>
  std::pair<node<T>*, enum node<T>::NodeLastMovement> node<T>::xml_previous(node<T>::NodeLastMovement last_movement) const {
    node<T>* result;
    node<T>::NodeLastMovement next_movement;

    if(last_movement != node<T>::NodeLastMovement::NODE_TO_PARENT && _last_child) {
      result = _last_child;
      next_movement = NODE_TO_LAST_CHILD;
    }
    else if(_previous_sibling) {
      result = _previous_sibling;
      next_movement = NODE_TO_PREVIOUS_SIBLING;
    }
    else if(_parent) {
      result = _parent;
      next_movement = NODE_TO_PARENT;
    }
    else {
      result = nullptr;
      next_movement = NODE_UNDEFINED;
    }

    return std::pair<node<T>*, NodeLastMovement>(result, next_movement);
  }
}

#endif // UNBOUNDED_ORDERED_NODE_TRAVERSAL_XML_TPP