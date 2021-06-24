/**
 * @author hans@dkmt.o
 * @date 2021-06-24
 */

#include "delay.h"

#include "callback_awaiter.h"
#include "utils.h"

#include <stdint.h>
#include <utility>

namespace dkcoro {  //

coro_return<int64_t> delay(
  const std::shared_ptr<event_loop>& loop, int64_t ms  //
) {
  callback_awaiter<int64_t>::read_action read = [loop, ms](auto cb) {
    int64_t t0 = utils::now();
    loop->set_timeout(
      [cb, t0]() {
        int64_t t1 = utils::now();
        int64_t duration = t1 - t0;
        cb(std::move(duration));
      },
      ms  //
    );
  };
  auto awaiter_ptr = dkcoro::callback_awaiter<int64_t>::create(read);
  dkcoro::callback_awaiter<int64_t>& awaiter = *awaiter_ptr;
  int64_t duration = co_await awaiter;
  co_return std::move(duration);
}

}  // namespace dkcoro