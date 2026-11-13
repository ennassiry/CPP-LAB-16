
#include <iostream>
#include <string>
using namespace std;

class Configuration {

private:

    // Attributs prives
    string cheminFichier;
    string utilisateur;
    string motDePasse;

    // 1. Constructeur prive
    Configuration() {
        cheminFichier = "C:/application/config.txt";
        utilisateur = "admin";
        motDePasse = "123456";
    }

public:

    // 2. Methode statique getInstance()
    static Configuration& getInstance() {

        static Configuration instance;

        return instance;
    }

    // 3. Supprimer le constructeur de copie
    Configuration(const Configuration&) = delete;

    // Supprimer l'operateur d'affectation
    Configuration& operator=(const Configuration&) = delete;

    // Modifier les parametres
    void modifierParametres(
        string chemin,
        string user,
        string password
    ) {
        cheminFichier = chemin;
        utilisateur = user;
        motDePasse = password;
    }

    // Afficher les parametres
    void afficherParametres() const {

        cout << "===== CONFIGURATION =====" << endl;

        cout << "Chemin : " << cheminFichier << endl;
        cout << "Utilisateur : " << utilisateur << endl;
        cout << "Mot de passe : " << motDePasse << endl;
    }
};

// =====================================
// Programme principal
// =====================================
int main() {

    // Acceder a l'instance Singleton
    Configuration& config1 = Configuration::getInstance();

    config1.afficherParametres();

    cout << "\nModification des parametres..." << endl;

    config1.modifierParametres(
        "D:/projet/config.txt",
        "simo",
        "pass123"
    );

    config1.afficherParametres();

    // Deuxieme acces a la meme instance
    Configuration& config2 = Configuration::getInstance();

    cout << "\nVerification Singleton :" << endl;

    if (&config1 == &config2) {
        cout << "Les deux references pointent vers le meme objet."
             << endl;
    }

    return 0;
}
