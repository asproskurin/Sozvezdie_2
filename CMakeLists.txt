cmake_minimum_required(VERSION 3.14)

project(Sozvezdie_2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# socketrunnable.h  socketrunnable.cpp

set(HEADERS socketthread.h Server.h)
set(SRC main.cpp socketthread.cpp Server.cpp)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)

add_executable(
  Sozvezdie_2
  ${HEADERS}
  ${SRC}
)
target_link_libraries(Sozvezdie_2 Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)
