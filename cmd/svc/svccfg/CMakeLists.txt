add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/svccfg_lex.c
    COMMAND flex
    ARGS -o ${CMAKE_CURRENT_BINARY_DIR}/svccfg_lex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/svccfg.l
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/svccfg.l)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/svccfg_grammar.c
    ${CMAKE_CURRENT_BINARY_DIR}/svccfg_grammar.h
    COMMAND bison
    ARGS -o ${CMAKE_CURRENT_BINARY_DIR}/svccfg_grammar.c
        --defines=${CMAKE_CURRENT_BINARY_DIR}/svccfg_grammar.h
        ${CMAKE_CURRENT_SOURCE_DIR}/svccfg.y
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/svccfg.y)

add_executable(nwcfg svccfg_engine.c svccfg_help.c svccfg_internal.c
    svccfg_libscf.c svccfg_main.c svccfg_tmpl.c svccfg_xml.c
    ${CMAKE_CURRENT_BINARY_DIR}/svccfg_lex.c
    ${CMAKE_CURRENT_BINARY_DIR}/svccfg_grammar.c)
target_include_directories(nwcfg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(nwcfg svc_common_intf nw-scf nw-misc LibXml2::LibXml2
    tecla ssl)