#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <iostream>

/**
 * Classe FontManager (Gestionnaire de polices)
 * Concept: Classe avec membres statiques (page 84-85)
 * Concept: Singleton design pattern (vu dans les concepts de classes)
 * Role: Gerer le chargement et l'acces aux polices de caracteres
 */
class FontManager {
private:
    // Attributs statiques prives (encapsulation, page 84-88)
    static std::map<std::string, sf::Font> fonts;  // Conteneur STL (page 107-117)
    static bool isInitialized;                     // Etat d'initialisation
    static std::string defaultFontPath;            // Chemin de la police par defaut

    // Constructeur prive pour empecher l'instanciation (page 45-46)
    FontManager();
    ~FontManager();

    // Interdiction du constructeur de copie et de l'operateur d'affectation (page 54-56, 31-42)
    FontManager(const FontManager& autre);
    FontManager& operator=(const FontManager& autre);

public:
    /**
     * Methode statique pour charger une police
     * Parametres: const std::string& (passage par reference constante, page 50)
     * Retour: bool (true si succes, false sinon)
     */
    static bool chargerPolice(const std::string& nom, const std::string& cheminFichier);

    /**
     * Methode statique pour obtenir une police
     * Retour: sf::Font& (reference, page 133-134)
     * Note: Methode const (ne modifie pas les attributs, page 25-26)
     */
    static const sf::Font& getPolice(const std::string& nom);

    /**
     * Methode statique pour obtenir la police par defaut
     * Retour: sf::Font& (reference constante)
     */
    static const sf::Font& getPoliceDefaut();

    /**
     * Methode statique pour verifier si une police existe
     * Methode const (page 25-26)
     */
    static bool existePolice(const std::string& nom);

    /**
     * Methode statique pour supprimer une police
     */
    static void supprimerPolice(const std::string& nom);

    /**
     * Methode statique pour vider toutes les polices
     */
    static void viderToutesLesPolices();

    /**
     * Methode statique pour obtenir le nombre de polices chargees
     * Retour: size_t (type defini par l'utilisateur, page 173)
     */
    static size_t getNombrePolices();

    /**
     * Methode statique pour definir le chemin de la police par defaut
     */
    static void setPoliceDefautPath(const std::string& chemin);

    /**
     * Methode statique pour appliquer une police a un texte
     * Parametre: sf::Text& (reference, page 133-134)
     */
    static void appliquerPolice(sf::Text& texte, const std::string& nomPolice = "");

    /**
     * Methode statique pour initialiser le gestionnaire
     * Charge la police par defaut si disponible
     */
    static void initialiser();

    /**
     * Methode statique pour verifier si le gestionnaire est initialise
     */
    static bool estInitialise();
};

#endif