#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>

int main() {
    Display* display = XOpenDisplay(NULL);
    if (!display) {
        std::cerr << "Cannot open display" << std::endl;
        return 1;
    }

    int screen = DefaultScreen(display);
    Window window = XCreateSimpleWindow(display, RootWindow(display, screen),
                                      100, 100, 400, 300, 1,
                                      BlackPixel(display, screen),
                                      WhitePixel(display, screen));

    XStoreName(display, window, "MINIX Simple Window");
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    XEvent event;
    bool running = true;

    while (running) {
        XNextEvent(display, &event);
        
        if (event.type == Expose) {
            GC gc = XCreateGC(display, window, 0, NULL);
            XDrawString(display, window, gc, 50, 50, "Hello MINIX!", 12);
            XDrawString(display, window, gc, 50, 80, "Press ESC to exit", 17);
            XFreeGC(display, gc);
        }
        
        if (event.type == KeyPress) {
            KeySym key = XLookupKeysym(&event.xkey, 0);
            if (key == XK_Escape) {
                running = false;
            }
        }
    }

    XDestroyWindow(display, window);
    XCloseDisplay(display);
    return 0;
}
