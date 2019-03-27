#include "container_qt5_imgui.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imgui_internal.h"
#include "ImGuiRenderer.h"
#include <QDebug>
#include <QFont>
#include <QFontMetrics>
#include <QPainter>
#include <QMouseEvent>
#include <QDesktopServices>
#include <QDataStream>
#include <QScreen>

// TODO: see litehtml_from_utf8
#if defined(LITEHTML_UTF8)
#define _T(x) x
#else
#define _T(x) L ##x
#endif

/*static qint64 hash(const QString & str)
{
  QByteArray hash = QCryptographicHash::hash(
    QByteArray::fromRawData((const char*)str.utf16(), str.length()*2),
    QCryptographicHash::Md5
  );
  Q_ASSERT(hash.size() == 16);
  QDataStream stream(&hash);
  qint64 a, b;
  stream >> a >> b;
  return a ^ b;
}*/

#ifdef nope
struct ImGuiFont : public ImFont
{
    ImGuiFont(const QFontMetrics& metrics)
    {

ImGuiIO& io = ImGui::GetIO();
        for (int i = 0; i < 255; ++i)
        {
            Glyph g;
            /*
    ImWchar         Codepoint;          // 0x0000..0xFFFF
    float           AdvanceX;           // Distance to next character (= data from font + ImFontConfig::GlyphExtraSpacing.x baked in)
    float           X0, Y0, X1, Y1;     // Glyph corners
    float           U0, V0, U1, V1;     // Texture coordinates
             * */
            g.Codepoint = i;
            g.AdvanceX = metrics.width(i);
            if (i == '\t')
                g.AdvanceX = metrics.width(' ') * 4;
            IndexAdvanceX.push_back(g.AdvanceX);
            Glyphs.push_back(g);
io.Fonts->AddCustomRectFontGlyph(this, i, g.AdvanceX, g.AdvanceX, g.AdvanceX);
        }
        Scale = 1.0f;
        FontSize = metrics.height() + metrics.leading();
        Descent = metrics.descent();
        Ascent = metrics.ascent();
        FallbackAdvanceX = 0.0f;
        ConfigData = 0x0;

    }

    /*
    IMGUI_API const ImFontGlyph*FindGlyph(ImWchar c) const;
    IMGUI_API const ImFontGlyph*FindGlyphNoFallback(ImWchar c) const;*/
//  IMGUI_API const ImFontGlyph*FindGlyph(ImWchar c) const;
    virtual IMGUI_API const ImFontGlyph* FindGlyph(ImWchar c) const override
    {
        if (c >= 0 && c <= 256)
            return &Glyphs[c];
        return FallbackGlyph;
    }
};
#endif

/**
 * Simple conversion functions
 */
static QRect getRect(const litehtml::position &position) {
    return QRect(position.x, position.y, position.width, position.height);
}

static QColor getColor(const litehtml::web_color &color) {
    return QColor(color.red, color.green, color.blue, color.alpha);
}

//static ImFont* imFont_;


// Now for the real stuff

container_qt5::container_qt5(QWidget *parent)
    : litehtml::document_container()//, QWidget(parent)
{
    //setMouseTracking(true);

/*
ImGuiIO& io = ImGui::GetIO();
 ImFont* font = io.Fonts->AddFontDefault();*/

//QFont qfont("Segoe UI");
//QFont qfont("Noto Sans");
/*QFont qfont("Droid Sans");

    qfont.setPixelSize(20);
    auto fm = QFontMetrics(qfont);
  //imFont_ = new ImGuiFont(fm);*/

// TODO >>

  //imFont_ = QtImGui::ImGuiRenderer::getFont("Cousine Regular");//QtImGui::ImGuiRenderer::customFont;// io.Fonts->AddFontFromFileTTF("://DroidSans.ttf", 16.0f);

  //imFont_ = io.Fonts->AddFontFromMemoryTTF();
//imFont_ = io.FontDefault;
 //io.Fonts->AddExternalFont(imFont_);
 //io.Fonts->AddCustomRectFontGlyph(imFont_,"Times New Roman",fm.width(),fm.height(),fm.xHeight())
}

container_qt5::~container_qt5()
{

}

void container_qt5::set_document(std::shared_ptr< litehtml::document > doc)
{
    _doc = doc;
}

/*void container_qt5::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    qDebug() << __FUNCTION__ << width();
    _doc->render(width());
    _doc->draw(&painter, 0, 0, nullptr);
}*/

void container_qt5::render()
{
    //qDebug() << __FUNCTION__ << "render";
}

void container_qt5::onMouseMove(QMouseEvent *event)
{
  litehtml::position::vector vec;
        onMouseMove(event->x(), event->y(), event->x(), event->y(), vec);
}

void container_qt5::onMouseMove(
int x, int y, int client_x, int client_y, litehtml::position::vector& redraw_boxes)
{
    lastCursorX = x;
    lastCursorY = y;
    lastCursorClientX = x;
    lastCursorClientY = y;
//qDebug() << "lastCursorX " << lastCursorX<< " lastCursorY " << lastCursorY;
    if (_doc->on_mouse_over(x, y, x, y, redraw_boxes))
        render();
}

