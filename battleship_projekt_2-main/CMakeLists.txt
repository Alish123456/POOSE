#----------------------------------------------#
#-----Konfiguration des Buildsystems CMake-----#
#----------------------------------------------#
cmake_minimum_required(VERSION 3.16)
project(project_battleship VERSION 1.0 LANGUAGES CXX)

#----------------------------------------------#
#-------------------Optionen-------------------#
#----------------------------------------------#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)
# Optional zur Lecksuche:
# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

# Include-Verzeichnisse
include_directories(${PROJECT_SOURCE_DIR}/include/project_battleship)

#----------------------------------------------#
#----------Download and use GoogleTest---------#
#----------------------------------------------#
include(FetchContent)
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/b514bdc898e2951020cbdca1304b75f5950d1f59.zip
)
# Prevent overriding parent project's settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

option(INSTALL_GTEST "Enable installation of googletest." OFF)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
enable_testing()

# ----------------------------------------------
# ----- Download & Einbindung von PyBind11 -----
# ----------------------------------------------
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v2.13.6   # oder eine neuere stabile Version
)
FetchContent_MakeAvailable(pybind11)


#----------------------------------------------#
#---------------Library-Interface---------------#
#----------------------------------------------#

add_library(project_battleship INTERFACE)
target_include_directories(project_battleship INTERFACE include)

# Bibliothek aus allen .cpp-Dateien in src/
file(GLOB ACTUAL_SRC
  ${PROJECT_SOURCE_DIR}/src/*.cpp
)

add_library(battleship_core STATIC
  ${ACTUAL_SRC}
)
set_target_properties(battleship_core PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(battleship_core
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)


#----------------------------------------------#
#--------------Demo-Executables----------------#
#----------------------------------------------#
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(griddemo
  examples/griddemo.cpp
)
target_link_libraries(griddemo PRIVATE battleship_core)


#----------------------------------------------#
#-------------Test-Executables-----------------#
#----------------------------------------------#
add_executable(Grid_test
  tests/Grid_test.cpp
)
target_link_libraries(Grid_test
  PRIVATE
    GTest::gtest_main
    battleship_core
)
gtest_discover_tests(Grid_test)
add_test(NAME Grid_test COMMAND Grid_test)


add_executable(Game_test
  tests/Game_test.cpp
)
target_link_libraries(Game_test
  PRIVATE
    GTest::gtest_main
    battleship_core
)
gtest_discover_tests(Game_test)
add_test(NAME Game_test COMMAND Game_test)

# ----------------------------------------------
# ----- PyBind11-Python-Modul "battleship_py" -----
# ----------------------------------------------

# Python-Entwicklungsumgebung suchen (für Python.h)
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
include_directories(${Python3_INCLUDE_DIRS})

pybind11_add_module(battleship_py
  src/server.cpp
)
target_link_libraries(battleship_py PRIVATE battleship_core)