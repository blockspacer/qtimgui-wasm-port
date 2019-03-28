#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

#include <QtImGui.h>
#include <imgui.h>
#include <imgui_internal.h>
#include "litehtml.h"
#include "container_qt5_imgui.h"
#include "IconsFontAwesome5.h"
#include "ImGuiRenderer.h"

#include <memory>
#include <cmath>
#include <utility>

#include <QPainter>
#include <QScreen>
#include <QGuiApplication>
#include <QTimer>
#include <QSurfaceFormat>
#include <QOpenGLWindow>
#include <QOpenGLExtraFunctions>
#include <QFile>
#include <QDebug>
#include <QPushButton>

static litehtml::position pos;

static  QPushButton* btn2;

class DemoWindow : public QOpenGLWindow, private QOpenGLExtraFunctions
{
QWidget *m_par;
public:
 DemoWindow(QWidget *parent){
  m_par = parent;
}
private:
  bool todo = false;
  litehtml::document::ptr doc{};
  std::unique_ptr<container_qt5> cont;
  litehtml::context ctxt{};

protected:
    void initializeGL() override
    {
        //btn2 = new QPushButton("QPushButton", m_par);
        btn2 = new QPushButton("QPushButton");

        initializeOpenGLFunctions();
        QtImGui::initialize(this);
        //QtImGui::ImGuiRenderer::instance()->
    }

void RenderMainMenu()
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Open"))
      {
      }

      ImGui::Separator();

      if (ImGui::MenuItem("Exit"))
      {
      }

      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }
}

void InitialiseDockLayout()
{
  static bool initialised = false;

  if (initialised)
    return;

  initialised = true;

  const auto dockspace_id = ImGui::GetID("DockspaceID");

  ImGuiViewport* viewport = ImGui::GetMainViewport();

  ImGui::DockBuilderRemoveNode(dockspace_id);
  ImGui::DockBuilderAddNode(dockspace_id, 0);
  ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

  auto root = dockspace_id;
  const auto dock_up =
      ImGui::DockBuilderSplitNode(root, ImGuiDir_Up, 0.05f, nullptr, &root);
  const auto dock_left =
      ImGui::DockBuilderSplitNode(root, ImGuiDir_Left, 0.20f, nullptr, &root);
  const auto dock_right =
      ImGui::DockBuilderSplitNode(root, ImGuiDir_Right, 0.20f, nullptr, &root);
  const auto dock_down =
      ImGui::DockBuilderSplitNode(root, ImGuiDir_Down, 0.10f, nullptr, &root);

  ImGui::DockBuilderDockWindow("Toolbar", dock_up);
  ImGui::DockBuilderDockWindow("Properties", dock_left);
  ImGui::DockBuilderDockWindow("Log", dock_down);
  ImGui::DockBuilderDockWindow("Folders", dock_right);
  ImGui::DockBuilderDockWindow("Framebuffer", root);
  ImGui::DockBuilderDockWindow("EmptySpace", root);

  ImGui::DockBuilderFinish(dockspace_id);
}

    void paintGL() override
    {


//qDebug() << "paintGL";
//ImGuiRenderer::instance()->newFrame();
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
          // <a href='http://linuxfr.org/'>????text20xf2bb\u6211\u662F\u4E2D\u6587</a>
/*
          <input type="checkbox" name="nameOfChoice" value="1" checked="checked" />
          <form method="post" action="/Tests/Post/">
              <fieldset>
                  <legend>What is Your Favorite Pet?</legend>
                  <input type="checkbox" name="favorite_pet" value="Cats">Cats<br>
                  <input type="checkbox" name="favorite_pet" value="Dogs">Dogs<br>
                  <input type="checkbox" name="favorite_pet" value="Birds">Birds<br>
                  <br>
                  <input type="submit" value="Submit now" />
              </fieldset>
          </form>
 */
          std::string htmlStr = "";
          htmlStr += R"raw(
          <html>
          <body>
          Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.
          There are many variations of passages of Lorem Ipsum available, but the majority have suffered alteration in some form, by injected humour, or randomised words which don't look even slightly believable. If you are going to use a passage of Lorem Ipsum, you need to be sure there isn't anything embarrassing hidden in the middle of text. All the Lorem Ipsum generators on the Internet tend to repeat predefined chunks as necessary, making this the first true generator on the Internet. It uses a dictionary of over 200 Latin words, combined with a handful of model sentence structures, to generate Lorem Ipsum which looks reasonable. The generated Lorem Ipsum is therefore always free from repetition, injected humour, or non-characteristic words etc.
          <input width="50px" height="50px" type="checkbox" name="nameOfChoice" value="1" style="width:50px;height:50px;background:darkgrey;">

          <customtag>customtag</customtag>
          <link rel="stylesheet" href=":/test1.css">

          <div id='home'>dddd</div>

          <div style='margin:15px;font: "Droid Sans";background:#CCC;border-bottom:6px solid yellow;width:30px;height:30px'>–”—text1</div>
          <div style='font: "Cousine Regular";background:#EEE;border-right:6px solid yellow;width:30px;height:30px'>–”—text1</div>
          <div style='font: "Font Awesome";background:pink;border-left:16px solid grey;width:30px;height:30px'>
          )raw";

          htmlStr += "\uf15c ? ";
          htmlStr += u8"\uf15c";
          htmlStr += u8"\uf118";
          htmlStr += u8"\uf118 ? \uf118";


          htmlStr += R"raw(\uf118 ? \uf118</div>

          <ul><li>One‚‡Ô‚‡Ô</li><li>Zwei\u6211\u662F\u4E2D\u6587</li><li>Trois</li></ul>
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

    /*ImGui::SetNextWindowSize(ImVec2(width(),height()), ImGuiSetCond_Once );
    ImGui::SetNextWindowPos(ImVec2(.0f, .0f), ImGuiSetCond_Once);
    ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background

    ImGuiWindowFlags wflags = ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_DockNodeHost;
    wflags |= ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
    wflags |= ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
    if (ImGui::Begin("1"), ImVec2(0,0), wflags)
    {
      ImGui::Text( "  Paint" );
    }
    ImGui::End();*/