void container_qt5::onMouseLeave(QMouseEvent *event)
{

   std::vector<litehtml::position> redraw_boxes;
   onMouseLeave(event->x(), event->y(), event->x(), event->y(), redraw_boxes);
}


void container_qt5::onMouseLeave(
int x, int y, int client_x, int client_y, litehtml::position::vector& redraw_boxes)
{
    lastCursorX = x;
    lastCursorY = y;
    lastCursorClientX = x;
    lastCursorClientY = y;

    if (_doc->on_mouse_leave(redraw_boxes))
        render();
}

void container_qt5::onMousePress(QMouseEvent *event)
{
    litehtml::position::vector vec;
    onMousePress(event->x(), event->y(), event->x(), event->y(), vec);
}

void container_qt5::onMousePress(
int x, int y, int client_x, int client_y, litehtml::position::vector& redraw_boxes )
{
    lastCursorX = x;
    lastCursorY = y;
    lastCursorClientX = x;
    lastCursorClientY = y;

    if (_doc->on_lbutton_down(x, y, x, y, redraw_boxes))
        render();
}

void container_qt5::onMouseRelease(QMouseEvent *event)
{
    litehtml::position::vector vec;
    onMouseRelease(event->x(), event->y(), event->x(), event->y(), vec);
}

void container_qt5::onMouseRelease(
int x, int y, int client_x, int client_y, litehtml::position::vector& redraw_boxes)
{
    lastCursorX = x;
    lastCursorY = y;
    lastCursorClientX = x;
    lastCursorClientY = y;

    if (_doc->on_lbutton_up(x, y, x, y, redraw_boxes))
        render();
}

bool container_qt5::OnMediaChanged()
{
    return _doc->media_changed();
}

int container_qt5::GetWidth()
{
    return _doc->width();
}

int container_qt5::GetHeight()
{
    return _doc->height();
}

// https://github.com/PingmanTools/LiteHtmlSharp/blob/3f4db0ff0ab4b5cd7f5e10aa1b6ed94f2eee0bcb/LiteHtmlLib/src/DocContainer.cpp#L159
/*ElementInfo* DocContainer::GetElementInfo(int ID)
{
  litehtml::tstring strToReturn;

  for (auto attr : this->m_attrs)
  {
    strToReturn.append(attr.first);
    strToReturn.append(_T("="));
    strToReturn.append(attr.second);
    strToReturn.append(_T("\n"));
  }
}*/

void container_qt5::get_language(litehtml::tstring& language, litehtml::tstring& culture) const
{
    qDebug() << "get_language";
    language = _t("en");
    culture = _t("");
}

void container_qt5::get_media_features(litehtml::media_features& media) const
{
    qDebug() << "get_media_features";
    /*media.width = width();
    media.height = height();
    media.device_width = width();
    media.device_height = height();
    media.type = litehtml::media_type_screen;*/

    litehtml::position client;
    get_client_rect(client);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    auto height = screenGeometry.height();
    auto width = screenGeometry.width();


    media.type = litehtml::media_type_screen;
    media.width = client.width;
    media.height = client.height;
    media.color = 8;
    media.monochrome = 0;
    media.color_index = 256;
    media.resolution = 96;
    media.device_width = width;
    media.device_height = height;

    qDebug() << "=> " << media.width << "x" << media.height;
}

static bool shouldCreateElement(const litehtml::tchar_t* tag_name, const litehtml::string_map& attributes, const std::shared_ptr< litehtml::document >& doc) {
  return true;
}

static int totalElements = 0;

// see https://github.com/litehtml/litebrowser/blob/master/src/ToolbarWnd.cpp#L572
std::shared_ptr< litehtml::element > container_qt5::create_element(const litehtml::tchar_t* tag_name, const litehtml::string_map& attributes, const std::shared_ptr< litehtml::document >& doc)
{
    //qDebug() << __FUNCTION__ << " this one can be 0";
    //doc->root()->get_child()
  if(!shouldCreateElement(tag_name, attributes, doc)) {
    return std::shared_ptr<litehtml::element>();
  }

  if (!t_strcasecmp(tag_name, _t("input")))
  {
  // action = /Tests/Post/
    //qDebug() << __FUNCTION__ << " input";
    /*auto iter = attributes.find(_t("type"));
    if (iter != attributes.end())
    {
      qDebug() << __FUNCTION__ <<  iter->first.c_str() << "=" << iter->second.c_str();
    }*/
    /*for (auto iter : attributes)
    {
      qDebug() << __FUNCTION__ <<  iter.first.c_str() << "=" << iter.second.c_str();
    }*/
    return std::make_shared<container_el_inputbox>(doc, attributes);
  }


  litehtml::tstring attributeStr;
  for (auto attr : attributes)
  {
    attributeStr.append(attr.first);
    attributeStr.append(_T("="));
    attributeStr.append(attr.second);
    attributeStr.append(_T("\n"));
  }
  std::string _attributes = std::string(attributeStr.begin(), attributeStr.end());

  //ElementInfo elementInfo = {};
  int elementID = totalElements++;
  if (elementID > 0)
  {
    // TODO

    //std::shared_ptr<TagElement> result = std::make_shared(doc);
    //result->SetManagedInfo(elementInfo);
    //_elements[elementID] = result;
    //return std::shared_ptr<litehtml::element>(result.get());
    //return std::make_shared<litehtml::element>(doc);
    return std::shared_ptr<litehtml::element>();
  }
  else
  {
    return std::shared_ptr<litehtml::element>();
  }
}

