#include <iostream>
#include <string>
#include "spis.h"

using namespace std;

void k_i_k()
{
    cout << "Wybrales gre kolko i krzyzyk" << endl;
    cout << "\nJak grac? wpisuj koordynaty wybranego pola, np. A3" << endl;
    cout << "\nWybierz poziom trudnosci 1 - 5, im wiekszy tym trudniejszy" << endl;
    int trudnosc = 5;
    cin >> trudnosc;
    
//    cout << "Jesli chcesz grac na standardowej planszy wpisz 1, jesli na niestandardowej wpisz 2, zeby wrocic do menu wpisz 0" << endl;
//    int wybor = 0;
//    cin >> wybor;
//    switch (wybor)
//    {
//        case 1:
//            standard_k_i_k(trudnosc);
//            break;
//        case 2:
//
//            break;
//        case 0:
//            glowne_menu();
//            break;
//        default:
//            break;
//    }
    if (trudnosc == 0)
    {
        glowne_menu();
    }
    else
    {
        standard_k_i_k(trudnosc);
    }
}

void zerowanie_planszy(char** plansza, int szerokosc, int wysokosc)
{
    for (int i = 0; i < wysokosc; i++)
    {
        for (int j = 0; j < szerokosc; j++)
        {
            plansza[i][j] = ' ';
        }
    }
}

