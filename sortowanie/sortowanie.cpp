//#include "tablica.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std; 

template <typename T>
void utoworztab(T *tab, int rozm)
{
	for (int i = 0; i < rozm ; i++)
		tab[i] = rand() % 300;
}

template <typename T>
void wypisz(T *tab, int rozm)
{
	for (int i = 0; i<rozm; i++)
		cout << tab[i] << " , ";
	cout << endl;
}
//sortowanie przez scalanie

/*template<typename T>
void scal(T *tab, int p, int k, int s)
{
	int i = p, j = s;
	T *tmp = new T[k+1];
	//kopiujemy lewą i prawą część tablicy do tablicy pomocniczej
	for (int i = p; i <= k; i++)
		tmp[i] = tab[i];
	//scalenie dwóch podtablic pomocniczych i zapisanie ich 
	//we własciwej tablicy
	
	for (int m = p; m <= k; m++)
		if (i <= s-1)
			if (j <= k)
				if (tmp[j]<tmp[i])
					tab[m] = tmp[j++];
				else
					tab[m] = tmp[i++];
			else
				tab[m] = tmp[i++];
		else
			tab[m] = tmp[j++];
	cout << "wykonanie scal" << endl;
}
*/
template<typename T>
void scal(T* tab, int p, int s, int k)
{
	T *tmp = new T[(k+1)];
	//T *tab_pom = new T[(koniec - start)]; // utworzenie tablicy pomocniczej
	int i = p, j = s + 1, m = 0; // zmienne pomocnicze

	while (i <= s && j <= k)
	{
		if (tab[j] < tab[i])
		{
			tmp[m] = tab[j];
			j++;
		}
		else
		{
			tmp[m] = tab[i];
			i++;
		}
		m++;
	}

	if (i <= s)
	{
		while (i <= s)
		{
			tmp[m] = tab[i];
			i++;
			m++;
		}
	}
	else
	{
		while (j <= k)
		{
			tmp[m] = tab[j];
			j++;
			m++;
		}
	}

	for (i = 0; i <= k-p; i++)
		tab[p + i] = tmp[i];

}

template <typename T>
void sortowanie_przez_scalanie(T *tab, int p, int k)
{
	int s; 
	if (p < k)
	{	s= (p + k ) / 2; // +1 w przypadku kiedy jest jeden elem
		sortowanie_przez_scalanie(tab, p, s);
		sortowanie_przez_scalanie(tab, s+1, k);
		scal(tab, p, s, k);
	}
}

//sortowanie szybkie

template<typename T>
void sortowanie_szybkie(T *tab, int p, int k)
{
	int l = p;
	int r = k;
	T piwot = tab[rand()%k];
	do {

		while (tab[l] < piwot)
			l++;
		while (tab[r] > piwot)
			r--;
		if (l <= r) 
		{
			swap(tab[l], tab[r]);
			l++;  r--;
		}
	} while (l <= r);

	if (p < r)
		sortowanie_szybkie(tab, p, r);
	if (k > l)
		sortowanie_szybkie(tab, l, k);
}
 template <typename T>
 bool czy_posortowane(T *tab, int k)
 {
	 bool posortowane = true;
	 for (int i= 0; i < k; k++)
	 {
		 if (tab[i + 1] < tab[i]) posortowane = false;
	 }
	 return posortowane;
}
int main()
{
 	srand((unsigned) time (NULL) ); 
	int wybor;
	int liczba = 20;
	int *tab = new int [liczba];
	
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

			break;
		case 5:
		
			break;
		case 6:
			exit(1);
			break;
		default:
			cout << "Nie ma takiej opcji" << endl;
		}
	}
	return 0;
}

