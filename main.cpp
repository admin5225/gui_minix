#include <iostream>
#include <vector>
#include <string>
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
        menuItems.push_back("Zapustit' programmu");
        menuItems.push_back("Nastrojki");
        menuItems.push_back("Spravka");
        menuItems.push_back("O programme");
        menuItems.push_back("Vyhod");
    }

    void showMainMenu() {
        char input;
        do {
            clearScreen();
            
            std::cout << "=========================================" << std::endl;
            std::cout << "        GRAFICHESKIJ INTERFEJS MINIX" << std::endl;
            std::cout << "=========================================" << std::endl;
            std::cout << std::endl;
            
            // Отображение меню с ASCII символами
            for (int i = 0; i < menuItems.size(); i++) {
                if (i == selectedItem) {
                    std::cout << " ==> [" << (i + 1) << "] " << menuItems[i] << " <==" << std::endl;
                } else {
                    std::cout << "     [" << (i + 1) << "] " << menuItems[i] << std::endl;
                }
            }
            
            std::cout << std::endl;
            std::cout << "Ispol'zujte W/S dlya navigacii, Enter dlya vybora" << std::endl;
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
                std::cout << "Vyhod iz programmy..." << std::endl;
                exit(0);
                break;
        }
        
        std::cout << std::endl << "Najmite Enter dlya vozvrata v menu...";
        std::cin.ignore();
        std::cin.get();
    }

    void showProgramScreen() {
        std::cout << "=========================================" << std::endl;
        std::cout << "         ZAPUSK PROGRAMMY" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << " Programma vypolnyaetsya..." << std::endl;
        std::cout << std::endl;
        std::cout << " Status: [==========] 100%" << std::endl;
        std::cout << std::endl;
        std::cout << " Zadacha zavershena uspeshno!" << std::endl;
        std::cout << "=========================================" << std::endl;
    }

    void showSettings() {
        std::cout << "=========================================" << std::endl;
        std::cout << "             NASTROJKI" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << " [ ] Avtozagruzka" << std::endl;
        std::cout << " [ ] Logirovanie" << std::endl;
        std::cout << " [ ] Vysokaya proizvoditel'nost'" << std::endl;
        std::cout << std::endl;
        std::cout << " [Sohranit']  [Otmena]" << std::endl;
        std::cout << "=========================================" << std::endl;
    }

    void showHelp() {
        std::cout << "=========================================" << std::endl;
        std::cout << "               SPRAVKA" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << " Upravlenie:" << std::endl;
        std::cout << "   W/S - Navigaciya po menu" << std::endl;
        std::cout << "   Enter - Vybor punkta" << std::endl;
        std::cout << "   Q - Vyhod" << std::endl;
        std::cout << std::endl;
        std::cout << " Eto tekstovaya versiya GUI dlya MINIX" << std::endl;
        std::cout << "=========================================" << std::endl;
    }

    void showAbout() {
        std::cout << "=========================================" << std::endl;
        std::cout << "             O PROGRAMME" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << " Tekstovyj GUI dlya MINIX" << std::endl;
        std::cout << " Versiya 1.0" << std::endl;
        std::cout << std::endl;
        std::cout << " Sozdano dlya raboty bez X11" << std::endl;
        std::cout << " Ispol'zuyet standartnyj vvod/vyvod" << std::endl;
        std::cout << "=========================================" << std::endl;
    }
};

int main() {
    TextGUI gui;
    gui.showMainMenu();
    return 0;
}
