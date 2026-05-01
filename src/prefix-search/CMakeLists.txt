find_package(Threads REQUIRED)

add_executable(prefix_search main.c)
target_link_libraries(prefix_search PRIVATE sha256 Threads::Threads)