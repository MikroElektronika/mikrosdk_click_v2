cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_oledb LANGUAGES MikroC)
else()
    project(lib_oledb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_oledb
STATIC
src/oledb.c
src/oledb_resources.c
include/oledb.h
include/oledb_resources.h
)
add_library(Click.OLEDB  ALIAS lib_oledb)



target_include_directories(lib_oledb PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_oledb PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_oledb PUBLIC MikroSDK.Driver)
