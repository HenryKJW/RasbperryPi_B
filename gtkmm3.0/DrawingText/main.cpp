#include "myarea.h"
#include <gtkmm/main.h>
#include <gtkmm/window.h>
int main(int argc, char** argv)
{
  Gtk::Main kit(argc, argv);

  Gtk::Window win;
  win.set_title("DrawingArea");

  MyArea area;
  win.add(area);
  area.show();

  Gtk::Main::run(win);
  
  return 0;
}