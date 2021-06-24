/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#include "async_awaiter.h"

namespace dkcoro {

std::shared_ptr<async_awaiter<>> async_awaiter<>::create(
  const async_action& action  //
) {
  using self_type = async_awaiter<>;
  std::shared_ptr<self_type> self(new self_type());
  std::weak_ptr<self_type> weak_self(self);
  action([weak_self]() {
    auto self = weak_self.lock();
    if (self == nullptr) {
      return;
    }
    CHECK(!self->m_result_ready);
    self->m_result_ready = true;
    if (self->m_coro != nullptr) {
      self->m_coro.resume();
    }
  });
  return self;
}

bool async_awaiter<>::await_ready() {  //
  CHECK(!m_await_ready_called);
  m_await_ready_called = true;
  return m_result_ready;
}

void async_awaiter<>::await_suspend(std::coroutine_handle<> coro) {
  CHECK(!m_result_ready);
  CHECK(m_coro == nullptr);
  m_coro = coro;
}

void async_awaiter<>::await_resume() {
  CHECK(m_result_ready);
  return;
}

}  // namespace dkcoro
