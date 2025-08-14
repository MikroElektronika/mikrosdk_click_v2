cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_charger29 LANGUAGES MikroC)
else()
    project(lib_charger29 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_charger29 STATIC
        src/charger29.c
        include/charger29.h
)
add_library(Click.Charger29  ALIAS lib_charger29)



target_include_directories(lib_charger29 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_charger29 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_charger29 PUBLIC MikroSDK.Driver)

