#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "approxmc" for configuration "Debug"
set_property(TARGET approxmc APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(approxmc PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/approxmc"
  )

list(APPEND _IMPORT_CHECK_TARGETS approxmc )
list(APPEND _IMPORT_CHECK_FILES_FOR_approxmc "${_IMPORT_PREFIX}/bin/approxmc" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
