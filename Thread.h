#include <pthread.h>
#include <string>
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

  void create(const char *name, size_t stacksize);
  int try_create(const char *name, size_t stacksize);
  

  virtual ~Thread();

protected:
  virtual void *entry() = 0;
private:
  static void *_entry_func(void *arg);
};
