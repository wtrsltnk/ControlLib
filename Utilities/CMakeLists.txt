cmake_minimum_required(VERSION 3.1)

project(ControlLib)

set(SRC_APP
    List.cpp
    ReadMe.txt
    StdAfx.cpp
    StdAfx.h
    Utilities.cpp
    utilities.h
    )

add_library(Utilities
    ${SRC_APP}
	)

target_compile_features(Utilities
    PRIVATE cxx_auto_type
	PRIVATE cxx_nullptr
	PRIVATE cxx_range_for
	)

target_compile_definitions(Utilities
    PRIVATE UTILITIES_EXPORTS
    )
