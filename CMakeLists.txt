cmake_minimum_required(VERSION 3.12)
project(manufactury C)

set(CMAKE_C_STANDARD 11)
set(CURSES D:/LIBCXX/pdcurses)

include_directories(${CURSES})

add_library(curses STATIC IMPORTED)
set_target_properties(curses PROPERTIES IMPORTED_LOCATION D:/LIBCXX/pdcurses/wincon/pdcurses.a)

add_executable(manufactury main.c)
target_link_libraries(manufactury curses)

add_executable(tuidemo tui.c tuidemo.c)
target_link_libraries(tuidemo curses)