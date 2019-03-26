#include <QtImGui.h>
#include <imgui.h>
#include "litehtml.h"
#include "container_qt5_imgui.h"

#include <QGuiApplication>
#include <QTimer>
#include <QSurfaceFormat>
#include <QOpenGLWindow>
#include <QOpenGLExtraFunctions>
#include <QFile>
#include <QDebug>


class DemoWindow : public QOpenGLWindow, private QOpenGLExtraFunctions
{
private:
bool todo = false;
litehtml::document::ptr doc{};
std::unique_ptr<container_qt5> cont;
litehtml::context ctxt{};

protected:
    void initializeGL() override
    {
        initializeOpenGLFunctions();
        QtImGui::initialize(this);

    }

    void paintGL() override
    {
        QtImGui::newFrame();

        if(!todo) {
          // TODO >>>
          QFile master_css_fh("/home/avakimov_am/job/qtimgui/master.css");
          master_css_fh.open(QIODevice::ReadOnly);
          QByteArray master_css = master_css_fh.readAll();
          //ctxt.load_master_stylesheet("/home/pierre/projects/litehtml/include/master.css");
          qDebug() << master_css;
          ctxt.load_master_stylesheet(master_css.constData());

          cont = std::make_unique<container_qt5>();

          //auto doc = litehtml::document::createFromUTF8("<html><body><ul><li>One</li><li>Zwei</li><li>Trois</li></ul></body></html>", &c, &ctxt);
          //auto doc = litehtml::document::createFromUTF8("<html><body><p>Line1.1 Line1.2<br />Line2</p><ul><li>One</li><li>Zwei</li><li>Trois</li></ul></body></html>", &c, &ctxt);
          doc = litehtml::document::createFromUTF8("<html><body><div style='background:green;width:30px;height:30px'>text1</div><a href=\"http://linuxfr.org/\">text2</a></body></html>", cont.get(), &ctxt);
          //auto doc = litehtml::document::createFromUTF8("<html><body><table><tr><th>H1</th><th>H2</th></tr><tr><td>C1.1</td><td>C1.2</td></tr><tr><td>C2.1</td><td>C2.2</td></tr></table></body></html>", &c, &ctxt);
          cont->set_document(doc);
          todo = true;
        }


     ImGui::SetNextWindowSize(ImVec2(800,800), ImGuiSetCond_FirstUseEver);
    if (ImGui::Begin("HTML"))
    {
      /*if (ImGui::Button("refresh")) first = true;
      ImGui::SameLine();
      ImGui::InputText("Host", host, sizeof(host));
      ImGui::SameLine();
      ImGui::InputText("Path", path, sizeof(path));*/

      if (ImGui::BeginChildFrame(0123, ImVec2(0, 0)))
      {
        litehtml::position clip(0, 0, 1024, 1024);
        //m_document->draw((litehtml::uint_ptr)this, 0, 0, &clip);

        if(doc) {
          doc->render(1024); // TODO
          doc->draw((litehtml::uint_ptr)this, 0, 0, nullptr);
          cont->render();
        }

        ImVec2 mouse_pos = ImGui::GetMousePos();
        ImVec2 win_pos = ImGui::GetWindowPos();
        mouse_pos.x = mouse_pos.x - win_pos.x;
        mouse_pos.y = mouse_pos.y - win_pos.y;
        std::vector<litehtml::position> redraw_boxes;
        if (ImGui::IsMouseClicked(0))
        {
          doc->on_lbutton_down(mouse_pos.x, mouse_pos.y, mouse_pos.x, mouse_pos.y, redraw_boxes);
        }
        if (ImGui::IsMouseReleased(0))
        {
          doc->on_lbutton_up(mouse_pos.x, mouse_pos.y, mouse_pos.x, mouse_pos.y, redraw_boxes);
        }
        doc->on_mouse_over(mouse_pos.x, mouse_pos.y, mouse_pos.x, mouse_pos.y, redraw_boxes);


      }
      ImGui::EndChildFrame();
    }
    ImGui::End();

#ifdef nope
        // 1. Show a simple window
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
        {
            static float f = 0.0f;
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
            if (ImGui::Button("Test Window")) show_test_window ^= 1;
            if (ImGui::Button("Another Window")) show_another_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        // 2. Show another simple window, this time using an explicit Begin/End pair
        if (show_another_window)
        {
            ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello");
            ImGui::End();
        }

        // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
        if (show_test_window)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
            ImGui::ShowTestWindow();
        }
#endif
        // Do render before ImGui UI is rendered
        glViewport(0, 0, width(), height());
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
    }

private:
    bool show_test_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImColor(114, 144, 154);
};

int main(int argc, char *argv[])
{
    // Use OpenGL 3 Core Profile
    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);

    QGuiApplication a(argc, argv);

    // Show window
    DemoWindow w;
    w.setTitle("QtImGui window example");
    w.resize(1280, 720);
    w.show();

    // Update at 60 fps
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &w, SLOT(update()));
    timer.start(16);

    return a.exec();
}
