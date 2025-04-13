#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Menu_Bar.H>
#include <fstream>
#include <sstream>
#include <iostream>

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300

int main() {
  Fl_Window* window = new Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "viewfile");

  Fl_Text_Buffer* buffer = new Fl_Text_Buffer();
  Fl_Text_Display* display = new Fl_Text_Display(10, 10, WINDOW_WIDTH-20, WINDOW_HEIGHT-20);
  display->buffer(buffer);

  Fl_File_Chooser chooser(".", "*", Fl_File_Chooser::SINGLE, "select file");

  chooser.show();
  
  while (chooser.shown()) {
    Fl::wait();
  }

  std::ifstream file(chooser.value());
  if (file) {
    std::stringstream ss;
    ss << file.rdbuf();
    buffer->text(ss.str().c_str());
  }
  else {
    buffer->text("Could not open file 'ifle'.");
  }

  window->callback([](Fl_Widget* w) {
    w->hide();
  });

  window->end();
  window->show();
  return Fl::run();
}
