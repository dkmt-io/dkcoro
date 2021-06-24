/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#include "coro_return.h"

#include <coroutine>

namespace dkcoro {

coro_return<> coro_return<>::promise_type::get_return_object() {
  return coro_return<>(this);
}

std::suspend_never coro_return<>::promise_type::initial_suspend() {
  return {};
}

std::suspend_never coro_return<>::promise_type::final_suspend() noexcept {
  return {};
}

void coro_return<>::promise_type::unhandled_exception() {
  auto exception_ptr = std::current_exception();
  try {
    CHECK_NOTNULL(exception_ptr);
    std::rethrow_exception(exception_ptr);
  } catch (const std::exception& e) {
    LOG(FATAL) << "unhandled exception: " << e.what();
  }
}

void coro_return<>::promise_type::return_void() {
  auto holder = m_result_holder.lock();
  if (holder == nullptr) {
    return;
  }
  holder->result_ready = true;
  if (m_awaiter_coro == nullptr) {
    return;
  }
  m_awaiter_coro.resume();
}

void coro_return<>::promise_type::set_awaiter_coro(
  const std::coroutine_handle<>& coro) {
  CHECK(m_awaiter_coro == nullptr);
  m_awaiter_coro = coro;
}

void coro_return<>::promise_type::set_result_holder(
  const std::shared_ptr<result_holder>& holder) {
  m_result_holder = holder;
}

coro_return<>::coro_return(promise_type* promise) :
  m_promise(promise),
  m_result_holder(new result_holder())  //
{
  CHECK_NOTNULL(m_promise);
  m_promise->set_result_holder(m_result_holder);
}

}  // namespace dkcoro
