#include "Thread.h"

Thread::Thread()
    : thread_id(0), pid(0), thread_name(NULL){

                            };

bool Thread::is_strart() const { return thread_id != 0; }

bool Thread::am_self() const { return (pthread_self() == thread_id); }

int Thread::kill(int signal) {
  if (thread_id)
    std::cout << "kill thread "
              << "" << std::endl;
  return pthread_kill(thread_id, signal);

  return -EINVAL;
}

Thread::~Thread() {}

void Thread::create(const char *name, size_t stacksize) {
  thread_name = name;
  int ret = try_create(name, stacksize);
}

int Thread::try_create(const char *name, size_t stacksize) {
    //设置属性  信号量
  pthread_attr_t *thread_attr = NULL;
  int r = 0;
  r = pthread_create(&thread_id, thread_attr, _entry_func, (void *)this);
}
void *Thread::entry_wrapper() {

  pthread_setname_np(thread_id, thread_name);
  return entry();
}

void *Thread::_entry_func(void *arg) {
  void *r = ((Thread *)arg)->entry_wrapper();
  std::cout << r;
  return r;
}

const pthread_t Thread::get_thread_id() const { return thread_id; }
