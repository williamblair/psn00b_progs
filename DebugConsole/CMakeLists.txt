# test cmakelists

cmake_minimum_required(VERSION 2.6)

set(PROJ_NAME   "bjtest")
set(GCC_DIR     "/d/mipsel-unknown-elf")
set(GCC_VERSION "7.4.0")
set(PSNOOB_DIR  "/d/Programming/psx/psn00bsdk")

set(CMAKE_SYSTEM_NAME Generic) # tell cmake we're cross compiling
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_C_COMPILER   "mipsel-unknown-elf-gcc")
set(CMAKE_CXX_COMPILER "mipsel-unknown-elf-g++")

# util library
#add_library("${PROJ_NAME}" STATIC
#    src/System.cpp
#    src/Model.cpp
#    src/Model_textured.cpp
#    src/Cube.cpp
#    src/Cube_textured.cpp
#    src/Texture.cpp
#    src/Light.cpp
#    src/Pad.cpp
#    src/Camera.cpp
#    src/FPSMovableObject.cpp
#)

include_directories( "${PSNOOB_DIR}/libpsn00b/include"
                     "${GCC_DIR}/lib/gcc/mipsel-unknown-elf/${GCC_VERSION}/include"
                     "${CMAKE_CURRENT_SOURCE_DIR}/src")

link_directories( "${PSNOOB_DIR}/libpsn00b"
                  "${GCC_DIR}/lib/gcc/mipsel-unknown-elf/${GCC_VERSION}")

target_link_libraries("${PROJ_NAME}" c psxetc psxgpu psxgte psxspu psxapi gcc)

set(CMAKE_CXX_FLAGS "-g -O2 -fno-builtin -fdata-sections -ffunction-sections -fno-exceptions")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g -Ttext=0x80010000 -gc-sections -T ${GCC_DIR}/mipssel-unknown-elf/lib/ldscripts/elf32elmip.x")

set(CMAKE_C_LINK_EXECUTABLE "mipsel-unknown-elf-ld ${CMAKE_EXE_LINKER_FLAGS} <OBJECTS> -L${GCC_DIR}/lib/gcc/mipsel-unknown-elf/${GCC_VERSION} -L${PSNOOB_DIR} <LINK_LIBRARIES> -o <TARGET>")
set(CMAKE_CXX_LINK_EXECUTABLE "mipsel-unknown-elf-ld ${CMAKE_EXE_LINKER_FLAGS} <OBJECTS> -L${GCC_DIR}/lib/gcc/mipsel-unknown-elf/${GCC_VERSION} -L${PSNOOB_DIR} <LINK_LIBRARIES> -o <TARGET>")


