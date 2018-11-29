cmake_minimum_required(VERSION 3.12)
project(manufactury C)

set(CMAKE_C_STANDARD 11)
set(PDCURSES D:/WorkC/PDCurses)
set(LOGC D:/LIBC/logc)
set(COLLECTIONSC D:/LIBC/CollectionsC)
add_compile_definitions(PDC_WIDE)
add_compile_definitions(PDC_FORCE_UTF8)
add_compile_definitions(PDC_USE_STD_BOOL)

include_directories(${PDCURSES})
include_directories(${LOGC})
include_directories(${COLLECTIONSC}/src/include)
include_directories(.)

add_library(pdcurses STATIC IMPORTED)
set_target_properties(pdcurses PROPERTIES IMPORTED_LOCATION ${PDCURSES}/wincon/pdcurses.a)

add_library(collectionsc STATIC IMPORTED view/component/edit.c view/component/edit.h model/data_source.c model/data_source.h)
set_target_properties(collectionsc PROPERTIES IMPORTED_LOCATION ${COLLECTIONSC}/cmake-build-debug/src/libcollectc.a)

add_executable(manufactury main.c
        ${LOGC}/src/log.c ${LOGC}/src/log.h
        view/hotkey.h view/hotkey.c view/styles.h view/styles.c view/view_contract.h
        view/view.c view/component.h view/component.c view/interactive_panel.c view/interactive_panel.h
            view/component/edit.c view/component/edit.h view/component/label.c view/component/label.h
        view/layout.c view/layout.h view/component/menu.c view/component/menu.h key_codes.h view/component/button.c view/component/button.h
        view/component/scroll_bar.c view/component/scroll_bar.h view/component/select.c view/component/select.h
        view/winapi_bridge.c view/winapi_bridge.h view/component/column_label.c view/component/column_label.h
        model/data_types.c model/data_types.h view/logo.c view/logo.h model/data_source.c model/data_source.h model/array_ext.c model/array_ext.h
        presenter.c presenter_contract.h model/comparator.c model/comparator.h)
target_link_libraries(manufactury pdcurses)
target_link_libraries(manufactury collectionsc)

add_executable(test test/test_gui.c ${LOGC}/src/log.c ${LOGC}/src/log.h
        view/hotkey.h view/hotkey.c view/styles.h view/styles.c
        view/component.h view/component.c view/interactive_panel.c view/interactive_panel.h
        view/component/edit.c view/component/edit.h view/component/label.c view/component/label.h
        view/layout.c view/layout.h view/component/menu.c view/component/menu.h key_codes.h view/component/button.c
        view/component/button.h view/component/scroll_bar.c view/component/scroll_bar.h view/component/select.c view/component/select.h
        view/winapi_bridge.c view/winapi_bridge.h view/component/column_label.c view/component/column_label.h test/test_console.c test/test_console.h test/test.c test/test_gui.h
        model/array_ext.c model/array_ext.h)
target_link_libraries(test pdcurses)
target_link_libraries(test collectionsc)