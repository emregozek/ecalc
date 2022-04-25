
# Generic test that uses conan libs
file(GLOB source_files_ecalc "*.cpp")
add_executable(ecalc ${source_files_ecalc})
target_link_libraries(
    ecalc
  PRIVATE project_options
          project_warnings
          )

target_include_directories(ecalc PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

