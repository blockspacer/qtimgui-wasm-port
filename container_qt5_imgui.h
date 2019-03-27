#pragma once

#include <QtImGui.h>
#include <imgui.h>
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

struct Image {
  ImTextureID textureId;
  int w;
  int h;
};

/**
 * @todo write docs
 */
class container_qt5 : public litehtml::document_container
{
private:
    std::shared_ptr< litehtml::document > _doc;
    //QMap<quint32, Image> m_images;
    QHash<QString, Image> m_images;
    QHash<QString, QByteArray> m_loaded_css;
    //GLuint my_opengl_texture;
    int lastCursorX;
    int lastCursorY;
    int lastCursorClientX;
    int lastCursorClientY;

public:
    void render();
    void onMouseMove(QMouseEvent *event);
    void onMousePress(QMouseEvent *event);
    void onMouseRelease(QMouseEvent *event);
    void onMouseLeave(QMouseEvent *event);
    bool OnMediaChanged();
    int GetWidth();
    int GetHeight();

public:
  litehtml::element::ptr elementUnderCursor()
  {
    return _doc->root()->get_element_by_point(lastCursorX, lastCursorY, lastCursorClientX, lastCursorClientY);
  }

  litehtml::document::ptr getDocument()
  {
    return _doc;
  }

    /**
     * Default constructor
     */
    container_qt5(QWidget *parent = nullptr);

    /**
     * Destructor
     */
    virtual ~container_qt5();

    void set_document(std::shared_ptr<litehtml::document> doc);

    /**
     * @todo write docs
     *
     * @param language TODO
     * @param culture TODO
     * @return TODO
     */
    virtual void get_language(litehtml::tstring& language, litehtml::tstring& culture) const override;

    /**
     * @todo write docs
     *
     * @param media TODO
     * @return TODO
     */
    virtual void get_media_features(litehtml::media_features& media) const override;

    /**
     * @todo write docs
     *
     * @param tag_name TODO
     * @param attributes TODO
     * @param doc TODO
     * @return TODO
     */
    virtual std::shared_ptr< litehtml::element > create_element(const litehtml::tchar_t* tag_name, const litehtml::string_map& attributes, const std::shared_ptr< litehtml::document >& doc) override;

    /**
     * @todo write docs
     *
     * @param client TODO
     * @return TODO
     */
    virtual void get_client_rect(litehtml::position& client) const override;

    /**
     * @todo write docs
     *
     * @return TODO
     */
    virtual void del_clip() override;

    /**
     * @todo write docs
     *
     * @param pos TODO
     * @param bdr_radius TODO
     * @param valid_x TODO
     * @param valid_y TODO
     * @return TODO
     */
    virtual void set_clip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius, bool valid_x, bool valid_y) override;

    /**
     * @todo write docs
     *
     * @param text TODO
     * @param url TODO
     * @param baseurl TODO
     * @return TODO
     */
    virtual void import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl) override;

    /**
     * @todo write docs
     *
     * @param text TODO
     * @param tt TODO
     * @return TODO
     */
    virtual void transform_text(litehtml::tstring& text, litehtml::text_transform tt) override;

    /**
     * @todo write docs
     *
     * @param cursor TODO
     * @return TODO
     */
    virtual void set_cursor(const litehtml::tchar_t* cursor) override;

    /**
     * @todo write docs
     *
     * @param url TODO
     * @param el TODO
     * @return TODO
     */
    virtual void on_anchor_click(const litehtml::tchar_t* url, const litehtml::element::ptr& el) override;

    /**
     * @todo write docs
     *
     * @param doc TODO
     * @param el TODO
     * @return TODO
     */
    virtual void link(const std::shared_ptr< litehtml::document >& doc, const litehtml::element::ptr& el) override;

    /**
     * @todo write docs
     *
     * @param base_url TODO
     * @return TODO
     */
    virtual void set_base_url(const litehtml::tchar_t* base_url) override;

    /**
     * @todo write docs
     *
     * @param caption TODO
     * @return TODO
     */
    virtual void set_caption(const litehtml::tchar_t* caption) override;

    /**
     * @todo write docs
     *
     * @param hdc TODO
     * @param borders TODO
     * @param draw_pos TODO
     * @param root TODO
     * @return TODO
     */
    virtual void draw_borders(litehtml::uint_ptr hdc, const litehtml::borders& borders, const litehtml::position& draw_pos, bool root) override;

    /**
     * @todo write docs
     *
     * @param hdc TODO
     * @param bg TODO
     * @return TODO
     */
    virtual void draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint& bg) override;

    /**
     * @todo write docs
     *
     * @param src TODO
     * @param baseurl TODO
     * @param sz TODO
     * @return TODO
     */
    virtual void get_image_size(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, litehtml::size& sz) override;

    /**
     * @todo write docs
     *
     * @param src TODO
     * @param baseurl TODO
     * @param redraw_on_ready TODO
     * @return TODO
     */
    virtual void load_image(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, bool redraw_on_ready) override;

    /**
     * @todo write docs
     *
     * @param hdc TODO
     * @param marker TODO
     * @return TODO
     */
    virtual void draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker) override;

    /**
     * @todo write docs
     *
     * @return TODO
     */
    virtual const litehtml::tchar_t* get_default_font_name() const override;

    /**
     * @todo write docs
     *
     * @return TODO
     */
    virtual int get_default_font_size() const override;

    /**
     * @todo write docs
     *
     * @param pt TODO
     * @return TODO
     */
    virtual int pt_to_px(int pt) override;

    /**
     * @todo write docs
     *
     * @param hdc TODO
     * @param text TODO
     * @param hFont TODO
     * @param color TODO
     * @param pos TODO
     * @return TODO
     */
    virtual void draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos) override;

    /**
     * @todo write docs
     *
     * @param text TODO
     * @param hFont TODO
     * @return TODO
     */
    virtual int text_width(const litehtml::tchar_t* text, litehtml::uint_ptr hFont) override;

    /**
     * @todo write docs
     *
     * @param hFont TODO
     * @return TODO
     */
    virtual void delete_font(litehtml::uint_ptr hFont) override;

    /**
     * @todo write docs
     *
     * @param faceName TODO
     * @param size TODO
     * @param weight TODO
     * @param italic TODO
     * @param decoration TODO
     * @param fm TODO
     * @return TODO
     */
    virtual litehtml::uint_ptr create_font(const litehtml::tchar_t* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm) override;

};