/*
  // Flags
  const auto window_flags =
    ImGuiWindowFlags_MenuBar |
    ImGuiWindowFlags_NoDocking |
    ImGuiWindowFlags_NoTitleBar |
    ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoBringToFrontOnFocus |
ImGuiWindowFlags_NoNavFocus;

auto open = true;
const auto viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(ImVec2(.0f, .0f));
  ImGui::SetNextWindowSize(ImVec2(500.0f, 500.0f));
ImGui::SetNextWindowViewport(viewport->ID);
ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::SetNextWindowBgAlpha(0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("_Editor::dockspace_name", &open, window_flags);
  ImGui::PopStyleVar();
ImGui::PopStyleVar(2);



  // Dock space
  const auto dockspace_id = ImGui::GetID("_Editor::dockspace_name");
  if (!ImGui::DockBuilderGetNode(dockspace_id))
  {
    // Reset/clear current docking state
    ImGui::DockBuilderRemoveNode(dockspace_id);
    ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_None);

    // DockBuilderSplitNode(ImGuiID node_id, ImGuiDir split_dir, float size_ratio_for_node_at_dir, ImGuiID* out_id_dir, ImGuiID* out_id_other);
    auto dock_main_id		= dockspace_id;
    auto dock_right_id						= ImGui::DockBuilderSplitNode(dock_main_id,		ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
    const auto dock_right_down_id	= ImGui::DockBuilderSplitNode(dock_right_id,	ImGuiDir_Down,	0.6f, nullptr, &dock_right_id);
    auto dock_down_id				= ImGui::DockBuilderSplitNode(dock_main_id,		ImGuiDir_Down,	0.3f, nullptr, &dock_main_id);
    const auto dock_down_right_id	= ImGui::DockBuilderSplitNode(dock_down_id,		ImGuiDir_Right, 0.6f, nullptr, &dock_down_id);

    // Dock windows
    ImGui::DockBuilderDockWindow("World",		dock_right_id);
    ImGui::DockBuilderDockWindow("Properties",	dock_right_down_id);
    ImGui::DockBuilderDockWindow("Console",		dock_down_id);
    ImGui::DockBuilderDockWindow("Assets",		dock_down_right_id);
    ImGui::DockBuilderDockWindow("Viewport",	dock_main_id);
    ImGui::DockBuilderFinish(dock_main_id);
  }
ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruDockspace);

ImGui::SetNextWindowSize(ImVec2(width(),height()), ImGuiSetCond_Once );
    ImGui::SetNextWindowPos(ImVec2(.0f, .0f), ImGuiSetCond_Once);
    ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background

    if (ImGui::Begin("1"))
    {
      ImGui::Text( "  Paint" );
    }
    ImGui::End();


ImGui::End();*/


  ImGuiWindowFlags flags = 0;
  //flags |= ImGuiWindowFlags_MenuBar;
  //flags |= ImGuiWindowFlags_NoNav;
  flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
  flags |= ImGuiWindowFlags_NoCollapse;
  flags |= ImGuiWindowFlags_NoDocking;
  flags |= ImGuiWindowFlags_NoMove;
  flags |= ImGuiWindowFlags_NoNavFocus;
  flags |= ImGuiWindowFlags_NoResize;
  flags |= ImGuiWindowFlags_NoTitleBar;
  //flags |= ImGuiWindowFlags_NoDecoration;
  //flags |= ImGuiWindowFlags_HorizontalScrollbar;
  flags |= ImGuiWindowFlags_HorizontalScrollbar;

  flags |= ImGuiWindowFlags_HorizontalScrollbar;
  flags |= ImGuiWindowFlags_AlwaysHorizontalScrollbar;
  flags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;

  ImGuiViewport* viewport = ImGui::GetMainViewport();
  //viewport->Size
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);
  //ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background


  ImGui::SetNextWindowPos(ImVec2(.0f, .0f));
  ImGui::SetNextWindowSize(ImVec2(width(),height()));
  //ImGui::SetNextWindowSize(ImVec2(200,200));
