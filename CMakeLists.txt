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

add_library(collectionsc STATIC IMPORTED tui/component/edit.c tui/component/edit.h model/data_source.c model/data_source.h)
set_target_properties(collectionsc PROPERTIES IMPORTED_LOCATION ${COLLECTIONSC}/cmake-build-debug/src/libcollectc.a)

add_executable(manufactury main.c
        ${LOGC}/src/log.c ${LOGC}/src/log.h
        tui/hotkey.h tui/hotkey.c tui/styles.h tui/styles.c main/main_view.h
        main/main_view.c tui/component.h tui/component.c tui/interactive_panel.c tui/interactive_panel.h
        tui/component/edit.c tui/component/edit.h tui/component/label.c tui/component/label.h
        tui/layout.c tui/layout.h tui/component/menu.c tui/component/menu.h key_codes.h tui/component/button.c tui/component/button.h
        tui/component/scroll_bar.c tui/component/scroll_bar.h tui/component/select.c tui/component/select.h
        tui/winapi_bridge.c tui/winapi_bridge.h tui/component/column_label.c tui/component/column_label.h
        model/data_types.c model/data_types.h main/logo.c main/logo.h model/data_source.c model/data_source.h model/array_ext.c model/array_ext.h
        main/main_presenter.c main/main_presenter.h model/comparator.c model/comparator.h tui/dialog.c tui/dialog.h tui/component/textarea.c tui/component/textarea.h
        edit/edit_view.c edit/edit_view.h model/filter.c model/filter.h edit/edit_presenter.c edit/edit_presenter.h version.h edit/id_input_dialog.c edit/id_input_dialog.h
        report/report_view.c report/report_view.h report/report_param_dialog.c report/report_param_dialog.h main/filter_dialog.c main/filter_dialog.h report/report_presenter.c report/report_presenter.h model/predicate.c model/predicate.h)
target_link_libraries(manufactury pdcurses)
target_link_libraries(manufactury collectionsc)

add_executable(test test/test_gui.c ${LOGC}/src/log.c ${LOGC}/src/log.h
        tui/hotkey.h tui/hotkey.c tui/styles.h tui/styles.c
        tui/component.h tui/component.c tui/interactive_panel.c tui/interactive_panel.h
        tui/component/edit.c tui/component/edit.h tui/component/label.c tui/component/label.h
        tui/layout.c tui/layout.h tui/component/menu.c tui/component/menu.h key_codes.h tui/component/button.c
        tui/component/button.h tui/component/scroll_bar.c tui/component/scroll_bar.h tui/component/select.c tui/component/select.h
        tui/winapi_bridge.c tui/winapi_bridge.h tui/component/column_label.c tui/component/column_label.h test/test_console.c test/test_console.h test/test.c test/test_gui.h
        model/array_ext.c model/array_ext.h tui/component/textarea.c tui/component/textarea.h)
target_link_libraries(test pdcurses)
target_link_libraries(test collectionsc)