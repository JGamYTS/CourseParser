cmake_minimum_required(VERSION 3.16)

project(CourseParser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CourseParser main.cpp
    course.h course.cpp
)

include(GNUInstallDirs)
install(TARGETS CourseParser
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
