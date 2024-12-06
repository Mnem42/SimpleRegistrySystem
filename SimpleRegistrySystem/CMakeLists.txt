# CMakeList.txt : CMake project for SimpleRegistrySystem, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (SimpleRegistrySystem "SimpleRegistrySystem.cpp" "SimpleRegistrySystem.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SimpleRegistrySystem PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
