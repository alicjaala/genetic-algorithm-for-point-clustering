#include "Osobnik.h"
#include <iostream>

using namespace std;


Osobnik::Osobnik(int ile_genow, int max_zakres, mt19937& generator) {
	przystosowanie = 0.0;
	genotyp.resize(ile_genow);
    this->generator = generator;

	uniform_int_distribution<int> rozklad(1, max_zakres);

	for (int i = 0; i < ile_genow; i++) {
		genotyp[i] = rozklad(generator);
	}
}

double Osobnik::getPrzystosowanie() {
	return przystosowanie;
}

void Osobnik::setPrzystosowanie(double przystosowanie) {
	this->przystosowanie = przystosowanie;
}

vector<int> Osobnik::getGenotyp() {
	return genotyp;
}

double Osobnik::obliczPrzystosowanie(NGroupingChallenge::CGroupingEvaluator& evaluator)
{
    return evaluator.dEvaluate(genotyp);
}


double Osobnik::obliczPrzystosowanie() {
    int liczba_punktow = genotyp.size();

    vector<pair<double, double>> punkty(liczba_punktow);

    uniform_real_distribution<double> rozklad(0.0, 1000.0);
    for (auto& punkt : punkty) {
        punkt.first = rozklad(generator);
        punkt.second = rozklad(generator);
    }

    double suma_odleglosci = 0.0;

    for (int i = 0; i < liczba_punktow; i++) {
        for (int j = i + 1; j < liczba_punktow; j++) {
            if (genotyp[i] == genotyp[j]) {
                double dx = punkty[i].first - punkty[j].first;
                double dy = punkty[i].second - punkty[j].second;
                double odleglosc = sqrt(dx * dx + dy * dy);
                suma_odleglosci += odleglosc;
            }
        }
    }

    return suma_odleglosci;
}


void Osobnik::wyswietlGenotyp() {

	for (int i = 0; i < genotyp.size(); i++) {
		cout << genotyp[i] << " ";
	}
	cout << endl;
}

pair<Osobnik, Osobnik> Osobnik::krzyzuj(const Osobnik& drugiOsobnik, double praw_krzyzowania, mt19937& generator) {

    uniform_real_distribution<double> rozklad_prawdopodobienstwa(0.0, 1.0);
    uniform_int_distribution<int> rozklad_punktu(1, genotyp.size() - 1);

    if (rozklad_prawdopodobienstwa(generator) > praw_krzyzowania) {
        return { *this, drugiOsobnik };
    }

    int punkt_krzyzowania = rozklad_punktu(generator);

    Osobnik dziecko1(*this);
    Osobnik dziecko2(drugiOsobnik);

    for (int i = punkt_krzyzowania; i < genotyp.size(); i++) {
        dziecko1.genotyp[i] = drugiOsobnik.genotyp[i];
        dziecko2.genotyp[i] = genotyp[i];
    }

    return { dziecko1, dziecko2 };
}

void Osobnik::mutuj(double praw_mutacji, int max_zakres) {
    uniform_real_distribution<double> rozklad_mutacji(0.0, 1.0);
    uniform_int_distribution<int> rozklad_genow(1,  max_zakres);

    for (int i = 0; i < genotyp.size(); i++) {
        double czy_mutowac = rozklad_mutacji(generator);
        if (czy_mutowac < praw_mutacji) {
            genotyp[i] = rozklad_genow(generator);
        }
    }
}