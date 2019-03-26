#pragma once

#if defined(Q_OS_HTML5) or defined(Q_OS_WASM) or defined(__EMSCRIPTEN__)

#define USE_GL_ES2
#include <GLES2/gl2.h>
#include "emscripten.h"
#endif

#include <QOpenGLExtraFunctions>
#include <QObject>
#include <QPoint>
#include <imgui.h>
#include <memory>
#include <cstring>
#include <string>
#include <map>

class QMouseEvent;
class QWheelEvent;
class QKeyEvent;

namespace QtImGui {

class WindowWrapper {
public:
    virtual ~WindowWrapper() {}
    virtual void installEventFilter(QObject *object) = 0;
    virtual QSize size() const = 0;
    virtual qreal devicePixelRatio() const = 0;
    virtual bool isActive() const = 0;
    virtual QPoint mapFromGlobal(const QPoint &p) const = 0;
};

class ImGuiRenderer : public QObject, QOpenGLExtraFunctions {
    Q_OBJECT
public:
    void initialize(WindowWrapper *window);
    void newFrame();

    bool eventFilter(QObject *watched, QEvent *event);

    static ImGuiRenderer *instance();

public:
  static ImFont* getFont(const QString& fontName) noexcept {
    return fontname2font[fontName];
  }

private:
    ImGuiRenderer() {}

    void onMousePressedChange(QMouseEvent *event);
    void onWheel(QWheelEvent *event);
    void onKeyPressRelease(QKeyEvent *event);

    void renderDrawList(ImDrawData *draw_data);
    bool createFontsTexture();
    bool createDeviceObjects();

private:
    static std::map<QString, QString> fontname2path;
    static std::map<QString, ImFont*> fontname2font;
    std::unique_ptr<WindowWrapper> m_window;
    double       g_Time = 0.0f;
    bool         g_MousePressed[3] = { false, false, false };
    float        g_MouseWheel;
    float        g_MouseWheelH;
    GLuint       g_FontTexture = 0;
    int          g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
    int          g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;
    int          g_AttribLocationPosition = 0, g_AttribLocationUV = 0, g_AttribLocationColor = 0;
    unsigned int g_VboHandle = 0, g_VaoHandle = 0, g_ElementsHandle = 0;
};

}