void standard_k_i_k(int trudnosc)
{
    char plansza[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    char* tab_wsk[3];
    for (int i = 0; i < 3; i++)
    {
        tab_wsk[i] = plansza[i];
    }
    char** wsk = tab_wsk;
    
    wyswietlanie_mapy_k_i_k(wsk, 3, 3, 1);
    
    char odpowiedz[6];
    int kolumna = 0;
    int wiersz = 0;
    
    bool koniec = false;
    while (koniec == false)
    {
        cin.getline(odpowiedz, 1024);
        
        if (odpowiedz[0] == '0')
        {
            koniec = true;
        }
        else
        {
            wiersz = odpowiedz[1] - '0';
            kolumna = odpowiedz[0] - 'A';
            if (wiersz < 4 && kolumna < 4 && plansza[wiersz - 1][kolumna] == ' ')
            {
                plansza[wiersz - 1][kolumna] = 'X';
                wyswietlanie_mapy_k_i_k(wsk, 3, 3, 1);
                if ( sprawdzenie_warunkow_zwyciestwa(wsk, 3, 3) != 0 )
                {
                    zerowanie_planszy(wsk, 3, 3);
                    wyswietlanie_mapy_k_i_k(wsk, 3, 3, 0);
                }
                else
                {
                    bot(wsk, 3, 3, trudnosc);
                    wyswietlanie_mapy_k_i_k(wsk, 3, 3, 1);
                    if ( sprawdzenie_warunkow_zwyciestwa(wsk, 3, 3) != 0 )
                    {
                        zerowanie_planszy(wsk, 3, 3);
                        wyswietlanie_mapy_k_i_k(wsk, 3, 3, 0);
                    }
                }
            }
            else if (odpowiedz[0] != 0)
            {
                cout << "To pole jest niewlasciwe" << endl;
            }
        }
        
    }
    k_i_k();
}

void wyswietlanie_mapy_k_i_k(char** plansza ,int szerokosc, int wysokosc, bool clean)
{
    if ( clean == 1 )
    {
        for (int m = 0; m < 100; m++)   //odswiezanie ekranu lvl master
        {
            cout << endl;
        }
    }
    char kolumna = 'A';
    cout << "   | ";
    for (int k = 0; k < szerokosc; k++)
    {
        cout << kolumna << " | ";
        kolumna++;
    }
    cout << endl;
    for (int j = 0; j <= szerokosc; j++)
    {
        cout << "---|";
    }
    cout << endl;
    for (int i = 0; i < wysokosc; i++)
    {
        cout << " " << i + 1 << " |";
        for (int j = 0; j < szerokosc; j++)
        {
            cout << " " << plansza[i][j] << " |";
        }
        cout << endl;
        for (int j = 0; j <= szerokosc; j++)
        {
            cout << "---|";
        }
        cout << endl;
    }
    cout << endl;
}

int sprawdzenie_warunkow_zwyciestwa(char** plansza, int szerokosc, int wysokosc)
{
    //wiersze
    for (int i = 0; i < wysokosc; i++)
    {
        for (int j = 1; j < szerokosc - 1; j++)
        {
            if (plansza[i][j] != ' ' && plansza[i][j - 1] == plansza[i][j] && plansza[i][j] == plansza[i][j + 1])
            {
                if (plansza[i][j] == 'X')
                {
                    cout << "\nWygrywasz!" << endl;
                    //cout << "wiersz " << i + 1<< endl;
                    return 1;
                }
                else if (plansza[i][j] == 'O')
                {
                    cout << "\nPrzegrywasz :(" << endl;
                    //cout << "wiersz " << i + 1<< endl;
                    return 2;
                }
            }
        }
    }
    
    //kolumny
    for (int i = 0; i < szerokosc; i++)
    {
        for (int j = 1; j < wysokosc - 1; j++)
        {
            if (plansza[j][i] != ' ' && plansza[j - 1][i] == plansza[j][i] && plansza[j + 1][i] == plansza[j][i])
            {
                if (plansza[j][i] == 'X')
                {
                    cout << "\nWygrywasz!" << endl;
                    //cout << "kolumna " << i + 1<< endl;
                    return 1;
                }
                else if (plansza[j][i] == 'O')
                {
                    cout << "\nPrzegrywasz :(" << endl;
                    //cout << "kolumna " << i + 1<< endl;
                    return 2;
                }
            }
        }
    }
    
    //skosy
    for (int i = 1; i < wysokosc - 1; i++)
    {
        for (int j = 1; j < szerokosc - 1; j++)
        {
            if (plansza[i][j] != ' ' && plansza[i][j] == plansza[i - 1][j - 1] && plansza[i][j] == plansza[i + 1][j + 1])
            {
                if (plansza[j][i] == 'X')
                {
                    cout << "\nWygrywasz!" << endl;
                    //cout << "skos " << endl;
                    return 1;
                }
                else if (plansza[j][i] == 'O')
                {
                    cout << "\nPrzegrywasz :(" << endl;
                    //cout << "skos " << endl;
                    return 2;
                }
            }
            if (plansza[i][j] != ' ' && plansza[i][j] == plansza[i - 1][j + 1] && plansza[i][j] == plansza[i + 1][j - 1])
            {
                if (plansza[j][i] == 'X')
                {
                    cout << "\nWygrywasz!" << endl;
                    //cout << "skos " << endl;
                    return 1;
                }
                else if (plansza[j][i] == 'O')
                {
                    cout << "\nPrzegrywasz :(" << endl;
                    //cout << "skos " << endl;
                    return 2;
                }
            }
        }
    }
    int puste = 0;
    for (int i = 0; i < szerokosc; i++)
    {
        for (int j = 0; j < wysokosc; j++)
        {
            if (plansza[i][j] == ' ')
            {
                puste++;
            }
        }
    }
    if (puste == 0)
    {
        cout <<"\nRemis" << endl;
        return 1;
    }
    return 0;
}

void bot(char** plansza, int szerokosc, int wysokosc, int trudnosc) //no działaj nooo
{
    int ruch_bota = 0;
    ruch_bota = wygrac(plansza, szerokosc, wysokosc);
    if (ruch_bota == 0 && trudnosc > 1)
    {
        ruch_bota = blok(plansza, szerokosc, wysokosc);
    }
    if (ruch_bota == 0 && trudnosc > 4)
    {
        ruch_bota = rozg_atak(plansza, szerokosc, wysokosc);
    }
    if (ruch_bota == 0 && trudnosc > 4)
    {
        ruch_bota = rozg_blok(plansza, szerokosc, wysokosc);
    }
    if (ruch_bota == 0 && trudnosc > 3)
    {
        ruch_bota = srodek(plansza, szerokosc, wysokosc);
    }
    if (ruch_bota == 0 && trudnosc > 3)
    {
        ruch_bota = przeciwny_rog(plansza, szerokosc, wysokosc);
    }
    if (ruch_bota == 0 && trudnosc > 2)
    {
        ruch_bota = pusty_rog(plansza, szerokosc, wysokosc);
    }
    if (ruch_bota == 0 && trudnosc > 2)
    {
        ruch_bota = pusty_bok(plansza, szerokosc, wysokosc);
    }
    if (ruch_bota == 0)
    {
        ruch_szalenca(plansza, szerokosc, wysokosc);
    }
}

int wygrac(char** plansza, int szerokosc, int wysokosc)
{
    int bot = 0;
    int puste = 0;
    for (int i = 0; i < wysokosc; i++)
    {
        for (int j = 1; j < szerokosc - 1; j++)
        {
            bot = 0;
            puste = 0;
            if (plansza[i][j - 1] == 'O')
                bot++;
            else if (plansza[i][j - 1] == ' ')
                puste++;
            if (plansza[i][j] == 'O')
                bot++;
            else if (plansza[i][j] == ' ')
                puste++;
            if (plansza[i][j + 1] == 'O')
                bot++;
            else if (plansza[i][j + 1] == ' ')
                puste++;
            if (bot == 2 && puste == 1)
            {
                plansza[i][j - 1] = 'O';
                plansza[i][j] = 'O';
                plansza[i][j + 1] = 'O';
                return 1;
            }
        }
    }
    for (int i = 0; i < szerokosc; i++)
    {
        for (int j = 1; j < wysokosc - 1; j++)
        {
            bot = 0;
            puste = 0;
            if (plansza[j - 1][i] == 'O')
                bot++;
            else if (plansza[j - 1][i] == ' ')
                puste++;
            if (plansza[j][i] == 'O')
                bot++;
            else if (plansza[j][i] == ' ')
                puste++;
            if (plansza[j + 1][i] == 'O')
                bot++;
            else if (plansza[j + 1][i] == ' ')
                puste++;
            if (bot == 2 && puste == 1)
            {
                plansza[j - 1][i] = 'O';
                plansza[j][i] = 'O';
                plansza[j + 1][i] = 'O';
                return 1;
            }
        }
    }
    for (int i = 1; i < wysokosc - 1; i++)
    {
        for (int j = 1; j < szerokosc - 1; j++)
        {
            bot = 0;
            puste = 0;
            if (plansza[i][j] == 'O')
                bot++;
            else if (plansza[i][j] == ' ')
                puste++;
            if (plansza[i - 1][j + 1] == 'O')
                bot++;
            else if (plansza[i - 1][j + 1] == ' ')
                puste++;
            if (plansza[i + 1][j - 1] == 'O')
                bot++;
            else if (plansza[i + 1][j - 1] == ' ')
                puste++;
            if (bot == 2 && puste == 1)
            {
                plansza[i][j] = 'O';
                plansza[i - 1][j + 1] = 'O';
                plansza[i + 1][j - 1] = 'O';
                return 1;
            }
            bot = 0;
            puste = 0;
            if (plansza[i][j] == 'O')
                bot++;
            else if (plansza[i][j] == ' ')
                puste++;
            if (plansza[i - 1][j - 1] == 'O')
                bot++;
            else if (plansza[i - 1][j - 1] == ' ')
                puste++;
            if (plansza[i + 1][j + 1] == 'O')
                bot++;
            else if (plansza[i + 1][j + 1] == ' ')
                puste++;
            if (bot == 2 && puste == 1)
            {
                plansza[i][j] = 'O';
                plansza[i - 1][j - 1] = 'O';
                plansza[i + 1][j + 1] = 'O';
                return 1;
            }
        }
    }
    return 0;
}

int blok(char** plansza, int szerokosc, int wysokosc)
{
    int gracz = 0;
    int puste = 0;
    for (int i = 0; i < wysokosc; i++)
    {
        for (int j = 1; j < szerokosc - 1; j++)
        {
            gracz = 0;
            puste = 0;
            if (plansza[i][j - 1] == 'X')
                gracz++;
            else if (plansza[i][j - 1] == ' ')
                puste++;
            if (plansza[i][j] == 'X')
                gracz++;
            else if (plansza[i][j] == ' ')
                puste++;
            if (plansza[i][j + 1] == 'X')
                gracz++;
            else if (plansza[i][j + 1] == ' ')
                puste++;
            if (gracz == 2 && puste == 1)
            {
                if (plansza[i][j - 1] == ' ')
                    plansza[i][j - 1] = 'O';
                else if (plansza[i][j] == ' ')
                    plansza[i][j] = 'O';
                else if (plansza[i][j + 1] == ' ')
                    plansza[i][j + 1] = 'O';
                return 1;
            }
        }
    }
    for (int i = 0; i < szerokosc; i++)
    {
        for (int j = 1; j < wysokosc - 1; j++)
        {
            gracz = 0;
            puste = 0;
            if (plansza[j - 1][i] == 'X')
                gracz++;
            else if (plansza[j - 1][i] == ' ')
                puste++;
            if (plansza[j][i] == 'X')
                gracz++;
            else if (plansza[j][i] == ' ')
                puste++;
            if (plansza[j + 1][i] == 'X')
                gracz++;
            else if (plansza[j + 1][i] == ' ')
                puste++;
            if (gracz == 2 && puste == 1)
            {
                if (plansza[j - 1][i] == ' ')
                    plansza[j - 1][i] = 'O';
                else if (plansza[j][i] == ' ')
                    plansza[j][i] = 'O';
                else if (plansza[j + 1][i] == ' ')
                    plansza[j + 1][i] = 'O';
                return 1;
            }
        }
    }
    for (int i = 1; i < wysokosc - 1; i++)
    {
        for (int j = 1; j < szerokosc - 1; j++)
        {
            gracz = 0;
            puste = 0;
            if (plansza[i][j] == 'X')
                gracz++;
            else if (plansza[i][j] == ' ')
                puste++;
            if (plansza[i - 1][j + 1] == 'X')
                gracz++;
            else if (plansza[i - 1][j + 1] == ' ')
                puste++;
            if (plansza[i + 1][j - 1] == 'X')
                gracz++;
            else if (plansza[i + 1][j - 1] == ' ')
                puste++;
            if (gracz == 2 && puste == 1)
            {
                if (plansza[i][j] == ' ')
                    plansza[i][j] = 'O';
                else if (plansza[i - 1][j + 1] == ' ')
                    plansza[i - 1][j + 1] = 'O';
                else if (plansza[i + 1][j - 1] == ' ')
                    plansza[i + 1][j - 1] = 'O';
                return 1;
            }
            gracz = 0;
            puste = 0;
            if (plansza[i][j] == 'X')
                gracz++;
            else if (plansza[i][j] == ' ')
                puste++;
            if (plansza[i - 1][j - 1] == 'X')
                gracz++;
            else if (plansza[i - 1][j - 1] == ' ')
                puste++;
            if (plansza[i + 1][j + 1] == 'X')
                gracz++;
            else if (plansza[i + 1][j + 1] == ' ')
                puste++;
            if (gracz == 2 && puste == 1)
            {
                if (plansza[i][j] == ' ')
                    plansza[i][j] = 'O';
                else if (plansza[i - 1][j - 1] == ' ')
                    plansza[i - 1][j - 1] = 'O';
                else if (plansza[i + 1][j + 1] == ' ')
                    plansza[i + 1][j + 1] = 'O';
                return 1;
            }
        }
    }
    return 0;
}

int rozg_atak(char** plansza, int szerokosc, int wysokosc) //nadaje sie tylko do 3x3, wymaga poprawy
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (plansza[i][j] == ' ')
            {
                int puste = 0;
                int bot = 0;
                for (int k = 0; k < 3; k++)
                {
                    if (plansza[i][k] == ' ')
                        puste++;
                    else if (plansza[i][k] == 'O')
                        bot++;
                    if (plansza[j][k] == ' ')
                        puste++;
                    else if (plansza[j][k] == 'O')
                        bot++;
                }
                if (bot == 2 && puste == 4)
                {
                    plansza[i][j] = 'O';
                    return 1;
                }
            }
        }
    }
    if (plansza[1][1] == ' ')
    {
        
    }
    return 0;
}

