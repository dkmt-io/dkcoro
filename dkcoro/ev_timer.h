/**
 * @author hans@dkmt.o
 * @date 2021-06-22
 */

#pragma once

#include "timer.h"
#include "uncopyable.h"

namespace dkcoro {  //

class ev_timer final : public timer {
 public:
  static std::shared_ptr<ev_timer> create(const timer::options& options);

  virtual bool start() override;

  virtual bool stop() override;

  virtual ~ev_timer() {}

 protected:
  ev_timer(const timer::options& options);

 private:
  DK_DECLARE_UNCOPYABLE(ev_timer);
};

}  // namespace dkcoro