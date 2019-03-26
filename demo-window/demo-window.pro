QT       += core gui
TARGET = demo-window
TEMPLATE = app

CONFIG += c++14

include(../qtimgui.pri)

INCLUDEPATH  += \
    ../litehtml \
    ../litehtml/include \
    ../litehtml/src \
    ../litehtml/src/gumbo

HEADERS += \
    ../container_qt5_imgui.h

SOURCES += \
    demo-window.cpp \
    ../container_qt5_imgui.cpp \
    ../litehtml/src/gumbo/attribute.c \
    ../litehtml/src/gumbo/char_ref.c \
    ../litehtml/src/gumbo/error.c \
    ../litehtml/src/gumbo/parser.c \
    ../litehtml/src/gumbo/string_buffer.c \
    ../litehtml/src/gumbo/string_piece.c \
    ../litehtml/src/gumbo/tag.c \
    ../litehtml/src/gumbo/tokenizer.c \
    ../litehtml/src/gumbo/utf8.c \
    ../litehtml/src/gumbo/util.c \
    ../litehtml/src/gumbo/vector.c \
    ../litehtml/src/background.cpp \
    ../litehtml/src/box.cpp \
    ../litehtml/src/context.cpp \
    ../litehtml/src/css_length.cpp \
    ../litehtml/src/css_selector.cpp \
    ../litehtml/src/document.cpp \
    ../litehtml/src/el_anchor.cpp \
    ../litehtml/src/el_base.cpp \
    ../litehtml/src/el_before_after.cpp \
    ../litehtml/src/el_body.cpp \
    ../litehtml/src/el_break.cpp \
    ../litehtml/src/el_cdata.cpp \
    ../litehtml/src/el_comment.cpp \
    ../litehtml/src/el_div.cpp \
    ../litehtml/src/element.cpp \
    ../litehtml/src/el_font.cpp \
    ../litehtml/src/el_image.cpp \
    ../litehtml/src/el_link.cpp \
    ../litehtml/src/el_para.cpp \
    ../litehtml/src/el_script.cpp \
    ../litehtml/src/el_space.cpp \
    ../litehtml/src/el_style.cpp \
    ../litehtml/src/el_table.cpp \
    ../litehtml/src/el_td.cpp \
    ../litehtml/src/el_text.cpp \
    ../litehtml/src/el_title.cpp \
    ../litehtml/src/el_tr.cpp \
    ../litehtml/src/html.cpp \
    ../litehtml/src/html_tag.cpp \
    ../litehtml/src/iterators.cpp \
    ../litehtml/src/media_query.cpp \
    ../litehtml/src/style.cpp \
    ../litehtml/src/stylesheet.cpp \
    ../litehtml/src/table.cpp \
    ../litehtml/src/utf8_strings.cpp \
    ../litehtml/src/web_color.cpp \

RESOURCES += \
    res.qrc
