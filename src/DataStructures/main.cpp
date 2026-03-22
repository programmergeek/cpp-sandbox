#include "iostream"
#include "lib/LinkedList.h"

int main() {
  LinkedList<int> *list = new LinkedList<int>();
  list->append(1);
  list->append(2);
  list->append(3);
  list->append(5);
  list->append(234);
  list->append(4);
  list->append(15);
  list->append(52);
  list->append(43);
  std::cout << list->toString() << std::endl;
  int *value = list->findByIndex(34);

  if (value != nullptr) {
    std::cout << "searched value: " + std::to_string(*value) << std::endl;
  } else {
    std::cout << "value not in list" << std::endl;
  }
  delete list;
  return 0;
}
