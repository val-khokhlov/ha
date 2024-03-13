cmake_minimum_required(VERSION 2.8)

project(ha)
include_directories(include)
set(SOURCE c/acoder.c c/archive.c c/asc.c c/cpy.c c/error.c c/ha.c c/haio.c c/hsc.c c/misc.c c/swdict.c)
set(HEADER include/acoder.h include/archive.h include/asc.h include/cpy.h include/error.h include/ha.h include/haio.h include/hsc.h include/misc.h include/swdict.h)
echo "CMAKE_C_COMPILER=" ${CMAKE_C_COMPILER}
echo "CMAKE_C_COMPILER_ID=" ${CMAKE_C_COMPILER_ID}
if(CMAKE_C_COMPILER_ID EQUAL MSVC)
  set(SOURCE ${SOURCE} win_msvc/dirent.c win_msvc/info.c win_msvc/machine.c)
  set(HEADER ${HEADER} win_msvc/dirent.h win_msvc/dir.h win_msvc/machine.h)
  include_directories(win_msvc)
else()
  set(SOURCE ${SOURCE} nix/info.c nix/machine.c)
  set(HEADER ${HEADER} nix/machine.h)
  include_directories(nix)
endif()

add_executable(ha ${SOURCE})
