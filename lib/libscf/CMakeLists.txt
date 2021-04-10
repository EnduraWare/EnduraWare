add_library(nw-scf error.c highlevel.c)
target_include_directories(nw-scf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(nw-scf nw-nvpair nw-uutil)