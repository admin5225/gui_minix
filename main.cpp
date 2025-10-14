#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <cstdio>
#include <cstring>

// Глобальные переменные для виджетов
Fl_Input *input;
Fl_Output *output;

// Callback функция для кнопки
void button_callback(Fl_Widget* widget, void* data) {
    const char* text = input->value();
    char buffer[256];
    
    if (strlen(text) > 0) {
        snprintf(buffer, sizeof(buffer), "Привет, %s!", text);
        output->value(buffer);
    } else {
        output->value("Введите имя!");
    }
}

// Callback для выхода
void exit_callback(Fl_Widget* widget, void* data) {
    exit(0);
}

int main() {
    // Создание главного окна
    Fl_Window *window = new Fl_Window(400, 300, "FLTK Example на Minix");
    window->color(FL_WHITE);

    // Заголовок
    Fl_Box *title = new Fl_Box(50, 20, 300, 30, "Добро пожаловать в FLTK!");
    title->labelsize(16);
    title->labelfont(FL_BOLD);

    // Поле ввода
    Fl_Box *input_label = new Fl_Box(50, 70, 100, 25, "Ваше имя:");
    input_label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    
    input = new Fl_Input(150, 70, 200, 25);

    // Кнопка приветствия
    Fl_Button *hello_btn = new Fl_Button(150, 110, 100, 30, "Поприветствовать");
    hello_btn->callback(button_callback);
    hello_btn->color(FL_BLUE);
    hello_btn->labelcolor(FL_WHITE);

    // Поле вывода
    Fl_Box *output_label = new Fl_Box(50, 160, 100, 25, "Результат:");
    output_label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    
    output = new Fl_Output(150, 160, 200, 25);

    // Кнопка выхода
    Fl_Button *exit_btn = new Fl_Button(150, 210, 100, 30, "Выход");
    exit_btn->callback(exit_callback);
    exit_btn->color(FL_RED);
    exit_btn->labelcolor(FL_WHITE);

    // Информационная строка
    Fl_Box *info = new Fl_Box(50, 260, 300, 30, "FLTK GUI на Minix");
    info->labelsize(10);
    info->labelcolor(FL_DARK_GREEN);

    // Завершение создания окна
    window->end();
    window->show();

    // Запуск главного цикла FLTK
    return Fl::run();
}
