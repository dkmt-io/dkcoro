add_library(dkcoro
  CoReturn.cpp
  CoReturn.h
  EventLoop.cpp
  EventLoop.h
  EvEventLoop.cpp
  EvEventLoop.h
  UvEventLoop.cpp
  UvEventLoop.h
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
