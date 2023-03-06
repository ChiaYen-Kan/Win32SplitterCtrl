cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME "Win32SplitterCtrl")

project(${TARGET_NAME}
    DESCRIPTION ${TARGET_NAME}
    LANGUAGES CXX
)

set(CMAKE_GENERATOR_PLATFORM Win32)

# C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# output name
add_executable(${TARGET_NAME})

# complier and linker flags

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto")
set(LINK_FLAGS_RELEASE "-flto")
set(CMAKE_CXX_FLAGS_DEBUG "-g3")

target_compile_definitions(${TARGET_NAME} PUBLIC
    UNICODE
    _UNICODE
    WIN32
)

set(CMAKE_EXE_LINKER_FLAGS "-Wl,-subsystem,windows -municode -static")
set(CMAKE_CXX_FLAGS "-fno-keep-inline-dllexport")


# windows resource file
execute_process(COMMAND windres --codepage=65001 -i ${CMAKE_CURRENT_SOURCE_DIR}/resource.rc -o ${CMAKE_CURRENT_BINARY_DIR}/resource.o --include-dir=./)
target_link_libraries(${TARGET_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/resource.o
)

#  source code
target_include_directories(${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/WinClass.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WinMaker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WinString.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/splitter.cpp
)