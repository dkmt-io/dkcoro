/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#include <stdlib.h>
#include <iostream>

#include "dkcoro/CoReturn.h"
#include "dkcoro/EvEventLoop.h"
#include "dkcoro/EventLoop.h"

int main(int argc, char** argv) {
  auto loop = dkcoro::EvEventLoop::Create();
  loop->Run();
  return EXIT_SUCCESS;
}
