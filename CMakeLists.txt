# CMakeLists.txt for the object library
cmake_minimum_required(VERSION 3.12)
project(stm-lib)

# Create the object library
add_library(stm_lib INTERFACE)

# Add header files
target_include_directories(stm_lib INTERFACE
    Inc/
)

# Example LIB_COMPS
# set(LIB_COMPS
#     ENCODER
#     BUTTON
# )

foreach(LIB_COMP IN LISTS LIB_COMPS)
    string(TOLOWER "${LIB_COMP}" LOWER_COMP)
    target_sources(stm_lib INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/${LOWER_COMP}.c
    )
endforeach()

