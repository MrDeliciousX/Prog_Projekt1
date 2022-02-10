#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include "spis.h"

using namespace std;

int rng(int a, int b) //losowanie liczb w razie jakby co
{
    random_device r;
    mt19937 generator(r());
    uniform_int_distribution<int> dist(a, b);
    return dist(generator);
}

void glowne_menu()
{
    cout << "lista gier do wyboru:\n";
    cout << "1. kamien papier nozyce\n";
    cout << "2. kolko i krzyzyk\n";
    
    cout << "\n0. koniec programu\n";
    
    int wybor = 0;
    cin >> wybor;
    switch (wybor)
    {
        case 0:
            exit(0);
        case 1:
            k_p_n();
            break;
        case 2:
            k_i_k();
            break;
        default:
            cout << "Error\n";
            break;
    }
}

void test_pliku(string nazwaPliku) //moze sie przydac
{
    fstream plik;
    plik.open(nazwaPliku, ios::out);
    if(!plik.good())
    {
        cout << "Error\n";
    }
    plik.close();
    plik.open(nazwaPliku, ios::in);
    if(!plik.good())
    {
        cout << "Error\n";
    }
    plik.close();
}
