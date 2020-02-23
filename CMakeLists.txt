cmake_minimum_required(VERSION 3.11)
project(AI_HW3 C CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

file (GLOB HEADER_FILES
      "include/*.h")
file (GLOB SOURCE_FILES
      "src/*.cpp")
	  
source_group("Source Files" FILES ${SOURCE_FILES})
source_group("Header Files" FILES ${HEADER_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER ${PROJECT_NAME})

if (MSVC)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif ()