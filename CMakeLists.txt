cmake_minimum_required(VERSION 2.8)

project(4Wins_gui)

# Variables //!!
set(BOOST_TEST_INCLUDE_DIR, "F:/ext/boost")

# Build project
file(GLOB_RECURSE 4Wins_gui_SOURCES "src/*.cpp")
file(GLOB_RECURSE 4Wins_gui_HEADERS "src/*.h")

set(4Wins_gui_INCLUDE_DIRS "")
foreach (_headerFile ${4Wins_gui_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND 4Wins_gui_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES 4Wins_gui_INCLUDE_DIRS)

include_directories(${4Wins_gui_INCLUDE_DIRS})

# Build Boost unit tests
if (${CMAKE_BUILD_TYPE} STREQUAL "Test")

	# Remove main
	list(REMOVE_ITEM 4Wins_gui_INCLUDE_DIRS "src/application/main.cpp")
	
	# Include Boost test includes path
	include_directories("F:/ext/boost")

	# Build unit tests
	file(GLOB_RECURSE 4Wins_gui_SOURCES_TEST "test/*.cpp")
	file(GLOB_RECURSE 4Wins_gui_HEADERS_TEST "test/*.h")

	set(4Wins_gui_INCLUDE_DIRS "")
	foreach (_headerFile ${4Wins_gui_HEADERS_TEST})
		get_filename_component(_dir ${_headerFile} PATH)
		list(APPEND 4Wins_gui_INCLUDE_DIRS ${_dir})
	endforeach()
	list(REMOVE_DUPLICATES 4Wins_gui_INCLUDE_DIRS)

	include_directories(${4Wins_gui_INCLUDE_DIRS})
	
	# Compile and link with 4Wins_gui
	set(SOURCES_TEST ${4Wins_gui_SOURCES} ${4Wins_gui_SOURCES_TEST})
	add_executable(4Wins_gui_tests ${SOURCES_TEST})
	
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Test")

	add_executable(4Wins_gui ${4Wins_gui_SOURCES})
	
endif (${CMAKE_BUILD_TYPE} STREQUAL "Test")




