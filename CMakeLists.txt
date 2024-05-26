cmake_minimum_required(VERSION 3.5)

project(Unofficial_Acer_Care_Center VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        carecenter.cpp
        carecenter.h
        backend.cpp
        backend.h
        carecenter.ui
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)


qt_add_executable(Unofficial_Acer_Care_Center
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        BatteryIcon.qrc
        CpuIcon.qrc
        LaptopIcon.qrc
        ApplicationIcon.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Unofficial_Acer_Care_Center APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Unofficial_Acer_Care_Center SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Unofficial_Acer_Care_Center
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Unofficial_Acer_Care_Center PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Unofficial_Acer_Care_Center)
endif()
set_target_properties(Unofficial_Acer_Care_Center PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Unofficial_Acer_Care_Center
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Unofficial_Acer_Care_Center)
endif()
