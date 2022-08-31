// Your implementation of the Stack class goes here!!!!

#include "Stack.hpp"

#include <iostream>

using namespace std;

ActivationRecord* Stack::pop() {
  ActivationRecord* front = nullptr;
  if (!isEmpty()) {
    front = this->top();
    this->pop_front();
  }
  else {
    cout << "Stack is already empty" << endl;
  }
  return front;
}

void Stack::push(ActivationRecord *newAR) {
  this->push_front(newAR);
  return;
}

ActivationRecord* Stack::top() const {
  return this->front();
}

ActivationRecord* Stack::peek() const {
  auto it = this->front();
  return ++it;
}

bool Stack::isEmpty() const {
  return this->empty();
}

std::ostream& operator<<(std::ostream &os, const Stack &s) {
  for (auto it = s.begin(); it != s.end(); it++) {
    os << *it << endl;
  }
  return os;
}

