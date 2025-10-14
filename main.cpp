#include <Fl.h>
#include <Fl_Window.h>
#include <Fl_Box.h>
int main( int argc, char **argv ) {
Fl_Window *window = new Fl_Window( 300, 180, "Hello!" );
window->begin();
Fl_Box *box = new Fl_Box( 20, 40, 260, 100, "Hello, MINIX 3!" );
window->show( argc, argv );
return Fl::run();
}
