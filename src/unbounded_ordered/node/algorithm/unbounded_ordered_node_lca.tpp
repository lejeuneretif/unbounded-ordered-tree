#ifndef UNBOUNDED_ORDERED_NODE_LCA_TPP
#define UNBOUNDED_ORDERED_NODE_LCA_TPP

#include <list>
#include "unbounded_ordered/node/unbounded_ordered_node_decl.hpp"

namespace unbounded_ordered {
  template <typename T>
  std::list<const node<T>*> node<T>::ancestors() const {
    std::list<const node<T>*> result = std::list<const node<T>*>();
    const node<T>* current = this;

    while(current) {
      result.push_front(current);
      current = current->_parent;
    }

    return result;
  }

  template <typename T>
  const node<T>* node<T>::lowest_common_ancestor(const node<T>* other) const {
    if(this == other) return this;

    std::list<const node<T>*> ancestors_this = this->ancestors();
    std::list<const node<T>*> ancestors_other = other->ancestors();

    if(! ancestors_this.size() || ! ancestors_other.size())
      throw std::out_of_range("The nodes have no common ancestors.");

    typename std::list<const node<T>*>::const_iterator it_this = ancestors_this.cbegin();
    typename std::list<const node<T>*>::const_iterator it_other = ancestors_other.cbegin();

    if(*it_this != *it_other)
      throw std::out_of_range("The node has no ancestors.");

    const node<T>* result = *it_this;

    while(it_this != ancestors_this.cend() && it_other != ancestors_other.cend() && *it_this == *it_other) {
      result = *it_this;

      ++it_this;
      ++it_other;
    }

    return result;
  }
}

#endif // UNBOUNDED_ORDERED_NODE_LCA_TPP