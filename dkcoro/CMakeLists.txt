add_library(dkcoro
  callback_awaiter.cpp
  callback_awaiter.h
  coro_return.cpp
  coro_return.h
  delay.cpp
  delay.h
  event_loop.cpp
  event_loop.h
  ev_event_loop.cpp
  ev_event_loop.h
  ev_timer.cpp
  ev_timer.h
  timer.cpp
  timer.h
  uncopyable.cpp
  uncopyable.h
  utils.cpp
  utils.h
  uv_event_loop.cpp
  uv_event_loop.h
  uv_timer.cpp
  uv_timer.h
)

target_include_directories(dkcoro PUBLIC ${GFLAGS_INCLUDE_DIRS})
target_compile_options(dkcoro PUBLIC ${GFLAGS_CFLAGS})
target_link_libraries(dkcoro PUBLIC ${GFLAGS_LINK_LIBRARIES})
target_link_options(dkcoro PUBLIC ${GFLAGS_LINK_LDFLAGS})

target_include_directories(dkcoro PUBLIC ${LIBGLOG_INCLUDE_DIRS})
target_compile_options(dkcoro PUBLIC ${LIBGLOG_CFLAGS})
target_link_libraries(dkcoro PUBLIC ${LIBGLOG_LINK_LIBRARIES})
target_link_options(dkcoro PUBLIC ${LIBGLOG_LINK_LDFLAGS})

target_include_directories(dkcoro PUBLIC ${LIBUV_INCLUDE_DIRS})
target_compile_options(dkcoro PUBLIC ${LIBUV_CFLAGS})
target_link_libraries(dkcoro PUBLIC ${LIBUV_LINK_LIBRARIES})
target_link_options(dkcoro PUBLIC ${LIBUV_LINK_LDFLAGS})

target_include_directories(dkcoro PUBLIC ${LIBUV_INCLUDE_DIRS})
target_compile_options(dkcoro PUBLIC ${LIBUV_CFLAGS})
target_link_libraries(dkcoro PUBLIC ${LIBUV_LINK_LIBRARIES})
target_link_options(dkcoro PUBLIC ${LIBUV_LINK_LDFLAGS})

target_include_directories(dkcoro PUBLIC ${LIBEVENT_INCLUDE_DIRS})
target_compile_options(dkcoro PUBLIC ${LIBEVENT_CFLAGS})
target_link_libraries(dkcoro PUBLIC ${LIBEVENT_LINK_LIBRARIES})
target_link_options(dkcoro PUBLIC ${LIBEVENT_LINK_LDFLAGS})
