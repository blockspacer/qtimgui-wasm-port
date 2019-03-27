#pragma once

//#include <imgui.h>
#include "litehtml.h"
//#include "crc32.h"

  class container_el_inputbox : public litehtml::html_tag
  {
    litehtml::tstring	m_src;
  public:
    container_el_inputbox(const std::shared_ptr<litehtml::document>& doc, const litehtml::string_map& attributes);
    virtual ~container_el_inputbox(void);

    virtual int		line_height() const override;
    virtual bool	is_replaced() const override;
    virtual int		render(int x, int y, int max_width, bool second_pass = false) override;
    virtual void	parse_attributes() override;
    virtual void	parse_styles(bool is_reparse = false) override;
    virtual void	draw(litehtml::uint_ptr hdc, int x, int y, const litehtml::position* clip) override;
    virtual void	get_content_size(litehtml::size& sz, int max_width) override;
  };
