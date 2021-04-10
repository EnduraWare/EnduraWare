configure_file(config.h.in config.h)
add_library(nw-compat compat.c)
target_include_directories(nw-compat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})