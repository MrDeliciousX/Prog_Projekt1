#include <iostream>
#include <string>
#include "spis.h"

using namespace std;

void k_p_n() //glowna funkcja kamien papier nozyce
{
    cout << "Wybrales gre kamien, papier, nożyce" << endl;
    cout << "\nto nie prawda ze program po prostu sprawdza co wlasnie dales/as i wystawia kontre" << endl;
    cout << "\nco nie znaczy ze jest glupi i daje losowo, program uczy sie na podstawie twoich ruchow, wiec im dluzej grasz tym trudniejszy staje sie przeciwnik" << endl;
    cout << "\nzamiast wpisywac pelne nazwy mozesz uzywac poznizszych skrotow:" << endl;
    cout << "k - kamien\np - papier\nn - nozyce\nreset - resetuje wynik i bota\n\nwpisz stop aby zakonczyc gre" << endl;
    cout << "\nPowodzenia!\n\n" << endl;
    
    int wynik_gracz = 0;
    int wynik_bot = 0;
    int* wynik_g = & wynik_gracz;
    int* wynik_b = & wynik_bot;
    int macierz[3][3] = {{0,0,0},{0,0,0},{0,0,0}}; //macierz do zapisywania ruchow gracza
    int* macierz_wsk[3];
    for ( int i = 0; i < 3; i++)
    {
        macierz_wsk[i] = macierz[i];
    }
    int** wsk = macierz_wsk;
    int poprzedni_ruch = 0;
    string ruch;
    int bot = 0;
    
    while( true )
    {
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n" << endl;
        cout << "twoj ruch: ";
        cin >> ruch;
        if ( ruch == "0" || ruch == "stop")
        {
            cout << "\ngra zakonczona z wynikiem\ngracz: " << wynik_gracz;
            cout << "\nvs\nbot: " << wynik_bot << endl;
            break;
        }
        else if ( ruch == "reset" )
        {
            wynik_g = 0;
            wynik_b = 0;
            for ( int i = 0; i < 3; i++ )
            {
                for ( int j = 0; j < 3; j++ )
                {
                    macierz[i][j] = 0;
                }
            }
            poprzedni_ruch = 0;
        }
        else
        {
            bot = ruch_bota_k_p_n(poprzedni_ruch, wsk);
            
            if ( ruch == "k" || ruch == "kamien" )
            {
                kto_wygral_k_p_n(bot, 1, wynik_b, wynik_g);
                uzupelnienie_botowej_magii_k_p_n(1, poprzedni_ruch, wsk);
                poprzedni_ruch = 1;
            }
            else if ( ruch == "p" || ruch == "papier" )
            {
                kto_wygral_k_p_n(bot, 2, wynik_b, wynik_g);
                uzupelnienie_botowej_magii_k_p_n(2, poprzedni_ruch, wsk);
                poprzedni_ruch = 2;
            }
            else if ( ruch == "n" || ruch == "nozyce" )
            {
                kto_wygral_k_p_n(bot, 3, wynik_b, wynik_g);
                uzupelnienie_botowej_magii_k_p_n(3, poprzedni_ruch, wsk);
                poprzedni_ruch = 3;
            }
            else
            {
                cout << "nieprawidlowy ruch, dostepne ruchy to:\nk, kamien, p, papier, n, nozyce, stop\n" << endl;
                continue;
            }
            cout << "\ngracz: " << wynik_gracz << " - " << wynik_bot << " :bot\n" << endl;
        }
        
        //  test macierzy
        
//        cout << "\n  k p n" << endl;
//        char tab[3] = {'k', 'p', 'n'};
//        for(int r = 0; r < 3; r++)
//        {
//            cout << tab[r] << " ";
//            for(int l = 0; l < 3; l++)
//            {
//                cout << macierz[r][l] << " ";
//            }
//            cout << endl;
//        }
        
    }
    glowne_menu();
}

int ruch_bota_k_p_n(int ostatni, int** macierz_wsk) //wykonanie ruchu na podstawie macierzy
{
    int ruch = 0;
    switch ( ostatni )
    {
        case 1:
            ruch = cala_magia_bota_k_p_n(1, macierz_wsk);
            break;
        case 2:
            ruch = cala_magia_bota_k_p_n(2, macierz_wsk);
            break;
        case 3:
            ruch = cala_magia_bota_k_p_n(3, macierz_wsk);
            break;
        default:
            ruch = rng(1, 3);
            break;
    }
    
    //cout << "ruch: " << ruch << endl;
    
    switch ( ruch )
    {
        case 1:
            cout << "ruch bota: kamien" << endl;
            return 1;
            break;
        case 2:
            cout << "ruch bota: papier" << endl;
            return 2;
            break;
        case 3:
            cout << "ruch bota: nozyce" << endl;
            return 3;
            break;
    }
    return 0;
}

void kto_wygral_k_p_n(int bot, int gracz, int* wynik_b, int* wynik_g)
{
    cout << endl;
    if ( bot == gracz)
    {
        cout << "remis" << endl;
    }
    else if ( bot == 1 )
    {
        if ( gracz == 2 )
        {
            cout << "wygrales te runde" << endl;
            *wynik_g += 1;
        }
        else if ( gracz == 3 )
        {
            cout << "te runde wygral bot" << endl;
            *wynik_b += 1;
        }
    }
    else if ( bot == 2 )
    {
        if ( gracz == 3 )
        {
            cout << "wygrales te runde" << endl;
            *wynik_g += 1;
        }
        else if ( gracz == 1 )
        {
            cout << "te runde wygral bot" << endl;
            *wynik_b += 1;
        }
    }
    else if ( bot == 3 )
    {
        if ( gracz == 1 )
        {
            cout << "wygrales te runde" << endl;
            *wynik_g += 1;
        }
        else if ( gracz == 2 )
        {
            cout << "te runde wygral bot" << endl;
            *wynik_b += 1;
        }
    }
}

int cala_magia_bota_k_p_n(int poprzedni, int** macierz_wsk)
{
    int a = *(*(macierz_wsk + (poprzedni - 1)));
    int b = *(*(macierz_wsk + (poprzedni - 1)) + 1);
    int c = *(*(macierz_wsk + (poprzedni - 1)) + 2);
    
    cout << "a=" << a << "\nb=" << b << "\nc=" << c << endl;
    
    if ( a == b && b == c )
    {
        return rng(1, 3);
    }
    else if ( a > b && a > c )
    {
        return 2;
    }
    else if ( b > a && b > c )
    {
        return 3;
    }
    else if ( c > a && c > b )
    {
        return 1;
    }
    else if ( a == b )
    {
        return rng(2, 3);
    }
    else if ( b == c )
    {
        int z = rng(1, 3);
        while( z == 2 )
        {
            z = rng(1, 3);
        }
        return z;
    }
    else if ( a == c )
    {
        return rng(1, 2);
    }
    return 0;
}

void uzupelnienie_botowej_magii_k_p_n(int ruch, int poprzedni, int** macierz_wsk)
{
    if ( poprzedni != 0 )
        *(*(macierz_wsk + (poprzedni - 1)) + (ruch - 1)) += 1; //uzupelnienie macierzy
}
