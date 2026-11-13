
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ==================================
// 1. Interface Observateur
// ==================================

class Observateur {
public:
    virtual void mettreAJour(
        float temperature,
        float humidite,
        float pression
    ) = 0;

    virtual ~Observateur() {}
};

// ==================================
// 2. Observateur Temperature
// ==================================

class AffichageTemperature : public Observateur {
public:
    void mettreAJour(float temperature,
                     float humidite,
                     float pression) override {

        cout << "Temperature : "
             << temperature << " C" << endl;
    }
};

// ==================================
// 3. Observateur Humidite
// ==================================

class AffichageHumidite : public Observateur {
public:
    void mettreAJour(float temperature,
                     float humidite,
                     float pression) override {

        cout << "Humidite : "
             << humidite << " %" << endl;
    }
};

// ==================================
// 4. Observateur Pression
// ==================================

class AffichagePression : public Observateur {
public:
    void mettreAJour(float temperature,
                     float humidite,
                     float pression) override {

        cout << "Pression : "
             << pression << " hPa" << endl;
    }
};

// ==================================
// 5. Sujet : StationMeteo
// ==================================

class StationMeteo {
private:
    float temperature;
    float humidite;
    float pression;

    vector<Observateur*> observateurs;

public:
    StationMeteo()
        : temperature(0),
          humidite(0),
          pression(0) {}

    // Inscrire un observateur
    void ajouterObservateur(Observateur* obs) {
        if (obs != nullptr &&
            find(observateurs.begin(),
                 observateurs.end(), obs) == observateurs.end()) {

            observateurs.push_back(obs);
        }
    }

    // Desinscrire un observateur
    void supprimerObservateur(Observateur* obs) {
        observateurs.erase(
            remove(observateurs.begin(),
                   observateurs.end(), obs),
            observateurs.end()
        );
    }

    // Envoyer les notifications
    void notifierObservateurs() {
        for (Observateur* obs : observateurs) {
            obs->mettreAJour(
                temperature,
                humidite,
                pression
            );
        }
    }

    // Modifier les donnees
    void modifierDonnees(float t, float h, float p) {
        temperature = t;
        humidite = h;
        pression = p;

        cout << "\n--- Nouvelles donnees meteo ---" << endl;

        notifierObservateurs();
    }
};

// ==================================
// 6. Fonction principale
// ==================================

int main() {

    StationMeteo station;

    // Creation des affichages
    AffichageTemperature affichageTemp;
    AffichageHumidite affichageHum;
    AffichagePression affichagePress;

    // Inscription des observateurs
    station.ajouterObservateur(&affichageTemp);
    station.ajouterObservateur(&affichageHum);
    station.ajouterObservateur(&affichagePress);

    // Premiere modification
    station.modifierDonnees(25, 60, 1013);

    // Deuxieme modification
    station.modifierDonnees(30, 70, 1010);

    // Suppression d'un observateur
    station.supprimerObservateur(&affichageHum);

    cout << "\n--- Apres suppression de l'affichage humidite ---"
         << endl;

    // Troisieme modification
    station.modifierDonnees(22, 55, 1015);

    return 0;
}