void container_qt5::get_client_rect(litehtml::position& client) const
{
    //qDebug() << "get_client_rect";
    // No scroll yet
    //client.move_to(0, 0);
    /*client.width = width();
    client.height = height();*/
    //qDebug() << "==> " << client.width << "x" << client.height;
/*
    client.height = 1024;
    client.width = 1024;
    ImGuiWindow* win = ImGui::GetCurrentWindow();
    client.x = win->Pos.x;
    client.y = win->Pos.y;*/


    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    auto height = screenGeometry.height();
    auto width = screenGeometry.width();

    client.height = height;
    client.width = width;
    ImGuiWindow* win = ImGui::GetCurrentWindow();
    client.x = win->Pos.x;
    client.y = win->Pos.y;

    /*qDebug() << "get_client_rect xy" << client.x << " " << client.y;
    qDebug() << "get_client_rect wh" << client.width << " " << client.height;*/
}

// Deletes the last clipping.
void container_qt5::del_clip()
{
    //qDebug() << "del_clip";

    // background image clip?
}

// Set the painting clip rectangle here. valid_x and valid_y are ignored.
// Please note, litehtml can set some clip rects.
// You have to save the clip positions and apply clipping on draw something.
void container_qt5::set_clip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius, bool valid_x, bool valid_y)
{
    //qDebug() << "set_clip";
}

void container_qt5::import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl)
{
    /*download(m_host, url.c_str(), &data);
    text = (const char*)&data[0];*/

    QFile qFile(url.c_str());

        if(!qFile.exists())
        {
          qDebug() << "nonexistent file " << qFile.fileName();
          return;
        }

        if(!qFile.open(QIODevice::ReadOnly))
        {
            qDebug() << "Can`t read data from " << qFile.fileName();
           return;
        }

        //QByteArray fileData = qFile.readAll();
        m_loaded_css[QString(url.c_str())] = qFile.readAll();
        QByteArray& fileData = m_loaded_css[QString(url.c_str())];

        if(!fileData.size())
        {
            qDebug() << "Empty data from " << qFile.fileName();
          return;
        }

        qFile.close();

        text = (const char*)&fileData.data()[0];

        qDebug() << "imported css" << url.c_str();
        //qDebug() << "imported css data" << fileData.data();

        // TODO: free resources?
}

void container_qt5::transform_text(litehtml::tstring& text, litehtml::text_transform tt)
{
  qDebug() << "transform_text";

// TODO: UTF8 https://github.com/pinaraf/litehtml-qt/blob/f3f4959f1d4a4884a0a18d87db7483e886cc3ee3/containers/cairo/cairo_container.cpp#L942

/*
 * The text-transform property in CSS controls text case and capitalization.
    lowercase makes all of the letters in the selected text lowercase.
    uppercase makes all of the letters in the selected text uppercase.
    capitalize capitalizes the first letter of each word in the selected text.
    none leaves the text's case and capitalization exactly as it was entered.
    inherit gives the text the case and capitalization of its parent.
 */

  std::string temp = text;

  // capitalizes the first letter of each word
  if (tt == litehtml::text_transform_capitalize) {
    // Convert lowercase letter to uppercase
    // see http://www.cplusplus.com/reference/cctype/toupper/
    temp[0] = toupper(temp[0]); // TODO: do to each word

  } else if (tt == litehtml::text_transform_uppercase) {
    // std::transform applies the given function to a range and stores the result in another range
    // see https://en.cppreference.com/w/cpp/algorithm/transform
    std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);

  } else if (tt == litehtml::text_transform_lowercase) {
    // std::transform applies the given function to a range and stores the result in another range
    // see https://en.cppreference.com/w/cpp/algorithm/transform
    std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
  }

  text = temp.c_str();
}

void container_qt5::set_cursor(const litehtml::tchar_t* cursor_)
{
    QString cursor(cursor_);
    /*if (cursor == "auto")
        setCursor(Qt::IBeamCursor);
    else if (cursor == "pointer")
        setCursor(Qt::PointingHandCursor);
    else
        qDebug() << __FUNCTION__ << cursor;*/
}

void container_qt5::on_anchor_click(const litehtml::tchar_t* url, const litehtml::element::ptr& el)
{
    qDebug() << __FUNCTION__ << url;
    QDesktopServices::openUrl(QUrl(url));
}

void container_qt5::link(const std::shared_ptr< litehtml::document >& doc, const litehtml::element::ptr& el)
{
    qDebug() << __FUNCTION__;
}

void container_qt5::set_base_url(const litehtml::tchar_t* base_url)
{
    qDebug() << __FUNCTION__;
}

void container_qt5::set_caption(const litehtml::tchar_t* caption)
{
    qDebug() << __FUNCTION__;
}

