add_executable(GoogleTestsRun main.cpp crc-bufferTest.cpp)

add_subdirectory(crc)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${crc_SOURCE_DIR})

target_link_libraries(GoogleTestsRun crc-buffer gtest gtest_main crc)