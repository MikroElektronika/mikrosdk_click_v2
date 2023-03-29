cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ooktx LANGUAGES MikroC)
else()
    project(lib_ooktx LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ooktx STATIC
        src/ooktx.c
        include/ooktx.h
)
add_library(Click.OOKTX  ALIAS lib_ooktx)



target_include_directories(lib_ooktx PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ooktx PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ooktx PUBLIC MikroSDK.Driver)
