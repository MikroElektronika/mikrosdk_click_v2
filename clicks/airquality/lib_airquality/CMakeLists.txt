cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_airquality LANGUAGES MikroC)
else()
    project(lib_airquality LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_airquality STATIC
        src/airquality.c
        include/airquality.h
)
add_library(Click.Airquality  ALIAS lib_airquality)



target_include_directories(lib_airquality PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_airquality PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_airquality PUBLIC MikroSDK.Driver)
