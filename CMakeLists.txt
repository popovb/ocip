cmake_minimum_required(VERSION 2.6)

project(ocip)

##################################################################
set(CurrentDir      "${CMAKE_CURRENT_SOURCE_DIR}")
set(SourceDir       "${CurrentDir}/src")
set(TestDir         "${SourceDir}/tests")

include_directories(
  "${SourceDir}"
  )

set(CMAKE_CXX_FLAGS "-Wall")
##################################################################

aux_source_directory("${SourceDir}" ocip_files)
add_library(ocip ${ocip_files})

# ------------------------------------------------------------
function(is_ocidirs_exist)
  if(NOT DEFINED OCI_INC_DIR)
    message("************************************************")
    message("*                                              *")
    message("* re-run cmake with -D OCI_INC_DIR=bla-bla-bla *")
    message("*                                              *")
    message("************************************************")
    message(FATAL_ERROR "OCI_INC_DIR not defined!")
  endif()
  if(NOT DEFINED OCI_LIB_DIR)
    message("************************************************")
    message("*                                              *")
    message("* re-run cmake with -D OCI_LIB_DIR=bla-bla-bla *")
    message("*                                              *")
    message("************************************************")
    message(FATAL_ERROR "OCI_LIB_DIR not defined!")
  endif()
endfunction(is_ocidirs_exist)
# ------------------------------------------------------------

is_ocidirs_exist()
target_include_directories(ocip PRIVATE ${OCI_INC_DIR})
add_library(clntsh SHARED IMPORTED)
set_target_properties(clntsh PROPERTIES IMPORTED_LOCATION ${OCI_LIB_DIR}/libclntsh.so)

add_executable(1 "${TestDir}/1.cpp")
target_link_libraries(1
  ocip
  clntsh
  )

target_include_directories(1 PRIVATE ${OCI_INC_DIR})

target_compile_options(ocip PUBLIC -g -std=c++1y)
target_compile_options(1    PUBLIC -g -std=c++1y)
##################################################################
