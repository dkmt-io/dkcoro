/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#pragma once

#include "timer.h"
#include "uncopyable.h"

#include <memory>

namespace dkcoro {

class event_loop {
 public:
  enum class type : uint8_t {
    EV = 1,
    UV = 2,
  };

  static std::shared_ptr<event_loop> create(
    const type type = type::UV  //
  );

  virtual void run() = 0;

  virtual std::shared_ptr<timer> set_timeout(
    const timer::callback&, uint64_t  // clang-format off
  ) = 0;  // clang-format on

  virtual std::shared_ptr<timer> set_interval(
    const timer::callback&, uint64_t  // clang-format off
  ) = 0;  // clang-format on

  virtual ~event_loop() {}

 protected:
  event_loop() {}

 private:
  DK_DECLARE_UNCOPYABLE(event_loop);
};

}  // namespace dkcoro
