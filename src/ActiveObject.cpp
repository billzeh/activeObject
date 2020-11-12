//
// Created by William Zeh on 8/14/20.
//

#include "activeObject/ActiveObject.h"

//**********************************************************
//
//**********************************************************
ActiveObject::ActiveObject() : running_(true) {
  thread_ = std::thread(&ActiveObject::run, this);
}

//**********************************************************
//
//**********************************************************
ActiveObject::~ActiveObject() {
  enqueue([&]() { running_ = false; });
  thread_.join();
}

//**********************************************************
//
//**********************************************************
void ActiveObject::async(const ActiveObject::AsyncWorkCallBack &cb) {
  enqueue(cb);
}

//**********************************************************
//
//**********************************************************
void ActiveObject::run() {
  while (running_) {
    dequeue()();
  }
}

//**********************************************************
//
//**********************************************************
void ActiveObject::enqueue(const ActiveObject::AsyncWorkCallBack &cb) {
  std::lock_guard<std::mutex> guard(qLock_);
  queue_.push(cb);
  empty_.notify_one();
}

//**********************************************************
//
//**********************************************************
ActiveObject::AsyncWorkCallBack ActiveObject::dequeue() {
  std::unique_lock<std::mutex> lock(qLock_);
  empty_.wait(lock, [&] { return !queue_.empty(); });

  AsyncWorkCallBack cb = queue_.front();
  queue_.pop();
  return cb;
}
