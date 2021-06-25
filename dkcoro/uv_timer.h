/**
 * @author hans@dkmt.o
 * @date 2021-06-22
 */

#pragma once

#include "timer.h"
#include "uncopyable.h"

#include <uv.h>

#include <stdint.h>
#include <memory>

namespace dkcoro {  //

class uv_timer final : public timer,
                       public std::enable_shared_from_this<uv_timer> {
 public:
  static std::shared_ptr<uv_timer> create(
    const timer::options& options, uv_loop_t* loop  //
  );

  virtual bool start() override;

  virtual bool stop() override;

  virtual ~uv_timer() {}

 protected:
  uv_timer(const timer::options& options, uv_loop_t* loop);

  timer::callback m_cb;
  const uint64_t m_delay;
  bool m_finished = false;
  std::shared_ptr<uv_timer> m_self;
  const bool m_repeat;
  uv_any_handle m_uv_handle;

  static void close_cb(uv_handle_t* handle);

  static void timer_cb(uv_timer_t* timer);

 private:
  DK_DECLARE_UNCOPYABLE(uv_timer);
};

}  // namespace dkcoro