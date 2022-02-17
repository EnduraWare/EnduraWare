project(EnduraWare)
cmake_minimum_required(VERSION 3.9)
cmake_policy(VERSION 3.9)

include(CMakePushCheckState)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

#
# feature checking assistance
#

list(APPEND CMAKE_REQUIRED_DEFINITIONS "-D_GNU_SOURCE -D__BSD_VISIBLE")

macro(check_type_size_in type headers var)
  cmake_push_check_state()
  list(APPEND CMAKE_REQUIRED_DEFINITIONS "-D_GNU_SOURCE -D__BSD_VISIBLE")
  set(CMAKE_EXTRA_INCLUDE_FILES ${headers})
  check_type_size(${type} ${var})
  cmake_push_check_state(RESET)
endmacro()

#
# platform checking
#

if(CMAKE_SYSTEM_NAME MATCHES ".*Linux")
    set(Plat_Linux TRUE)
    add_definitions("-D_GNU_SOURCE")
elseif(CMAKE_SYSTEM_NAME MATCHES "DragonFly.*")
    set(Plat_BSD TRUE)
    set(Plat_DragonFlyBSD TRUE)
elseif(CMAKE_SYSTEM_NAME MATCHES "kFreeBSD.*|FreeBSD")
    set(Plat_BSD TRUE)
    set(Plat_FreeBSD TRUE)
elseif(CMAKE_SYSTEM_NAME MATCHES "kNetBSD.*|NetBSD.*")
    set(Plat_BSD TRUE)
    set(Plat_NetBSD TRUE)
elseif(CMAKE_SYSTEM_NAME MATCHES "kOpenBSD.*|OpenBSD.*")
    set(Plat_BSD TRUE)
    set(Plat_OpenBSD TRUE)
elseif(CMAKE_SYSTEM_NAME MATCHES "HP-UX")
    set(Plat_HPUX TRUE)
    # make _r functions available
    add_definitions(-D_REENTRANT=1)
elseif(APPLE)
    set(Plat_BSD TRUE)
endif()

#
# prerequisites
#
find_package(Threads)


#
# types
#

check_type_size("void *" Size_VoidStar)

#
# functions, variables, and macros
#
check_symbol_exists(program_invocation_short_name "errno.h" Have_program_invocation_short_name)

add_subdirectory(lib)
add_subdirectory(cmd)