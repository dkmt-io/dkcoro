add_executable(EventLoopTest EventLoopTest.cpp)
target_link_libraries(EventLoopTest PUBLIC dkcoro)
target_include_directories(EventLoopTest PUBLIC ${GTEST_INCLUDE_DIRS})
target_compile_options(EventLoopTest PUBLIC ${GTEST_CFLAGS})
target_link_libraries(EventLoopTest PUBLIC ${GTEST_LINK_LIBRARIES})
target_link_libraries(EventLoopTest PUBLIC ${GTEST_MAIN_LINK_LIBRARIES})
target_link_options(EventLoopTest PUBLIC ${GTEST_LINK_LDFLAGS})

add_test(NAME EventLoopTest COMMAND EventLoopTest)
