#include<iostream>
#include<cstdio>

using namespace std;

class Node
{
public:
	int klucz = 0;
	int wartosc = 0;
	Node* rodzic = nullptr;
	Node* brat = nullptr;
	Node* syn = nullptr;

};

class Drzewo
{
public:
	Node node[20];
};

void dodaj_brata(Drzewo* drzewa, int k, int ostatni_wezel)
{
	cout << "tworze brata" << endl;


	Node* wsk_stary_brat = &drzewa[k].node[ostatni_wezel];
	Node* wsk_rodzic = drzewa[k].node[ostatni_wezel].rodzic;


	Node* wsk_nowy_brat = &drzewa[k].node[ostatni_wezel + 1];

	drzewa[k].node[ostatni_wezel].brat = wsk_nowy_brat;
	drzewa[k].node[ostatni_wezel + 1].rodzic = wsk_rodzic;

	drzewa[k].node[ostatni_wezel + 1].klucz = ostatni_wezel + 1;
}

void dodaj_syna(Drzewo* drzewa, int k, int ostatni_wezel)
{
	cout << "tworze syna" << endl;
	cout << "syn: " << ostatni_wezel + 1 << endl;

	Node* wsk_syn = &drzewa[k].node[ostatni_wezel + 1];

	Node* wsk_rodzic = &drzewa[k].node[ostatni_wezel];

	drzewa[k].node[ostatni_wezel].syn = wsk_syn;
	drzewa[k].node[ostatni_wezel + 1].rodzic = wsk_rodzic;


	drzewa[k].node[ostatni_wezel + 1].klucz = ostatni_wezel + 1;
}

void stworz_root(Drzewo* drzewa, int k)
{
	cout << "tworze roota" << endl;
	drzewa[k].node[0].wartosc = 0;
}

void wypisz(Drzewo* drzewa, int k, int* liczba_wezlow, int n)
{
	/*
	cout << "brat: " << drzewa[k].node[ostatni_wezel].brat;
	cout << "klucz: " << drzewa[k].node[ostatni_wezel].klucz;
	cout << "rodzic: " << drzewa[k].node[ostatni_wezel].rodzic;
	cout << "syn: " << drzewa[k].node[ostatni_wezel].syn;
	cout << "wartosc: " << drzewa[k].node[ostatni_wezel].wartosc;
	*/
	cout << "UWAGA:" << endl;
	cout << "liczba wezlow: " << liczba_wezlow[k];
	for (int h = 0; h < liczba_wezlow[k]; h++)
	{
		cout << drzewa[k].node[h].wartosc << " ";
	}
}

int main()
{
	int liczba;
	int n;
	char znak;
	cin >> n;

	int* liczba_wezlow = new int[n];
	int* ostatnia_ujemna = new int[n];
	Drzewo* drzewa = new Drzewo[n];

	for (int k = 0; k < n; k++)
	{
		liczba_wezlow[k] = 1;
		int ostatni_wezel = 0;    //jest to ostatni utworzony wêze³
		int wypelniacz = 0;
		Node* wsk_rodzic;
		Node rodzic;
		cin >> znak;

		stworz_root(drzewa, k);
		while (znak != ';')
		{
			switch (znak)
			{
			case '(':

				dodaj_syna(drzewa, k, ostatni_wezel);
				if (drzewa[k].node[ostatni_wezel].wartosc == 0)
				{
					wypelniacz--;
					drzewa[k].node[ostatni_wezel].wartosc = wypelniacz;
				}
				liczba_wezlow[k]++;
				ostatni_wezel++;
				
				break;

			case ',':

				dodaj_brata(drzewa, k, ostatni_wezel);
				liczba_wezlow[k]++;
				ostatni_wezel++;
				break;

			case ')':

				cout << "jestem tu" << endl;
				wsk_rodzic = drzewa[k].node[ostatni_wezel].rodzic;   //wska¿nik na rodzica ostatniego wêz³a 
				if(wsk_rodzic != nullptr) cout << "wsk rodzic" <<wsk_rodzic<< endl;
				rodzic = *wsk_rodzic;                                //rodzic ostatniego wêz³a
				
				ostatni_wezel = rodzic.klucz;
				break;

			default:
				//liczba = znak - 48;
				//cin >> znak;
				//liczba = liczba * 10 + (znak - 48);
				drzewa[k].node[ostatni_wezel].wartosc = znak-48;
			}
			cout << "ostatni wezel: " << ostatni_wezel << endl;
			cin >> znak;
		}

		ostatnia_ujemna[k] = wypelniacz;
		wypisz(drzewa, k, liczba_wezlow, n);
	}
	

	for (int k = 0; k < n-1; k++)
	{
		for (int h = k + 1; h < n; h++)
		{
			Drzewo drzewo1 = drzewa[k];
			Drzewo drzewo2 = drzewa[h];
			int kolumny = liczba_wezlow[k];           
			int wiersze = liczba_wezlow[h];
			int ujemne1 = 1  -ostatnia_ujemna[k];
			int ujemne2 = 1 - ostatnia_ujemna[h];
			int dodatnie1 = kolumny - ujemne1;
			int dodatnie2 = wiersze - ujemne2;
			
			int** hashmapa = new int* [wiersze];
			for (int f = 0; f < wiersze; f++)            //tworzenie hashmapy
			{
				hashmapa[f] = new int[kolumny];   
			}

			cout << "kolumny: " << kolumny<<endl;
			cout << "wiersze: " << wiersze << endl;
			cout << "ujemne1: " << ujemne1 << endl;
			cout << "ujemne2: " << ujemne2 << endl;
			cout << "dodatnie1: " << dodatnie1 << endl;
			cout << "dodatnie2: " << dodatnie2 << endl;
		}
	}

}