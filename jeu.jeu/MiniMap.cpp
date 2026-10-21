#include "MiniMap.h"
#include "Config.h"
#include <iostream>

using namespace std;  // Espace de nom std (page 182-183)

// ------------------------------------------------------------------
// Initialisation des membres statiques const (page 25-26)
// ------------------------------------------------------------------
const sf::Color MiniMap::BACKGROUND_COLOR = sf::Color(0, 0, 0, 180);   // Noir transparent
const sf::Color MiniMap::OUTLINE_COLOR = sf::Color(255, 255, 255);      // Blanc
const sf::Color MiniMap::PLAYER_COLOR = sf::Color(255, 255, 0);         // Jaune
const sf::Color MiniMap::FINISH_COLOR = sf::Color(255, 0, 0);           // Rouge
const sf::Color MiniMap::PROGRESS_COLOR = sf::Color(50, 255, 50);       // Vert

// ------------------------------------------------------------------
// Constructeur par defaut (page 45-46, 51-53)
// Utilisation de la liste d'initialisation (page 48-50)
// ------------------------------------------------------------------
MiniMap::MiniMap()
    : worldWidth(GameConstants::WORLD_WIDTH)
    , worldHeight(GameConstants::WORLD_HEIGHT)
    , mapWidth(180.0f)
    , mapHeight(100.0f)
    , mapPosition(10.0f, 10.0f) {

    // ------------------------------------------------------------------
    // Configuration du fond de la mini-map (page 73-74)
    // ------------------------------------------------------------------
    mapBackground.setSize(sf::Vector2f(mapWidth, mapHeight));
    mapBackground.setFillColor(BACKGROUND_COLOR);
    mapBackground.setOutlineColor(OUTLINE_COLOR);
    mapBackground.setOutlineThickness(1.0f);
    mapBackground.setPosition(mapPosition);

    // ------------------------------------------------------------------
    // Configuration du point representant le joueur
    // ------------------------------------------------------------------
    playerDot.setRadius(4.0f);
    playerDot.setFillColor(PLAYER_COLOR);
    playerDot.setOrigin(4.0f, 4.0f);  // Centre du cercle (page 48-50)

    // ------------------------------------------------------------------
    // Configuration du point representant l'arrivee
    // ------------------------------------------------------------------
    finishDot.setRadius(5.0f);
    finishDot.setFillColor(FINISH_COLOR);
    finishDot.setOrigin(5.0f, 5.0f);  // Centre du cercle

    // ------------------------------------------------------------------
    // Configuration de la barre de progression
    // ------------------------------------------------------------------
    progressBar.setSize(sf::Vector2f(0.0f, 6.0f));
    progressBar.setFillColor(PROGRESS_COLOR);
    progressBar.setPosition(mapPosition.x, mapPosition.y + mapHeight + 8.0f);
}

// ------------------------------------------------------------------
// Constructeur de copie (page 54-56)
// ------------------------------------------------------------------
MiniMap::MiniMap(const MiniMap& autre) {
    // Copie des attributs (page 54-56)
    this->mapBackground = autre.mapBackground;
    this->playerDot = autre.playerDot;
    this->progressBar = autre.progressBar;
    this->finishDot = autre.finishDot;
    this->worldWidth = autre.worldWidth;
    this->worldHeight = autre.worldHeight;
    this->mapWidth = autre.mapWidth;
    this->mapHeight = autre.mapHeight;
    this->mapPosition = autre.mapPosition;
}

// ------------------------------------------------------------------
// Destructeur (page 57-60)
// ------------------------------------------------------------------
MiniMap::~MiniMap() {
    // Rien a liberer dynamiquement
}

// ------------------------------------------------------------------
// Operateur d'affectation (page 31-42)
// ------------------------------------------------------------------
MiniMap& MiniMap::operator=(const MiniMap& autre) {
    // Verification d'auto-affectation (page 66-67)
    if (this != &autre) {
        this->mapBackground = autre.mapBackground;
        this->playerDot = autre.playerDot;
        this->progressBar = autre.progressBar;
        this->finishDot = autre.finishDot;
        this->worldWidth = autre.worldWidth;
        this->worldHeight = autre.worldHeight;
        this->mapWidth = autre.mapWidth;
        this->mapHeight = autre.mapHeight;
        this->mapPosition = autre.mapPosition;
    }
    return *this;  // Retourne l'objet courant (page 66-67)
}

