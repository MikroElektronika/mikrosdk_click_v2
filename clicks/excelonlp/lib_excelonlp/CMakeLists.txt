cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_excelonlp LANGUAGES MikroC)
else()
    project(lib_excelonlp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_excelonlp STATIC
        src/excelonlp.c
        include/excelonlp.h
)
add_library(Click.ExcelonLP  ALIAS lib_excelonlp)



target_include_directories(lib_excelonlp PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_excelonlp PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_excelonlp PUBLIC MikroSDK.Driver)
