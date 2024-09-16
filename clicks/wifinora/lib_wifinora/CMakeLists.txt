cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_wifinora LANGUAGES MikroC)
else()
    project(lib_wifinora LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_wifinora STATIC
        src/wifinora.c
        include/wifinora.h
)
add_library(Click.WiFiNORA  ALIAS lib_wifinora)



target_include_directories(lib_wifinora PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_wifinora PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_wifinora PUBLIC MikroSDK.Driver)

