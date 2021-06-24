/**
 * @author Hans Liu (hans@dkmt.io)
 * @since 2021-06-20
 */

#include <stdlib.h>
#include <iostream>

#include "dkcoro/coro_return.h"
#include "dkcoro/ev_event_loop.h"
#include "dkcoro/event_loop.h"

int main(int argc, char** argv) {
  auto loop = dkcoro::event_loop::create();
  loop->run();
  return EXIT_SUCCESS;
}
