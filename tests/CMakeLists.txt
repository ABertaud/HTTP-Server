set(INCLUDES_SERVER_DIR ${PROJECT_SOURCE_DIR}/include/Server)
set(SRCS_SERVER_DIR ${PROJECT_SOURCE_DIR}/src/Server)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_package(Threads)

# -------------------------------- SERVER SOURCES -------------------------------- #
set(SRCS_SERVER ${SRCS_SERVER_DIR}/src.cpp
)

# -------------------------------- TESTS SERVER -------------------------------- #
set(TESTS_SERVER ${TESTS_SERVER_DIR}/test.cpp
)

add_executable(unit_tests_server ${TESTS_SERVER} ${SRCS_SERVER})
target_compile_features(unit_tests_server PRIVATE cxx_std_17)
target_compile_options(unit_tests_server
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3>)
target_include_directories(unit_tests_server PRIVATE SYSTEM ${INCLUDES_SERVER_DIR})
target_link_libraries(unit_tests_server criterion)
target_link_libraries(unit_tests_server ${CONAN_LIBS})
target_link_libraries(unit_tests_server ${CMAKE_THREAD_LIBS_INIT})
add_test(second unit_tests_server)