static void setPenForBorder(QPainter *painter, const litehtml::border &border)
{
    qDebug() << __FUNCTION__ ;
    /*QPen pen(painter->pen());
    pen.setWidth(border.width);
    pen.setColor(getColor(border.color));

    border_style_none,
    border_style_hidden,
    border_style_dotted,
    border_style_dashed,
    border_style_solid,
    border_style_double,
    border_style_groove,
    border_style_ridge,
    border_style_inset,
    border_style_outset

    switch (border.style) {
        case litehtml::border_style_none:
        case litehtml::border_style_hidden: pen.setStyle(Qt::NoPen); break;
        case litehtml::border_style_dotted: pen.setStyle(Qt::DotLine); break;
        case litehtml::border_style_dashed: pen.setStyle(Qt::DashLine); break;
        default: pen.setStyle(Qt::SolidLine); break;
    }
    painter->setPen(pen);*/
}

void container_qt5::draw_borders(litehtml::uint_ptr hdc, const litehtml::borders& borders, const litehtml::position& draw_pos, bool root)
{
    //qDebug() << __FUNCTION__ << " for root = " << root;
    /*QPainter *painter = (QPainter *) hdc;
    painter->save();
    QRect area = getRect(draw_pos);
    if (root) {
        painter->setPen(Qt::NoPen);
        painter->fillRect(area, Qt::white);
    } else {
        if (borders.top.style != litehtml::border_style_none) {
            setPenForBorder(painter, borders.top);
            painter->drawLine(area.topLeft(), area.topRight());
        }
        if (borders.bottom.style != litehtml::border_style_none) {
            setPenForBorder(painter, borders.bottom);
            painter->drawLine(area.bottomLeft(), area.bottomRight());
        }
        if (borders.left.style != litehtml::border_style_none) {
            setPenForBorder(painter, borders.left);
            painter->drawLine(area.topLeft(), area.bottomLeft());
        }
        if (borders.right.style != litehtml::border_style_none) {
            setPenForBorder(painter, borders.right);
            painter->drawLine(area.topRight(), area.bottomRight());
        }
    }
    painter->restore();*/

    ImGuiWindow* win = ImGui::GetCurrentWindow();
    //ImVec2 imgui_pos = { win->Pos.x + (float)draw_pos.x, win->Pos.y + (float)draw_pos.y };
    //win->DrawList->AddRect(imgui_pos, )

    /*auto drawBorder = [](const litehtml::border& border) {
    };*/

    int bdr_top		= 0;
    int bdr_bottom	= 0;
    int bdr_left	= 0;
    int bdr_right	= 0;

    if(borders.top.width != 0 && borders.top.style > litehtml::border_style_hidden)
    {
      bdr_top = (int) borders.top.width;
    }
    if(borders.bottom.width != 0 && borders.bottom.style > litehtml::border_style_hidden)
    {
      bdr_bottom = (int) borders.bottom.width;
    }
    if(borders.left.width != 0 && borders.left.style > litehtml::border_style_hidden)
    {
      bdr_left = (int) borders.left.width;
    }
    if(borders.right.width != 0 && borders.right.style > litehtml::border_style_hidden)
    {
      bdr_right = (int) borders.right.width;
    }

    if (bdr_bottom)
    {
      ImVec2 aFrom(win->Pos.x + draw_pos.left(), win->Pos.y + draw_pos.bottom());
      ImVec2 bTo(win->Pos.x + draw_pos.right(), win->Pos.y + draw_pos.bottom());
      ImColor color(borders.bottom.color.red, borders.bottom.color.green, borders.bottom.color.blue, borders.bottom.color.alpha);

      for (int x = 0; x < bdr_bottom; x++)
      {
        win->DrawList->AddLine(aFrom, bTo, color);
        ++aFrom.y;
        ++bTo.y;
      }
    }

    if (bdr_top)
    {
      ImVec2 aFrom(win->Pos.x + draw_pos.left(), win->Pos.y + draw_pos.top());
      ImVec2 bTo(win->Pos.x + draw_pos.right(), win->Pos.y + draw_pos.top());
      ImColor color(borders.top.color.red, borders.top.color.green, borders.top.color.blue, borders.top.color.alpha);

      for (int x = 0; x < bdr_top; x++)
      {
        win->DrawList->AddLine(aFrom, bTo, color);
        ++aFrom.y;
        ++bTo.y;
      }
    }

    if (bdr_right)
    {
      ImVec2 aFrom(win->Pos.x + draw_pos.right(), win->Pos.y + draw_pos.top());
      ImVec2 bTo(win->Pos.x + draw_pos.right(), win->Pos.y + draw_pos.bottom());
      ImColor color(borders.right.color.red, borders.right.color.green, borders.right.color.blue, borders.right.color.alpha);

      for (int x = 0; x < bdr_right; x++)
      {
        win->DrawList->AddLine(aFrom, bTo, color);
        --aFrom.x;
        --bTo.x;
      }
    }

    if (bdr_left)
    {
      ImVec2 aFrom(win->Pos.x + draw_pos.left(), win->Pos.y + draw_pos.top());
      ImVec2 bTo(win->Pos.x + draw_pos.left(), win->Pos.y + draw_pos.bottom());
      ImColor color(borders.left.color.red, borders.left.color.green, borders.left.color.blue, borders.left.color.alpha);

      for (int x = 0; x < bdr_left; x++)
      {
        win->DrawList->AddLine(aFrom, bTo, color);
        ++aFrom.x;
        ++bTo.x;
      }
    }
}

