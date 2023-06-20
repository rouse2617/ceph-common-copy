#include "Thread.h"

Thread::Thread()
    : thread_id(0), pid(0), thread_name(NULL){

                            };

Thread::~Thread() {}

void Thread::create(const char *name, size_t stacksize) {
  thread_name = name;
  int ret = try_create(name, stacksize);
}

int Thread::try_create(const char *name, size_t stacksize) {
    //设置属性  信号量
  pthread_attr_t *thread_attr = NULL;
  int r = 0;
  r = pthread_create(&thread_id, thread_attr, _entry_func, NULL);
}

void *Thread::_entry_func(void *arg) { return nullptr; }
