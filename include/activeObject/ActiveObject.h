//
// Created by William Zeh on 8/14/20.
//

#ifndef ACTIVEOBJECT_ACTIVEOBJECT_H
#define ACTIVEOBJECT_ACTIVEOBJECT_H

#include <future>
#include <mutex>
#include <queue>
#include <thread>

class ActiveObject {
public:
  typedef std::function<void()> AsyncWorkCallBack;

  ActiveObject();

  ~ActiveObject();

  void async(const AsyncWorkCallBack &cb);

  template <class ReturnT>
  ReturnT asyncAndBlock(const std::function<ReturnT()> &cb) {
    std::promise<ReturnT> returnVal;
    enqueue([&]() { returnVal.set_value(cb()); });
    return returnVal.get_future().get();
  }

private:
  void run();

  void enqueue(const AsyncWorkCallBack &cb);

  AsyncWorkCallBack dequeue();

  std::atomic<bool> running_;
  std::thread thread_;
  std::mutex qLock_;
  std::condition_variable empty_;
  std::queue<AsyncWorkCallBack> queue_;
};

#endif // ACTIVEOBJECT_ACTIVEOBJECT_H
