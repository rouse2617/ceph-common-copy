#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <string>
#include <thread>
#include <unistd.h>

class Mutex {
private:
  std::string name;
  int id;
  bool recursive;
  bool lockdep;
  bool backtrace; // gather backtrace on lock acquisition

  int nlock;
  pthread_t locked_by;
  void operator=(const Mutex &M);
  Mutex(const Mutex &M);

public:
  pthread_mutex_t _m;

  Mutex(const std::string &n, bool r = false, bool ld = true, bool bt = false);
  ~Mutex();
  bool is_locked() const { return (nlock > 0); }

  bool is_locked_by_me() const {
    return nlock > 0 && locked_by == pthread_self();
  }
  bool TryLock() { return try_lock(); }
  bool try_lock() {
    int r = pthread_mutex_trylock(&_m); // pthread_mutex_lock() 的非阻塞版本
    if (r == 0) {

      //     _locked();
      //   _post_lock();
    }
    return r == 0;
  }

  void Lock(bool no_lockdep = false) { lock(no_lockdep); }
  void lock(bool no_lockdep = false);

  void Unlock() { unlock(); }
  void unlock();
};
