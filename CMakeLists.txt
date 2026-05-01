cmake_minimum_required(VERSION 3.25)

project(SHA_256
    VERSION 0.0.1
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT CMAKE_C_COMPILER_ID STREQUAL "GNU")
    message(WARNING
        "This project targets GCC 15+ for complete C23 support. "
        "Current compiler: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}. "
        "Behaviour may differ or be incompatible."
    )
elseif(CMAKE_C_COMPILER_VERSION VERSION_LESS "15")
    message(WARNING
        "GCC 15 or later is required for full C23 support. "
        "Detected GCC ${CMAKE_C_COMPILER_VERSION}. "
        "Behaviour may differ or be incompatible."
    )
endif()


enable_testing()

add_subdirectory(src)

target_compile_options(sha256 PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror=implicit-function-declaration
)
