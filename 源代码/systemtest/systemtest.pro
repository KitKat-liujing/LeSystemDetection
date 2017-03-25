#-------------------------------------------------
#
# Project created by QtCreator 2015-01-08T16:32:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = systemtest
TEMPLATE = app

QT += widgets network
QT += testlib
CONFIG += thread


#QT += widgets
QT += webkit
#QT += webkitwidgets/webview
#QT += network

SOURCES += main.cpp\
        main_widget.cpp \
    tool_button.cpp \
    drop_shadow_widget.cpp \
    title_widget.cpp \
    boot_start_time.cpp \
    input_pwd.cpp \
    common.cpp \
    push_button.cpp \
    sys_test_widget.cpp \
    buttom_widget.cpp \
    show_percent_page.cpp \
    main_page_one.cpp \
    main_page_two.cpp \
    main_page_three.cpp \
    main_page_four.cpp \
    main_page_five.cpp \
    main_page_six.cpp \
    user_msg.cpp \
    net_speed.cpp \
    main_page_serven.cpp \
    main_menu.cpp \
    about_us.cpp

HEADERS  += main_widget.h \
    tool_button.h \
    drop_shadow_widget.h \
    title_widget.h \
    boot_start_time.h \
    common.h \
    input_pwd.h \
    push_button.h \
    sys_test_widget.h \
    buttom_widget.h \
    show_percent_page.h \
    main_page_one.h \
    main_page_two.h \
    main_page_three.h \
    main_page_four.h \
    main_page_five.h \
    main_page_six.h \
    user_msg.h \
    net_speed.h \
    main_page_serven.h \
    main_menu.h \
    about_us.h

RESOURCES += \
    sources/resources.qrc
QT += widgets
QT += webkit
QT += network


TRANSLATIONS += sources/sys_test.ts
RC_FILE = logo1.rc
