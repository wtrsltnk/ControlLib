cmake_minimum_required(VERSION 3.1)

project(ControlLib)

find_package(OpenGL REQUIRED)

set(SRC_APP
    3DEngine.cpp
    BaseApp.cpp
    BaseMDIApp.cpp
    BasePropertieChild.cpp
    Button.cpp
    Check.cpp
    Combo.cpp
    ComboList.cpp
    Commondlg.cpp
    Control.cpp
    Controls.cpp
    CustomButton.cpp
    CustomControl.cpp
    Dialog.cpp
    Edit.cpp
    Label.cpp
    List.cpp
    ListView.cpp
    MDIChild.cpp
    Menu.cpp
    Option.cpp
    OptionFrame.cpp
    PopUpMenu.cpp
    PropertieDialog.cpp
    PropertieWindow.cpp
    resource.h
    resource.rc
    Splitter.cpp
    StdAfx.cpp
    StdAfx.h
    SysImageList.cpp
    SystrayIcon.cpp
    ToolBox.cpp
    ToolBoxContainer.cpp
    ToolBoxDlg.cpp
    ToolWindow.cpp
    Trackbar.cpp
    TreeView.cpp
    )

add_library(Controls SHARED
    ${SRC_APP}
	)

target_link_libraries(Controls
    ${OPENGL_LIBRARIES}
    comctl32
    )

target_include_directories(Controls
    PRIVATE ../package/include
    )

target_compile_features(Controls
    PRIVATE cxx_auto_type
	PRIVATE cxx_nullptr
	PRIVATE cxx_range_for
	)

target_compile_definitions(Controls
    PRIVATE CONTROLS_EXPORTS
    )
