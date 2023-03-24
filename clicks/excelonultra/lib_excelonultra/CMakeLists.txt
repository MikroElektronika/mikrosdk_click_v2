cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_excelonultra LANGUAGES MikroC)
else()
    project(lib_excelonultra LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_excelonultra STATIC
        src/excelonultra.c
        include/excelonultra.h
)
add_library(Click.ExcelonUltra  ALIAS lib_excelonultra)



target_include_directories(lib_excelonultra PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_excelonultra PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_excelonultra PUBLIC MikroSDK.Driver)
