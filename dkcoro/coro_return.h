/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#pragma once

#include <glog/logging.h>

#include <coroutine>
#include <exception>
#include <memory>
#include <utility>

namespace dkcoro {

template <typename T>
class coro_return final {
 public:
  struct result_holder {
    T result;
    bool result_ready = false;
  };

  class promise_type {
   public:
    auto get_return_object() {  //
      return coro_return(this);
    }

    auto initial_suspend() {  //
      return std::suspend_never();
    }

    auto final_suspend() noexcept {  //
      return std::suspend_never();
    }

    void unhandled_exception() {
      auto exception_ptr = std::current_exception();
      try {
        CHECK_NOTNULL(exception_ptr);
        std::rethrow_exception(exception_ptr);
      } catch (const std::exception& e) {
        LOG(FATAL) << "unhandled exception: " << e.what();
      }
    }

    void return_value(T&& v) {
      auto holder = m_result_holder.lock();
      if (holder == nullptr) {
        return;
      }
      holder->result = std::move(v);
      holder->result_ready = true;
      if (m_awaiter_coro == nullptr) {
        return;
      }
      m_awaiter_coro.resume();
    }

    void set_awaiter_coro(const std::coroutine_handle<>& coro) {
      CHECK(m_awaiter_coro == nullptr);
      m_awaiter_coro = coro;
    }

    void set_result_holder(const std::shared_ptr<result_holder>& holder) {
      m_result_holder = holder;
    }

   private:
    std::weak_ptr<result_holder> m_result_holder;
    std::coroutine_handle<> m_awaiter_coro;
  };

  coro_return(promise_type* promise) : m_promise(promise) {
    CHECK_NOTNULL(m_promise);
    m_result_holder = new result_holder();
    m_promise->set_result_holder(m_result_holder);
  }

  decltype(auto) operator co_await() {
    class awaiter {
     public:
      awaiter(coro_return<T>* r) : m_coro_return(r) {
        CHECK_NOTNULL(m_coro_return);
      }

      bool await_ready() {
        CHECK_NOTNULL(m_coro_return->m_result_holder);
        bool ready = m_coro_return->m_result_holder->result_ready;
        if (ready) {
          m_promise = nullptr;
        }
        return ready;
      }

      void await_suspend(std::coroutine_handle<> c) {
        m_coro_return.promise.set_awaiter_coro(c);
      }

      T& await_resume() {
        CHECK_NOTNULL(m_coro_return->m_result_holder);
        CHECK(m_coro_return->m_result_holder->result_ready);
        return m_coro_return->m_result_holder->result;
      }

     private:
      bool m_await_ready_called = false;
      coro_return<T>* m_coro_return;
    };
    return awaiter(this);
  }

 private:
  promise_type* m_promise;
  std::shared_ptr<result_holder> m_result_holder;
};

}  // namespace dkcoro
