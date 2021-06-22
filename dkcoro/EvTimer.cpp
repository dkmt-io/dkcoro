/**
 * @author hans@dkmt.o
 * @date 2021-06-22
 */

#include "EvTimer.h"

namespace dkcoro {  //

std::shared_ptr<EvTimer> EvTimer::Create(const Timer::Options& options) {
  std::shared_ptr<EvTimer> timer(new EvTimer(options));
  return timer;
}

EvTimer::EvTimer(const Timer::Options& options) {}

bool EvTimer::Start() {
  return false;
}

bool EvTimer::Stop() {
  return false;
}

}  // namespace dkcoro