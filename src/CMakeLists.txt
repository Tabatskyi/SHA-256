add_library(sha256 STATIC sha256.c)
target_include_directories(sha256 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(sha256 PRIVATE
	-O3
	-Wall
	-Wextra
	-Wpedantic
	-Werror=implicit-function-declaration
)

add_executable(main main.c)
target_link_libraries(main PRIVATE sha256)

target_compile_options(main PRIVATE
	-O3
	-Wall
	-Wextra
	-Wpedantic
	-Werror=implicit-function-declaration
)

add_subdirectory(prefix-search)