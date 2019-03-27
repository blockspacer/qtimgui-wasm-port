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
  //get_document()->container()->get_image_size(m_src.c_str(), 0, sz);
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
  m_src = get_attr(_t("src"), _t(""));

  for(auto it = m_attrs.begin(); it != m_attrs.end(); it++)
  {
    //qDebug() << it->first.c_str() << "" << it->second.c_str();
  }

/*
  const tchar_t* attr_height = get_attr(_t("height"));
  if(attr_height)
  {
    m_style.add_property(_t("height"), attr_height, 0, false);
  }
  const tchar_t* attr_width = get_attr(_t("width"));
  if(attr_width)
  {
    m_style.add_property(_t("width"), attr_width, 0, false);
  }*/
}

void container_el_inputbox::draw( litehtml::uint_ptr hdc, int x, int y, const litehtml::position* clip )
{
  litehtml::position pos = m_pos;
  pos.x += x;
  pos.y += y;

  litehtml::position el_pos = pos;
  el_pos += m_padding;
  el_pos += m_borders;

    ImGuiWindow* win = ImGui::GetCurrentWindow();
/*
  // clip_box. Defines the position of the clipping box. See the background-clip CSS property.
  ImVec2 clip_a(-1500,-1500);
  ImVec2 clip_b(1500,1500);
  // The image contains the background image URL. URL can be relative.
  // Use the baseurl member to find the base URL for image.
  // This member defines the background-color CSS property.
  ImColor color(155, 55, 155, 255);
  win->DrawList->AddRectFilled(clip_a, clip_b, color);*/
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

ImGui::Text("Hello, world!");

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

  if(!m_src.empty())
  {
    if(!m_css_height.is_predefined() && !m_css_width.is_predefined())
    {
      get_document()->container()->load_image(m_src.c_str(), 0, true);
    } else
    {
      get_document()->container()->load_image(m_src.c_str(), 0, false);
    }
  }
}
