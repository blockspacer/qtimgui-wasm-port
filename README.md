# QtImGui

Qt (QOpenGLWidget / QOpenGLWindow) backend for [ImGui](https://github.com/ocornut/imgui)

It enables ImGui to run in QOpenGLWidget / QOpenGLWindow.

[![https://gyazo.com/eb68699c96b9147cca3d5ea9fadfc263](https://i.gyazo.com/eb68699c96b9147cca3d5ea9fadfc263.gif)](https://gyazo.com/eb68699c96b9147cca3d5ea9fadfc263)

## How to use

* Add QtImGui sources and headers to your project
    * If you are using git submodule, run `git submodule update --init --recursive` to ensure that the inner submodule is initialized as well.
* Add `include(path/to/qtimgui.pri)` to your `.pro` file
* Subclass `QOpenGLWindow` or `QOpenGLWidget` and:

```cpp
class DemoWindow : public QOpenGLWindow
{
protected:
    void initializeGL() override
    {
        QtImGui::initialize(this);
    }
    void paintGL() override
    {
        // you can do custom GL rendering as well in paintGL

        QtImGui::newFrame();

        ImGui::Text("Hello");
        // more widgets...

        ImGui::Render();
    }
};
```

See [QOpenGLWidget example](demo-widget/demo-widget.cpp) and [QOpenGLWindow example](/demo-window/demo-window.cpp) for details.


## TODO

Lottie and opengl
https://github.com/lijianegret/SkiaInGL
https://github.com/sudaoblinnnk/apple/blob/58f0edacf5ed250d5341c90c18e10c83b1cdd3a1/lottie/src/main/java/com/airbnb/lottie/playvideo_texuture/VideoTextureSurfaceRenderer.java#L115
https://github.com/JimmieKJ/osgProjs/blob/b7a113a1db345fe424721e0f261c54d054ec5996/PROJECT/Qt/Qt5.5.1/5.5/Src/qtwebengine/src/3rdparty/chromium/third_party/skia/debugger/QT/SkGLWidget.cpp
https://github.com/google/skia/blob/ff6a73cc08af15f1fc8ba38dfa1dc7c2774fa060/dm/DM.cpp#L791
https://github.com/octoon/octoon/blob/367ff3d393db08f74bc3cd8b381c34c89deba0f3/samples/lottie/main.cpp
https://github.com/Samsung/rlottie/issues/25
https://www.bogotobogo.com/Qt/Qt5_OpenGL_QGLWidget.php
https://github.com/grimace87/RandomToadJunk/blob/91219bd278db4cd77ab9c1578df3ab7cad542a27/app/src/main/java/grimace/toad/MainActivity.java
http://www.trentreed.net/blog/qt5-opengl-part-1-basic-rendering/
https://github.com/7thFACTOR/horus_ui
https://github.com/Conntac/lottie-qt/blob/92bb68003b3ec1a0986b6e954ad2dbde9c87b16f/lottie_qt/Classes/Extensions/LOTBezierPath.cpp#L112

SkTypeface opengl
https://github.com/datadog23/image-test/blob/c26adebc64b2535a331a012fcde6ac36a0e2790c/src/TextTextureAtlas.cpp
https://github.com/huipengzhao/screentimestamp/blob/f8f0448e01aaafa92251b64bf1bf3a7954e6f067/TimestampRender.cpp
https://en.sfml-dev.org/forums/index.php?topic=11800.0

cairo
https://gist.github.com/derofim/d4862a41fa53c910d2efae86b7ac04dc

cairo svg
Dsable some features for web build https://blog.basyskom.com/2017/qt-lite/

cairo font "cairo_ft_font_face_create_for_ft_face" glClearColor
>>>
https://github.com/michaeljclark/graphstorm/blob/57a4db5d125f61fca0ec00e1553aa8273ad2dd55/src/EGTextCairo.cc#L27
https://github.com/goo160047co/mapserver/blob/efa6ce2c6c821a0ff34e0e4d4a86fc5e11cee666/mapcairo.c#L163
https://github.com/mastensg/windportal/blob/73f6be8efc85b530a09381fe651c24c290de17b2/firmware/wp_visuals/src/visuals.cc#L343
https://gist.github.com/blockspacer/208eb788c2e326be1938793985492f68
https://github.com/ds-hwang/OpenGL-ES-3.0-Cookbook/blob/master/SourceRepository/GLPIFramework/Font/harfbuzz-ng/util/helper-cairo.cc#L64
https://github.com/DavidLudwig/sg13-research/blob/master/hello_world.cpp#L35
https://www.lemoda.net/c/free-type/index.html
https://github.com/WayfireWM/wayfire/blob/master/plugins/decor/deco-subsurface.cpp#L31
<<<
https://jan.newmarch.name/Wayland/Cairo/
qtimgui/litehtml/containers/cairo/cairo_container.cpp
https://coadycode.co.uk/code
http://changetheworldwithyourpassion.blogspot.com/2009/08/draw-text-with-opengl-and-cairo.html
http://liyanrui.is-programmer.com/posts/16643.html
http://liyanrui.is-programmer.com/tag/Cairo
https://link.springer.com/book/10.1007%2F978-1-4842-2472-4
https://github.com/mahiso/JudoShiai/blob/5b549b68d05b1029d83c41e1356561b4705574c8/emscripten/common/cairowrapper.h#L213

cairo Emscripten
https://forums.wesnoth.org/viewtopic.php?t=43313
https://github.com/emscripten-core/emscripten/issues/5049


Opengl UI
https://github.com/litehtml/litehtml
https://github.com/lc-soft/LCUI
LibRocket
https://github.com/Flix01/imgui/wiki/ImGui-Addons-Branch-Home
litehtml + SVG https://github.com/bigfatbrowncat/nanohtml/blob/master/src/Window.cpp#L108 https://github.com/memononen/nanosvg
litehtml + imgui https://github.com/nem0/lumixengine_html/blob/master/src/editor/plugins.cpp

flexbox / layout engine

plugin based design

utf8 fonts

shadow dom manipulations

dynamic fonts

https://stackoverflow.com/a/33558820
    HTML, CSS, SVG, aPNG (animated PNGs), image sprites,
    <plaintext> - editor with syntax highlighting,
    <htmlarea> - WYSIWYG HTML editor,
    <frame type=pager> - print preview and HTML/CSS print,
    animations,
    HTTP client, REST/JSON client, WebSocket's, DataSockets,
    etc.

TODO: button/input callbacks

TODO: fix fps
