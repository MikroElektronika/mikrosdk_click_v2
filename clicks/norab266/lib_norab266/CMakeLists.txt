cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_norab266 LANGUAGES MikroC)
else()
    project(lib_norab266 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_norab266 STATIC
        src/norab266.c
        include/norab266.h
)
add_library(Click.NORAB266  ALIAS lib_norab266)



target_include_directories(lib_norab266 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_norab266 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_norab266 PUBLIC MikroSDK.Driver)

