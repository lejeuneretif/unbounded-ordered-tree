#ifndef UNBOUNDED_ORDERED_ITERATOR_FREE_ITERATOR_T_HPP
#define UNBOUNDED_ORDERED_ITERATOR_FREE_ITERATOR_T_HPP

#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include "unbounded_ordered/tree/iterator/iterator_t.tpp"
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  class no_destination : public std::exception {
  public:
    typedef enum {
      PARENT = 0,
      PREVIOUS_SIBLING = 1,
      NEXT_SIBLING = 2,
      FIRST_CHILD = 3,
      LAST_CHILD = 4,
    } DESTINATION;

  private:
    DESTINATION _destination;

  public:
    no_destination(DESTINATION destination) : _destination(destination) {}

    const char* what() const throw() {
      switch (_destination) {
      case PARENT:
        return "No parent";
      case PREVIOUS_SIBLING:
        return "No previous sibling";
      case NEXT_SIBLING:
        return "No next sibling";
      case FIRST_CHILD:
        return "No first child";
      case LAST_CHILD:
        return "No last child";
      default:
        return "Destination unknown";
      }
    }
  };
  class last_movement_undefined : public std::exception {
  public:
    const char* what() const throw() { return "Node's last movement undefined."; }
  };

  template <typename T>
  template <typename T_value>
  class tree<T>::free_iterator_t : virtual public tree<T>::template iterator_t<T_value> {
  protected:
    static TreeLastMovement translateLastMovement(typename node<T>::NodeLastMovement nodeLastMovement) {
      switch(nodeLastMovement) {
        case node<T>::NodeLastMovement::NODE_UNDEFINED: return TREE_UNDEFINED;
        case node<T>::NodeLastMovement::NODE_TO_ROOT: return TREE_TO_ROOT;
        case node<T>::NodeLastMovement::NODE_TO_NEXT_ANCESTOR: return TREE_TO_NEXT_ANCESTOR;
        case node<T>::NodeLastMovement::NODE_TO_PREVIOUS_ANCESTOR: return TREE_TO_PREVIOUS_ANCESTOR;
        case node<T>::NodeLastMovement::NODE_TO_NEXT_LEAF: return TREE_TO_NEXT_LEAF;
        case node<T>::NodeLastMovement::NODE_TO_PREVIOUS_LEAF: return TREE_TO_PREVIOUS_LEAF;
        case node<T>::NodeLastMovement::NODE_TO_PARENT: return TREE_TO_PARENT;
        case node<T>::NodeLastMovement::NODE_TO_PREVIOUS_SIBLING: return TREE_TO_PREVIOUS_SIBLING;
        case node<T>::NodeLastMovement::NODE_TO_NEXT_SIBLING: return TREE_TO_NEXT_SIBLING;
        case node<T>::NodeLastMovement::NODE_TO_FIRST_CHILD: return TREE_TO_FIRST_CHILD;
        case node<T>::NodeLastMovement::NODE_TO_LAST_CHILD: return TREE_TO_LAST_CHILD;
        default: throw last_movement_undefined();
      }
    }

    typename node<T>::NodeLastMovement _last_movement;

    free_iterator_t(node<T>* root, node<T>* current, typename node<T>::NodeLastMovement last_movement)
      : iterator_t<T_value>(root, current), _last_movement(last_movement) {}

  public:
    free_iterator_t() : iterator_t<T_value>(), _last_movement(node<T>::NodeLastMovement::NODE_NONE_BEGIN) {}

    TreeLastMovement get_last_movement() const { return translateLastMovement(_last_movement); }
    
    inline bool has_parent() const { return (this->_current->_parent != nullptr); }
    inline void go_to_parent() {
      if(this->_current->_parent) {
        this->_current = this->_current->_parent;
        _last_movement = node<T>::NodeLastMovement::NODE_TO_PARENT;
      }
      throw no_destination(no_destination::PARENT);
    }

    inline bool has_previous_sibling() const { return (this->_current->_previous_sibling != nullptr); }
    inline void go_to_previous_sibling() {
      if(this->_current->_previous_sibling) {
        this->_current = this->_current->_previous_sibling;
        _last_movement = node<T>::NodeLastMovement::NODE_TO_PREVIOUS_SIBLING;
      }
      throw no_destination(no_destination::PREVIOUS_SIBLING);
    }

    inline bool has_next_sibling() const { return (this->_current->_next_sibling != nullptr); }
    inline void go_to_next_sibling() {
      if(this->_current->_next_sibling) {
        this->_current = this->_current->_next_sibling;
        _last_movement = node<T>::NodeLastMovement::NODE_TO_NEXT_SIBLING;
      }
      throw no_destination(no_destination::NEXT_SIBLING);
    }

    inline bool has_first_child() const { return (this->_current->_first_child != nullptr); }
    inline void go_to_first_child() {
      if(this->_current->_first_child) {
        this->_current = this->_current->_first_child;
        _last_movement = node<T>::NodeLastMovement::NODE_TO_FIRST_CHILD;
      }
      throw no_destination(no_destination::FIRST_CHILD);
    }

    inline bool has_last_child() const { return (this->_current->_last_child != nullptr); }
    inline void go_to_last_child() {
      if(this->_current->_last_child) {
        this->_current = this->_current->_last_child;
        _last_movement = node<T>::NodeLastMovement::NODE_TO_LAST_CHILD;
      }
      throw no_destination(no_destination::LAST_CHILD);
    }
  };
}

#endif // UNBOUNDED_ORDERED_ITERATOR_FREE_ITERATOR_T_HPP