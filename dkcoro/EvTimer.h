/**
 * @author hans@dkmt.o
 * @date 2021-06-22
 */

#pragma once

#include "Timer.h"
#include "Uncopyable.h"

namespace dkcoro {  //

class EvTimer final : public Timer {
 public:
  static std::shared_ptr<EvTimer> Create(const Timer::Options& options);

  virtual bool Start() override;

  virtual bool Stop() override;

  virtual ~EvTimer() {}

 protected:
  EvTimer(const Timer::Options& options);

 private:
  DK_DECLARE_UNCOPYABLE(EvTimer);
};

}  // namespace dkcoro