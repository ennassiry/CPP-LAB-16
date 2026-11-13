
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

using namespace std;

// 1. Classe abstraite
class Forme {
public:
    virtual void afficher() const = 0;

    virtual ~Forme() {}
};

// 2. Classes concretes

class Cercle : public Forme {
public:
    void afficher() const override {
        cout << "Je suis un Cercle." << endl;
    }
};

class Carre : public Forme {
public:
    void afficher() const override {
        cout << "Je suis un Carre." << endl;
    }
};

class Triangle : public Forme {
public:
    void afficher() const override {
        cout << "Je suis un Triangle." << endl;
    }
};

// 3. Fabrique
class FabriqueForme {
public:
    static unique_ptr<Forme> creerForme(const string& type) {

        if (type == "cercle") {
            return make_unique<Cercle>();
        }

        else if (type == "carre") {
            return make_unique<Carre>();
        }

        else if (type == "triangle") {
            return make_unique<Triangle>();
        }

        else {
            throw invalid_argument("Type de forme inconnu !");
        }
    }
};

// 4. Programme principal
int main() {

    try {
        unique_ptr<Forme> f1 =
            FabriqueForme::creerForme("cercle");

        unique_ptr<Forme> f2 =
            FabriqueForme::creerForme("carre");

        unique_ptr<Forme> f3 =
            FabriqueForme::creerForme("triangle");

        f1->afficher();
        f2->afficher();
        f3->afficher();
    }

    catch (const exception& e) {
        cout << "Erreur : " << e.what() << endl;
    }

    return 0;
}
