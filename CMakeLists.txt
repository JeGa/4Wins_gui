cmake_minimum_required (VERSION 2.8)

project (4Wins_gui)

file(GLOB_RECURSE 4Wins_gui_SOURCES "src/*.cpp")
file(GLOB_RECURSE 4Wins_gui_HEADERS "src/*.h")

set (4Wins_gui_INCLUDE_DIRS "")
foreach (_headerFile ${4Wins_gui_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND 4Wins_gui_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES 4Wins_gui_INCLUDE_DIRS)

include_directories(${4Wins_gui_INCLUDE_DIRS})
add_executable (4Wins_gui ${4Wins_gui_SOURCES})