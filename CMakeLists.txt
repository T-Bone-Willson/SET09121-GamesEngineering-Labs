cmake_minimum_required(VERSION 3.9)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
# Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all the libs into the main build folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/res" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res)

### Tile Loader Lib ###
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" PRIVATE ${SFML_INCS})
target_link_libraries(lib_tile_level_loader sfml-graphics)

#### Practical 1 ####
file(GLOB_RECURSE SOURCES practical_1/*.cpp practical_1/*.h)
add_executable(PRACTICAL_1 ${SOURCES})
target_include_directories(PRACTICAL_1 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_1 sfml-graphics)

### Practical 2 Space Invaders ####
file(GLOB_RECURSE SOURCES practical_2/*.cpp practical_2/*.h)
add_executable(PRACTICAL_2 ${SOURCES} )
target_include_directories(PRACTICAL_2 SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_2 sfml-graphics)
add_dependencies(PRACTICAL_2 copy_resources)
set_target_properties(PRACTICAL_2 PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))
### listing 2.8 ###
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_2)

#### Practical 3 ####
file(GLOB_RECURSE SOURCES practical_3/*.cpp practical_3/*.h)
add_executable(PRACTICAL_3 ${SOURCES})
target_include_directories(PRACTICAL_3 SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_3 lib_tile_level_loader sfml-graphics)
add_dependencies(PRACTICAL_3 copy_resources)
set_target_properties(PRACTICAL_3 PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))

### Link Dependencies ###
foreach (exe ${EXECUTABLES})
	### Set working directory to build dir in visual studio ###
	set_target_properties(${exe} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY 
	${CMAKE_RUNTIME_OUTPOUT_DIRECTORY}/$(Configuration))

	target_link_libraries(${exe}
	### lib_maths will be made later ###
	optimized sfml-graphics debug sfml-graphics-d
	optimized sfml-audio debug sfml-audio-d
	optimized sfml-window debug sfml-window-d
	optimized sfml-system debug sfml-system-d
	optimized sfml-graphics debug sfml-graphics-d
	optimized sfml-main)

add_dependencies(${exe} sfml-graphics sfml-audio copy_resources)
endforeach ()