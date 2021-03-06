#include <cstddef>
#include <iostream>

class Item {
  public:
    int _a;
    Item* _next;
  
    Item(int a, Item* next = nullptr): _a( a ), _next( next ) {
      std::cout << _a << " -> new " << this << std::endl;
    }

    Item* copy() const {
      Item* next = _next? _next->copy() : nullptr;

      Item* result = new Item(_a, next);

      return result;
    }

    ~Item() {
      if(_next) delete _next;
      std::cout << _a << " -> del " << this << std::endl;
    }
};

void print(Item& i) {
  std::cout << "( " << i._a << ", ";
  if(i._next) print(*(i._next));
  else std::cout << "nullptr";
  std::cout << " )";
}

void print_item(Item& i) {
  std::cout << "( " << i._a << " -> " << i._next << ", ";
  if(i._next) print_item(*(i._next));
  else std::cout << "nullptr";
  std::cout << " )";
}

class Container {
  public:
    Item* _value;

    Container(): _value(nullptr) {}
    Container(int a) { _value = new Item(a); }

    Container(const Container& other) : _value(other._value->copy()) {}

    Container(Container&& other) : _value(other._value) {
      other._value = nullptr;
    }

    // Copy assignment
    Container& operator=(const Container& other) {
      if(this == &other) {
        return *this;
      }

      Item* copy = other._value->copy();

      delete _value;

      _value = copy;

      return *this;
    }

    // Move assignment operator
    Container& operator=(Container&& other) {
      Item* tmp = _value;

      _value = other._value;

      delete tmp;

      return *this;
    }

    ~Container() { if(_value) delete _value; }

    Container& append(Container&& c) {
      std::cout << "append" << std::endl;

      if(! _value) {
        _value = c._value;
      }
      else {
        Item* last = _value;
        while(last->_next) last = last->_next;

        last->_next = c._value;
      }

      c._value = nullptr;

      return *this;
    }
};

void print(Container& c) {
  std::cout << "Container ";
  if(c._value) {
    print(*(c._value));
  }
  else {
    std::cout << "nullptr";
  }
  std::cout << std::endl;
}

void print_item(Container& c) {
  std::cout << "Container ";
  if(c._value) {
    print_item(*(c._value));
  }
  else {
    std::cout << "nullptr";
  }
  std::cout << std::endl;
}

int main(int argc, char** argv) {
  Container c = Container(0).append(Container(1)).append(Container(2));

  print_item(c);
  print(c);

  return 0;
}
