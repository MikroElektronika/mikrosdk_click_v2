cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ammonia LANGUAGES MikroC)
else()
    project(lib_ammonia LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ammonia STATIC
        src/ammonia.c
        include/ammonia.h
)
add_library(Click.Ammonia  ALIAS lib_ammonia)



target_include_directories(lib_ammonia PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ammonia PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ammonia PUBLIC MikroSDK.Driver)
