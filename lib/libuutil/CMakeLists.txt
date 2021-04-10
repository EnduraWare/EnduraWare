add_library(nw-uutil uu_alloc.c uu_avl.c uu_dprintf.c uu_ident.c uu_list.c
    uu_misc.c uu_open.c uu_pname.c uu_string.c uu_strtoint.c)
target_include_directories(nw-uutil PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(nw-uutil nw-compat nw-avl)