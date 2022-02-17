add_executable(nw.configd backend.c file_object.c object.c rc_node.c snapshot.c)
target_link_libraries(nw.configd svc_common_intf nw-sqlite nw-scf)