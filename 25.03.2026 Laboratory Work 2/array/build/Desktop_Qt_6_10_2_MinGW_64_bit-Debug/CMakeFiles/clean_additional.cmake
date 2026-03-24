# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\array_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\array_autogen.dir\\ParseCache.txt"
  "array_autogen"
  )
endif()
