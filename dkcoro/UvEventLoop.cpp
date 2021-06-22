/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#include "UvEventLoop.h"

namespace dkcoro {

std::shared_ptr<UvEventLoop> UvEventLoop::Create() {
  std::shared_ptr<UvEventLoop> self(new UvEventLoop());
  return self;
}

UvEventLoop::UvEventLoop() {}

UvEventLoop::~UvEventLoop() {}

void UvEventLoop::Run() {}

}  // namespace dkcoro
