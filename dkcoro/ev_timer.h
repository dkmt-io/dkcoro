/**
 * @author hans@dkmt.o
 * @date 2021-06-22
 */

#pragma once

#include "timer.h"
#include "uncopyable.h"

#include <event2/event.h>

namespace dkcoro {  //

class ev_timer final : public timer,
                       public std::enable_shared_from_this<ev_timer> {
 public:
  static std::shared_ptr<ev_timer> create(
    const timer::options& options, event_base* base  //
  );

  virtual bool start() override;

  virtual bool stop() override;

  virtual ~ev_timer();

 protected:
  ev_timer(const timer::options& options, event_base* base);

  timer::callback m_cb;
  const uint64_t m_delay;
  event* m_event = nullptr;
  bool m_finished = false;
  std::shared_ptr<ev_timer> m_self;
  const bool m_repeat;

  static void timeout_cb(evutil_socket_t fd, short event, void* arg);

 private:
  DK_DECLARE_UNCOPYABLE(ev_timer);
};

}  // namespace dkcoro