void container_qt5::draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint& bg)
{
    //qDebug() << "draw_background" << __FUNCTION__ << bg.image.c_str();
    // draw_background draw_background https://images2017.cnblogs.com/blog/847289/201712/847289-20171207174342691-530707282.png

    ImGuiWindow* win = ImGui::GetCurrentWindow();

    // clip_box. Defines the position of the clipping box. See the background-clip CSS property.
    ImVec2 clip_a(win->Pos.x + bg.clip_box.left(), win->Pos.y + bg.clip_box.top());
    ImVec2 clip_b(win->Pos.x + bg.clip_box.right(), win->Pos.y + bg.clip_box.bottom());

    // The image contains the background image URL. URL can be relative.
    // Use the baseurl member to find the base URL for image.
    if (bg.image.empty())
    {
      // This member defines the background-color CSS property.
      ImColor color(bg.color.red, bg.color.green, bg.color.blue, bg.color.alpha);
      win->DrawList->AddRectFilled(clip_a, clip_b, color);
      return;
    }


    // Defines the position of the origin box. See the background-origin CSS property.
    // The background-origin property specifies the origin position (the background positioning area) of a background image.
    // bg.origin_box
    // TODO https://github.com/PingmanTools/LiteHtmlSharp/blob/3f4db0ff0ab4b5cd7f5e10aa1b6ed94f2eee0bcb/LiteHtmlLib/src/DocContainer.cpp#L67


    /*
      This is the background-attachment CSS property. Can be one of the following values:

      background_attachment_scroll - CSS scroll
      background_attachment_fixed - - CSS fixed
    */
    if (bg.attachment == litehtml::background_attachment::background_attachment_fixed)
    {
      // TODO
      return;
    }

    // TODO: https://github.com/nem0/lumixengine_html/blob/e2da43e704ad0ad474c8ecafc16fcae4a51e8aff/src/editor/plugins.cpp#L162
    //Crc32 crc32;
    //auto iter = m_images.find(crc32.calculateFromData(bg.image.c_str()));
    auto iter = m_images.find(bg.image.c_str());
    if (iter == m_images.end()) {
      qDebug() << "iter == m_images.end()" << __FUNCTION__;
      // drw placeholder
      ImColor dummyColor(100, 100, 100, 100);
      win->DrawList->AddRectFilled(clip_a, clip_b, dummyColor);
      return;
    }

    auto img = iter.value();

    /*
     * This the background-repeat CSS property. Can be one of the following values:

        background_repeat_repeat - CSS repeat
        background_repeat_repeat_x - CSS repeat-x
        background_repeat_repeat_y - CSS repeat-y
        background_repeat_no_repeat - CSS no-repeat
     */
    switch (bg.repeat)
    {
      case litehtml::background_repeat_no_repeat:
      {
        win->DrawList->AddImage(img.textureId, clip_a, clip_b);
        break;
      }
      case litehtml::background_repeat_repeat_x:
      {
        ImVec2 uv((clip_b.x - clip_a.x) / img.w, 0);
        //glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
        //ImGui::GetWindowDrawList()->PushTextureID(img.textureId);
        win->DrawList->AddImage(img.textureId, clip_a, clip_b, ImVec2(0, 0), uv);
        //ImGui::GetWindowDrawList()->PopTextureID();
        break;
      }
      break;
      case litehtml::background_repeat_repeat_y:
      {
        ImVec2 uv(0, (clip_b.y - clip_a.y) / img.h);
        //glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
        //ImGui::GetWindowDrawList()->PushTextureID(img.textureId);
        win->DrawList->AddImage(img.textureId, clip_a, clip_b, ImVec2(0, 0), uv);
        //ImGui::GetWindowDrawList()->PopTextureID();
        break;
      }
      case litehtml::background_repeat_repeat:
      {
        ImVec2 uv((clip_b.x - clip_a.x) / img.w, (clip_b.y - clip_a.y) / img.h);
        //glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
        //ImGui::GetWindowDrawList()->PushTextureID(img.textureId);
        win->DrawList->AddImage(img.textureId, clip_a, clip_b, ImVec2(0, 0), uv);
        //ImGui::GetWindowDrawList()->PopTextureID();
        break;
      }
    }
}

static uintptr_t CreateFontAtlas(int width, int height, uint8_t * data)
{
  GLuint handle = 0;
  glGenTextures(1, &handle);
  glBindTexture(GL_TEXTURE_2D, handle);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_R8,width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  return uintptr_t(handle);
}

// TODO: DeleteTexture? glDeleteTextures(1, reinterpret_cast<GLuint*>(&handle));
// https://github.com/feliwir/webgui/blob/18b92372bb29933a5d9500e42aebf8bf1db5a675/sample/renderer.cpp#L38

static uintptr_t CreateTexture(int width, int height, uint8_t * pixels)
{
  GLuint my_opengl_texture = 0;
  glGenTextures(1, &my_opengl_texture);
  glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  //glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
  return uintptr_t(my_opengl_texture);
}

