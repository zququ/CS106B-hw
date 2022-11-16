add_library(cslib)

file(GLOB_RECURSE cslib_files CONFIGURE_DEPENDS *.cpp *.h)
target_sources(cslib PUBLIC ${cslib_files})

set(HEADER_FILES
     ${CMAKE_CURRENT_SOURCE_DIR}/include/
     ${CMAKE_CURRENT_SOURCE_DIR}/include/private
)

target_include_directories(cslib
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
PRIVATE
     ${HEADER_FILES}
)
