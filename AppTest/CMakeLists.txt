cmake_minimum_required(VERSION 3.1)

project(ControlLib)


set(SRC_APP
    MainWindow.cpp
    MainWindow.h
    Props.cpp
    Props.h
    resource.rc
    TrayIcon.cpp
    TrayIcon.h
    )

add_executable(AppTest
    ${SRC_APP}
    )

target_link_libraries(AppTest
    Controls
    )

target_include_directories(AppTest
    PRIVATE ../package/include
    )

target_compile_features(AppTest
    PRIVATE cxx_auto_type
    PRIVATE cxx_nullptr
    PRIVATE cxx_range_for
    )
