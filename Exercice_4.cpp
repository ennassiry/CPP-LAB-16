
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ===================================
// 1. Interface StrategieTri
// ===================================

class StrategieTri {
public:
    virtual void trier(vector<string>& donnees) = 0;

    virtual ~StrategieTri() {}
};

// ===================================
// 2. Strategie : Tri croissant
// ===================================

class TriCroissant : public StrategieTri {
public:
    void trier(vector<string>& donnees) override {
        sort(donnees.begin(), donnees.end());
    }
};

// ===================================
// 3. Strategie : Tri decroissant
// ===================================

class TriDecroissant : public StrategieTri {
public:
    void trier(vector<string>& donnees) override {
        sort(donnees.begin(),
             donnees.end(),
             greater<string>());
    }
};

// ===================================
// 4. Strategie : Tri par longueur
// ===================================

class TriParLongueur : public StrategieTri {
public:
    void trier(vector<string>& donnees) override {
        sort(donnees.begin(), donnees.end(),
            [](const string& a, const string& b) {
                return a.length() < b.length();
            }
        );
    }
};

// ===================================
// 5. GestionnaireTri (Contexte)
// ===================================

class GestionnaireTri {
private:
    StrategieTri* strategie;

public:
    GestionnaireTri(StrategieTri* s)
        : strategie(s) {}

    void changerStrategie(StrategieTri* nouvelleStrategie) {
        strategie = nouvelleStrategie;
    }

    void executerTri(vector<string>& donnees) {
        if (strategie == nullptr) {
            throw runtime_error("Aucune strategie !");
        }

        strategie->trier(donnees);
    }
};

// ===================================
// 6. Fonction d'affichage
// ===================================

void afficher(const vector<string>& donnees) {
    for (const string& mot : donnees) {
        cout << mot << " ";
    }
    cout << endl;
}

// ===================================
// 7. Programme principal
// ===================================

int main() {

    vector<string> mots = {
        "Orange", "Chat", "Banane", "Kiwi", "Pomme"
    };

    // Creation des strategies
    TriCroissant croissant;
    TriDecroissant decroissant;
    TriParLongueur longueur;

    // Creation du gestionnaire
    GestionnaireTri gestionnaire(&croissant);

    cout << "Vecteur initial : ";
    afficher(mots);

    // Tri croissant
    cout << "\n--- Tri croissant ---" << endl;
    gestionnaire.changerStrategie(&croissant);
    gestionnaire.executerTri(mots);
    afficher(mots);

    // Tri decroissant
    cout << "\n--- Tri decroissant ---" << endl;
    gestionnaire.changerStrategie(&decroissant);
    gestionnaire.executerTri(mots);
    afficher(mots);

    // Tri par longueur
    cout << "\n--- Tri par longueur ---" << endl;
    gestionnaire.changerStrategie(&longueur);
    gestionnaire.executerTri(mots);
    afficher(mots);

    return 0;
}
