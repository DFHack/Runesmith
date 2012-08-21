project(Runesmith)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(Runesmith_SRCS Runesmith.cpp main.cpp)
qt4_automoc(${Runesmith_SRCS})
add_executable(Runesmith ${Runesmith_SRCS})
target_link_libraries(Runesmith ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install(TARGETS Runesmith RUNTIME DESTINATION bin)
