/**
 * @author hans@dkmt.o
 * @date 2021-06-24
 */

#pragma once

#include "coro_return.h"
#include "event_loop.h"

#include <stdint.h>
#include <memory>

namespace dkcoro {  //

coro_return<> delay(const std::shared_ptr<event_loop>& loop, int64_t ms);

}  // namespace dkcoro