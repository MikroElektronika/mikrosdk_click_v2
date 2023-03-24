cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_excelonlp LANGUAGES MikroC)
else()
    project(example_excelonlp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_excelonlp
        main.c

)


############################ example_excelonlp GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_excelonlp PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_excelonlp PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_excelonlp PUBLIC MikroSDK.Log)
add_subdirectory(lib_excelonlp)
target_link_libraries(example_excelonlp PUBLIC Click.ExcelonLP)
############################ example_excelonlp GENERATED CODE END ###########################
