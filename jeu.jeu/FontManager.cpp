#include "FontManager.h"

using namespace std;  // Espace de nom std (page 182-183)

// ------------------------------------------------------------------
// Initialisation des membres statiques (page 84-85)
// ------------------------------------------------------------------
map<string, sf::Font> FontManager::fonts;
bool FontManager::isInitialized = false;
string FontManager::defaultFontPath = "fonts/Roboto.ttf";  

// ------------------------------------------------------------------
// Constructeur prive (page 45-46)
// ------------------------------------------------------------------
FontManager::FontManager() {
    // Ne rien faire - constructeur prive
}

// ------------------------------------------------------------------
// Destructeur prive (page 57-60)
// ------------------------------------------------------------------
FontManager::~FontManager() {
    // Ne rien faire - destructeur prive
}

// ------------------------------------------------------------------
// Constructeur de copie prive (page 54-56)
// ------------------------------------------------------------------
FontManager::FontManager(const FontManager& autre) {
    // Ne rien faire - constructeur de copie prive
}

// ------------------------------------------------------------------
// Operateur d'affectation prive (page 31-42)
// ------------------------------------------------------------------
FontManager& FontManager::operator=(const FontManager& autre) {
    // Ne rien faire - operateur d'affectation prive
    return *this;  // Retourne l'objet courant (page 66-67)
}

// ------------------------------------------------------------------
// Chargement d'une police
// ------------------------------------------------------------------
bool FontManager::chargerPolice(const string& nom, const string& cheminFichier) {
    sf::Font nouvellePolice;

    // Tentative de chargement
    if (nouvellePolice.loadFromFile(cheminFichier)) {
        // Stocker la police dans la map
        fonts[nom] = nouvellePolice;

        // Affichage de confirmation (page 179-181 pour cout)
        cout << "Police chargee avec succes: " << nom
            << " depuis " << cheminFichier << endl;
        return true;
    }

    // Affichage d'erreur (page 179-181 pour cerr)
    cerr << "Erreur: Impossible de charger la police "
        << nom << " depuis " << cheminFichier << endl;
    return false;
}

// ------------------------------------------------------------------
// Obtention d'une police (retourne une reference constante, page 133-134)
// ------------------------------------------------------------------
const sf::Font& FontManager::getPolice(const string& nom) {
    // Recherche dans la map (page 107-117 pour STL)
    map<string, sf::Font>::const_iterator it = fonts.find(nom);

    if (it != fonts.end()) {
        return it->second;
    }

    // Si la police n'existe pas, on retourne la police par defaut
    cerr << "Attention: Police '" << nom << "' non trouvee!" << endl;
    return getPoliceDefaut();
}

// ------------------------------------------------------------------
// Obtention de la police par defaut
// ------------------------------------------------------------------
const sf::Font& FontManager::getPoliceDefaut() {
    // Recherche de la police "default"
    map<string, sf::Font>::const_iterator it = fonts.find("default");

    if (it != fonts.end()) {
        return it->second;
    }

    // Si aucune police n'est chargee, on cree une police vide statique
    static sf::Font policeVide;
    cerr << "Attention: Aucune police par defaut disponible!" << endl;
    return policeVide;
}

// ------------------------------------------------------------------
// Verification de l'existence d'une police
// ------------------------------------------------------------------
bool FontManager::existePolice(const string& nom) {
    return fonts.find(nom) != fonts.end();
}

// ------------------------------------------------------------------
// Suppression d'une police
// ------------------------------------------------------------------
void FontManager::supprimerPolice(const string& nom) {
    map<string, sf::Font>::iterator it = fonts.find(nom);
    if (it != fonts.end()) {
        fonts.erase(it);
        cout << "Police supprimee: " << nom << endl;
    }
}

// ------------------------------------------------------------------
// Vidage de toutes les polices
// ------------------------------------------------------------------
void FontManager::viderToutesLesPolices() {
    fonts.clear();
    cout << "Toutes les polices ont ete supprimees" << endl;
}

// ------------------------------------------------------------------
// Obtention du nombre de polices chargees
// ------------------------------------------------------------------
size_t FontManager::getNombrePolices() {
    return fonts.size();
}

// ------------------------------------------------------------------
// Definition du chemin de la police par defaut
// ------------------------------------------------------------------
void FontManager::setPoliceDefautPath(const string& chemin) {
    defaultFontPath = chemin;
}

// ------------------------------------------------------------------
// Application d'une police a un texte
// ------------------------------------------------------------------
void FontManager::appliquerPolice(sf::Text& texte, const string& nomPolice) {
    if (nomPolice.empty()) {
        // Utiliser la police par defaut
        if (existePolice("default")) {
            texte.setFont(getPoliceDefaut());
        }
        else if (fonts.size() > 0) {
            // Utiliser la premiere police disponible
            texte.setFont(fonts.begin()->second);
        }
    }
    else {
        // Utiliser la police specifiee
        if (existePolice(nomPolice)) {
            texte.setFont(getPolice(nomPolice));
        }
        else {
            cerr << "Attention: Police '" << nomPolice << "' non trouvee!" << endl;
        }
    }
}

// ------------------------------------------------------------------
// Initialisation du gestionnaire
// ------------------------------------------------------------------
void FontManager::initialiser() {
    if (!isInitialized) {
        // Tentative de chargement de la police par defaut
        if (chargerPolice("default", defaultFontPath)) {
            cout << "Police par defaut chargee avec succes!" << endl;
        }
        else {
            // Tentative avec un chemin alternatif (page 47-48 pour surcharge)
            string altPath = "fonts/Roboto.ttf";
            if (chargerPolice("default", altPath)) {
                cout << "Police par defaut chargee (chemin alternatif)!" << endl;
            }
            else {
                cerr << "Impossible de charger la police par defaut!" << endl;
            }
        }
        isInitialized = true;
    }
}

// ------------------------------------------------------------------
// Verification de l'etat d'initialisation
// ------------------------------------------------------------------
bool FontManager::estInitialise() {
    return isInitialized;
}