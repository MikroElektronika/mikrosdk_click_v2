cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lighthz LANGUAGES MikroC)
else()
    project(lib_lighthz LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lighthz STATIC
        src/lighthz.c
        include/lighthz.h
)
add_library(Click.LightHz  ALIAS lib_lighthz)



target_include_directories(lib_lighthz PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lighthz PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lighthz PUBLIC MikroSDK.Driver)

