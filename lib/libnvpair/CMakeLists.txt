add_library(nw-nvpair libnvpair.c nvpair.c nvpair_alloc_system.c)
target_include_directories(nw-nvpair PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})