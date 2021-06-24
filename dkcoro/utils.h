/**
 * @author hans@dkmt.io
 * @date 2021-06-24
 */

#pragma once

#include <stdint.h>

namespace dkcoro {

class utils final {
 public:
  static int64_t current_time_millis();

  static int64_t now();

  static int64_t nano_time();
};

}  // namespace dkcoro