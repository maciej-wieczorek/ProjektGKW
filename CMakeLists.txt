cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(ProjektGKW)

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp
	${CMAKE_SOURCE_DIR}/src/core/*.cpp
	${CMAKE_SOURCE_DIR}/src/core/types/*.cpp
	${CMAKE_SOURCE_DIR}/src/vendor/*/*.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp
	${CMAKE_SOURCE_DIR}/src/core/*.h
	${CMAKE_SOURCE_DIR}/src/core/*.hpp
	${CMAKE_SOURCE_DIR}/src/core/types/*.h
	${CMAKE_SOURCE_DIR}/src/core/types/*.hpp
	${CMAKE_SOURCE_DIR}/src/vendor/*/*.hpp)

# Configure assets header file
configure_file(src/helpers/RootDir.h.in src/helpers/RootDir.h)
include_directories(${CMAKE_BINARY_DIR}/src)
	
# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} )

# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#######################################
# LOOK for the packages that we need! #
#######################################

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# GLM
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# GLFW
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

# GLAD
add_library(GLAD "thirdparty/glad.c" )

# Put all libraries into a variable
set(LIBS ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} GLAD ${CMAKE_DL_LIBS})

# Define the include DIRs
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/include/glad"
	"${CMAKE_SOURCE_DIR}/include/glm"
	"${CMAKE_SOURCE_DIR}/src/vendor/imgui"
	"${CMAKE_SOURCE_DIR}/src/core"
	"${CMAKE_SOURCE_DIR}/src/core/types"
)

# Define the link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS})
