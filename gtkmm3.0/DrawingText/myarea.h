#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H
#include <gtkmm/drawingarea.h>

class MyArea : public Gtk::DrawingArea
{ 
public:
  MyArea();
  virtual ~MyArea();

protected:
  //Override default signal handler:
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

private:
  void draw_rectangle(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
  void draw_text(const Cairo::RefPtr<Cairo::Context>& cr, int rectangle_width, int rectangle_height);

};
#endif // GTKMM_EXAMPLE_MYAREA_H