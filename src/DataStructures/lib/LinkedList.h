// LinkedList.h
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <string>

template <typename T>

class LinkedList {

  class Node {
  public:
    T *value;
    Node *next;

    Node(T *value) {
      this->value = value;
      this->next = nullptr;
    }
  };

private:
  Node *_head;
  Node *_tail;
  int _length;

public:
  void append(T value) {
    Node *newNode = new Node(new T(value));

    if (this->_head == nullptr) {
      this->_head = newNode;
      this->_tail = newNode;
      this->_length = 1;
    } else {
      this->_tail->next = newNode;
      this->_tail = newNode;
      this->_length++;
    }
  }

  bool contains(T *value);

  int length() { return this->_length; }

  void remove(T value);

  // void remove(int index);

  T *find(T value);

  std::string toString() {
    std::string output = "";
    Node *current = this->_head;
    for (int i = 0; i < this->_length; i++) {
      output += std::to_string(*(current->value));
      if (current->next != nullptr) {
        current = current->next;
        output += ", ";
      }
    }
    return output;
  }

  ~LinkedList() {
    Node *current = this->_head;
    while (current != nullptr) {
      Node *temp = current->next;
      delete current->value;
      delete current;
      current = temp;
    }
  }
};

#endif
