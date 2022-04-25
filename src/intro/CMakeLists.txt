add_executable(intro main.cpp)

target_link_libraries(
  intro
  PRIVATE project_options
          project_warnings
          )

target_include_directories(intro PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