void container_qt5::get_image_size(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, litehtml::size& sz)
{
    // qDebug() << __FUNCTION__ << src;
    // https://images2017.cnblogs.com/blog/847289/201712/847289-20171207174342691-530707282.png

    //Crc32 crc32;

    //auto iter = m_images.find(crc32.calculateFromData(src));
    auto iter = m_images.find(src);
    if (iter != m_images.end())
    {
      sz.width = iter.value().w;
      sz.height = iter.value().h;
      //qDebug() << "sz.width" << sz.width;
      //qDebug() << "sz.height" << sz.height;
    }
    else
    {
      sz.width = sz.height = 100;
    }
}

void container_qt5::load_image(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, bool redraw_on_ready)
{
    //qDebug() << __FUNCTION__ << src;
    // load_image https://images2017.cnblogs.com/blog/847289/201712/847289-20171207174342691-530707282.png

    QFile qFile(src);

        if(!qFile.exists())
        {
          qDebug() << "nonexistent file " << qFile.fileName();
          return;
        }

        if(!qFile.open(QIODevice::ReadOnly))
        {
            qDebug() << "Can`t read data from " << qFile.fileName();
           return;
        }

        QByteArray fileData = qFile.readAll();

        if(!fileData.size())
        {
            qDebug() << "Empty data from " << qFile.fileName();
          return;
        }

        qFile.close();

    unsigned int bufSize = fileData.size();
    //unsigned char* data = new unsigned char[bufSize];
    unsigned char* data = (unsigned char*)fileData.data();
    //download(m_host, src, &data);
    int channels;
    Image img;
    stbi_uc* pixels = stbi_load_from_memory(&data[0], bufSize, &img.w, &img.h, &channels, 4);
    if (!pixels) {
    qDebug() << "Empty pixels for " << qFile.fileName();
      return;
    }

    // https://github.com/nem0/LumixEngine/blob/f77a0b6a899be4736f0ce26133bbe8061a3828f1/src/renderer/editor/plugins.cpp#L2202
    //img.textureId = ri->createTexture(src, pixels, img.w, img.h);
        // Turn the RGBA pixel data into an OpenGL texture:

        /*glGenTextures(1, &my_opengl_texture);
        glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.w, img.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
*/

    //glGetIntegerv(GL_TEXTURE_BINDING_2D, &my_opengl_texture);

    /*glGenTextures(1, &my_opengl_texture);
    img.textureId = (ImTextureID)my_opengl_texture;
    glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.w, img.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);*/

    auto texId = CreateTexture(img.w, img.h, pixels);
    img.textureId = (ImTextureID)texId;

        // Now that we have an OpenGL texture, assuming our imgui rendering function (imgui_impl_xxx.cpp file) takes GLuint as ImTextureID, we can display it:
        //ImGui::Image((void*)(intptr_t)my_opengl_texture, ImVec2(img.w, img.h));
// <<<<

    //Crc32 crc32;
    //m_images.insert(crc32.calculateFromData(src), img);
    m_images.insert(src, img);
}

void container_qt5::draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker)
{
    ImGuiWindow* win = ImGui::GetCurrentWindow();

    int top_margin = marker.pos.height / 3;

    //qDebug() << "marker.baseurl" << marker.pos.right();

    int draw_x		= win->Pos.x + marker.pos.x;// + abs(marker.pos.right());
    int draw_y		= win->Pos.y + marker.pos.y + top_margin;
    int draw_width	= marker.pos.height - top_margin * 2;
    int draw_height = marker.pos.height - top_margin * 2;

    /*qDebug() << marker.marker_type << marker.pos.x << "x" << marker.pos.y << marker.pos.left() << marker.pos.right();
    qDebug() << marker.baseurl << QString::fromStdString(marker.image);
    QPainter *painter = (QPainter *) hdc;
    QRect position = getRect(marker.pos);
    QColor color = getColor(marker.color);
    painter->save();
    painter->setPen(color);
    switch (marker.marker_type) {
        case litehtml::list_style_type_none: break;
        case litehtml::list_style_type_circle: painter->drawEllipse(position); break;
        case litehtml::list_style_type_disc: painter->setBrush(color); painter->drawEllipse(position); break;
        case litehtml::list_style_type_square: painter->fillRect(position, getColor(marker.color)); break;
        // How to implement numeral markers ??
        default: break;
    }
    painter->restore();*/

/*
    list_style_type_none,
    list_style_type_circle,
    list_style_type_disc,
    list_style_type_square,
    list_style_type_armenian,
    list_style_type_cjk_ideographic,
    list_style_type_decimal,
    list_style_type_decimal_leading_zero,
    list_style_type_georgian,
    list_style_type_hebrew,
    list_style_type_hiragana,
    list_style_type_hiragana_iroha,
    list_style_type_katakana,
    list_style_type_katakana_iroha,
    list_style_type_lower_alpha,
    list_style_type_lower_greek,
    list_style_type_lower_latin,
    list_style_type_lower_roman,
    list_style_type_upper_alpha,
    list_style_type_upper_latin,
    list_style_type_upper_roman,
*/

    // clip_box. Defines the position of the clipping box. See the background-clip CSS property.
    ImVec2 clip_a(draw_x, draw_y);
    ImVec2 clip_b(draw_x + draw_width, draw_y + draw_height);

    switch(marker.marker_type)
      {
            case litehtml::list_style_type_circle:
            case litehtml::list_style_type_disc:
            case litehtml::list_style_type_square:
            default:
        {
          // fill_rect(hdc, litehtml::position(draw_x, draw_y, draw_width, draw_height), color, litehtml::css_border_radius());
          ImColor color(marker.color.red, marker.color.green, marker.color.blue, marker.color.alpha);
          win->DrawList->AddRectFilled(clip_a, clip_b, color);

          // TODO: marker.image

          // TODO: depends on font size. fix fonts, add different sizes!

          //win->DrawList->AddRectFilled(ImVec2(draw_x,draw_y), ImVec2(draw_x+draw_width+15,draw_y+draw_height), color);
          //qDebug() << __FUNCTION__ << draw_x+draw_width;
        }
        break;
    }
}

