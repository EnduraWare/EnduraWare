add_executable(lemon tool/lemon.c)

set(File_sqlite_h_in ${CMAKE_CURRENT_SOURCE_DIR}/src/sqlite.h.in)
set(File_sqlite_h ${CMAKE_CURRENT_BINARY_DIR}/sqlite.h)
set(File_parse_h ${CMAKE_CURRENT_BINARY_DIR}/parse.h)
set(File_parse_c ${CMAKE_CURRENT_BINARY_DIR}/parse.c)

add_custom_command(
    OUTPUT ${File_sqlite_h}
    COMMAND sed -e 's\"--VERS--\"${SQLite_Version}\"'
        -e s/--ENCODING--/${SQLite_Encoding}/ 
        ${File_sqlite_h_in}
        > ${File_sqlite_h}
)

add_custom_command(
    OUTPUT ${File_parse_h} ${File_parse_c}
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/tool/lempar.c ./
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/src/parse.y ./
    COMMAND $<TARGET_FILE:lemon> parse.y
)

add_custom_command(
    OUTPUT opcodes.h opcodes.c
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/tool/genopcodes.sh
      ${CMAKE_CURRENT_SOURCE_DIR}/src/vdbe.c
)

add_library(nw-sqlite src/attach.c src/auth.c src/btree.c src/btree_rb.c
    src/build.c src/copy.c src/date.c src/delete.c src/expr.c src/func.c 
    src/hash.c src/insert.c src/main.c src/os.c src/pager.c src/pragma.c
    src/printf.c src/random.c src/select.c src/table.c src/tokenize.c
    src/trigger.c src/update.c src/util.c src/vacuum.c src/vdbe.c src/vdbeaux.c
    src/where.c src/tclsqlite.c
    ${File_sqlite_h}
    ${File_parse_h}
    ${File_parse_c}
    ${CMAKE_CURRENT_BINARY_DIR}/opcodes.h ${CMAKE_CURRENT_BINARY_DIR}/opcodes.c)

target_include_directories(nw-sqlite
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)