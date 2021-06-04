# Install script for directory: /home/duan0308/C_project (copy)/cgraph/ctc

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/bkc/ctc" TYPE FILE FILES
    "/home/duan0308/C_project (copy)/cgraph/ctc/array.h"
    "/home/duan0308/C_project (copy)/cgraph/ctc/common.h"
    "/home/duan0308/C_project (copy)/cgraph/ctc/deque.h"
    "/home/duan0308/C_project (copy)/cgraph/ctc/hashset.h"
    "/home/duan0308/C_project (copy)/cgraph/ctc/hashtable.h"
    "/home/duan0308/C_project (copy)/cgraph/ctc/list.h"
    "/home/duan0308/C_project (copy)/cgraph/ctc/pqueue.h"
    "/home/duan0308/C_project (copy)/cgraph/ctc/queue.h"
    "/home/duan0308/C_project (copy)/cgraph/ctc/ring_buffer.h"
    "/home/duan0308/C_project (copy)/cgraph/ctc/slist.h"
    "/home/duan0308/C_project (copy)/cgraph/ctc/stack.h"
    "/home/duan0308/C_project (copy)/cgraph/ctc/treeset.h"
    "/home/duan0308/C_project (copy)/cgraph/ctc/treetable.h"
    "/home/duan0308/C_project (copy)/cgraph/ctc/tsttable.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/bkc/ctc/my" TYPE FILE FILES "/home/duan0308/C_project (copy)/cgraph/ctc/my/hsi.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/duan0308/C_project (copy)/b/cgraph/ctc/libcollectc.a")
endif()

