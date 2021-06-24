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
class async_awaiter final {
 public:
  typedef std::function<void(T&&)> callback;
  typedef std::function<void(const callback&)> async_action;

  static decltype(auto) create(const async_action& action) {
    using self_type = async_awaiter<T>;
    std::shared_ptr<self_type> self(new self_type());
    std::weak_ptr<self_type> weak_self(self);
    action([weak_self](auto&& result) {
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
    CHECK(!m_await_ready_called);
    m_await_ready_called = true;
    return m_result_ready;
  }

  void await_suspend(std::coroutine_handle<> coro) {
    CHECK(!m_result_ready);
    CHECK(m_coro == nullptr);
    m_coro = coro;
  }

  T& await_resume() {
    CHECK(m_result_ready);
    return m_result;
  }

 protected:
  async_awaiter() = default;

  bool m_await_ready_called = false;
  std::coroutine_handle<> m_coro;
  T m_result;
  bool m_result_ready = false;

 private:
  DK_DECLARE_UNCOPYABLE(async_awaiter);
};

template <typename T = void>
class async_awaiter;

template <>
class async_awaiter<void> {
 public:
  typedef std::function<void()> callback;
  typedef std::function<void(const callback&)> async_action;

  static std::shared_ptr<async_awaiter<>> create(const async_action&);

  bool await_ready();

  void await_suspend(std::coroutine_handle<> coro);

  void await_resume();

 protected:
  async_awaiter() = default;

  bool m_await_ready_called = false;
  std::coroutine_handle<> m_coro;
  bool m_result_ready = false;

 private:
  DK_DECLARE_UNCOPYABLE(async_awaiter);
};

}  // namespace dkcoro
