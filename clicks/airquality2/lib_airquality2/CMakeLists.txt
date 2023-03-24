cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_airquality2 LANGUAGES MikroC)
else()
    project(lib_airquality2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_airquality2 STATIC
        src/airquality2.c
        include/airquality2.h
)
add_library(Click.Airquality2  ALIAS lib_airquality2)



target_include_directories(lib_airquality2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_airquality2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_airquality2 PUBLIC MikroSDK.Driver)
