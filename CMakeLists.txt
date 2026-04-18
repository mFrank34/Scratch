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

if (NOT EXISTS ${CPM_DOWNLOAD_LOCATION})
    message(STATUS "Downloading CPM.cmake v${CPM_DOWNLOAD_VERSION}...")
    file(DOWNLOAD
            "https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake"
            ${CPM_DOWNLOAD_LOCATION}
    )
endif ()

include(${CPM_DOWNLOAD_LOCATION})

# Qt6
# On Linux, Qt6 is found automatically from the system install.
# On Windows, falls back to a common install path — override with:
#   cmake -DQt6_DIR="C:/Qt/6.x.x/msvc2022_64/lib/cmake/Qt6" ..
if (NOT DEFINED Qt6_DIR AND WIN32)
    # Detect Qt version installed under C:/Qt and pick the latest
    file(GLOB QT_VERSIONS "C:/Qt/6.*")
    if (QT_VERSIONS)
        list(SORT QT_VERSIONS ORDER DESCENDING)
        list(GET QT_VERSIONS 0 QT_LATEST)
        # Try MSVC first, then MinGW
        if (EXISTS "${QT_LATEST}/msvc2022_64/lib/cmake/Qt6")
            set(Qt6_DIR "${QT_LATEST}/msvc2022_64/lib/cmake/Qt6")
        elseif (EXISTS "${QT_LATEST}/mingw_64/lib/cmake/Qt6")
            set(Qt6_DIR "${QT_LATEST}/mingw_64/lib/cmake/Qt6")
        endif ()
        if (DEFINED Qt6_DIR)
            message(STATUS "Auto-detected Qt6 at: ${Qt6_DIR}")
        endif ()
    endif ()
endif ()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

# Catch2 (via CPM)
CPMAddPackage("gh:catchorg/Catch2@3.5.4")

# Source Collection
file(GLOB_RECURSE SOURCES
        "${CMAKE_SOURCE_DIR}/src/core/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/io/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/ui/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/utils/*.cpp"
)

#  Executable
# WIN32 hides the console window on Windows (no-op on Linux/macOS)
qt_add_executable(${PROJECT_NAME}
        WIN32 MACOSX_BUNDLE
        src/main.cpp
        ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

# Assets
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
        COMMENT "Copying assets..."
)

# On Windows, automatically deploy Qt DLLs next to the executable
if (WIN32)
    find_program(WINDEPLOYQT windeployqt HINTS "${Qt6_DIR}/../../../bin")
    if (WINDEPLOYQT)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${WINDEPLOYQT}
                --no-translations
                --no-system-d3d-compiler
                "$<TARGET_FILE:${PROJECT_NAME}>"
                COMMENT "Deploying Qt DLLs..."
        )
    else ()
        message(WARNING "windeployqt not found — Qt DLLs won't be copied automatically. Run windeployqt manually after build.")
    endif ()
endif ()

# Tests (Catch2)
option(BUILD_TESTS "Build tests" ON)

if (BUILD_TESTS)
    enable_testing()

    file(GLOB_RECURSE TEST_SOURCES "${CMAKE_SOURCE_DIR}/src/tests/*.cpp")

    if (TEST_SOURCES)
        add_executable(${PROJECT_NAME}_tests
                ${TEST_SOURCES}
                ${SOURCES}
        )

        target_include_directories(${PROJECT_NAME}_tests PRIVATE
                ${CMAKE_SOURCE_DIR}/src
        )

        target_link_libraries(${PROJECT_NAME}_tests PRIVATE
                Catch2::Catch2WithMain
                Qt6::Core
                Qt6::Gui
                Qt6::Widgets
        )

        include(Catch)
        catch_discover_tests(${PROJECT_NAME}_tests)
    endif ()
endif ()