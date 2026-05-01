find_package(Threads REQUIRED)

add_executable(prefix_search main.c)
target_link_libraries(prefix_search PRIVATE sha256 Threads::Threads)

add_custom_target(run_prefix_search
        COMMAND prefix_search
        DEPENDS prefix_search
        COMMENT "Running Prefix Search..."
        USES_TERMINAL
)