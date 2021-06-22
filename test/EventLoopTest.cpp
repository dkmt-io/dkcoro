/**
 * @author hans@dkmt.io
 * @date 2021-06-22
 */

#include "dkcoro/EventLoop.h"

#include <glog/logging.h>
#include <gtest/gtest.h>

TEST(EventLoopTest, EvTest) {
  using dkcoro::EventLoop;
  auto loop = EventLoop::Create(EventLoop::ProviderType::EV);
  loop->Run();
}

TEST(EventLoopTest, UvTest) {
  using dkcoro::EventLoop;
  auto loop = EventLoop::Create(EventLoop::ProviderType::UV);
  loop->Run();
}

TEST(EventLoopTest, UvSetTimeoutTest) {
  using dkcoro::EventLoop;
  auto loop = EventLoop::Create(EventLoop::ProviderType::UV);
  LOG(INFO) << "timer begin";
  loop->SetTimeout([]() { LOG(INFO) << "timer end"; }, 1000);
  loop->Run();
}
