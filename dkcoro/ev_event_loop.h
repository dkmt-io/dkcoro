/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#pragma once

#include "event_loop.h"
#include "uncopyable.h"

#include <event2/event.h>

#include <memory>

namespace dkcoro {

class ev_event_loop final : public event_loop {
 public:
  static std::shared_ptr<ev_event_loop> create();

  virtual void run() override;

  virtual std::shared_ptr<timer> set_timeout(
    const timer::callback&, uint64_t  // clang-format off
  ) override;  // clang-format on

  virtual std::shared_ptr<timer> set_interval(
    const timer::callback&, uint64_t  // clang-format off
  ) override;  // clang-format on

  virtual ~ev_event_loop();

 protected:
  ev_event_loop();

  event_base* m_event_base = nullptr;

 private:
  DK_DECLARE_UNCOPYABLE(ev_event_loop);
};

}  // namespace dkcoro
