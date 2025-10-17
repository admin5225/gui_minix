#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <iostream>
#include <string>
#include <vector>



class SimpleX11GUI {
private:
    Display* display;
    Window window;
    GC gc;
    int screen;
    std::vector<std::string> menu_items;
    int selected_item;

public:
    SimpleX11GUI() : display(nullptr), window(0), gc(0), selected_item(0) {
        menu_items = {
            "Запустить программу 1",
            "Запустить программу 2",
            "Показать информацию",
            "Настройки",
            "Выход"
        };
    }

    bool initialize() {
        // Открываем соединение с X сервером
        display = XOpenDisplay(NULL);
        if (!display) {
            std::cerr << "Не удалось подключиться к X серверу" << std::endl;
            return false;
        }

        screen = DefaultScreen(display);
        
        // Создаем окно
        window = XCreateSimpleWindow(display, RootWindow(display, screen),
                                    100, 100, 400, 300, 2,
                                    BlackPixel(display, screen),
                                    WhitePixel(display, screen));

        // Устанавливаем заголовок окна
        XStoreName(display, window, "Simple MINIX GUI");

        // Выбираем события для обработки
        XSelectInput(display, window, 
                    ExposureMask | KeyPressMask | ButtonPressMask);

        // Создаем графический контекст
        gc = XCreateGC(display, window, 0, NULL);
        XSetForeground(display, gc, BlackPixel(display, screen));

        // Показываем окно
        XMapWindow(display, window);

        return true;
    }

    void draw_menu() {
        // Очищаем окно
        XClearWindow(display, window);

        // Устанавливаем шрифт
        XFontStruct* font = XLoadQueryFont(display, "fixed");
        if (font) {
            XSetFont(display, gc, font->fid);
        }

        // Рисуем заголовок
        XDrawString(display, window, gc, 150, 30, 
                   "MINIX GUI Application", 21);

        // Рисуем пункты меню
        for (size_t i = 0; i < menu_items.size(); ++i) {
            if (i == selected_item) {
                // Выделенный пункт
                XSetForeground(display, gc, 
                              WhitePixel(display, screen));
                XFillRectangle(display, window, gc, 
                             50, 60 + i * 30, 300, 25);
                XSetForeground(display, gc, 
                              BlackPixel(display, screen));
            } else {
                XSetForeground(display, gc, 
                              BlackPixel(display, screen));
                XDrawRectangle(display, window, gc, 
                             50, 60 + i * 30, 300, 25);
            }
            
            XDrawString(display, window, gc, 60, 80 + i * 30,
                       menu_items[i].c_str(), menu_items[i].length());
        }

        // Рисуем подсказку
        XDrawString(display, window, gc, 50, 250,
                   "Используйте стрелки и Enter для выбора", 40);
    }

    void handle_events() {
        XEvent event;
        bool running = true;

        while (running) {
            XNextEvent(display, &event);

            switch (event.type) {
                case Expose:
                    draw_menu();
                    break;

                case KeyPress:
                    {
                        KeySym key = XLookupKeysym(&event.xkey, 0);
                        switch (key) {
                            case XK_Down:
                                selected_item = (selected_item + 1) % menu_items.size();
                                draw_menu();
                                break;
                            case XK_Up:
                                selected_item = (selected_item - 1 + menu_items.size()) % menu_items.size();
                                draw_menu();
                                break;
                            case XK_Return:
                            case XK_KP_Enter:
                                execute_menu_item();
                                if (selected_item == menu_items.size() - 1) {
                                    running = false;
                                }
                                break;
                            case XK_Escape:
                                running = false;
                                break;
                        }
                    }
                    break;

                case ButtonPress:
                    // Простая обработка клика мыши
                    handle_mouse_click(event.xbutton.x, event.xbutton.y);
                    break;
            }
        }
    }

    void handle_mouse_click(int x, int y) {
        // Проверяем клик по пунктам меню
        for (size_t i = 0; i < menu_items.size(); ++i) {
            if (x >= 50 && x <= 350 && 
                y >= (60 + i * 30) && y <= (85 + i * 30)) {
                selected_item = i;
                execute_menu_item();
                if (i == menu_items.size() - 1) {
                    cleanup();
                    exit(0);
                }
                draw_menu();
                break;
            }
        }
    }

    void execute_menu_item() {
        // Здесь можно добавить выполнение действий
        switch (selected_item) {
            case 0:
                system("xterm &");
                break;
            case 1:
                system("xcalc &");
                break;
            case 2:
                show_system_info();
                break;
            case 3:
                show_settings();
                break;
            case 4:
                // Выход
                break;
        }
    }

    void show_system_info() {
        // Создаем диалоговое окно с информацией
        Window info_window = XCreateSimpleWindow(display, window,
                                               50, 100, 300, 150, 2,
                                               BlackPixel(display, screen),
                                               WhitePixel(display, screen));
        
        XSelectInput(display, info_window, ExposureMask | KeyPressMask);
        XMapWindow(display, info_window);

        XEvent event;
        bool info_open = true;

        while (info_open) {
            XNextEvent(display, &event);

            if (event.type == Expose && event.xexpose.window == info_window) {
                XClearWindow(display, info_window);
                XDrawString(display, info_window, gc, 20, 30, 
                           "Системная информация:", 22);
                XDrawString(display, info_window, gc, 20, 60, 
                           "MINIX с X11", 11);
                XDrawString(display, info_window, gc, 20, 90, 
                           "Нажмите любую клавишу...", 24);
            }

            if (event.type == KeyPress && event.xkey.window == info_window) {
                info_open = false;
            }
        }

        XDestroyWindow(display, info_window);
        draw_menu(); // Перерисовываем основное меню
    }

    void show_settings() {
        // Простое сообщение о настройках
        std::cout << "Открыты настройки" << std::endl;
    }

    void cleanup() {
        if (gc) XFreeGC(display, gc);
        if (window) XDestroyWindow(display, window);
        if (display) XCloseDisplay(display);
    }

    void run() {
        if (initialize()) {
            draw_menu();
            handle_events();
            cleanup();
        }
    }
};

int main() {
    SimpleX11GUI gui;
    gui.run();
    return 0;
}
