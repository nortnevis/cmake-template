include(cmake/SetupEnvironments.cmake)

project(
  TemplateProject
  DESCRIPTION "This is a template cmake project."
  VERSION ${GIT_DESCRIBED_TAG}
  LANGUAGES CXX)

include(cmake/CompileFlags.cmake)
find_or_fetch_dependency(
  simdjson 4.6.7 https://github.com/simdjson/simdjson.git 4.6.7
  simdjson::simdjson)

add_library(pch INTERFACE ${pch_files})
target_precompile_headers(
  project_options INTERFACE
  "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/include/pch/pch.hpp>")

target_precompile_headers(pch PUBLIC pch/pch.hpp)
target_link_libraries(pch PUBLIC raylib glfw OpenCL::OpenCL)

file(GLOB_RECURSE hpp_files CONFIGURE_DEPENDS include/*.hpp)
file(GLOB_RECURSE cpp_files CONFIGURE_DEPENDS src/*.cpp)

add_executable(app ${hpp_files} ${cpp_files})
target_precompile_headers(app REUSE_FROM pch)
target_link_libraries(app PRIVATE pch)

if(EXISTS "${PROJECT_SOURCE_DIR}/snippets/")
  add_subdirectory(snippets)
endif()

if(EXISTS ${PROJECT_BINARY_DIR}/compile_commands.json)
  message(
    "Copying ${PROJECT_BINARY_DIR}/compile_commands.json to root directory")
  file(COPY ${PROJECT_BINARY_DIR}/compile_commands.json
       DESTINATION ${PROJECT_SOURCE_DIR})
else()
  # message(WARNING "File ${PROJECT_BINARY_DIR}/compile_commands.json not found.
  # Maybe this file didn't created yet, so reconfigure CMake project.")
endif()
