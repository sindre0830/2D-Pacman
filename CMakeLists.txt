#This is a CMakeLists.txt file. CMakeLists.txt files
#specify "how" to build a project. Among other things,
#this is very beneficial for:
# 1) Generating a project four our development environment
#    regardless of what this develoment environment is
#    (some would use Visual Studio, some others would use Linux
#    Makefiles, etc.).
# 2) Avoiding manual configurations that only will work i
#    one's machine.

# This lab conveniently comes with the dependencies needed
# (GLEW and GLFW) in source code form and the intention of this
# CMakeLists.txt file is to instruct CMake to generate a project
# in which GLEW and GLFW will be compiled first and the resulting
# binaries will be then be used to link with our executable Lab02 file.
# As opposed to GLEW and GLFW, OpenGL is a well-known library, found
# in most systems, therefore we can use the find_package command
# to find it out in the system; therefore we don't need to build it
# as part of this project.

#Indicate the minimum version of CMake needed to use
#this CMakeLists.txt file.
cmake_minimum_required(VERSION 3.12)

# Declare the name of the project.
project(SandBox)

# Ask CMake to find the OpenGL package indicating
# that this package is required. If OpenGL is not found, CMake
# will issue an error. This will make available the OpenGL::GL
# library that we will be using during linking.
find_package(OpenGL REQUIRED)

# Set a global output directory for libraries and runtime
# If we don't set this up, GLFW and GLEW could generate the
# binary files inside their own subdirectories. We specify
# we want our excecutables and dll's inside the bin folder
# while the static libraries will be inside the lib folder.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Instructs CMake to get into the external/glfw-3.3.2 folder
# and look for CMakeLists.txt file inside. If it is found, then
# it will follow those instructions. Such CMakeLists.txt is
# provided by GLFW and contains the instructions to build it.
add_subdirectory(external/glfw-3.3.2)

# Similar to the above. In this case the reader should note that
# the official GLEW source code does not come with a CMakeLists.txt
# file. Instead of using the official, we are using a fork of GLEW
# that comes with the CMakeLists.txt
# (https://github.com/Perlmint/glew-cmake)
add_subdirectory(external/glew-cmake-2.1.0)

# Up to this point we have either found or built our dependencies--


# Add a new executable to our project (Lab02), which
# is based on main.cpp, shaders/triangle.h and shaders/square.h.
# It is not strictly necessary to add the header files (.h) here,
# but doing so guarantees that the VisualStudio project explorer
# will see the header files and will allow us to edit them if we
# need so.
add_executable(SandBox
	main.cpp
	shaders/square.h)

# As seen in Lab01 static linking against glew required
# the compile definition of GLEW_STATIC. This is the way
# it is specified in CMake. The PRIVATE keyword indicates
# that this definition will not be propagated over to any
# hypothetic target having Lab02 as dependency. This makes
# sense because Lab02 is an executable and therefore,
# it is not meant to be used further by any other
# library/executable.
target_compile_definitions(SandBox PRIVATE GLEW_STATIC)

# Here we indicate what are the libraries Lab02 need to
# link against. PRIVATE has the same rationale as above.
# The reader should note that it is not necessary to specify
# linking or include directories. These properties are
# automatically propagated along with the library.
target_link_libraries(SandBox
  PRIVATE
  libglew_static
  glfw
  OpenGL::GL)
