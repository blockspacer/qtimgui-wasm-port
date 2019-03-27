# QtImGui

Qt (QOpenGLWidget / QOpenGLWindow) backend for [ImGui](https://github.com/ocornut/imgui)

It enables ImGui to run in QOpenGLWidget / QOpenGLWindow.

[![https://gyazo.com/eb68699c96b9147cca3d5ea9fadfc263](https://i.gyazo.com/eb68699c96b9147cca3d5ea9fadfc263.gif)](https://gyazo.com/eb68699c96b9147cca3d5ea9fadfc263)

## How to use

* Add QtImGui sources and headers to your project
    * If you are using git submodule, run `git submodule update --init --recursive` to ensure that the inner submodule is initialized as well.
* Add `include(path/to/qtimgui.pri)` to youre `.pro` file
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
https://www.bogotobogo.com/Qt/Qt5_OpenGL_QGLWidget.php
https://github.com/grimace87/RandomToadJunk/blob/91219bd278db4cd77ab9c1578df3ab7cad542a27/app/src/main/java/grimace/toad/MainActivity.java
http://www.trentreed.net/blog/qt5-opengl-part-1-basic-rendering/
https://github.com/7thFACTOR/horus_ui

Dsable some features for web build https://blog.basyskom.com/2017/qt-lite/

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
