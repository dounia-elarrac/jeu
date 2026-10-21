#include "Menu.h"
#include "Config.h"
#include "FontManager.h"
#include <iostream>

using namespace std;  // Espace de nom std (page 182-183)

// ------------------------------------------------------------------
// Initialisation des membres statiques const (page 25-26 pour const)
// ------------------------------------------------------------------
const float Menu::TITLE_Y = 80.0f;
const float Menu::MENU_START_Y = 260.0f;
const float Menu::MENU_SPACING = 70.0f;

// ------------------------------------------------------------------
// Chargement de l'image de fond
// ------------------------------------------------------------------
void Menu::loadBackground() {
    // Chemin de l'image de fond (à modifier selon votre dossier)
    std::string backgroundPath = "textures/menu_background.jpg";

    if (backgroundTexture.loadFromFile(backgroundPath)) {
        backgroundSprite.setTexture(backgroundTexture);

        // Ajuster la taille de l'image à la taille de l'écran
        sf::Vector2u textureSize = backgroundTexture.getSize();
        float scaleX = GameConstants::SCREEN_WIDTH / static_cast<float>(textureSize.x);
        float scaleY = GameConstants::SCREEN_HEIGHT / static_cast<float>(textureSize.y);
        backgroundSprite.setScale(scaleX, scaleY);

        std::cout << " Menu background loaded successfully!" << std::endl;
    }
    else {
        // Si l'image n'existe pas, utiliser un fond noir
        std::cerr << " Failed to load menu background! Using black background." << std::endl;
        background.setSize(sf::Vector2f(GameConstants::SCREEN_WIDTH,
            GameConstants::SCREEN_HEIGHT));
        background.setFillColor(sf::Color(0, 0, 0));
    }
}

// ------------------------------------------------------------------
// Constructeur par defaut (page 45-46, 51-53)
// Utilisation de la liste d'initialisation (page 48-50)
// ------------------------------------------------------------------
Menu::Menu() : selectedItem(0), showAbout(false) {
    // Chargement de l'image de fond
    loadBackground();

    // Configuration du fond de secours (si l'image n'est pas chargée)
    background.setSize(sf::Vector2f(GameConstants::SCREEN_WIDTH,
        GameConstants::SCREEN_HEIGHT));
    background.setFillColor(sf::Color(0, 0, 0));

    // Initialisation du FontManager
    FontManager::initialiser();

    // Configuration du titre
    title.setString("JEU DE CACHETTE");
    title.setCharacterSize(TITLE_SIZE);
    title.setFillColor(sf::Color(255, 215, 0));  // Jaune
    title.setStyle(sf::Text::Bold);

    // Application de la police (page 133-134 pour reference)
    FontManager::appliquerPolice(title, "default");
    centerText(title);
    title.setPosition(title.getPosition().x, TITLE_Y);

    // Initialisation des items du menu
    initMenuItems();

    // Initialisation du texte "A propos"
    initAboutText();
}

// ------------------------------------------------------------------
// Constructeur de copie (page 54-56)
// ------------------------------------------------------------------
Menu::Menu(const Menu& autre) {
    // Copie des attributs (page 54-56)
    this->menuItems = autre.menuItems;
    this->selectedItem = autre.selectedItem;
    this->title = autre.title;
    this->aboutText = autre.aboutText;
    this->background = autre.background;
    this->backgroundSprite = autre.backgroundSprite;
    this->backgroundTexture = autre.backgroundTexture;
    this->showAbout = autre.showAbout;
}

// ------------------------------------------------------------------
// Destructeur (page 57-60)
// ------------------------------------------------------------------
Menu::~Menu() {
    // Rien a liberer dynamiquement
    // Les polices sont gerees par FontManager
}

// ------------------------------------------------------------------
// Operateur d'affectation (page 31-42)
// ------------------------------------------------------------------
Menu& Menu::operator=(const Menu& autre) {
    // Verification d'auto-affectation (page 66-67)
    if (this != &autre) {
        this->menuItems = autre.menuItems;
        this->selectedItem = autre.selectedItem;
        this->title = autre.title;
        this->aboutText = autre.aboutText;
        this->background = autre.background;
        this->backgroundSprite = autre.backgroundSprite;
        this->backgroundTexture = autre.backgroundTexture;
        this->showAbout = autre.showAbout;
    }
    return *this;  // Retourne l'objet courant (page 66-67)
}

// ------------------------------------------------------------------
// Centrage d'un texte
// ------------------------------------------------------------------
void Menu::centerText(sf::Text& text) {
    sf::FloatRect textRect = text.getLocalBounds();
    float x = (GameConstants::SCREEN_WIDTH - textRect.width) / 2.0f;
    float y = text.getPosition().y;
    text.setPosition(x, y);
}

