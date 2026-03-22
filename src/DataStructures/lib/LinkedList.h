// LinkedList.h
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdexcept>
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

  void removeByValue(T value);

  void removeByIndex(int index) {

    if (index == 0) {
      Node *temp = this->_head;
      this->_head = this->_head->next;
      delete temp->value;
      delete temp;
      this->_length--;
    } else if (index > (_length - 1)) {
      throw std::invalid_argument("Index out of range.");
    }

    Node *current = this->_head;
    int count = 0;
    while (count != index - 1) {
      current = current->next;
      count++;
    }

    if (current->next != this->_tail) {
      Node *temp = current->next;
      current->next = current->next->next;
      delete temp->value;
      delete temp;
      this->_length--;
    } else {
      Node *temp = this->_tail;
      this->_tail = current;
      delete temp->value;
      delete temp;
      this->_length--;
    }
  }

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
