#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <iostream>
#include <string>
#include <cstdlib>

class SimpleWindow {
private:
    Display* display;
    Window window;
    GC gc;
    int screen;

public:
    SimpleWindow() : display(nullptr), window(0), gc(nullptr), screen(0) {}
    
    bool initialize() {
        // Открываем соединение с X-сервером
        display = XOpenDisplay(nullptr);
        if (!display) {
            std::cerr << "Не удалось подключиться к X-серверу" << std::endl;
            return false;
        }
        
        screen = DefaultScreen(display);
        
        // Создаем окно
        window = XCreateSimpleWindow(
            display,
            RootWindow(display, screen),
            100, 100, 400, 300, 2,
            BlackPixel(display, screen),
            WhitePixel(display, screen)
        );
        
        // Устанавливаем заголовок окна
        XStoreName(display, window, "MINIX X11 Пример");
        
        // Выбираем события для обработки
        XSelectInput(display, window, 
                    ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask);
        
        // Создаем графический контекст
        gc = XCreateGC(display, window, 0, nullptr);
        XSetForeground(display, gc, BlackPixel(display, screen));
        
        // Показываем окно
        XMapWindow(display, window);
        
        return true;
    }
    
    void run() {
        XEvent event;
        bool running = true;
        
        while (running) {
            XNextEvent(display, &event);
            
            switch (event.type) {
                case Expose:
                    handleExpose();
                    break;
                    
                case KeyPress:
                    running = handleKeyPress(event);
                    break;
                    
                case ButtonPress:
                    handleButtonPress(event);
                    break;
                    
                case ConfigureNotify:
                    handleConfigure(event);
                    break;
            }
        }
    }
    
    void handleExpose() {
        // Очищаем окно
        XClearWindow(display, window);
        
        // Рисуем текст
        std::string title = "Добро пожаловать в MINIX!";
        std::string instruction = "Нажмите любую клавишу для выхода";
        std::string clickInfo = "Или кликните мышью для изменения цвета";
        
        XDrawString(display, window, gc, 50, 50, 
                   title.c_str(), title.length());
        XDrawString(display, window, gc, 50, 80, 
                   instruction.c_str(), instruction.length());
        XDrawString(display, window, gc, 50, 110, 
                   clickInfo.c_str(), clickInfo.length());
        
        // Рисуем простые фигуры
        XDrawRectangle(display, window, gc, 50, 150, 100, 60);
        XFillRectangle(display, window, gc, 200, 150, 100, 60);
        XDrawArc(display, window, gc, 320, 150, 60, 60, 0, 360 * 64);
    }
    
    bool handleKeyPress(const XEvent& event) {
        std::cout << "Клавиша нажата. Выход..." << std::endl;
        return false; // Завершаем программу
    }
    
    void handleButtonPress(const XEvent& event) {
        // Меняем цвет при клике мыши
        static int colorIndex = 0;
        unsigned long colors[] = {
            BlackPixel(display, screen),
            WhitePixel(display, screen),
            RedPixel(display, screen),
            GreenPixel(display, screen),
            BluePixel(display, screen)
        };
        
        colorIndex = (colorIndex + 1) % 5;
        XSetForeground(display, gc, colors[colorIndex]);
        
        // Перерисовываем окно
        XClearWindow(display, window);
        handleExpose();
    }
    
    void handleConfigure(const XEvent& event) {
        // Обработка изменения размера окна
        XClearWindow(display, window);
        handleExpose();
    }
    
    ~SimpleWindow() {
        if (gc) {
            XFreeGC(display, gc);
        }
        if (window) {
            XDestroyWindow(display, window);
        }
        if (display) {
            XCloseDisplay(display);
        }
    }
};

// Вспомогательная функция для получения красного пикселя
unsigned long RedPixel(Display* display, int screen) {
    Colormap colormap = DefaultColormap(display, screen);
    XColor color;
    color.red = 65535;
    color.green = 0;
    color.blue = 0;
    color.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(display, colormap, &color);
    return color.pixel;
}

// Вспомогательная функция для получения зеленого пикселя
unsigned long GreenPixel(Display* display, int screen) {
    Colormap colormap = DefaultColormap(display, screen);
    XColor color;
    color.red = 0;
    color.green = 65535;
    color.blue = 0;
    color.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(display, colormap, &color);
    return color.pixel;
}

// Вспомогательная функция для получения синего пикселя
unsigned long BluePixel(Display* display, int screen) {
    Colormap colormap = DefaultColormap(display, screen);
    XColor color;
    color.red = 0;
    color.green = 0;
    color.blue = 65535;
    color.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(display, colormap, &color);
    return color.pixel;
}

int main() {
    std::cout << "Запуск графического приложения для MINIX..." << std::endl;
    
    SimpleWindow app;
    
    if (!app.initialize()) {
        std::cerr << "Ошибка инициализации приложения" << std::endl;
        return 1;
    }
    
    app.run();
    
    std::cout << "Приложение завершено." << std::endl;
    return 0;
}
