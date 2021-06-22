/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#pragma once

#include <glog/logging.h>

#include <coroutine>
#include <functional>
#include <memory>

namespace dkcoro {

template <typename T>
class CallbackAwaiter final
  : public std::enable_shared_from_this<CallbackAwaiter<T>> {
 public:
  typedef std::function<void(T&&)> ReadCallback;
  typedef std::function<void(const ReadCallback&)> Read;

  static decltype(auto) create(const Read& read) {
    using SelfType = CallbackAwaiter<T>;
    std::shared_ptr<SelfType> self(new SelfType());
    std::weak_ptr<SelfType> weak_self(self);
    read([weak_self](auto&& result) {
      auto self = weak_self.lock();
      if (self == nullptr) {
        return;
      }
      CHECK(!self->resultReady);
      self->result = std::move(result);
      self->resultReady = true;
      if (self->coro != nullptr) {
        self->coro.resume();
      }
    });
    return self;
  }

  bool await_ready() {  //
    CHECK(!awaitReadyCalled && "co_await invocaked more than once");
    awaitReadyCalled = true;
    return resultReady;
  }

  void await_suspend(std::coroutine_handle<> c) {
    coro = c;
    if (resultReady) {
      coro.resume();
    }
  }

  T& await_resume() {
    CHECK(resultReady);
    return result;
  }

 private:
  CallbackAwaiter() {}

  bool awaitReadyCalled = false;
  std::coroutine_handle<> coro;
  T result;
  bool resultReady = false;
};

}  // namespace dkcoro
