add_library(ZECS INTERFACE)

# PUBLIC: consumers of ZECS inherit this include path automatically.
target_include_directories(ZECS INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)
