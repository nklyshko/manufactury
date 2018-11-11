cmake_minimum_required(VERSION 3.12)
project(manufactury C)

set(CMAKE_C_STANDARD 11)
#set(PDCURSES D:/LIBC/pdcurses)
set(PDCURSES D:/WorkC/PDCurses)
set(LOGC D:/LIBC/logc)
set(COLLECTIONSC D:/LIBC/CollectionsC)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -DPDC_WIDE=ON)

include_directories(${PDCURSES})
include_directories(${LOGC})
include_directories(${COLLECTIONSC}/src/include)
include_directories(.)

add_library(pdcurses STATIC IMPORTED)
set_target_properties(pdcurses PROPERTIES IMPORTED_LOCATION ${PDCURSES}/wincon/pdcurses.a)

add_library(collectionsc STATIC IMPORTED)
set_target_properties(collectionsc PROPERTIES IMPORTED_LOCATION ${COLLECTIONSC}/cmake-build-debug/src/libcollectc.dll.a)

add_executable(manufactury main.c view/hotkey.h view/hotkey.c view/styles.h view/styles.c view/mouse_handler.h view/mouse_handler.c view/view_contract.h view/view.c view/menu_view.h view/menu_view.c
        ${LOGC}/src/log.c ${LOGC}/src/log.h view/component.h view/component.c)
target_link_libraries(manufactury pdcurses)

add_executable(tuidemo tui.c tuidemo.c)
target_link_libraries(tuidemo pdcurses)