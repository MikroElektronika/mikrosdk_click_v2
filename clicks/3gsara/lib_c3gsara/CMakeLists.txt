cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c3gsara LANGUAGES MikroC)
else()
    project(lib_c3gsara LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c3gsara STATIC
        src/c3gsara.c
        include/c3gsara.h
)
add_library(Click.3gSara  ALIAS lib_c3gsara)



target_include_directories(lib_c3gsara PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c3gsara PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c3gsara PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_c3gsara PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_c3gsara PUBLIC MikroSDK.GenericPointer)
