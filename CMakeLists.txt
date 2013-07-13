cmake_minimum_required(VERSION 2.8)

project(4Wins_gui)

# Variables - to build add here the library locations
set(BOOST_TEST_SEARCH_INCLUDE_DIR
"F:/ext/boost")
set(BOOST_TEST_SEARCH_LIB_DIR
"F:/ext/boost_build/boost/bin.v2/libs")
set(FLTK_SEARCH_INCLUDE_DIR
"F:/ext/FLTK/include")
set(FLTK_SEARCH_LIB_DIR
"F:/ext/FLTK/lib")

# Because fluid not found
set(FLTK_FLUID_EXECUTABLE
"F:/ext/FLTK/bin/fluid.exe")

# Because the libraries are not at standard locations:
# Set the path were the FLTK and boost test binaries are
set(CMAKE_INCLUDE_PATH ${BOOST_TEST_SEARCH_INCLUDE_DIR} ${FLTK_SEARCH_INCLUDE_DIR})
set(CMAKE_LIBRARY_PATH ${BOOST_TEST_SEARCH_LIB_DIR} ${FLTK_SEARCH_LIB_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x -D_WIN32_WINNT=0x0501")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

# ==============================================================================

# Get project files
file(GLOB_RECURSE 4Wins_gui_SOURCES "src/*.cpp")
file(GLOB_RECURSE 4Wins_gui_HEADERS "src/*.h")

set(4Wins_gui_INCLUDE_DIRS "")
foreach (_headerFile ${4Wins_gui_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND 4Wins_gui_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES 4Wins_gui_INCLUDE_DIRS)

include_directories(${4Wins_gui_INCLUDE_DIRS})

# Find FLTK
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})

if (CMAKE_BUILD_TYPE STREQUAL "Test") # Build boost unit tests

	# Remove main
	list(REMOVE_ITEM 4Wins_gui_SOURCES "${CMAKE_SOURCE_DIR}/src/application/main.cpp")
	
	# Get unit test files
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
    
    # Link with boost system
    target_link_libraries(4Wins_gui_tests ${Boost_LIBRARIES})
    
    # Link with boost test and boost system
    set(Boost_USE_STATIC_LIBS ON) # Static library
    find_package(Boost COMPONENTS thread regex system unit_test_framework REQUIRED)
    include_directories(${Boost_INCLUDE_DIR})
    target_link_libraries(4Wins_gui_tests ${Boost_LIBRARIES})
    
    # Link with FLTK
    target_link_libraries(4Wins_gui_tests ${FLTK_LIBRARIES})
    
    # Link with winsock
    if (WIN32)
        target_link_libraries(4Wins_gui ws2_32)
    endif (WIN32)
	
else (CMAKE_BUILD_TYPE STREQUAL "Test")
    
    # Build project without tests
	add_executable(4Wins_gui ${4Wins_gui_SOURCES})
	
    # Link with FLTK
    target_link_libraries(4Wins_gui debug ${FLTK_LIBRARIES})
    
    # Link with boost system
    set(Boost_USE_STATIC_LIBS ON) # Static library
    find_package(Boost COMPONENTS thread regex system REQUIRED)
    include_directories(${Boost_INCLUDE_DIR})
    target_link_libraries(4Wins_gui ${Boost_LIBRARIES})
    
    # Link with winsock
    if (WIN32)
        target_link_libraries(4Wins_gui ws2_32)
    endif (WIN32)
    
endif (CMAKE_BUILD_TYPE STREQUAL "Test")