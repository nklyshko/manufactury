cmake_minimum_required(VERSION 3.12)
project(manufactury C)

set(CMAKE_C_STANDARD 11)
set(PDCURSES D:/LIBC/pdcurses)

include_directories(${PDCURSES})

add_library(pdcurses STATIC IMPORTED)
set_target_properties(pdcurses PROPERTIES IMPORTED_LOCATION ${PDCURSES}/wincon/pdcurses.a)

add_executable(manufactury main.c view.c)
target_link_libraries(manufactury pdcurses)

add_executable(tuidemo tui.c tuidemo.c)
target_link_libraries(tuidemo pdcurses)