#include <QtImGui.h>
#include <imgui.h>
#include "litehtml.h"
#include "container_qt5_imgui.h"
#include "IconsFontAwesome5.h"
#include "ImGuiRenderer.h"

#include <memory>
#include <cmath>
#include <utility>

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
          QFile master_css_fh("://master.css");
          master_css_fh.open(QIODevice::ReadOnly);
          QByteArray master_css = master_css_fh.readAll();
          //ctxt.load_master_stylesheet("://master.css");
          //qDebug() << master_css;
          ctxt.load_master_stylesheet(master_css.constData());

          cont = std::make_unique<container_qt5>();
          //const char* html2 = u"g";
          // <a href='http://linuxfr.org/'>我是中文text20xf2bb\u6211\u662F\u4E2D\u6587</a>

          std::string htmlStr = "";
          htmlStr += R"raw(
          <html>
          <body>
          <customtag>customtag</customtag>
          <link rel="stylesheet" href=":/test1.css">
          <div style='margin:15px;font: "Droid Sans";background:#CCC;border-bottom:6px solid yellow;width:30px;height:30px'>РУСtext1</div>
          <div style='font: "Cousine Regular";background:#EEE;border-right:6px solid yellow;width:30px;height:30px'>РУСtext1</div>
          <div style='font: "Font Awesome";background:pink;border-left:16px solid grey;width:30px;height:30px'>
          )raw";

          htmlStr += "\uf15c  ";
          htmlStr += u8"\uf15c";
          htmlStr += u8"\uf118";
          htmlStr += u8"\uf118  \uf118";


          htmlStr += R"raw(\uf118  \uf118</div>

          <ul><li>Oneвапвап</li><li>Zwei\u6211\u662F\u4E2D\u6587</li><li>Trois</li></ul>
          <bold>123SFSDFDFSDF</bold>
          <strong>emphasized text</strong>
          <span style='font-weight: bold;'>bold text</span>
          <p>Line1.1 Line1.2<br />Line2</p><ul><li>One</li><li>Zwei</li><li>Trois</li></ul>
          <table><tr><th>H1</th><th>H2</th></tr><tr><td>C1.1</td><td>C1.2</td></tr><tr><td>C2.1</td><td>C2.2</td></tr></table>
          <img src='://test.png' alt=''>
          <img src='://test2.png' alt=''>
          </body>
          </html>)raw";

          const char* html = htmlStr.c_str();
          doc = litehtml::document::createFromUTF8(html, cont.get(), &ctxt);
          //auto doc = litehtml::document::createFromUTF8("<html><body></body></html>", &c, &ctxt);
          cont->set_document(doc);
          todo = true;
        }

     ImGui::SetNextWindowSize(ImVec2(800,800), ImGuiSetCond_FirstUseEver);
    if (ImGui::Begin("HTML"))
    {
      //ImGui::Text( ICON_FA_PAINT_BRUSH "  Paint" );

      {
        ImFont* font = QtImGui::ImGuiRenderer::getFont(QString("\"Font Awesome\""));
        ImGui::PushFont(font);
        ImGui::Text( u8"\uf118 \uf118" );
        ImGui::PopFont();
      }
      //ImGui::Text( u8"" );
      //ImGui::Text("%s Search", ICON_FA_SEARCH);
      /*ImGui::Text("\xE4\xBD\xA0\xE5\xA5\xBD");
      ImGui::Text(u8"\xE4\xBD\xA0\xE5\xA5\xBD");
      ImGui::Text(u8"EDFDЫЫВВЫВАУУhello 菜单 在哪里文件我是中文a");
      ImGui::Text("hello 菜单 在哪里文件我是中文a");
      ImGui::Text("\x68\x65\x6C\x6C\x6F\x20" "\xE8\x8F\x9C\xE5\x8D\x95\x20" "\xE5\x9C\xA8\xE5\x93\xAA\x20" "a" "\xE9\x87\x8C\xE6\x96\x87" "\xE4\xBB\x3F\xE6\x88\x91\xE6\x98\xAF\xE4\xB8\xAD\xE6\x96\x87\x61");
      ImGui::Text("hello 菜单 在哪 里文件 我是中文a");
      ImGui::Text("fsdfsdad我是中文");
      ImGui::Text("Kanjis: \xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e (nihongo)");*/
      ImGui::Text("RU: вапвап");
      /*if (ImGui::Button("refresh")) first = true;
      ImGui::SameLine();
      ImGui::InputText("Host", host, sizeof(host));
      ImGui::SameLine();
      ImGui::InputText("Path", path, sizeof(path));*/

      if (ImGui::BeginChildFrame(0123, ImVec2(0, 0)))
      {
        //litehtml::position clip(0, 0, 1024, 1024);
        //m_document->draw((litehtml::uint_ptr)this, 0, 0, &clip);

        if(doc) {
          ImVec2 debugDataSize = ImGui::GetWindowSize();
          litehtml::position pos;
          pos.x = 0;
          pos.y = 0;
          pos.width = debugDataSize.x;
          pos.height = debugDataSize.y;
          //qDebug() << debugDataSize.x;
          doc->render(std::max(debugDataSize.x, 1.f)); // TODO
          doc->draw((litehtml::uint_ptr)this, 0, 0, &pos);
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
#define nope
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
