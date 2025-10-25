#include "AlgorytmGenetyczny.h"
#include <iostream>

using namespace std;

AlgorytmGenetyczny::AlgorytmGenetyczny(int rozmiar_populacji, double praw_krzyzowania, double praw_mutacji, int liczba_pokolen, unsigned int seed, int ile_genow, int maks_zakres) {
	this->rozmiar_populacji = rozmiar_populacji;
	this->praw_krzyzowania = praw_krzyzowania;
	this->praw_mutacji = praw_mutacji;
	this->liczba_pokolen = liczba_pokolen;
	this->generator = mt19937(seed);
	this->max_zakres = maks_zakres;

	populacja.reserve(rozmiar_populacji);
	for (int i = 0; i < rozmiar_populacji; i++) {
		populacja.emplace_back(Osobnik(ile_genow, maks_zakres, generator));
	}
}



void AlgorytmGenetyczny::ocenPopulacje() {
	for (int i = 0; i < populacja.size(); i++) {
		double przystosowanie = populacja[i].obliczPrzystosowanie();
		populacja[i].setPrzystosowanie(przystosowanie);
		
	}
}

void AlgorytmGenetyczny::wyswietlPopulacje() {
	for (int i = 0; i < populacja.size(); i++) {
		populacja[i].wyswietlGenotyp();
	}
}

void AlgorytmGenetyczny::krzyzowanie() {
	vector<Osobnik> nowa_populacja;

	uniform_int_distribution<int> rozklad_losowania(0, rozmiar_populacji - 1);
	uniform_real_distribution<double> rozklad_praw(0.0, 1.0);

	while (nowa_populacja.size() < rozmiar_populacji) {
		int indeks1 = rozklad_losowania(generator);
		int indeks2 = rozklad_losowania(generator);

		Osobnik& rodzic1 = (populacja[indeks1].getPrzystosowanie() > populacja[indeks2].getPrzystosowanie())
			? populacja[indeks1]
			: populacja[indeks2];

		indeks1 = rozklad_losowania(generator);
		indeks2 = rozklad_losowania(generator);

		Osobnik& rodzic2 = (populacja[indeks1].getPrzystosowanie() > populacja[indeks2].getPrzystosowanie())
			? populacja[indeks1]
			: populacja[indeks2];

		pair<Osobnik, Osobnik> dzieci = rodzic1.krzyzuj(rodzic2, praw_krzyzowania, generator);

		nowa_populacja.push_back(dzieci.first);
		
		if (nowa_populacja.size() < rozmiar_populacji) {
			nowa_populacja.push_back(dzieci.second);
		}
	}
	populacja = move(nowa_populacja);

}

void AlgorytmGenetyczny::mutowanie() {
	for (int i = 0; i < populacja.size(); i++) {
		populacja[i].mutuj(praw_mutacji, max_zakres);
	}
}