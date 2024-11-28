cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c4glte2datana LANGUAGES MikroC)
else()
    project(lib_c4glte2datana LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c4glte2datana STATIC
        src/c4glte2datana.c
        include/c4glte2datana.h
)
add_library(Click.4GLTE2DataNA  ALIAS lib_c4glte2datana)



target_include_directories(lib_c4glte2datana PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c4glte2datana PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c4glte2datana PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_c4glte2datana PUBLIC MikroSDK.Conversions)
