/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#pragma once

#include "event_loop.h"
#include "timer.h"
#include "uncopyable.h"

#include <uv.h>

#include <memory>

namespace dkcoro {

class uv_event_loop final : public event_loop {
 public:
  static std::shared_ptr<uv_event_loop> create();

  virtual void run() override;

  virtual std::shared_ptr<timer> set_timeout(
    const timer::callback&, uint64_t  // clang-format off
  ) override;  // clang-format on

  virtual std::shared_ptr<timer> set_interval(
    const timer::callback&, uint64_t  // clang-format off
  ) override;  // clang-format on

  virtual ~uv_event_loop();

 protected:
  uv_event_loop();

  uv_loop_t m_uv_loop;

 private:
  DK_DECLARE_UNCOPYABLE(uv_event_loop);
};

}  // namespace dkcoro
