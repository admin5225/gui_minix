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

public:
    TextGUI() : selectedItem(0) {
        // Старый способ инициализации для совместимости
        menuItems.push_back("Запустить программу");
        menuItems.push_back("Настройки");
        menuItems.push_back("Справка");
        menuItems.push_back("О программе");
        menuItems.push_back("Выход");
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
            
            switch(input) {
                case 'w':
                case 'W':
                    if (selectedItem > 0) selectedItem--;
                    break;
                case 's':
                case 'S':
                    if (selectedItem < menuItems.size() - 1) selectedItem++;
                    break;
                case '\n':
                case '\r':
                    handleMenuSelection();
                    break;
                case '1':
                    selectedItem = 0;
                    handleMenuSelection();
                    break;
                case '2':
                    selectedItem = 1;
                    handleMenuSelection();
                    break;
                case '3':
                    selectedItem = 2;
                    handleMenuSelection();
                    break;
                case '4':
                    selectedItem = 3;
                    handleMenuSelection();
                    break;
                case '5':
                    selectedItem = 4;
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
        std::cin.ignore(); // Очистка предыдущего ввода
        std::cin.get();
    }

    void showProgramScreen() {
        std::cout << "=========================================" << std::endl;
        std::cout << "         ЗАПУСК ПРОГРАММЫ" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << " Программа выполняется..." << std::endl;
        std::cout << " " << std::endl;
        std::cout << " Статус: [##########] 100%" << std::endl;
        std::cout << " " << std::endl;
        std::cout << " Задача завершена успешно!" << std::endl;
        std::cout << "=========================================" << std::endl;
    }

    void showSettings() {
        std::cout << "=========================================" << std::endl;
        std::cout << "             НАСТРОЙКИ" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << " [ ] Автозагрузка" << std::endl;
        std::cout << " [ ] Логирование" << std::endl;
        std::cout << " [ ] Высокая производительность" << std::endl;
        std::cout << " " << std::endl;
        std::cout << " [Сохранить]  [Отмена]" << std::endl;
        std::cout << "=========================================" << std::endl;
    }

    void showHelp() {
        std::cout << "=========================================" << std::endl;
        std::cout << "               СПРАВКА" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << " Управление:" << std::endl;
        std::cout << "   W/S - Навигация по меню" << std::endl;
        std::cout << "   Enter - Выбор пункта" << std::endl;
        std::cout << "   Q - Выход" << std::endl;
        std::cout << " " << std::endl;
        std::cout << " Это текстовая версия GUI для MINIX" << std::endl;
        std::cout << "=========================================" << std::endl;
    }

    void showAbout() {
        std::cout << "=========================================" << std::endl;
        std::cout << "             О ПРОГРАММЕ" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << " Текстовый GUI для MINIX" << std::endl;
        std::cout << " Версия 1.0" << std::endl;
        std::cout << " " << std::endl;
        std::cout << " Создано для работы без X11" << std::endl;
        std::cout << " Использует стандартный ввод/вывод" << std::endl;
        std::cout << "=========================================" << std::endl;
    }
};

int main() {
    TextGUI gui;
    gui.showMainMenu();
    return 0;
}
