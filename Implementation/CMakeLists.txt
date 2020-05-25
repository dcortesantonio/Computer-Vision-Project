CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## ================
## = Project name =
## ================

PROJECT( Intensities_ITK_OCV )

## ============
## = Packages =
## ============

FIND_PACKAGE( OpenCV REQUIRED )

## ================================================
## = Do not allow to build inside the source tree =
## ================================================

IF(PROJECT_BINARY_DIR STREQUAL ${PROJECT_SOURCE_DIR})
  MESSAGE(FATAL_ERROR "Building in the source tree is not allowed")
ENDIF(PROJECT_BINARY_DIR STREQUAL ${PROJECT_SOURCE_DIR})

## =====================================
## = Where to put executables and libs =
## =====================================

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
MARK_AS_ADVANCED(
  CMAKE_BACKWARDS_COMPATIBILITY
  EXECUTABLE_OUTPUT_PATH
  LIBRARY_OUTPUT_PATH
  )

## =======================
## = Programs to compile =
## =======================
include_directories(include)
# add Coin library
add_library(
            Libraries
            Coin.h
            Coin.cxx
            ImageProcess.h
            ImageProcess.cxx
            )
ADD_EXECUTABLE( main Main.cxx )
TARGET_LINK_LIBRARIES( main  PRIVATE Libraries  ${OpenCV_LIBS} )

