cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_airquality5 LANGUAGES MikroC)
else()
    project(lib_airquality5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_airquality5 STATIC
        src/airquality5.c
        include/airquality5.h
)
add_library(Click.Airquality5  ALIAS lib_airquality5)



target_include_directories(lib_airquality5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_airquality5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_airquality5 PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})