int rozg_blok(char** plansza, int szerokosc, int wysokosc) //nadaje sie tylko do 3x3, wymaga poprawy
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (plansza[i][j] == ' ')
            {
                int puste = 0;
                int gracz = 0;
                for (int k = 0; k < 3; k++)
                {
                    if (plansza[i][k] == ' ')
                        puste++;
                    else if (plansza[i][k] == 'X')
                        gracz++;
                    if (plansza[j][k] == ' ')
                        puste++;
                    else if (plansza[j][k] == 'X')
                        gracz++;
                }
                if (gracz == 2 && puste == 4)
                {
                    plansza[i][j] = 'O';
                    return 1;
                }
            }
        }
    }
    return 0;
}

int srodek(char** plansza, int szerokosc, int wysokosc)
{
    int puste = 0;
    for (int i = 1; i < wysokosc - 1; i++)
    {
        for (int j = 1; j < szerokosc - 1; j++)
        {
            if (plansza[i][j] == ' ')
            {
                puste++;
            }
        }
    }
    if (puste != 0)
    {
        int x = 1;
        int y = 1;
        while (true)
        {
            x = rng(1, wysokosc - 1);
            y = rng(1, szerokosc - 1);
            if (plansza[x][y] == ' ')
            {
                plansza[x][y] = 'O';
                return 1;
            }
        }
    }
    
    return 0;
}