// ------------------------------------------------------------------
// Mise a jour de la position du joueur sur la mini-map
// ------------------------------------------------------------------
void MiniMap::updatePlayerDotPosition(const sf::Vector2f& playerPos) {
    // Calcul des ratios (utilisation de l'operateur ternaire, page 31-42)
    float ratioX = (worldWidth > 0) ? (playerPos.x / worldWidth) : 0.0f;
    float ratioY = (worldHeight > 0) ? (playerPos.y / worldHeight) : 0.0f;

    // Clamp des valeurs entre 0 et 1
    if (ratioX < 0.0f) ratioX = 0.0f;
    if (ratioX > 1.0f) ratioX = 1.0f;
    if (ratioY < 0.0f) ratioY = 0.0f;
    if (ratioY > 1.0f) ratioY = 1.0f;

    // Calcul de la position sur la mini-map
    float dotX = mapPosition.x + ratioX * mapWidth;
    float dotY = mapPosition.y + ratioY * mapHeight;
    playerDot.setPosition(dotX, dotY);
}

// ------------------------------------------------------------------
// Mise a jour de la barre de progression
// ------------------------------------------------------------------
void MiniMap::updateProgressBar(float playerX) {
    // Calcul de la progression (utilisation de l'operateur ternaire)
    float progress = (worldWidth > 0) ? (playerX / worldWidth) : 0.0f;

    // Clamp entre 0 et 1
    if (progress < 0.0f) progress = 0.0f;
    if (progress > 1.0f) progress = 1.0f;

    // Mise a jour de la largeur de la barre
    progressBar.setSize(sf::Vector2f(progress * mapWidth, 6.0f));
}

// ------------------------------------------------------------------
// Mise a jour complete de la mini-map
// ------------------------------------------------------------------
void MiniMap::update(sf::Vector2f playerPosition, float worldW, float worldH) {
    // Mise a jour des dimensions du monde (page 133-134 pour reference)
    if (worldW > 0) worldWidth = worldW;
    if (worldH > 0) worldHeight = worldH;

    // Mise a jour des elements
    updatePlayerDotPosition(playerPosition);
    updateProgressBar(playerPosition.x);

    // Position du point d'arrivee (a droite de la mini-map)
    finishDot.setPosition(mapPosition.x + mapWidth - 10.0f,
        mapPosition.y + mapHeight / 2.0f);
}

// ------------------------------------------------------------------
// Rendu de la mini-map
// ------------------------------------------------------------------
void MiniMap::render(sf::RenderWindow& window) {
    // Dessin du fond
    window.draw(mapBackground);

    // Dessin de la barre de progression
    window.draw(progressBar);

    // Dessin du point d'arrivee
    window.draw(finishDot);

    // Dessin du point du joueur
    window.draw(playerDot);
}

// ------------------------------------------------------------------
// Reinitialisation de la mini-map
// ------------------------------------------------------------------
void MiniMap::reset() {
    // Reinitialisation de la barre de progression
    progressBar.setSize(sf::Vector2f(0.0f, 6.0f));

    // Reinitialisation de la position du joueur
    playerDot.setPosition(mapPosition);
}

// ------------------------------------------------------------------
// Definition de la position de la mini-map
// ------------------------------------------------------------------
void MiniMap::setMapPosition(float x, float y) {
    mapPosition = sf::Vector2f(x, y);
    mapBackground.setPosition(mapPosition);
    progressBar.setPosition(mapPosition.x, mapPosition.y + mapHeight + 8.0f);
}

// ------------------------------------------------------------------
// Definition de la taille de la mini-map
// ------------------------------------------------------------------
void MiniMap::setMapSize(float w, float h) {
    mapWidth = w;
    mapHeight = h;
    mapBackground.setSize(sf::Vector2f(mapWidth, mapHeight));
}

// ------------------------------------------------------------------
// Definition de la taille du monde
// ------------------------------------------------------------------
void MiniMap::setWorldSize(float w, float h) {
    if (w > 0) worldWidth = w;
    if (h > 0) worldHeight = h;
}

// ------------------------------------------------------------------
// Verification si un point est a l'interieur de la mini-map
// ------------------------------------------------------------------
bool MiniMap::isPointInside(sf::Vector2f point) const {
    // Utilisation de l'operateur de comparaison (page 31-42)
    return (point.x >= mapPosition.x &&
        point.x <= mapPosition.x + mapWidth &&
        point.y >= mapPosition.y &&
        point.y <= mapPosition.y + mapHeight);
}