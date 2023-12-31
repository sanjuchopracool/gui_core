cmake_minimum_required(VERSION 3.5)

project(gui_core VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        test.cpp
        test.h
        widgets/editors/label_editor.h widgets/editors/label_editor.cpp
        widgets/editors/line_editor.h widgets/editors/line_editor.cpp
        widgets/editors/number_editor.h widgets/editors/number_editor.cpp
        styles/dark_style.h styles/dark_style.cpp
        widgets/linked_number_editor.h widgets/linked_number_editor.cpp
        widgets/checkable_icon.h widgets/checkable_icon.cpp
        model/composition_view_model.h model/composition_view_model.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(gui_core
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET gui_core APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(gui_core SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(gui_core
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(gui_core PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Resources:
set(icons_resource_file
    "icons/dark/actions/16@2x/link.png"
    "icons/dark/actions/16/link.png"
)

qt_add_resources(gui_core "icons"
    PREFIX
        "/"
    FILES
        ${icons_resource_file}
)

qt_add_resources(gui_core "stylesheet"
    PREFIX
        "/"
    FILES
        "styles/dark_style.css"
)

set_target_properties(gui_core PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS gui_core
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(gui_core)
endif()
