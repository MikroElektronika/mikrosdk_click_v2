cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_qireceiver LANGUAGES MikroC)
else()
    project(lib_qireceiver LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_qireceiver STATIC
        src/qireceiver.c
        include/qireceiver.h
)
add_library(Click.QiReceiver  ALIAS lib_qireceiver)



target_include_directories(lib_qireceiver PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_qireceiver PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_qireceiver PUBLIC MikroSDK.Driver)
