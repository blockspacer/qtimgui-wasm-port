#include <QtImGui.h>
#include <imgui.h>
#include <imgui_internal.h>
#include "litehtml.h"
#include "container_qt5_imgui.h"
#include "IconsFontAwesome5.h"
#include "ImGuiRenderer.h"

#include "mainwindow.h"

#include <memory>
#include <cmath>
#include <utility>

#include <QScreen>
#include <QGuiApplication>
#include <QTimer>
#include <QSurfaceFormat>
#include <QOpenGLWindow>
#include <QOpenGLExtraFunctions>
#include <QFile>
#include <QDebug>

static litehtml::position pos;

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Use OpenGL 3 Core Profile
    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);

    //QGuiApplication a(argc, argv);

    // Show window
    /*DemoWindow w;
    w.setTitle("QtImGui window example");
    w.resize(1280, 720);
    w.show();*/

    MainWindow w2;
    //w2.setTitle("QtImGui window example");
    w2.resize(1280, 720);
    w2.show();

    // Show window
    /*DemoWindow w2;
    w2.setTitle("QtImGui window example");
    w2.resize(444, 444);
    w2.show();*/

    // Update at 60 fps
    /*QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &w, SLOT(update()));
    //QObject::connect(&timer, SIGNAL(timeout()), &w2, SLOT(update()));
    timer.start(16);*/

    return a.exec();
}
