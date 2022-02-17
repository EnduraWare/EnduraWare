add_library(svc_common_intf INTERFACE)
target_include_directories(svc_common_intf
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/common)

add_subdirectory(configd)
add_subdirectory(svccfg)