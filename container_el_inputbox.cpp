#include "container_el_inputbox.h"

#include <QtImGui.h>
#include <imgui.h>
#include <imgui_internal.h>
#include "litehtml.h"
//#include "crc32.h"

#include <QGuiApplication>
#include <QTimer>
#include <QSurfaceFormat>
#include <QOpenGLWindow>
#include <QOpenGLExtraFunctions>
#include <QFile>
#include <QDebug>
#include <QMap>

container_el_inputbox::container_el_inputbox(const std::shared_ptr<litehtml::document>& doc, const litehtml::string_map& attributes) : html_tag(doc)
{
  //m_display = display_inline_block;
}

container_el_inputbox::~container_el_inputbox( void )
{

}

void container_el_inputbox::get_content_size( litehtml::size& sz, int max_width )
{
  html_tag::get_content_size( sz, max_width);

  //get_document()->container()->get_image_size(m_src.c_str(), 0, sz);
  //sz = m_size;
  if(m_display == litehtml::display_block)
  {
    sz.width	= max_width;
  } else
  {
    sz.width	= 0;
  }
}

int container_el_inputbox::line_height() const
{
  return height();
}

bool container_el_inputbox::is_replaced() const
{
  return true;
}

int container_el_inputbox::render( int x, int y, int max_width, bool second_pass )
{
  html_tag::render(x,y,max_width,second_pass);

  //qDebug() << "container_el_inputbox::render";
  //ImGui::PushID()
  {
    /*bool show_test_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImColor(114, 144, 154);
    static float f = 0.0f;
    ImGui::Text("Hello, world!");
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::ColorEdit3("clear color", (float*)&clear_color);
    if (ImGui::Button("Test Window")) show_test_window ^= 1;
    if (ImGui::Button("Another Window")) show_another_window ^= 1;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  */}

//ImGui::Text("Hello1");

  /*
            ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Another Window");
            ImGui::Text("Hello1");
            ImGui::End();

    ImGuiWindow* win = ImGui::GetCurrentWindow();

    // clip_box. Defines the position of the clipping box. See the background-clip CSS property.
    ImVec2 clip_a(-1500,-1500);
    ImVec2 clip_b(1500,1500);

    // The image contains the background image URL. URL can be relative.
    // Use the baseurl member to find the base URL for image.

      // This member defines the background-color CSS property.
      ImColor color(155, 55, 155, 255);
      win->DrawList->AddRectFilled(clip_a, clip_b, color);*/


  /*int parent_width = max_width;

  calc_outlines(parent_width);

  m_pos.move_to(x, y);

  document::ptr doc = get_document();

  litehtml::size sz;
  doc->container()->get_image_size(m_src.c_str(), 0, sz);

  m_pos.width		= sz.width;
  m_pos.height	= sz.height;

  if(m_css_height.is_predefined() && m_css_width.is_predefined())
  {
    m_pos.height	= sz.height;
    m_pos.width		= sz.width;

    // check for max-height
    if(!m_css_max_width.is_predefined())
    {
      int max_width = doc->cvt_units(m_css_max_width, m_font_size, parent_width);
      if(m_pos.width > max_width)
      {
        m_pos.width = max_width;
      }
      if(sz.width)
      {
        m_pos.height = (int) ((float) m_pos.width * (float) sz.height / (float)sz.width);
      } else
      {
        m_pos.height = sz.height;
      }
    }

    // check for max-height
    if(!m_css_max_height.is_predefined())
    {
      int max_height = doc->cvt_units(m_css_max_height, m_font_size);
      if(m_pos.height > max_height)
      {
        m_pos.height = max_height;
      }
      if(sz.height)
      {
        m_pos.width = (int) (m_pos.height * (float)sz.width / (float)sz.height);
      } else
      {
        m_pos.width = sz.width;
      }
    }
  } else if(!m_css_height.is_predefined() && m_css_width.is_predefined())
  {
    if (!get_predefined_height(m_pos.height))
    {
      m_pos.height = (int)m_css_height.val();
    }

    // check for max-height
    if(!m_css_max_height.is_predefined())
    {
      int max_height = doc->cvt_units(m_css_max_height, m_font_size);
      if(m_pos.height > max_height)
      {
        m_pos.height = max_height;
      }
    }

    if(sz.height)
    {
      m_pos.width = (int) (m_pos.height * (float)sz.width / (float)sz.height);
    } else
    {
      m_pos.width = sz.width;
    }
  } else if(m_css_height.is_predefined() && !m_css_width.is_predefined())
  {
    m_pos.width = (int) m_css_width.calc_percent(parent_width);

    // check for max-width
    if(!m_css_max_width.is_predefined())
    {
      int max_width = doc->cvt_units(m_css_max_width, m_font_size, parent_width);
      if(m_pos.width > max_width)
      {
        m_pos.width = max_width;
      }
    }

    if(sz.width)
    {
      m_pos.height = (int) ((float) m_pos.width * (float) sz.height / (float)sz.width);
    } else
    {
      m_pos.height = sz.height;
    }
  } else
  {
    m_pos.width		= (int) m_css_width.calc_percent(parent_width);
    m_pos.height	= 0;
    if (!get_predefined_height(m_pos.height))
    {
      m_pos.height = (int)m_css_height.val();
    }

    // check for max-height
    if(!m_css_max_height.is_predefined())
    {
      int max_height = doc->cvt_units(m_css_max_height, m_font_size);
      if(m_pos.height > max_height)
      {
        m_pos.height = max_height;
      }
    }

    // check for max-height
    if(!m_css_max_width.is_predefined())
    {
      int max_width = doc->cvt_units(m_css_max_width, m_font_size, parent_width);
      if(m_pos.width > max_width)
      {
        m_pos.width = max_width;
      }
    }
  }

  calc_auto_margins(parent_width);

  m_pos.x	+= content_margins_left();
  m_pos.y += content_margins_top();

  return m_pos.width + content_margins_left() + content_margins_right();*/

  return m_pos.width + content_margins_left() + content_margins_right();
}

