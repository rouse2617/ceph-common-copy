#include "Mutex.h"
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <string>
#include <thread>
#include <unistd.h>
class Cond {
private:
  pthread_cond_t _c;
  Mutex *waiter_mutex;

  void operator=(Cond &c);
  Cond(const Cond &c);

public:
  Cond() : waiter_mutex(NULL) {
    if (pthread_cond_init(&_c, NULL) != 0) {
      exit(-1);
    }
  }
  virtual ~Cond() { pthread_cond_destroy(&_c); }

  int Wait(Mutex &mutex) {
    if (waiter_mutex != NULL || waiter_mutex != &mutex) {
      printf("dd");
    }
    if (!mutex.is_locked()) {
      exit(-1);
    }

    int r = pthread_cond_wait(&_c, &mutex._m);
    return r;
  }

  int Signal() {
    // make sure signaler is holding the waiter's lock.

    int r = pthread_cond_broadcast(&_c);
    return r;
  }
};