/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#pragma once

#include "uncopyable.h"

#include <glog/logging.h>

#include <coroutine>
#include <functional>
#include <memory>

namespace dkcoro {

template <typename T>
class callback_awaiter final {
 public:
  typedef std::function<void(T&&)> read_callback;
  typedef std::function<void(const read_callback&)> read_action;

  static decltype(auto) create(const read_action& read) {
    using self_type = callback_awaiter<T>;
    std::shared_ptr<self_type> self(new self_type());
    std::weak_ptr<self_type> weak_self(self);
    read([weak_self](auto&& result) {
      auto self = weak_self.lock();
      if (self == nullptr) {
        return;
      }
      CHECK(!self->m_result_ready);
      self->m_result = std::move(result);
      self->m_result_ready = true;
      if (self->m_coro != nullptr) {
        self->m_coro.resume();
      }
    });
    return self;
  }

  bool await_ready() {  //
    return m_result_ready;
  }

  void await_suspend(std::coroutine_handle<> coro) {
    if (m_result_ready) {
      coro.resume();
      return;
    }
    m_coro = coro;
  }

  T& await_resume() {
    CHECK(m_result_ready);
    return m_result;
  }

 protected:
  callback_awaiter() = default;

  bool m_await_ready_called = false;
  std::coroutine_handle<> m_coro;
  T m_result;
  bool m_result_ready = false;

 private:
  DK_DECLARE_UNCOPYABLE(callback_awaiter);
};

}  // namespace dkcoro
