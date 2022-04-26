include(${PROJECT_SOURCE_DIR}/cmake.macros)
subdirlist(children_dirs ${CMAKE_CURRENT_SOURCE_DIR})

foreach(child ${children_dirs})
  get_filename_component(module ${child} NAME)
  message("Processing module: ${module}")
  include_directories(${CMAKE_SOURCE_DIR}/include)
  file(GLOB source_files_exe_${module} "${CMAKE_CURRENT_SOURCE_DIR}/${module}/*.cpp")
  if(NOT
     "${source_files_exe_${module}}"
     STREQUAL
     "")
    add_executable(${module}_exe ${source_files_exe_${module}})
    target_link_libraries(${module}_exe project_warnings project_options)
  else()
    message("No source files have been discovered for ${module} module")
  endif()

endforeach()