void container_el_inputbox::parse_attributes()
{
  html_tag::parse_attributes();

  m_src = get_attr(_t("src"), _t(""));

  for(auto it = m_attrs.begin(); it != m_attrs.end(); it++)
  {
    //qDebug() << it->first.c_str() << "" << it->second.c_str();
  }

  const litehtml::tchar_t* attr_height = get_attr(_t("height"));
  if(attr_height)
  {
    m_style.add_property(_t("height"), attr_height, 0, false);
  }
  const litehtml::tchar_t* attr_width = get_attr(_t("width"));
  if(attr_width)
  {
    qDebug() << "attr_width" << attr_width;
    m_style.add_property(_t("width"), attr_width, 0, false);
  }
  html_tag::parse_attributes();
}

  static char str0[128] = "11Hello, world!";

void container_el_inputbox::draw( litehtml::uint_ptr hdc, int x, int y, const litehtml::position* clip )
{
  //html_tag::draw( hdc, x, y, clip);

  litehtml::position pos = m_pos;
  pos.x += x;
  pos.y += y;

  litehtml::position el_pos = pos;
  el_pos += m_padding;
  el_pos += m_borders;

    ImGuiWindow* win = ImGui::GetCurrentWindow();

  // clip_box. Defines the position of the clipping box. See the background-clip CSS property.
  ImVec2 clip_a(pos.x,pos.y);
  ImVec2 clip_b(pos.x+pos.width,pos.y+pos.height);
  /*qDebug() << pos.x << " y " << pos.y;
  qDebug() << pos.width << " height " << pos.height;
  qDebug() << clip->width << " clip->height " << clip->height;*/

  litehtml::position pos2 = litehtml::element::get_placement();
  /*qDebug() << pos2.bottom() << " pos2->top " << pos2.top();
  qDebug() << pos2.left() << " pos2->right " << pos2.right();
  qDebug() << pos2.width << " pos2->height " << pos2.height;
  qDebug() << pos2.x << " pos2->y " << pos2.y;*/

  // The image contains the background image URL. URL can be relative.
  // Use the baseurl member to find the base URL for image.
  // This member defines the background-color CSS property.
  ImColor color;
if(!m_bg.m_color.alpha)
    {
      color = ImColor(255,255,255,255);
    }
  else {
    color = ImColor(m_bg.m_color.red, m_bg.m_color.green, m_bg.m_color.blue, m_bg.m_color.alpha);
  }


  //m_bg.m_color		= get_color(_t("background-color"), false, web_color(0, 0, 0, 0));

  // TODO: input background
  win->DrawList->AddRectFilled(clip_a, clip_b, color);

  ImGui::SetCursorPos(ImVec2(win->Pos.x+clip_a.x+ImGui::GetScrollX(),win->Pos.y+clip_a.y+ImGui::GetScrollY()));//position the draw cursor.
  ImGui::PushItemWidth(pos.width);
  //ImGui::PushItemHeight(pos.width);
  //ImGui::InputText("input text", str0, IM_ARRAYSIZE(str0));
  ImVec2 size(pos.width,pos.height);
  // https://github.com/ocornut/imgui/blob/3d8ea352d1f11e9ae2dc6fe4ff457106bb1f224c/imgui_widgets.cpp#L2894
  // https://github.com/ocornut/imgui/blob/3d8ea352d1f11e9ae2dc6fe4ff457106bb1f224c/imgui_widgets.cpp#L3203
  ImGuiInputTextCallback  UserCallback;

  ImGuiStyle style_prev = ImGui::GetStyle();

  // set text color, background color e.t.c
  ImGuiStyle& style = ImGui::GetStyle();
style.Colors[ImGuiCol_Text]                  = ImVec4(0.90f, 0.90f, 0.90f, 1.0f);
style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.0f);
style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.09f, 0.09f, 0.15f, 0.0f);
style.Colors[ImGuiCol_ChildWindowBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.05f, 0.05f, 0.10f, 0.0f);
style.Colors[ImGuiCol_Border]                = ImVec4(0.70f, 0.70f, 0.70f, 0.0f);
style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.00f, 0.00f, 0.01f, 0.0f);
style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.90f, 0.80f, 0.80f, 0.0f);
style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.90f, 0.65f, 0.65f, 0.0f);
style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.40f, 0.40f, 0.80f, 0.0f);
style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.01f, 0.01f, 0.02f, 0.0f);
style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.20f, 0.25f, 0.30f, 0.0f);
style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.55f, 0.53f, 0.55f, 0.0f);
style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.56f, 0.56f, 0.56f, 0.0f);
style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.56f, 0.56f, 0.56f, 0.0f);
//style.Colors[ImGuiCol_ComboBg]               = ImVec4(0.1f, 0.1f, 0.1f, 0.0f);
style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.90f, 0.90f, 0.90f, 0.0f);
style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.70f, 0.70f, 0.70f, 0.0f);
style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.30f, 0.30f, 0.30f, 0.0f);
style.Colors[ImGuiCol_Button]                = ImVec4(0.48f, 0.72f, 0.89f, 0.0f);
style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.50f, 0.69f, 0.99f, 0.0f);
style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.80f, 0.50f, 0.50f, 0.0f);
style.Colors[ImGuiCol_Header]                = ImVec4(0.30f, 0.69f, 1.00f, 0.0f);
style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.44f, 0.61f, 0.86f, 0.0f);
style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.38f, 0.62f, 0.83f, 0.0f);
style.Colors[ImGuiCol_Column]                = ImVec4(0.50f, 0.50f, 0.50f, 0.0f);
style.Colors[ImGuiCol_ColumnHovered]         = ImVec4(0.70f, 0.60f, 0.60f, 0.0f);
style.Colors[ImGuiCol_ColumnActive]          = ImVec4(0.90f, 0.70f, 0.70f, 0.0f);
style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.0f);
style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(1.00f, 1.00f, 1.00f, 0.0f);
style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(1.00f, 1.00f, 1.00f, 0.0f);
/*style.Colors[ImGuiCol_CloseButton]           = ImVec4(0.50f, 0.50f, 0.90f, 0.50f);
style.Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(0.70f, 0.70f, 0.90f, 0.60f);
style.Colors[ImGuiCol_CloseButtonActive]     = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
*/
style.Colors[ImGuiCol_PlotLines]             = ImVec4(1.00f, 1.00f, 1.00f, 0.0f);
style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.90f, 0.70f, 0.00f, 0.0f);
style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 0.0f);
style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 0.0f);
style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.00f, 0.00f, 1.00f, 1.0f);
style.Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 0.0f);
  ImGuiInputTextFlags     UserFlags = ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue; // ImGuiInputTextFlags_Multiline
  //ImGui::InputText("", str0, IM_ARRAYSIZE(str0), UserFlags);
  ImGui::InputTextMultiline("", str0, IM_ARRAYSIZE(str0), size, UserFlags);

