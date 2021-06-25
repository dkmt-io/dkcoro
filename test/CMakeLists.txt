add_executable(event_loop_test event_loop_test.cpp)

target_link_libraries(event_loop_test PUBLIC dkcoro)

target_include_directories(event_loop_test PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(event_loop_test PUBLIC ${GTEST_LINK_LIBRARIES})
target_link_libraries(event_loop_test PUBLIC ${GTEST_MAIN_LINK_LIBRARIES})

add_test(NAME event_loop_test COMMAND event_loop_test)
