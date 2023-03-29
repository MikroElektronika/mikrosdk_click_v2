cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallcurrent7 LANGUAGES MikroC)
else()
    project(lib_hallcurrent7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallcurrent7 STATIC
        src/hallcurrent7.c
        include/hallcurrent7.h
)
add_library(Click.HallCurrent7  ALIAS lib_hallcurrent7)



target_include_directories(lib_hallcurrent7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallcurrent7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallcurrent7 PUBLIC MikroSDK.Driver)
