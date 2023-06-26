#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <string>
#include <thread>
#include <unistd.h>

class Thread {
private:
  pthread_t thread_id;
  pid_t pid;
  const char *thread_name;

public:
  Thread(const Thread &) = delete;
  Thread &operator=(const Thread &) = delete;
  Thread();

  void create(const char *name, size_t stacksize = 0);
  int try_create(const char *name, size_t stacksize);
  void *entry_wrapper();
  const pthread_t get_thread_id() const;
  const char *get_thread_name() const { return thread_name; }
  bool is_strart() const;
  bool am_self() const;
  int kill(int signal);
  int detach();

  virtual ~Thread();

protected:
  virtual void *entry() = 0;
private:
  static void *_entry_func(void *arg);
};

// template <typename Fun, typename... Args>
// std::thread make_named_thread(std::string n, Fun &&fun, Args &&...args) {

//   return std::thread(
//       [n = std::string(n)](auto &&fun, auto &&...args) {
//         // ceph_pthread_setname(pthread_self(), n.data());
//         std::invoke(std::forward<Fun>(fun), std::forward<Args>(args)...);
//       },
//       std::forward<Fun>(fun), std::forward<Args>(args)...);
// }