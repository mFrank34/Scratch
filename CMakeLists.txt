cmake_minimum_required(VERSION 3.20)
project(Scratch VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Required for Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# CPM Setup
set(CPM_DOWNLOAD_VERSION 0.40.2)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT EXISTS ${CPM_DOWNLOAD_LOCATION})
    message(STATUS "Downloading CPM.cmake v${CPM_DOWNLOAD_VERSION}...")
    file(DOWNLOAD
        "https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake"
        ${CPM_DOWNLOAD_LOCATION}
    )
endif()

include(${CPM_DOWNLOAD_LOCATION})

# Qt6
# Qt6 is large and not suited for CPM — find it from a system/local install.
# Set Qt6_DIR if Qt isn't on PATH, e.g.:
#   cmake -DQt6_DIR=/path/to/Qt/6.x.x/gcc_64/lib/cmake/Qt6 ..
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

CPMAddPackage("gh:catchorg/Catch2@3.5.4")

file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/src/core/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/io/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/ui/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/utils/*.cpp"
)

qt_add_executable(${PROJECT_NAME}
    src/main.cpp
    ${SOURCES}
        src/io/File_Handler.cpp
        src/io/File_Handler.h
        src/io/format/Text_Document.cpp
        src/io/format/Text_Document.h
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMENT "Copying assets..."
)

option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()

    file(GLOB_RECURSE TEST_SOURCES "${CMAKE_SOURCE_DIR}/src/tests/*.cpp")

    if(TEST_SOURCES)
        add_executable(${PROJECT_NAME}_tests
            ${TEST_SOURCES}
            ${SOURCES}
        )

        target_include_directories(${PROJECT_NAME}_tests PRIVATE
            ${CMAKE_SOURCE_DIR}/src/include
        )

        target_link_libraries(${PROJECT_NAME}_tests PRIVATE
            Catch2::Catch2WithMain
            Qt6::Core
            Qt6::Gui
            Qt6::Widgets
        )

        # Auto-discover Catch2 TEST_CASEs and register with CTest
        include(Catch)
        catch_discover_tests(${PROJECT_NAME}_tests)
    endif()
endif()