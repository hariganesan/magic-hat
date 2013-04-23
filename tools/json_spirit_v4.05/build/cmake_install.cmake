# Install script for directory: /Users/Hari/scm/magic-hat/tools/json_spirit_v4.05

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_spirit/json_spirit.h"
    "/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_spirit/json_spirit_error_position.h"
    "/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_spirit/json_spirit_reader.h"
    "/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_spirit/json_spirit_reader_template.h"
    "/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_spirit/json_spirit_stream_reader.h"
    "/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_spirit/json_spirit_utils.h"
    "/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_spirit/json_spirit_value.h"
    "/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_spirit/json_spirit_writer.h"
    "/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/json_spirit/json_spirit_writer_template.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_spirit/libjson_spirit.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_spirit/cmake_install.cmake")
  INCLUDE("/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_demo/cmake_install.cmake")
  INCLUDE("/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_headers_only_demo/cmake_install.cmake")
  INCLUDE("/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_map_demo/cmake_install.cmake")
  INCLUDE("/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/json_test/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/Users/Hari/scm/magic-hat/tools/json_spirit_v4.05/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
