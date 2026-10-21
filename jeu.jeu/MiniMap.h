#ifndef MINIMAP_H
#define MINIMAP_H

#include <SFML/Graphics.hpp>

/**
 * Classe MiniMap
 * Concept: Encapsulation (page 84-88)
 * Role: Afficher une carte miniature du niveau avec la position du joueur
 * Note: Utilise des formes geometriques (pas de ) pour rester lisible
 */
class MiniMap {
private:
    // Attributs prives (encapsulation, page 84-88)
    sf::RectangleShape mapBackground;   // Fond de la mini-map
    sf::CircleShape playerDot;          // Point representant le joueur
    sf::RectangleShape progressBar;     // Barre de progression
    sf::CircleShape finishDot;          // Point representant l'arrivee

    float worldWidth;                   // Largeur totale du monde
    float worldHeight;                  // Hauteur totale du monde
    float mapWidth;                     // Largeur de la mini-map
    float mapHeight;                    // Hauteur de la mini-map
    sf::Vector2f mapPosition;           // Position de la mini-map

    // Couleurs (constantes)
    static const sf::Color BACKGROUND_COLOR;
    static const sf::Color OUTLINE_COLOR;
    static const sf::Color PLAYER_COLOR;
    static const sf::Color FINISH_COLOR;
    static const sf::Color PROGRESS_COLOR;

    // Methodes privees
    void updatePlayerDotPosition(const sf::Vector2f& playerPos);  // Correction: ajout du parametre
    void updateProgressBar(float playerX);                        // Correction: ajout du parametre

public:
    // Constructeurs (page 45-56)
    MiniMap();                          // Constructeur par defaut
    MiniMap(const MiniMap& autre);      // Constructeur de copie

    // Destructeur (page 57-60)
    ~MiniMap();

    // Operateur d'affectation (page 31-42)
    MiniMap& operator=(const MiniMap& autre);

    // Methodes publiques
    void update(sf::Vector2f playerPosition, float worldW, float worldH);
    void render(sf::RenderWindow& window);
    void reset();                       // Reinitialiser la mini-map

    // Mutateurs (setters)
    void setMapPosition(float x, float y);
    void setMapSize(float w, float h);
    void setWorldSize(float w, float h);

    // Accesseurs (getters) - methodes const (page 25-26)
    sf::Vector2f getMapPosition() const { return mapPosition; }
    float getMapWidth() const { return mapWidth; }
    float getMapHeight() const { return mapHeight; }
    float getWorldWidth() const { return worldWidth; }
    float getWorldHeight() const { return worldHeight; }

    // Verification
    bool isPointInside(sf::Vector2f point) const;
};

#endif