const litehtml::tchar_t* container_qt5::get_default_font_name() const
{
    qDebug() << __FUNCTION__;
    return _t("\"Droid Sans\""); //Times New Roman"; //"Noto Sans";
}

int container_qt5::get_default_font_size() const
{
    //qDebug() << __FUNCTION__;
    return 12;
}

// https://github.com/Nanquitas/3DS_eBook_Reader/blob/51f1fedc2565de36253104a01f4689db00c35991/source/Litehtml3DSContainer.cpp#L18
#define PPI 132.1

int container_qt5::pt_to_px(int pt)
{
    qDebug() << __FUNCTION__;

    /*
  int ret = pt;
  #if _WIN32
  HDC dc = GetDC(NULL);
  ret = MulDiv(pt, GetDeviceCaps(dc, LOGPIXELSY), 72);
  ReleaseDC(NULL, dc);
  #endif
  return ret;
     */

    return pt / 72 * PPI;
}

void container_qt5::draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos)
{
// TODO: try cairo_font https://github.com/prepare/other_bsd_html_projects/blob/543f9b5aae9a474c07173b1c33b1fc48bb84916a/litehtml-read-only/containers/cairo/cairo_container.cpp
// TODO: try QFont https://github.com/eco747/foton/blob/2f9b68ca0ccc2f087f769e52f8caa30806c9484c/qhtmlrenderer.cpp#L80
// https://github.com/pinaraf/litehtml-qt/blob/a39ddeca173e88cf2572f6b8fdc31f0bfd27c0d3/containers/qt5/container_qt5.cpp#L311


    //qDebug() << __FUNCTION__;
    /*QPainter *painter = (QPainter *) hdc;
    QFont *font = (QFont *) hFont;
    painter->setFont(*font);
    painter->setPen(getColor(color));
    //painter->setBrush(QColor(color.red, color.green, color.blue, color.alpha));
    QFontMetrics metrics(*font);

    //qDebug() << "Paint " << text << " at " << pos.x << "x" << pos.y;
    painter->drawText(pos.x, pos.bottom() - metrics.descent(), text);*/


    //ImGui::PushFont((ImFont*)imFont_);
    //ImVec2 size = ImGui::CalcTextSize(text);

    ImFont* font = (ImFont*)hFont;//imFont_;//
    //ImFont* font = QtImGui::ImGuiRenderer::getFont(QString("\"Cousine Regular\""));
    //ImFont* font = QtImGui::ImGuiRenderer::getFont(QString("\"Font Awesome\""));
    //ImGui::PushFont(font);

    //qDebug() << "font->GetDebugName " << font->GetDebugName();
    //qDebug() << "font->FontSize " << font->FontSize;
    ImGuiWindow* win = ImGui::GetCurrentWindow();
    ImVec2 imgui_pos = {win->Pos.x + (float)pos.x, win->Pos.y + pos.y};
    ImColor col(color.red, color.green, color.blue, color.alpha);
    win->DrawList->AddText(font, font->FontSize, imgui_pos, col, text);
    //ImGui::PopFont();

    //ImGui::PopFont();
}

int container_qt5::text_width(const litehtml::tchar_t* text, litehtml::uint_ptr hFont)
{
    //qDebug() << __FUNCTION__;
    /*QFont *font = (QFont *) hFont;
    QFontMetrics metrics(*font);
    QString txt(text);
    qDebug() << "For" << txt << metrics.boundingRect(txt);
    if (txt == " ") {
        return metrics.boundingRect("x").width();
    }
    return metrics.boundingRect(txt).width();*/

    /*if (!hFont) return 50;

    ImGui::PushFont((ImFont*)hFont);
    ImVec2 size = ImGui::CalcTextSize(text);
    ImGui::PopFont();

    return size.x;*/

    if (!hFont) {
      qDebug() << __FUNCTION__ << " can`t get text width for empty font";
      return 50;
    }

    ImGui::PushFont((ImFont*)hFont);
    ImVec2 size = ImGui::CalcTextSize(text);
    ImGui::PopFont();

    return size.x;

    //return 50;
}

