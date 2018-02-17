set(GLOB_RECURSE "service_history_src" ./src/services/history/History.*)

add_executable(history ${service_history_src} tests/history.unit.cpp)
add_test(HISTORY history)
