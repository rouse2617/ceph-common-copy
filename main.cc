#include "Cond.h"
#include "Thread.h"
#include <iostream>

Mutex m_("mutex");
Cond cond;
class Test : public Thread {
public:
  int x = 0;
  void *entry() override {
    while (1) {
      m_.lock();

      sleep(1);
      cond.Wait(m_);
      std::cout << get_thread_id() << " dddddddddddddddddddddd  " << x++
                << std::endl;

      // std::cout << get_thread_name() << std::endl;
    }
  }
};

class Test2 : public Thread {
public:
  int x = 0;
  void *entry() override {
    while (1) {
      std::cout << get_thread_id() << "   " << x++ << std::endl;
      std::cout << get_thread_name() << std::endl;
      sleep(5);
      cond.Signal();
    }
  }
};

void sig_usr(int signo) {
      if (signo == SIGUSR1) {
        printf("recived siguser1\n");
      } else if (signo == SIGUSR2) {
        printf("recived sigure2 \n");
      }
}

int main() {
      std::cout << " start " << std::endl;
      Test t1;
      Test2 t2;

      t1.create("thread1", 0);
      t2.create("Test2", 0);
      {
        if (signal(SIGUSR1, sig_usr) == SIG_ERR)
          std::cout << "err";
        if (signal(SIGUSR2, sig_usr) == SIG_ERR)
          std::cout << "err";
      }

      sleep(100);
      return 1;
}