void container_qt5::delete_font(litehtml::uint_ptr hFont)
{
    qDebug() << "delete_font";

    // TODO

    /*QFont *font = (QFont *) hFont;
    delete(font);*/
}


// TODO: utf8 && dynamic font load && dynamic font size
litehtml::uint_ptr container_qt5::create_font(const litehtml::tchar_t* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm)
{
    //QString faceName(faceName_);

    //TODO: decoration
    qDebug() << __FUNCTION__ << " for " << faceName << size << weight;
    /*QFont *font = new QFont(faceName, size, weight, italic == litehtml::fontStyleItalic);
    font->setUnderline(decoration & litehtml::font_decoration_underline);
    font->setOverline(decoration & litehtml::font_decoration_overline);
    font->setStrikeOut(decoration & litehtml::font_decoration_linethrough);
    QFontMetrics metrics(*font);
    fm->height = metrics.ascent() + metrics.descent() + 2;
    fm->ascent = metrics.ascent();
    fm->descent = metrics.descent();
    fm->x_height = metrics.boundingRect("x").height();
    return font;*/

    /*RenderInterface* ri = m_app.getWorldEditor()->getRenderInterface();
    ImFont* font = ri->addFont("bin/veramono.ttf", size);*/

    ImGuiIO& io = ImGui::GetIO();
    ImFont* font = QtImGui::ImGuiRenderer::getFont(faceName);//QtImGui::ImGuiRenderer::customFont;//io.Fonts->AddFontFromFileTTF("://DroidSans.ttf", 16.0f);
    if (!font) {
      qDebug() << "unsupported font " << faceName;
      font = QtImGui::ImGuiRenderer::getFont("\"Droid Sans\"");
    }

    fm->height = font->Ascent - font->Descent;
    fm->ascent = font->Ascent;
    fm->descent = -font->Descent;
    fm->x_height = font->FontSize;
    //bool underline = (decoration & litehtml::font_decoration_underline) != 0;

    return (litehtml::uint_ptr)font;
}

litehtml::tstring container_qt5::resolve_color(const litehtml::tstring& color) const
{
  struct custom_color
  {
    litehtml::tchar_t*	name;
    int					color_index;
  };
/*
  static custom_color colors[] = {
    { _t("ActiveBorder"),          COLOR_ACTIVEBORDER},
    { _t("ActiveCaption"),         COLOR_ACTIVECAPTION},
    { _t("AppWorkspace"),          COLOR_APPWORKSPACE },
    { _t("Background"),            COLOR_BACKGROUND },
    { _t("ButtonFace"),            COLOR_BTNFACE },
    { _t("ButtonHighlight"),       COLOR_BTNHIGHLIGHT },
    { _t("ButtonShadow"),          COLOR_BTNSHADOW },
    { _t("ButtonText"),            COLOR_BTNTEXT },
    { _t("CaptionText"),           COLOR_CAPTIONTEXT },
        { _t("GrayText"),              COLOR_GRAYTEXT },
    { _t("Highlight"),             COLOR_HIGHLIGHT },
    { _t("HighlightText"),         COLOR_HIGHLIGHTTEXT },
    { _t("InactiveBorder"),        COLOR_INACTIVEBORDER },
    { _t("InactiveCaption"),       COLOR_INACTIVECAPTION },
    { _t("InactiveCaptionText"),   COLOR_INACTIVECAPTIONTEXT },
    { _t("InfoBackground"),        COLOR_INFOBK },
    { _t("InfoText"),              COLOR_INFOTEXT },
    { _t("Menu"),                  COLOR_MENU },
    { _t("MenuText"),              COLOR_MENUTEXT },
    { _t("Scrollbar"),             COLOR_SCROLLBAR },
    { _t("ThreeDDarkShadow"),      COLOR_3DDKSHADOW },
    { _t("ThreeDFace"),            COLOR_3DFACE },
    { _t("ThreeDHighlight"),       COLOR_3DHILIGHT },
    { _t("ThreeDLightShadow"),     COLOR_3DLIGHT },
    { _t("ThreeDShadow"),          COLOR_3DSHADOW },
    { _t("Window"),                COLOR_WINDOW },
    { _t("WindowFrame"),           COLOR_WINDOWFRAME },
    { _t("WindowText"),            COLOR_WINDOWTEXT }
  };

    if (color == _t("Highlight"))
    {
        int iii = 0;
        iii++;
    }

    for (auto& clr : colors)
    {
        if (!t_strcasecmp(clr.name, color.c_str()))
        {
            litehtml::tchar_t  str_clr[20];
            DWORD rgb_color =  GetSysColor(clr.color_index);
#ifdef LITEHTML_UTF8
            StringCchPrintfA(str_clr, 20, "#%02X%02X%02X", GetRValue(rgb_color), GetGValue(rgb_color), GetBValue(rgb_color));
#else
            StringCchPrintf(str_clr, 20, L"#%02X%02X%02X", GetRValue(rgb_color), GetGValue(rgb_color), GetBValue(rgb_color));
#endif // LITEHTML_UTF8
            return std::move(litehtml::tstring(str_clr));
        }
    }*/
    return std::move(litehtml::tstring());
}
