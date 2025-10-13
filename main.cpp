#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

class TextGUI {
private:
    int selectedItem;
    std::vector<std::string> menuItems;

    void clearScreen() {
        system("clear");
    }

    void drawBox(int width, int height) {
        // Верхняя граница
        std::cout << "┌";
        for (int i = 0; i < width - 2; i++) std::cout << "─";
        std::cout << "┐" << std::endl;

        // Середина
        for (int i = 0; i < height - 2; i++) {
            std::cout << "│";
            for (int j = 0; j < width - 2; j++) std::cout << " ";
            std::cout << "│" << std::endl;
        }

        // Нижняя граница
        std::cout << "└";
        for (int i = 0; i < width - 2; i++) std::cout << "─";
        std::cout << "┘" << std::endl;
    }

public:
    TextGUI() : selectedItem(0) {
        menuItems = {
            "Запустить программу",
            "Настройки",
            "Справка", 
            "О программе",
            "Выход"
        };
    }

    void showMainMenu() {
        char input;
        do {
            clearScreen();
            
            std::cout << "=========================================" << std::endl;
            std::cout << "        ГРАФИЧЕСКИЙ ИНТЕРФЕЙС MINIX" << std::endl;
            std::cout << "=========================================" << std::endl;
            std::cout << std::endl;
            
            // Отображение меню
            for (int i = 0; i < menuItems.size(); i++) {
                if (i == selectedItem) {
                    std::cout << " > [" << (i + 1) << "] " << menuItems[i] << " <" << std::endl;
                } else {
                    std::cout << "   [" << (i + 1) << "] " << menuItems[i] << std::endl;
                }
            }
            
            std::cout << std::endl;
            std::cout << "Используйте W/S для навигации, Enter для выбора" << std::endl;
            std::cout << "=========================================" << std::endl;
            
            input = std::cin.get();
            std::cin.ignore(); // Очистка буфера
            
            switch(input) {
                case 'w':
                case 'W':
                    selectedItem = (selectedItem - 1 + menuItems.size()) % menuItems.size();
                    break;
                case 's':
                case 'S':
                    selectedItem = (selectedItem + 1) % menuItems.size();
                    break;
                case '\n':
                case '\r':
                    handleMenuSelection();
                    break;
                case '1'...'5':
                    selectedItem = input - '1';
                    handleMenuSelection();
                    break;
                case 'q':
                case 'Q':
                    return;
            }
            
        } while (true);
    }

    void handleMenuSelection() {
        clearScreen();
        
        switch(selectedItem) {
            case 0:
                showProgramScreen();
                break;
            case 1:
                showSettings();
                break;
            case 2:
                showHelp();
                break;
            case 3:
                showAbout();
                break;
            case 4:
                std::cout << "Выход из программы..." << std::endl;
                exit(0);
                break;
        }
        
        std::cout << std::endl << "Нажмите Enter для возврата в меню...";
        std::cin.get();
    }

    void showProgramScreen() {
        std::cout << "┌─────────────────────────────────────┐" << std::endl;
        std::cout << "│         ЗАПУСК ПРОГРАММЫ           │" << std::endl;
        std::cout << "├─────────────────────────────────────┤" << std::endl;
        std::cout << "│ Программа выполняется...           │" << std::endl;
        std::cout << "│                                    │" << std::endl;
        std::cout << "│ Статус: ██████████ 100%            │" << std::endl;
        std::cout << "│                                    │" << std::endl;
        std::cout << "│ Задача завершена успешно!          │" << std::endl;
        std::cout << "└─────────────────────────────────────┘" << std::endl;
    }

    void showSettings() {
        std::cout << "┌─────────────────────────────────────┐" << std::endl;
        std::cout << "│             НАСТРОЙКИ              │" << std::endl;
        std::cout << "├─────────────────────────────────────┤" << std::endl;
        std::cout << "│ □ Автозагрузка                     │" << std::endl;
        std::cout << "│ □ Логирование                      │" << std::endl;
        std::cout << "│ □ Высокая производительность       │" << std::endl;
        std::cout << "│                                    │" << std::endl;
        std::cout << "│ [Сохранить]  [Отмена]              │" << std::endl;
        std::cout << "└─────────────────────────────────────┘" << std::endl;
    }

    void showHelp() {
        std::cout << "┌─────────────────────────────────────┐" << std::endl;
        std::cout << "│               СПРАВКА              │" << std::endl;
        std::cout << "├─────────────────────────────────────┤" << std::endl;
        std::cout << "│ Управление:                        │" << std::endl;
        std::cout << "│   W/S - Навигация по меню          │" << std::endl;
        std::cout << "│   Enter - Выбор пункта             │" << std::endl;
        std::cout << "│   Q - Выход                        │" << std::endl;
        std::cout << "│                                    │" << std::endl;
        std::cout << "│ Это текстовая версия GUI для MINIX │" << std::endl;
        std::cout << "└─────────────────────────────────────┘" << std::endl;
    }

    void showAbout() {
        std::cout << "┌─────────────────────────────────────┐" << std::endl;
        std::cout << "│             О ПРОГРАММЕ            │" << std::endl;
        std::cout << "├─────────────────────────────────────┤" << std::endl;
        std::cout << "│ Текстовый GUI для MINIX            │" << std::endl;
        std::cout << "│ Версия 1.0                         │" << std::endl;
        std::cout << "│                                    │" << std::endl;
        std::cout << "│ Создано для работы без X11         │" << std::endl;
        std::cout << "│ Использует стандартный ввод/вывод  │" << std::endl;
        std::cout << "└─────────────────────────────────────┘" << std::endl;
    }
};

int main() {
    TextGUI gui;
    gui.showMainMenu();
    return 0;
}
