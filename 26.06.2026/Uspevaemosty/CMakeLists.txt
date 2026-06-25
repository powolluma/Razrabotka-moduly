cmake_minimum_required(VERSION 3.16)
project(Uspevaemosty VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

# Подключение файлов проекта
set(PROJECT_SOURCES
    main.cpp
    loginwindow.cpp
    loginwindow.h
    forgotpasswordwindow.cpp
    forgotpasswordwindow.h
    resources.qrc
    studentmainwindow.cpp
    studentmainwindow.h
    database.h
    parentmainwindow.h
    parentmainwindow.cpp
    parentmessageswindow.h
    parentmessageswindow.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Uspevaemosty MANUAL_FINALIZATION ${PROJECT_SOURCES}
        resources.qrc
        database.h
        gradeswindow.h gradeswindow.cpp
        schedulewindow.h schedulewindow.cpp
        averagewindow.h averagewindow.cpp
        quartergradeswindow.h quartergradeswindow.cpp
        parentmessageswindow.h parentmessageswindow.cpp
        parentmainwindow.h parentmainwindow.cpp
        teachermainwindow.h teachermainwindow.cpp)
else()
    add_executable(Uspevaemosty ${PROJECT_SOURCES})
endif()

target_link_libraries(Uspevaemosty PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Uspevaemosty)
endif()