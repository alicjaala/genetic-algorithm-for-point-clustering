#include "AlgorytmGenetyczny.h"
#include <iostream>

using namespace std;

int main() {
    // Parametry algorytmu genetycznego
    int rozmiar_populacji = 10;      // Liczba osobnik�w w populacji
    double praw_krzyzowania = 0.8;   // Prawdopodobie�stwo krzy�owania
    double praw_mutacji = 0.1;       // Prawdopodobie�stwo mutacji
    int liczba_pokolen = 5;          // Liczba pokole� do symulacji
    unsigned int seed = 12345;          // Ziarno generatora liczb losowych
    int ile_genow = 5;               // Liczba gen�w w ka�dym osobniku
    int maks_zakres = 4;            // Maksymalny zakres warto�ci gen�w

    // Tworzenie obiektu algorytmu genetycznego
    AlgorytmGenetyczny algorytm(rozmiar_populacji, praw_krzyzowania, praw_mutacji, liczba_pokolen, seed, ile_genow, maks_zakres);

    // Symulacja algorytmu genetycznego przez wszystkie pokolenia
    for (int pokolenie = 0; pokolenie < liczba_pokolen; pokolenie++) {
        cout << "Pokolenie " << pokolenie + 1 << ":\n";

        // Ocenianie populacji
        algorytm.ocenPopulacje();

        // Wy�wietlanie stanu populacji po ocenie
        algorytm.wyswietlPopulacje();

        // Krzy�owanie populacji
        algorytm.krzyzowanie();

        // Mutowanie populacji
        algorytm.mutowanie();

        // Wy�wietlanie stanu populacji po mutacjach
        cout << "Populacja po mutacji:\n";
        algorytm.wyswietlPopulacje();

        cout << "\n-------------------------------------------------\n";
    }

    return 0;
}
