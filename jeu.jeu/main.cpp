#include "Game.h"
#include "Menu.h"

int main() {
    bool inMenu = true;

    while (inMenu) {
        sf::RenderWindow menuWindow(sf::VideoMode(800, 600), "Jeu de Cachette - Menu");
        Menu menu;
        Game game;

        while (menuWindow.isOpen()) {
            sf::Event event;
            while (menuWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    menuWindow.close();
                    inMenu = false;
                }
            }

            menu.handleInput();
            menuWindow.clear();
            menu.render(menuWindow);
            menuWindow.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                int option = menu.getSelectedOption();

                if (option == 0) {
                    menuWindow.close();
                    game.startGame(GameMode::DAY);
                    game.run();
                }
                else if (option == 1) {
                    menuWindow.close();
                    game.startGame(GameMode::NIGHT);
                    game.run();
                }
                else if (option == 2) {
                    // About - à implémenter
                }
                else if (option == 3) {
                    menuWindow.close();
                    inMenu = false;
                }
                sf::sleep(sf::milliseconds(200));
            }
        }
    }

    return 0;
}