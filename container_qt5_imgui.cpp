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


ImGuiIO& io = ImGui::GetIO();
 ImFont* font = io.Fonts->AddFontDefault();

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

void container_qt5::mouseMoveEvent(QMouseEvent *event)
{
    litehtml::position::vector vec;
    if (_doc->on_mouse_over(event->x(), event->y(), event->x(), event->y(), vec))
        render();
}

void container_qt5::mousePressEvent(QMouseEvent *event)
{
    litehtml::position::vector vec;
    if (_doc->on_lbutton_down(event->x(), event->y(), event->x(), event->y(), vec))
        render();
}

void container_qt5::mouseReleaseEvent(QMouseEvent *event)
{
    litehtml::position::vector vec;
    if (_doc->on_lbutton_up(event->x(), event->y(), event->x(), event->y(), vec))
        render();
}

void container_qt5::get_language(litehtml::tstring& language, litehtml::tstring& culture) const
{
    qDebug() << "get_language";
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

    media.type = litehtml::media_type_screen;
    media.width = client.width;
    media.height = client.height;
    media.color = 8;
    media.monochrome = 0;
    media.color_index = 256;
    media.resolution = 96;
    media.device_width = 1024;
    media.device_height = 1024;

    qDebug() << "=> " << media.width << "x" << media.height;
}

std::shared_ptr< litehtml::element > container_qt5::create_element(const litehtml::tchar_t* tag_name, const litehtml::string_map& attributes, const std::shared_ptr< litehtml::document >& doc)
{
    qDebug() << __FUNCTION__ << " this one can be 0";
    return 0;
}

void container_qt5::get_client_rect(litehtml::position& client) const
{
    //qDebug() << "get_client_rect";
    // No scroll yet
    //client.move_to(0, 0);
    /*client.width = width();
    client.height = height();*/
    //qDebug() << "==> " << client.width << "x" << client.height;

    client.height = 1024;
    client.width = 1024;
    ImGuiWindow* win = ImGui::GetCurrentWindow();
    client.x = win->Pos.x;
    client.y = win->Pos.y;

    /*qDebug() << "get_client_rect xy" << client.x << " " << client.y;
    qDebug() << "get_client_rect wh" << client.width << " " << client.height;*/
}

void container_qt5::del_clip()
{
    qDebug() << "del_clip";
}

void container_qt5::set_clip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius, bool valid_x, bool valid_y)
{
    qDebug() << "set_clip";
}

void container_qt5::import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl)
{
    qDebug() << "import_css";
    /*download(m_host, url.c_str(), &data);
    text = (const char*)&data[0];*/
}

void container_qt5::transform_text(litehtml::tstring& text, litehtml::text_transform tt)
{
    qDebug() << "transform_text";
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

    auto drawBorder = [](const litehtml::border& border) {
    };

    if (borders.bottom.width != 0 && borders.bottom.style > litehtml::border_style_hidden)
    {
      ImVec2 a(win->Pos.x + draw_pos.left(), win->Pos.y + draw_pos.bottom());
      ImVec2 b(win->Pos.x + draw_pos.right(), win->Pos.y + draw_pos.bottom());
      ImColor col(borders.bottom.color.red, borders.bottom.color.green, borders.bottom.color.blue, borders.bottom.color.alpha);

      for (int x = 0; x < borders.bottom.width; x++)
      {
        win->DrawList->AddLine(a, b, col);
        ++a.y;
        ++b.y;
      }
    }

    if (borders.top.width != 0 && borders.top.style > litehtml::border_style_hidden)
    {
      ImVec2 a(win->Pos.x + draw_pos.left(), win->Pos.y + draw_pos.top());
      ImVec2 b(win->Pos.x + draw_pos.right(), win->Pos.y + draw_pos.top());
      ImColor col(borders.top.color.red, borders.top.color.green, borders.top.color.blue, borders.top.color.alpha);

      for (int x = 0; x < borders.top.width; x++)
      {
        win->DrawList->AddLine(a, b, col);
        ++a.y;
        ++b.y;
      }
    }

    if (borders.right.width != 0 && borders.right.style > litehtml::border_style_hidden)
    {
      ImVec2 a(win->Pos.x + draw_pos.right(), win->Pos.y + draw_pos.top());
      ImVec2 b(win->Pos.x + draw_pos.right(), win->Pos.y + draw_pos.bottom());
      ImColor col(borders.right.color.red, borders.right.color.green, borders.right.color.blue, borders.right.color.alpha);

      for (int x = 0; x < borders.right.width; x++)
      {
        win->DrawList->AddLine(a, b, col);
        --a.x;
        --b.x;
      }
    }

    if (borders.left.width != 0 && borders.left.style > litehtml::border_style_hidden)
    {
      ImVec2 a(win->Pos.x + draw_pos.left(), win->Pos.y + draw_pos.top());
      ImVec2 b(win->Pos.x + draw_pos.left(), win->Pos.y + draw_pos.bottom());
      ImColor col(borders.left.color.red, borders.left.color.green, borders.left.color.blue, borders.left.color.alpha);

      for (int x = 0; x < borders.left.width; x++)
      {
        win->DrawList->AddLine(a, b, col);
        ++a.x;
        ++b.x;
      }
    }
}

