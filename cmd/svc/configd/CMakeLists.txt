add_executable(nw.configd backend.c)
target_link_libraries(nw.configd svc_common_intf nw-sqlite nw-scf)