#include "Mutex.h"

Mutex::Mutex(const std::string &n, bool r, bool ld, bool bt)
    : name(n), id(-1), recursive(r) {
  if (recursive) {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(
        &attr,
        PTHREAD_MUTEX_RECURSIVE); // 参数PTHREAD_MUTEX_RECURSIVE表示在同一个线程中可以多次获取同一把锁。并且不会死锁
    pthread_mutex_init(&_m, &attr);
    pthread_mutexattr_destroy(&attr);
  } else if (lockdep) {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr,
                              PTHREAD_MUTEX_ERRORCHECK); // PTHREAD_MUTEX_ERRORCHECK
                                                         // 可以对锁进行检测，同一个线程
                                                         // 重复加锁后会返回错误
    pthread_mutex_init(&_m, &attr);
    pthread_mutexattr_destroy(&attr);
  } else {
    pthread_mutex_init(&_m, NULL); // 正常的锁
  }
}

Mutex::~Mutex() { pthread_mutex_destroy(&_m); }

void Mutex::lock(bool no_lockdep) {
  int r = pthread_mutex_lock(&_m);
  if (r < 0)
    exit(1);
  nlock++;
}

void Mutex::unlock() {
  if (nlock <= 0) {
    exit(-1);
  }
  --nlock;
  int r = pthread_mutex_unlock(&_m);
}
