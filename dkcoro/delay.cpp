/**
 * @author hans@dkmt.o
 * @date 2021-06-24
 */

#include "delay.h"

#include "async_awaiter.h"
#include "utils.h"

#include <stdint.h>
#include <utility>

namespace dkcoro {  //

coro_return<> delay(
  const std::shared_ptr<event_loop>& loop, int64_t ms  //
) {
  async_awaiter<>::async_action action = [loop, ms](auto cb) {
    loop->set_timeout(cb, ms);
  };
  auto awaiter_ptr = dkcoro::async_awaiter<>::create(action);
  dkcoro::async_awaiter<>& awaiter = *awaiter_ptr;
  co_await awaiter;
  co_return;
}

}  // namespace dkcoro