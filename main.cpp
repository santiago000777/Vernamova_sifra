#define ABCD    27
#define NIC     -52

#include<iostream>
#include <cmath>
#include <string>       
#include <windows.h>
#include <winuser.h>                                                     
#include <conio.h>  
#include <stdlib.h>
#include <dos.h>
#include <stdio.h>
#include <fcntl.h>
#include <locale.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;


string abeceda = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

class TPismeno {
public:
    char znak;
    int poradi;
    int posun;
};

int main()
{
    int zadost;
    cout << "1 pro sifrovani | 2 pro desifrovani\n";
    cin >> zadost;
    system("cls");
    
    TPismeno abecedaTxt[ABCD];
    for (int i = 0; i < ABCD; i++) {
        abecedaTxt[i].znak = abeceda.at(i);
        abecedaTxt[i].poradi = i;
    }

    if (zadost == 1) {
        cout << "****TVUJ TEXT****\n";
        string mujSifraText;

        getline(cin >> ws, mujSifraText);
        transform(mujSifraText.begin(), mujSifraText.end(), mujSifraText.begin(), ::toupper);

        TPismeno sifraText[100];
        int pom = 0;
        for (int j = 0; j < mujSifraText.length(); j++) {
            for (int i = 0; i < ABCD; i++) {

                if (abecedaTxt[i].znak == mujSifraText.at(j)) {
                    sifraText[pom].znak = abeceda.at(i);
                    sifraText[pom].poradi = abecedaTxt[i].poradi;
                    pom++;
                }
            }
        }

        random_device nahodneCis;
        uniform_int_distribution<int> dist(0, ABCD - 1);

        vector<int> random;

        for (int i = 0; i < 100; i++) {
            if (sifraText[i].znak != NIC) {
                sifraText[i].posun = dist(nahodneCis);
                random.push_back(sifraText[i].posun);
                sifraText[i].poradi += sifraText[i].posun;
                if (sifraText[i].poradi > ABCD - 1) {  
                    sifraText[i].poradi -= ABCD;
                    if (sifraText[i].poradi < 0) {
                        sifraText[i].poradi += ABCD;
                    }
                }
            }
            else
                break;
        }
        char zkouska[2000];

        cout << "\n";
        cout << "****SIFRA****\n";
        for (int i = 0; i < mujSifraText.length(); i++) {   
            zkouska[i] = abeceda.at(sifraText[i].poradi);
            if (zkouska[i] == ' ') {
                cout << '_';
            }
            else
                cout << zkouska[i];
        }
        cout << "\n\n\n";
        cout << "- - - TOP SECRET - - -" << endl;
        for (int i = 0; i < random.size(); i++) {
            cout << random.at(i) << "  ";
        }
        cout << "\n\n";
    }
    //*******************************************************************************************************************************
    else if (zadost == 2) {
        string mojeSifra;
        
        cout << "****TVOJE SIFRA****\n";
        
        getline(cin >> ws, mojeSifra);
        transform(mojeSifra.begin(), mojeSifra.end(), mojeSifra.begin(), ::toupper);
        
        vector<TPismeno> sifraText;
        vector<int> klic;
        
        TPismeno pomT;
        pomT.poradi = 0;
        pomT.posun = 0;
        pomT.znak = ' ';
        int pomI;
        
        cout << "****TVUJ KLIC**** (enter)\n";

        for (int j = 0; j < mojeSifra.length(); j++) {
            cin >> pomI;
            klic.push_back(pomI);
            for (int i = 0; i < ABCD; i++) {
                if (mojeSifra.at(j) == '_') {
                    mojeSifra.at(j) = ' ';
                }
                if (abecedaTxt[i].znak == mojeSifra.at(j)) {
                    
                    pomT.znak = abecedaTxt[i].znak;
                    pomT.posun = klic[j];
                    pomT.poradi = abecedaTxt[i].poradi;

                    if (pomT.poradi < pomT.posun) {
                        pomT.poradi = pomT.poradi - pomT.posun + ABCD;
                        
                    }
                    else
                        pomT.poradi -= pomT.posun;

                    sifraText.push_back(pomT);
                }
            }
        }

        for (int j = 0; j < mojeSifra.length(); j++) {
            for (int i = 0; i < ABCD; i++) {
                if (abecedaTxt[i].poradi == sifraText.at(j).poradi) {
                    sifraText.at(j).znak = abecedaTxt[i].znak;
                }
            }
        }
        cout << endl << "****Rozlusteni****\n";
        for (int i = 0; i < mojeSifra.length(); i++) {
            cout << sifraText.at(i).znak;
        }
        cout << endl;
    }
}