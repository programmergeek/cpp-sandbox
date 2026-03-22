#include "iostream"
#include "lib/LinkedList.h"

int main() {
  LinkedList<int> *list = new LinkedList<int>();
  list->append(1);
  list->append(2);
  list->append(3);
  std::cout << list->toString() << std::endl;
  list->removeByIndex(1);
  std::cout << list->toString() << std::endl;
  delete list;
  return 0;
}