int przeciwny_rog(char** plansza, int szerokosc, int wysokosc)
{
    for (int i = 0; i < 4; i++)
    {
        int rog = 1;
        rog = rng(1, 4);
        if (plansza[0][0] != ' ' || plansza[0][szerokosc - 1] != ' ' || plansza[wysokosc - 1][0] != ' ' || plansza[wysokosc - 1][szerokosc - 1] != ' ')
        {
            switch (rog)
            {
                case 1:
                    if (plansza[0][0] == ' ' && plansza[wysokosc - 1][szerokosc - 1] == 'X')
                    {
                        plansza[0][0] = 'O';
                        return 1;
                    }
                    break;
                case 2:
                    if (plansza[0][szerokosc - 1] == ' ' && plansza[wysokosc - 1][0] == 'X')
                    {
                        plansza[0][szerokosc - 1] = 'O';
                        return 1;
                    }
                    break;
                case 3:
                    if (plansza[wysokosc - 1][0] == ' ' && plansza[0][szerokosc - 1] == 'X')
                    {
                        plansza[wysokosc - 1][0] = 'O';
                        return 1;
                    }
                    break;
                case 4:
                    if (plansza[wysokosc - 1][szerokosc - 1] == ' ' && plansza[0][0] == 'X')
                    {
                        plansza[wysokosc - 1][szerokosc - 1] = 'O';
                        return 1;
                    }
                    break;
            }
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

int pusty_rog(char** plansza, int szerokosc, int wysokosc)
{
    for (int i = 0; i < 4; i++)
    {
        int rog = 1;
        rog = rng(1, 4);
        if (plansza[0][0] != ' ' && plansza[0][szerokosc - 1] != ' ' && plansza[wysokosc - 1][0] != ' ' && plansza[wysokosc - 1][szerokosc - 1] != ' ')
        {
            return 0;
        }
        else
        {
            switch (rog)
            {
                case 1:
                    if (plansza[0][0] == ' ')
                    {
                        plansza[0][0] = 'O';
                        return 1;
                    }
                    break;
                case 2:
                    if (plansza[0][szerokosc - 1] == ' ')
                    {
                        plansza[0][szerokosc - 1] = 'O';
                        return 1;
                    }
                    break;
                case 3:
                    if (plansza[wysokosc - 1][0] == ' ')
                    {
                        plansza[wysokosc - 1][0] = 'O';
                        return 1;
                    }
                    break;
                case 4:
                    if (plansza[wysokosc - 1][szerokosc - 1] == ' ')
                    {
                        plansza[wysokosc - 1][szerokosc - 1] = 'O';
                        return 1;
                    }
                    break;
            }
        }
    }
    return 0;
}

int pusty_bok(char** plansza, int szerokosc, int wysokosc)
{
    int puste = 0;
    for (int i = 1; i < szerokosc - 1; i++)
    {
        if (plansza[0][i] == ' ' || plansza[wysokosc - 1][i] == ' ')
        {
            puste++;
        }
    }
    for (int i = 1; i < wysokosc - 1; i++)
    {
        if (plansza[i][0] == ' ' || plansza[i][szerokosc - 1] == ' ')
        {
            puste++;
        }
    }
    int bok = 1;
    int x = 0;
    if (puste != 0)
    {
        bok = rng(1, 4);
        switch (bok)
        {
            case 1:
                x = rng(1, szerokosc - 1);
                if (plansza[0][x] == ' ')
                    plansza[0][x] = 'O';
                break;
            case 2:
                x = rng(1, szerokosc - 1);
                if (plansza[wysokosc - 1][x] == ' ')
                    plansza[wysokosc - 1][x] = 'O';
                break;
            case 3:
                x = rng(1, wysokosc - 1);
                if (plansza[x][0] == ' ')
                    plansza[x][0] = 'O';
                break;
            case 4:
                x = rng(1, wysokosc - 1);
                if (plansza[x][szerokosc - 1] == ' ')
                    plansza[x][szerokosc - 1] = 'O';
                break;
        }
    }
    return 0;
}

int ruch_szalenca(char** plansza, int szerokosc, int wysokosc)
{
    int x = 0;
    int y = 0;
    while(true)
    {
        x = rng(0, szerokosc - 1);
        y = rng(0, wysokosc - 1);
        if (plansza[y][x] == ' ')
        {
            plansza[y][x] = 'O';
            return 1;
        }
    }
    return 0;
}
