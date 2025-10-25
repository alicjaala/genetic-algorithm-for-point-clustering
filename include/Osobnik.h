#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "GroupingEvaluator.h"

using namespace std;

namespace NGroupingChallenge {
    class CGroupingEvaluator;
}



class Osobnik {

private:
	vector<int> genotyp;
	double przystosowanie;
	mt19937 generator;

public:

	Osobnik(int ile_genow, int max_zakres, mt19937& generator);
	double getPrzystosowanie();
	void setPrzystosowanie(double przystosowanie);
	vector<int> getGenotyp();
	double obliczPrzystosowanie(NGroupingChallenge::CGroupingEvaluator& evaluator);
	double obliczPrzystosowanie();
	pair<Osobnik, Osobnik> krzyzuj(const Osobnik& drugi, double praw_krzyzowania, mt19937& generator);
	void mutuj(double praw_mutacji, int max_zakres);

	void wyswietlGenotyp();
};