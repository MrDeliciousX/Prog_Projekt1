#ifndef spis_h
#define spis_h

//inne
int rng(int a, int b);
void glowne_menu();
void test_pliku(std::string nazwaPliku);

//kamien papier nozyce
void k_p_n();
int ruch_bota_k_p_n(int ostatni, int** macierz_wsk);
void kto_wygral_k_p_n(int bot, int gracz, int* wynik_b, int* wynik_g);
int cala_magia_bota_k_p_n(int poprzedni, int** macierz_wsk);
void uzupelnienie_botowej_magii_k_p_n(int ruch, int poprzedni, int** macierz_wsk);

//kolko i krzyzyk
void k_i_k();
void zerowanie_planszy(char** plansza, int szerokosc, int wysokosc);
void standard_k_i_k(int trudnosc);
void wyswietlanie_mapy_k_i_k(char** plansza, int szerokosc, int wysokosc, bool clean);
int sprawdzenie_warunkow_zwyciestwa(char** plansza, int szerokosc, int wysokosc);
void bot(char** plansza, int szerokosc, int wysokosc, int trudnosc);
    //ruch bota
int wygrac(char** plansza, int szerokosc, int wysokosc);
int blok(char** plansza, int szerokosc, int wysokosc);
int rozg_atak(char** plansza, int szerokosc, int wysokosc);
int rozg_blok(char** plansza, int szerokosc, int wysokosc);
int srodek(char** plansza, int szerokosc, int wysokosc);
int przeciwny_rog(char** plansza, int szerokosc, int wysokosc);
int pusty_rog(char** plansza, int szerokosc, int wysokosc);
int pusty_bok(char** plansza, int szerokosc, int wysokosc);
int ruch_szalenca(char** plansza, int szerokosc, int wysokosc);

#endif /* spis_h */
