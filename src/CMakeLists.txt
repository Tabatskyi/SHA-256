add_library(sha256 STATIC sha256.c)
target_include_directories(sha256 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main main.c)
target_link_libraries(main PRIVATE sha256)

add_subdirectory(prefix-search)