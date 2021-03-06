#include "naglowki.h"
#include "sort.cpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <Windows.h>
//#include <memory>

#define RAND_MAX 0x7fff
#define LICZBA 10000
//podczas testu zmieniamy ilosc elemntow tablicy 10000;50000;100000; 500000;1000000;

using namespace std; 

//funckje do mierzenia czasu
LARGE_INTEGER startTimer()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return start;
}

LARGE_INTEGER endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return stop;
}

int main()
{
 	srand((unsigned) time (NULL) ); 
	// do mierzenia czasu
	LARGE_INTEGER performanceCountStart, performanceCountEnd;
	__int64 freq;
	QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
	double tm;
	double a=0;
	int *tab = new int[LICZBA];
	for (int i = 0; i < 100; i++)
	{
		//unique_ptr<int[]> tab (new [liczba1]); // tworzenie tablicy w c++17
		utoworztab(tab, LICZBA);
		//sortowanie_szybkie(tab, 0,LICZBA - 1);
		//odwrot(tab, LICZBA);
		performanceCountStart = startTimer();
		//sortowanie_przez_scalanie(tab, 0, LICZBA - 1);
		//sortowanie_szybkie(tab, 0, LICZBA-1);
		IntroSort(tab, 0, LICZBA);
		performanceCountEnd = endTimer();
		tm = (double)(performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / freq;
		a +=tm;
		//cout << "posortowane: " << czy_posortowane(tab, LICZBA) << endl;
		cout << "pomiar nr: "<<i<<"czas"<<tm << endl;
		
	}
	
	cout << "a" << a << endl;
	double srednia = a / 100;
	cout << "srednia pomiarow: " << srednia << endl;
	delete[] tab;
	
		
	/* Menu do sprawdzenia poprawnosci dzialania algorytmow
	while (1)
	{
		cout << "\n-------------------------------------------------" << endl;
		cout << "            Implementacja algorytmow sortowania  " << endl;
		cout << "\n-------------------------------------------------" << endl;
		cout << "1. Utwórz losowa tablice o zadanej ilosci elementow" << endl;
		cout << "2. Posortuj przez scalanie" << endl;
		cout << "3. Posortuj przez quicksort" << endl;
		cout << "4. Posortuj introspektywnie" << endl;
		cout << "5. Wyswietl tablice" << endl;
		cout << "6. Wyjdz " << endl;
		cout << "\n---------------------------------------------------" << endl;
		cout << "Wybierz opcje: ";
		cin >> wybor;
		switch (wybor)
		{
		case 1:
			//cout << "Wprowadz ilosc elemntow tablicy : ";
			//n >> liczba;
			utoworztab(tab, liczba);
			wypisz(tab, liczba);
			break;
		case 2:
			sortowanie_przez_scalanie(tab, 0, liczba-1);
			wypisz(tab, liczba);
			cout << "posortowane : " << czy_posortowane(tab, liczba) << endl;
			break;
		case 3:
			sortowanie_szybkie(tab, 0, liczba-1);
			wypisz(tab, liczba);
			break;
		case 4:
			IntroSort(tab, 0, liczba - 1);
			wypisz(tab, liczba);
			if (czy_posortowane(tab, liczba) == 1)
				cout << "poprawnie posortowane" << endl;
			else
				cout << "niepoprawnie posortowane" << endl;
			break;
		case 5:
			wypisz(tab,liczba);
			break;
		case 6:
			exit(1);
			break;
		default:
			cout << "Nie ma takiej opcji" << endl;
		}
	}*/
	return 0;
}

