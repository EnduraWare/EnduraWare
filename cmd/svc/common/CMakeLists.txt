add_library(nw-misc manifest_find.c manifest_hash.c notify_params.c)
target_link_libraries(nw-misc svc_common_intf nw-scf ssl crypto)