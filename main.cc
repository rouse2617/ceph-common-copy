#include <iostream>
#include "Thread.h"
class Test:public Thread{
    public:
      void *entry() override{

      }
};
int main() {
      std::cout << " start " << std::endl;
      Test t1;
      return 1;
}