void container_qt5::draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint& bg)
{
    //qDebug() << "draw_background" << __FUNCTION__ << bg.image.c_str();
    // draw_background draw_background https://images2017.cnblogs.com/blog/847289/201712/847289-20171207174342691-530707282.png

    ImGuiWindow* win = ImGui::GetCurrentWindow();
    ImVec2 a(win->Pos.x + bg.clip_box.left(), win->Pos.y + bg.clip_box.top());
    ImVec2 b(win->Pos.x + bg.clip_box.right(), win->Pos.y + bg.clip_box.bottom());
    if (bg.image.empty())
    {
      ImColor col(bg.color.red, bg.color.green, bg.color.blue, bg.color.alpha);
      win->DrawList->AddRectFilled(a, b, col);
      return;
    }

    // TODO: https://github.com/nem0/lumixengine_html/blob/e2da43e704ad0ad474c8ecafc16fcae4a51e8aff/src/editor/plugins.cpp#L162
    //Crc32 crc32;
    //auto iter = m_images.find(crc32.calculateFromData(bg.image.c_str()));
    auto iter = m_images.find(bg.image.c_str());
    if (iter == m_images.end()) {
      qDebug() << "iter == m_images.end()" << __FUNCTION__;
      return;
    }

    auto img = iter.value();

    switch (bg.repeat)
    {
      case litehtml::background_repeat_no_repeat: win->DrawList->AddImage(img.textureId, a, b); break;
      case litehtml::background_repeat_repeat_x:
      {
        ImVec2 uv((b.x - a.x) / img.w, 0);
        //glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
        //ImGui::GetWindowDrawList()->PushTextureID(img.textureId);
        win->DrawList->AddImage(img.textureId, a, b, ImVec2(0, 0), uv);
        //ImGui::GetWindowDrawList()->PopTextureID();
        break;
      }
      break;
      case litehtml::background_repeat_repeat_y:
      {
        ImVec2 uv(0, (b.y - a.y) / img.h);
        //glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
        //ImGui::GetWindowDrawList()->PushTextureID(img.textureId);
        win->DrawList->AddImage(img.textureId, a, b, ImVec2(0, 0), uv);
        //ImGui::GetWindowDrawList()->PopTextureID();
        break;
      }
      case litehtml::background_repeat_repeat:
      {
        ImVec2 uv((b.x - a.x) / img.w, (b.y - a.y) / img.h);
        //glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
        //ImGui::GetWindowDrawList()->PushTextureID(img.textureId);
        win->DrawList->AddImage(img.textureId, a, b, ImVec2(0, 0), uv);
        //ImGui::GetWindowDrawList()->PopTextureID();
        break;
      }
    }
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

    glGenTextures(1, &my_opengl_texture);
    img.textureId = (ImTextureID)my_opengl_texture;
    glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.w, img.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        // Now that we have an OpenGL texture, assuming our imgui rendering function (imgui_impl_xxx.cpp file) takes GLuint as ImTextureID, we can display it:
        //ImGui::Image((void*)(intptr_t)my_opengl_texture, ImVec2(img.w, img.h));
// <<<<

    //Crc32 crc32;
    //m_images.insert(crc32.calculateFromData(src), img);
    m_images.insert(src, img);
}

void container_qt5::draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker)
{
    qDebug() << __FUNCTION__;
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
}
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

const litehtml::tchar_t* container_qt5::get_default_font_name() const
{
    qDebug() << __FUNCTION__;
    return "\"Droid Sans\"";//Times New Roman"; //"Noto Sans";
}

int container_qt5::get_default_font_size() const
{
    qDebug() << __FUNCTION__;
    return 16;
}

int container_qt5::pt_to_px(int pt)
{
    qDebug() << __FUNCTION__;
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
    ImGui::PushFont(font);

    //qDebug() << "font->GetDebugName " << font->GetDebugName();
    //qDebug() << "font->FontSize " << font->FontSize;
    ImGuiWindow* win = ImGui::GetCurrentWindow();
    ImVec2 imgui_pos = {win->Pos.x + (float)pos.x, win->Pos.y + pos.y};
    ImColor col(color.red, color.green, color.blue, color.alpha);
    win->DrawList->AddText(font, font->FontSize, imgui_pos, col, text);
ImGui::PopFont();
    //ImGui::PopFont();
}

int container_qt5::text_width(const litehtml::tchar_t* text, litehtml::uint_ptr hFont)
{
    qDebug() << __FUNCTION__;
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

    if (!hFont) return 50;

    ImGui::PushFont((ImFont*)hFont);
    ImVec2 size = ImGui::CalcTextSize(text);
    ImGui::PopFont();

    return size.x;

    //return 50;
}

void container_qt5::delete_font(litehtml::uint_ptr hFont)
{
    qDebug() << "delete_font";
    /*QFont *font = (QFont *) hFont;
    delete(font);*/
}

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
