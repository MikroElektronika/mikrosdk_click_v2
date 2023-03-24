cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buck14 LANGUAGES MikroC)
else()
    project(lib_buck14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buck14 STATIC
        src/buck14.c
        include/buck14.h
)
add_library(Click.Buck14  ALIAS lib_buck14)



target_include_directories(lib_buck14 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buck14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buck14 PUBLIC MikroSDK.Driver)
