cmake_minimum_required(VERSION 3.1)

project(ControlLib)

add_executable(MDITest WIN32
    Document.cpp
    Document.h
    MainFrame.cpp
    MainFrame.h
    TrayIcon.cpp
    TrayIcon.h
    )

target_link_libraries(MDITest
    Controls
    )

target_include_directories(MDITest
    PRIVATE ../package/include
    )

target_compile_features(MDITest
    PRIVATE cxx_auto_type
    PRIVATE cxx_nullptr
    PRIVATE cxx_range_for
    )