// ------------------------------------------------------------------
// Mise a jour des couleurs des items
// ------------------------------------------------------------------
void Menu::updateItemColors() {
    for (size_t i = 0; i < menuItems.size(); ++i) {  // size_t (page 173)
        if (static_cast<int>(i) == selectedItem) {    // Conversion explicite (page 175)
            menuItems[i].setFillColor(sf::Color::Yellow);
        }
        else {
            menuItems[i].setFillColor(sf::Color::White);
        }
    }
}

// ------------------------------------------------------------------
// Initialisation des items du menu
// ------------------------------------------------------------------
void Menu::initMenuItems() {
    // Tableau des noms d'items (page 92-96 pour les tableaux)
    const char* items[] = {
        "> JOUEUR - MODE JOUR <",
        "> JOUEUR - MODE NUIT <",
        "> A PROPOS <",
        "> QUITTER <"
    };
    const int nbItems = 4;  // Nombre d'items

    menuItems.reserve(nbItems);  // Reservation de la memoire (page 105-106)

    for (int i = 0; i < nbItems; ++i) {
        sf::Text text;

        // Application de la police
        FontManager::appliquerPolice(text, "default");

        // Configuration du texte
        text.setString(items[i]);
        text.setCharacterSize(MENU_SIZE);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);

        // Centrage du texte
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        text.setPosition(GameConstants::SCREEN_WIDTH / 2.0f,
            MENU_START_Y + i * MENU_SPACING);

        menuItems.push_back(text);  // Ajout au vecteur (page 105)
    }

    // Selection du premier item
    updateItemColors();
}

// ------------------------------------------------------------------
// Initialisation du texte "A propos"
// ------------------------------------------------------------------
void Menu::initAboutText() {
    // Utilisation de l'operateur += pour la concatenation (page 157)
    string aboutString = "==================== JEU DE CACHETTE ====================\n\n";
    aboutString += "OBJECTIF: Atteindre la fin du niveau avant la fin du temps!\n\n";
    aboutString += "CONTROLES:\n";
    aboutString += "  fleche droite ou D : Courir vers la droite\n";
    aboutString += "  fleche gauche ou A : Courir vers la gauche\n";
    aboutString += "  fleche haut ou ESPACE : Sauter (double saut possible!)\n";
    aboutString += "  ESC : Pause / Fermer\n\n";
    aboutString += "MODE JOUR: Ennemis normaux\n";
    aboutString += "MODE NUIT: Ennemis speciaux (7 types!)\n\n";
    aboutString += "POWER-UPS:\n";
    aboutString += "  Grise : Grandir\n";
    aboutString += "  Jaune : Speed boost\n";
    aboutString += "  Rouge : Soin\n\n";
    aboutString += "==========================================================\n";
    aboutString += "   Appuyez sur ECHAP pour fermer";

    aboutText.setString(aboutString);
    aboutText.setCharacterSize(ABOUT_SIZE);
    aboutText.setFillColor(sf::Color::White);

    // Application de la police
    FontManager::appliquerPolice(aboutText, "default");

    aboutText.setPosition(50.0f, 100.0f);
}

// ------------------------------------------------------------------
// Gestion des entrees clavier
// ------------------------------------------------------------------
void Menu::handleInput() {
    // Affichage de la section "A propos"
    if (showAbout) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            showAbout = false;
            sf::sleep(sf::milliseconds(200));  // Anti-rebond
        }
        return;
    }

    // Navigation vers le haut
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && selectedItem > 0) {
        selectedItem--;
        updateItemColors();
        sf::sleep(sf::milliseconds(150));  // Anti-rebond
    }

    // Navigation vers le bas
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && selectedItem < 3) {
        selectedItem++;
        updateItemColors();
        sf::sleep(sf::milliseconds(150));  // Anti-rebond
    }

    // Selection d'un item
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        if (selectedItem == 2) {  // Option "A PROPOS"
            showAbout = true;
            sf::sleep(sf::milliseconds(200));  // Anti-rebond
        }
    }
}

// ------------------------------------------------------------------
// Rendu du menu
// ------------------------------------------------------------------
void Menu::render(sf::RenderWindow& window) {
    // Affichage de l'image de fond (si chargée)
    if (backgroundTexture.getSize().x > 0) {
        window.draw(backgroundSprite);
    }
    else {
        // Sinon, afficher le fond noir
        window.draw(background);
    }

    // Affichage de la section "A propos"
    if (showAbout) {
        window.draw(aboutText);
        return;
    }

    // Affichage du titre
    window.draw(title);

    // Affichage des items du menu
    for (vector<sf::Text>::const_iterator it = menuItems.begin();
        it != menuItems.end(); ++it) {  // Iterateur const (page 114-115)
        window.draw(*it);
    }
}

// ------------------------------------------------------------------
// Reinitialisation du menu
// ------------------------------------------------------------------
void Menu::reset() {
    selectedItem = 0;
    showAbout = false;
    updateItemColors();
}