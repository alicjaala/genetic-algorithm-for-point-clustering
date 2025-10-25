#pragma once
#include <iostream>
#include <vector>
#include "Osobnik.h"
#include <random>

using namespace std;

class AlgorytmGenetyczny {

private:
	vector<Osobnik> populacja;
	int rozmiar_populacji;
	double praw_krzyzowania;
	double praw_mutacji;
	int liczba_pokolen;
	mt19937 generator;
	int max_zakres;


public:
	AlgorytmGenetyczny(int rozmiar_populacji, double praw_krzyzowania, double praw_mutacji, int liczba_pokolen, unsigned int seed, int ile_genow, int max_zakres);
	void ocenPopulacje();
	void krzyzowanie();
	void mutowanie();

	void wyswietlPopulacje();
};
