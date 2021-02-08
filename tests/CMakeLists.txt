set(INCLUDES_SERVER_DIR ${PROJECT_SOURCE_DIR}/include/Server)
set(SRCS_SERVER_DIR ${PROJECT_SOURCE_DIR}/src/Server)
set(TESTS_SERVER_DIR ${PROJECT_SOURCE_DIR}/tests)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_package(Threads)

# -------------------------------- SERVER SOURCES -------------------------------- #
set(SRCS_SERVER ${SRCS_SERVER_DIR}/jsonReader.cpp
                ${SRCS_SERVER_DIR}/Error.cpp
                ${SRCS_SERVER_DIR}/pathHandler.cpp
                ${SRCS_SERVER_DIR}/serverCore.cpp
                ${SRCS_SERVER_DIR}/tcpConnection.cpp
                ${SRCS_SERVER_DIR}/processingList.cpp
                ${SRCS_SERVER_DIR}/HTTPObject.cpp
                ${SRCS_SERVER_DIR}/requestManager.cpp
                ${SRCS_SERVER_DIR}/configHandler.cpp
                ${SRCS_SERVER_DIR}/SignalHandler.cpp
)

# -------------------------------- TESTS SERVER -------------------------------- #
set(TESTS_SERVER ${TESTS_SERVER_DIR}/testJsonReader.cpp
                 ${TESTS_SERVER_DIR}/testPathHandler.cpp
                 ${TESTS_SERVER_DIR}/testProcessingList.cpp
                 ${TESTS_SERVER_DIR}/testHTTPObject.cpp
                 ${TESTS_SERVER_DIR}/testConfigHandler.cpp

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
target_link_libraries(unit_tests_server ${CMAKE_DL_LIBS})
add_test(second unit_tests_server)