//ImGui::SetNextWindowViewport(viewport->ID);
ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::SetNextWindowBgAlpha(0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::PopStyleVar();
ImGui::PopStyleVar(2);


  ImGui::Begin("Dockspace", nullptr, flags);

  InitialiseDockLayout();

ImGuiWindowFlags flags2 = 0;
  /*flags2 |= ImGuiWindowFlags_NoBringToFrontOnFocus;
  flags2 |= ImGuiWindowFlags_NoCollapse;
  flags2 |= ImGuiWindowFlags_NoDocking;
  flags2 |= ImGuiWindowFlags_NoMove;
  flags2 |= ImGuiWindowFlags_NoNavFocus;
  flags2 |= ImGuiWindowFlags_NoResize;
  flags2 |= ImGuiWindowFlags_NoTitleBar;*/
  flags2 |= ImGuiWindowFlags_HorizontalScrollbar;
  flags2 |= ImGuiWindowFlags_AlwaysHorizontalScrollbar;
  flags2 |= ImGuiWindowFlags_AlwaysVerticalScrollbar;


          //ImVec2 debugDataSize = ImGui::GetWindowSize();

        if(doc) {
          pos.x = 0;
          pos.y = 0;
          pos.width = width();//debugDataSize.x;
          pos.height = height();//debugDataSize.y;
          //qDebug() << debugDataSize.x;
          //doc->render(std::max(pos.width, 1)); // TODO
          doc->render(std::max(pos.width, pos.height)); // TODO
          //doc->render(100); // TODO
          //doc->render(8000);
        }
//qDebug() << doc->width();
  ImGui::DockSpace(ImGui::GetID("DockspaceID"), ImVec2(doc->width(),doc->height()), flags2);
ImGui::Dummy(ImVec2(doc->width(),doc->height())); // create space for it

   ImGui::Text( "  Paint" );



        {
          ImFont* font = QtImGui::ImGuiRenderer::getFont(QString("\"Font Awesome\""));
          ImGui::PushFont(font);
          ImGui::Text( u8"\uf118 \uf118" );
          ImGui::PopFont();
        }
        ImGui::Text("RU: ‚‡Ô‚‡Ô");
      //if (ImGui::BeginChildFrame(0123, ImVec2(debugDataSize.x, debugDataSize.y)))
      //if (ImGui::BeginChildFrame(0123, ImVec2(500, 500)))
      //if (ImGui::BeginChildFrame(0123, ImVec2(0, 0)))
      {
        //litehtml::position clip(0, 0, 1024, 1024);
        //m_document->draw((litehtml::uint_ptr)this, 0, 0, &clip);

        if(doc) {
          //ImGui::Dummy(ImVec2(doc->width(),doc->height())); // create space for it
          //ImGui::Dummy(ImVec2(2000,2000)); // create space for it
          doc->draw((litehtml::uint_ptr)this, -ImGui::GetScrollX(), -ImGui::GetScrollY(), &pos);
          //qDebug() << ImGui::GetScrollY();

          // TODO: scrollbar
          //ImGui::SetScrollY(ImGui::GetScrollY() + ImGui::GetWindowSize().y);

          cont->render();
        }

        ImVec2 mouse_pos = ImGui::GetMousePos();
        ImVec2 win_pos = ImGui::GetWindowPos();
        mouse_pos.x = mouse_pos.x - win_pos.x;
        mouse_pos.y = mouse_pos.y - win_pos.y;
        std::vector<litehtml::position> redraw_boxes;
        if (ImGui::IsMouseClicked(0))
        {
          //doc->on_lbutton_down(mouse_pos.x, mouse_pos.y, mouse_pos.x, mouse_pos.y, redraw_boxes);
          cont->onMousePress(mouse_pos.x, mouse_pos.y, mouse_pos.x, mouse_pos.y, redraw_boxes);
        }
        if (ImGui::IsMouseReleased(0))
        {
          //doc->on_lbutton_up(mouse_pos.x, mouse_pos.y, mouse_pos.x, mouse_pos.y, redraw_boxes);
          cont->onMouseRelease(mouse_pos.x, mouse_pos.y, mouse_pos.x, mouse_pos.y, redraw_boxes);
        }
        cont->onMouseMove(mouse_pos.x, mouse_pos.y, mouse_pos.x, mouse_pos.y, redraw_boxes);
        //doc->on_mouse_over(mouse_pos.x, mouse_pos.y, mouse_pos.x, mouse_pos.y, redraw_boxes);


      }
      //ImGui::EndChildFrame();

  ImGui::End();

  //RenderMainMenu();

  //UpdateCore();

  /*ImGui::Begin("Properties");
  ImGui::End();

  ImGui::Begin("Log");
  ImGui::End();

  ImGui::Begin("Folders");
  ImGui::End();

  ImGui::Begin("Toolbar");
  ImGui::End();*/


#ifdef hhhh


    // TODO: refresh only on resize
    /*QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    auto height = screenGeometry.height();
    auto width = screenGeometry.width();*/

    ImGui::SetNextWindowSize(ImVec2(width(),height()), ImGuiSetCond_Once );
    ImGui::SetNextWindowPos(ImVec2(.0f, .0f), ImGuiSetCond_Once);
    ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background
    /*
if (ImGui::BeginPopupContextWindow())
        {

          ImGui::Text( u8"\uf118 \uf118" );
          ImGui::EndPopup();
}*/

    // https://pong.hku.nl/blog/GuiTests/
    //ImGuiWindowFlags wflags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings;
    //ImGuiWindowFlags wflags = ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
    //ImGuiWindowFlags wflags = ImGuiWindowFlags_NoCollapse;
    ImGuiWindowFlags wflags = ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_DockNodeHost;
    wflags |= ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
    wflags |= ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
    if (ImGui::Begin("1"), ImVec2(0,0), wflags)
    //if (ImGui::BeginChildFrame(132, ImVec2(width(),height())))
    {
      //ImGui::Text( ICON_FA_PAINT_BRUSH "  Paint" );

      //ImGui::Text( u8"?" );
      //ImGui::Text("%s Search", ICON_FA_SEARCH);
      /*ImGui::Text("\xE4\xBD\xA0\xE5\xA5\xBD");
      ImGui::Text(u8"\xE4\xBD\xA0\xE5\xA5\xBD");
      ImGui::Text(u8"EDFD€€¬¬€¬¿””hello ?? ?????????a");
      ImGui::Text("hello ?? ?????????a");
      ImGui::Text("\x68\x65\x6C\x6C\x6F\x20" "\xE8\x8F\x9C\xE5\x8D\x95\x20" "\xE5\x9C\xA8\xE5\x93\xAA\x20" "a" "\xE9\x87\x8C\xE6\x96\x87" "\xE4\xBB\x3F\xE6\x88\x91\xE6\x98\xAF\xE4\xB8\xAD\xE6\x96\x87\x61");
      ImGui::Text("hello ?? ?? ??? ????a");
      ImGui::Text("fsdfsdad????");
      ImGui::Text("Kanjis: \xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e (nihongo)");*/
      /*if (ImGui::Button("refresh")) first = true;
      ImGui::SameLine();
      ImGui::InputText("Host", host, sizeof(host));
      ImGui::SameLine();
      ImGui::InputText("Path", path, sizeof(path));*/

          litehtml::position pos;
          ImVec2 debugDataSize = ImGui::GetWindowSize();

        if(doc) {
          pos.x = 0;
          pos.y = 0;
          pos.width = debugDataSize.x;
          pos.height = debugDataSize.y;
          //qDebug() << debugDataSize.x;
          doc->render(std::max(debugDataSize.x, 1.f)); // TODO
        }

        {
          ImFont* font = QtImGui::ImGuiRenderer::getFont(QString("\"Font Awesome\""));
          ImGui::PushFont(font);
          ImGui::Text( u8"\uf118 \uf118" );
          ImGui::PopFont();
        }
        ImGui::Text("RU: ‚‡Ô‚‡Ô");
      if (ImGui::BeginChildFrame(0123, ImVec2(debugDataSize.x, debugDataSize.y)))
      {
        //litehtml::position clip(0, 0, 1024, 1024);
        //m_document->draw((litehtml::uint_ptr)this, 0, 0, &clip);

        if(doc) {
          //ImGui::Dummy(ImVec2(doc->width(),doc->height())); // create space for it
          doc->draw((litehtml::uint_ptr)this, -ImGui::GetScrollX(), -ImGui::GetScrollY(), &pos);
          //qDebug() << ImGui::GetScrollY();

          // TODO: scrollbar
          //ImGui::SetScrollY(ImGui::GetScrollY() + ImGui::GetWindowSize().y);

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
//#define nope
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
#endif


QPainter qPainter(this);
  qPainter.beginNativePainting();

        // Do render before ImGui UI is rendered
        glViewport(0, 0, width(), height());
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

qPainter.endNativePainting();
        ImGui::Render();
qPainter.drawText(20, 40, "is is a minimal sample application which mixes OpenGL c");
QPen qPen;
  qPen.setWidth(1);
  qPen.setColor(QColor(Qt::black));
  qPen.setStyle(Qt::SolidLine);
  qPainter.resetMatrix();
  qPainter.setPen(qPen);
  qPainter.drawLine(0, 0, width(), height());
  qPainter.drawLine(0, height(), width(), 0);
    btn2->setText("*updateTimer = new QTimer(this); for");
    //btn2->setAttribute(Qt::WA_TranslucentBackground);
    btn2->render(this, QPoint(50, 50));
    //btn2->installEventFilter(this);
    }

private:
    bool show_test_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImColor(114, 144, 154);
};

static  DemoWindow* glWindow;
static QWidget* container;
static QTimer timer;

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{

resize(1280, 720);

ui->setupUi(this);


    QPushButton btn("asdsaddsaadsasdads");
     ui->verticalLayout->addWidget(&btn);

   glWindow = new DemoWindow(this);
    container = QWidget::createWindowContainer(glWindow);
    //container->setAcceptDrops(false);
    //container->installEventFilter(this);
    //container->setAcceptedMouseButtons(Qt::AllButtons) ;
    //container->setFocusPolicy(Qt::TabFocus);
    ui->verticalLayout->addWidget(container);

    /*glWindow->installEventFilter(QtImGui::ImGuiRenderer::instance());
    container->installEventFilter(QtImGui::ImGuiRenderer::instance());
    installEventFilter(QtImGui::ImGuiRenderer::instance());*/

    //setCentralWidget(container);

    // https://stackoverflow.com/questions/9638420/qmainwindow-not-tracking-mouse-with-setmousetracking/19495591
    //centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
    //setMouseTracking(true);

    //container->show();
    //ui->verticalLayout->setMargin(0);

    //connect (this, SIGNAL (keyEvent (int, int) ), container, SLOT (onKeyPressEvent (int, int) ) );
    /*connect (this, SIGNAL (mousePressEvent (QMouseEvent *event) ), container, SLOT (mousePressEvent (QMouseEvent *event) ) );
    connect (this, SIGNAL (mouseMoveEvent (QMouseEvent *event) ), container, SLOT (mouseMoveEvent (QMouseEvent *event) ) );
*/

    //container->focusWidget();

    //QObject::connect(&timer, SIGNAL(timeout()), glWindow, SLOT(update()));
    //QObject::connect(&timer, SIGNAL(timeout()), container, SLOT(update()));
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(refresh()));
    //QObject::connect(&timer, SIGNAL(timeout()), &w2, SLOT(update()));
    glWindow->update();
    timer.start(16); // Update at 60 fps

repaint();

    //ui->logTex;t->setLineWrapMode(QPlainTextEdit::NoWrap);

}

void MainWindow::refresh()
{

  glWindow->update();

//qDebug() << "MainWindow::refresh()";
  /*receiver.receiveData();
  cuboid->angleX = receiver.angleX->points.back().y();
  cuboid->angleY = receiver.angleY->points.back().y();

  cuboid->update();*/

}

MainWindow::~MainWindow()
{
delete ui;
}