style = style_prev;
// TODO: add <button> tag
// >>>>>>>>>
/*ImVec2 windowSize = ImGui::GetIO().DisplaySize; // My ImGui window as fullscreen - padding (x=50, y=60)
ImVec2 buttonSize(60, 30); // My button size
ImGui::Button("Save", buttonSize);//, e - ImVec2(10, 10) - buttonSize); // Draw button
*/
// <<<<<

/*
    bool show_test_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImColor(114, 144, 154);
    static float f = 0.0f;
    ImGui::Text("Hello, world!");
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::ColorEdit3("clear color", (float*)&clear_color);
    if (ImGui::Button("Test Window")) show_test_window ^= 1;
    if (ImGui::Button("Another Window")) show_another_window ^= 1;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
*/

//ImGui::Text("Hello, world!");

/*
  // draw standard background here
  if (el_pos.does_intersect(clip))
  {
    const background* bg = get_background();
    if (bg)
    {
      background_paint bg_paint;
      init_background_paint(pos, bg_paint, bg);

      get_document()->container()->draw_background(hdc, bg_paint);
    }
  }

  // draw image as background
  if(pos.does_intersect(clip))
  {
    if (pos.width > 0 && pos.height > 0) {
      background_paint bg;
      bg.image				= m_src;
      bg.clip_box				= pos;
      bg.origin_box			= pos;
      bg.border_box			= pos;
      bg.border_box			+= m_padding;
      bg.border_box			+= m_borders;
      bg.repeat				= background_repeat_no_repeat;
      bg.image_size.width		= pos.width;
      bg.image_size.height	= pos.height;
      bg.border_radius		= m_css_borders.radius.calc_percents(bg.border_box.width, bg.border_box.height);
      bg.position_x			= pos.x;
      bg.position_y			= pos.y;
      get_document()->container()->draw_background(hdc, bg);
    }
  }

  // draw borders
  if (el_pos.does_intersect(clip))
  {
    position border_box = pos;
    border_box += m_padding;
    border_box += m_borders;

    borders bdr = m_css_borders;
    bdr.radius = m_css_borders.radius.calc_percents(border_box.width, border_box.height);

    get_document()->container()->draw_borders(hdc, bdr, border_box, have_parent() ? false : true);
  }*/
}

void container_el_inputbox::parse_styles( bool is_reparse /*= false*/ )
{
  html_tag::parse_styles(is_reparse);

  /*if(!m_src.empty())
  {
    if(!m_css_height.is_predefined() && !m_css_width.is_predefined())
    {
      get_document()->container()->load_image(m_src.c_str(), 0, true);
    } else
    {
      get_document()->container()->load_image(m_src.c_str(), 0, false);
    }
  }*/
}
