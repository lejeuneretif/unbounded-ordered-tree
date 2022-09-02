#ifndef UNBOUNDED_ORDERED_TREE_XML_REVERSE_ITERATOR_T_TPP
#define UNBOUNDED_ORDERED_TREE_XML_REVERSE_ITERATOR_T_TPP

#include "unbounded_ordered/node/unbounded_ordered_node.hpp"
#include "unbounded_ordered/tree/iterator/bidirectional_iterator_t.tpp"
#include "unbounded_ordered/tree/unbounded_ordered_tree_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  template <typename T_value>
  class tree<T>::xml_reverse_iterator_t
      : public tree<T>::template bidirectional_iterator_t<T_value> {
  protected:
    xml_reverse_iterator_t(node<T>* root, node<T>* current,
      typename bidirectional_iterator_t<T_value>::Status status,
      typename node<T>::NodeLastMovement last_movement)
        : bidirectional_iterator_t<T_value>(root, current, status, last_movement) {}

    inline void next() {
      switch(this->_status) {
        case bidirectional_iterator_t<T_value>::BIDIRECTIONAL_ITERATOR_BEGIN:
          this->_current = this->_root;
          this->_status = bidirectional_iterator_t<T_value>::BIDIRECTIONAL_ITERATOR_MIDDLE;
          break;
        case bidirectional_iterator_t<T_value>::BIDIRECTIONAL_ITERATOR_MIDDLE: {
          std::pair<node<T>*, typename node<T>::NodeLastMovement> next = this->_current->xml_previous(this->_last_movement);
          this->_current = next.first;
          this->_last_movement = next.second;
          if(! this->_current) this->_status = bidirectional_iterator_t<T_value>::BIDIRECTIONAL_ITERATOR_END;
          break;
        }
        case bidirectional_iterator_t<T_value>::BIDIRECTIONAL_ITERATOR_END:
          THROW_ERROR_END_ITERATOR;
          break;
        default: THROW_ERROR_UNKNOWN_STATUS; break;
      }
    }
    inline void previous() {
      switch(this->_status) {
        case bidirectional_iterator_t<T_value>::BIDIRECTIONAL_ITERATOR_BEGIN:
          THROW_ERROR_BEGIN_ITERATOR;
          break;
        case bidirectional_iterator_t<T_value>::BIDIRECTIONAL_ITERATOR_MIDDLE: {
          std::pair<node<T>*, typename node<T>::NodeLastMovement> previous = this->_current->xml_next(this->_last_movement);
          this->_current = previous.first;
          this->_last_movement = previous.second;
          if(! this->_current) this->_status = bidirectional_iterator_t<T_value>::BIDIRECTIONAL_ITERATOR_BEGIN;
          break;
        }
        case bidirectional_iterator_t<T_value>::BIDIRECTIONAL_ITERATOR_END:
          this->_current = this->_root;
          this->_status = bidirectional_iterator_t<T_value>::BIDIRECTIONAL_ITERATOR_MIDDLE;
          break;
        default: THROW_ERROR_UNKNOWN_STATUS; break;
      }
    }

  public:
    xml_reverse_iterator_t() : bidirectional_iterator_t<T_value>() {}
  };
}

#endif // UNBOUNDED_ORDERED_TREE_XML_REVERSE_ITERATOR_T_TPP