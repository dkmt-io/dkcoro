/**
 * @author hans@dkmt.io
 * @date 2021-06-24
 */

#include "utils.h"

#include <chrono>

namespace dkcoro {

int64_t utils::current_time_millis() {
  using std::chrono::duration_cast;
  using std::chrono::milliseconds;
  using std::chrono::system_clock;
  auto now = system_clock::now();
  return duration_cast<milliseconds>(now.time_since_epoch()).count();
}

int64_t utils::now() {
  return current_time_millis();
}

int64_t utils::nano_time() {
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  using std::chrono::nanoseconds;
  auto now = high_resolution_clock::now();
  return duration_cast<nanoseconds>(now.time_since_epoch()).count();
}

}  // namespace dkcoro