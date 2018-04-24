#include "naglowki.h"
#include <iostream>
#include <cmath>

using namespace std;
//funkcja wypelniajaca tablice losowymi warosciami 
template <typename T>
void utoworztab(T *tab, int rozm)
{
	for (int i = 0; i < rozm; i++)
		tab[i] = rand() % 300; // tutaj mozemy okreslic z jakiego przedzialu losujemy liczby
}
//funkcja wypisujaca tablice
template <typename T>
void wypisz(T *tab, int rozm)
{
	for (int i = 0; i<rozm; i++)
		cout << tab[i] << " , ";
	cout << endl;
}
//funkcja potrzebna do testu w przypadku odwrotnie posortowanej tablicy
template<typename T>
void odwrot(T *tab, int rozm)
{
	T *tmp = new T[rozm];
	for (int i = 0, j = rozm - 1; i < rozm; i++, j--)
	{
		tmp[i] = tab[j];
	}
	for (int i = 0; i < rozm; i++)
	{
		tab[i] = tmp[i];
	}

}

//sortowanie przez scalanie funkcja pomocnicza
template<typename T>
void scal(T *tab, int p, int s, int k)
{
	//unique_ptr<T[]> tmp(new (k + 1));
	T *tmp = new T[(k - p)];
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
	for (i = 0; i <= k - p; i++)
		tab[p + i] = tmp[i];

	//delete [] tmp;
}
//sortowanie przez scalanie
template <typename T>
void sortowanie_przez_scalanie(T *tab, int p, int k)
{
	int s;
	if (p < k)
	{
		s = (p + k) / 2;
		sortowanie_przez_scalanie(tab, p, s);
		sortowanie_przez_scalanie(tab, s + 1, k);
		scal(tab, p, s, k);
	}
}
//funkcja potrzebna do introsorta
template <typename T>
int dzielenie(T *tab, int p, int k)
{
	T piwot = tab[rand() % k];
	//	int temp;
	int i = p;

	for (int j = p; j < k; ++j)
	{
		if (tab[j] <= piwot)
		{
			swap(tab[j], tab[i]);
			/*temp = tab[j];
			tab[j] = tab[i];
			tab[i] = temp;*/
			i++;
		}
	}

	tab[k] = tab[i];
	tab[i] = piwot;

	return i;

}

//sortowanie szybkie

template <typename T>
void sortowanie_szybkie(T *tab, int p, int k)
{
	//int x = rand();
	//T piwot = tab[x%k];
	int l = p;
	int r = k;

	T piwot = tab[(p + k) / 2];

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
// sortowanie introspektywne
template <typename T>
void IntroSort(T *tab, int p, int k)
{
	int wywolania = dzielenie(tab, p, k);
	if (wywolania >(2 * log(k)))
	{
		sortowanie_przez_kopcowanie(tab, k);
	}
	else
	{
		sortowanie_szybkie(tab, p, k);
	}
}
//funkcja potrzebna do kopcowania
template <typename T>
void MaxH(T *tab, int rozm, int k)
{
	int l = (k + 1) * 2 - 1;
	int r = (k + 1) * 2;
	int najwiekszy = 0;

	if (l < rozm && tab[l] > tab[k])
		najwiekszy = l;
	else
		najwiekszy = k;

	if (r < rozm && tab[r] > tab[najwiekszy])
		najwiekszy = r;

	if (najwiekszy != k)
	{
		//swap(data[index], data[largest]);
		int temp = tab[k];
		tab[k] = tab[najwiekszy];
		tab[najwiekszy] = temp;

		MaxH(tab, rozm, najwiekszy);
	}
}
template <typename T>
void sortowanie_przez_kopcowanie(T *tab, int k)
{
	int rozm = k;
	for (int p = (rozm - 1) / 2; p >= 0; --p)
		MaxH(tab, rozm, p);

	for (int i = k - 1; i > 0; --i)
	{
		swap(tab[i], tab[0]);
		/*int temp = data[i];
		data[i] = data[0];
		data[0] = temp;*/
		--rozm;
		MaxH(tab, rozm, 0);
	}
}

template <typename T>
bool czy_posortowane(T *tab, int k)
{
	bool posortowane = true;
	for (int i = 0; i < k; k++)
	{
		if (tab[i + 1] < tab[i]) posortowane = false;
	}
	return posortowane;
}