include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

# If pkg-config is not installed on the system, then the
# CHECK_INSTALL_DIR variable must be set to the install
# location of Check. For example, on Windows, this may
# be: C:/Program Files/check
# set(CHECK_INSTALL_DIR "C:/Program Files/check")

find_package(Check REQUIRED)
# Deal with "undefined reference to symbol '__pthread_unregister_cancel@@GLIBC_2.3.3'" error
# https://github.com/libcheck/check/issues/48#issuecomment-353591603
find_package(Threads REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})

set(TEST_SOURCES
  check_hello_world.c
)

add_executable(check_hello_world ${TEST_SOURCES})
target_link_libraries(check_hello_world helloworld ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
