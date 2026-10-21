#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

/**
 * Classe Menu
 * Concept: Encapsulation (page 84-88)
 * Role: Gerer l'affichage et les interactions du menu principal
 */
class Menu {
private:
    // Attributs prives (encapsulation, page 84-88)
    std::vector<sf::Text> menuItems;  // Conteneur STL (page 107-117)
    int selectedItem;                  // Index de l'element selectionne
    sf::Text title;                    // Titre du menu
    sf::Text aboutText;                // Texte de la section "A propos"
    sf::RectangleShape background;     // Fond du menu (carré)
    sf::Sprite backgroundSprite;       // Sprite pour l'image de fond
    sf::Texture backgroundTexture;     // Texture pour l'image de fond
    bool showAbout;                    // Affichage de la section "A propos"

    // Dimensions et positions (constantes)
    static const int TITLE_SIZE = 55;
    static const int MENU_SIZE = 32;
    static const int ABOUT_SIZE = 18;
    static const float TITLE_Y;
    static const float MENU_START_Y;
    static const float MENU_SPACING;

    // Methodes privees (helper methods)
    void centerText(sf::Text& text);                    // Centrer un texte
    void updateItemColors();                             // Mettre a jour les couleurs
    void initMenuItems();                                // Initialiser les items du menu
    void initAboutText();                                // Initialiser le texte "A propos"
    void loadBackground();                               // Charger l'image de fond

public:
    // Constructeurs (page 45-56)
    Menu();                                              // Constructeur par defaut
    Menu(const Menu& autre);                            // Constructeur de copie

    // Destructeur (page 57-60)
    ~Menu();

    // Operateur d'affectation (page 31-42)
    Menu& operator=(const Menu& autre);

    // Methodes publiques
    void handleInput();                                  // Gestion des entrees clavier
    void render(sf::RenderWindow& window);               // Rendu du menu
    void reset();                                        // Reinitialiser le menu

    // Accesseurs (getters) - methodes const (page 25-26)
    int getSelectedOption() const { return selectedItem; }
    bool isShowingAbout() const { return showAbout; }

    // Mutateurs (setters)
    void setShowAbout(bool show) { showAbout = show; }
    void setSelectedItem(int item) { selectedItem = item; updateItemColors(); }
};

#endif