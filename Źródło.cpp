#include<iostream>
#include<cstdio>
using namespace std;

struct Node
{
	int id;
	int wartosc;
	Node* rodzic;
	Node* brat;
	Node* syn;
};

void usun_drzewo(Node* w)
{
	if (w)
	{
		usun_drzewo(w->brat);
		usun_drzewo(w->syn);
		delete w;
	}
}

/*
Node* szukaj(Node** tab_root, int k, int id)
{

}

bool czy_sie_laczy(Node** tab_root, int k, int start, int meta)
{
	Node* node = szukaj(tab_root, k, start);
	bool wynik = 0;
	if (start== meta)wynik=1;
	else
	{
		int start2 = node->syn.id;
		if (node->syn != NULL)wynik=czy_sie_laczy(tab_root,k,start2,meta);
		start = node->brat.id;
		if (node->brat != NULL)wynik=czy_sie_laczy(tab_root,k,start2,meta);
	}
	return wynik;
}
*/

void dodaj_syna(Node** tab_root, int k, Node* rodzic, int id_2)
{
	Node* syn;
	
	syn = new Node;
	syn->rodzic = rodzic;
	syn->id = id_2;
	syn->brat = NULL;
	syn->syn = NULL;
	syn->wartosc = 0;

	rodzic->syn = syn;
}


void dodaj_brata(Node** tab_root, int k, Node* brat, int id_2)
{
	Node* nowybrat;
	nowybrat = new Node;
	nowybrat->brat = NULL;
	nowybrat->syn = NULL;
	nowybrat->id = id_2;
	nowybrat->wartosc = 0;

	Node* root = tab_root[k];

	brat->brat = nowybrat;
	nowybrat->rodzic = brat->rodzic;
}

void stworz_root(Node** tab_root, int k)
{
	tab_root[k] = new Node;
	tab_root[k]->id = 0;
	tab_root[k]->wartosc = 0;
	tab_root[k]->brat = NULL;
	tab_root[k]->rodzic = NULL;
	tab_root[k]->syn = NULL;
}

void wypisz(Node** tab_root, int k, int n)
{
	
	Node* node = tab_root[k];
	for (int k = 0; k < n; k++)
	{
		if (node == NULL)break;
		cout << k << node->wartosc << endl;
		node = node->syn;

	}
}

Node* znajdz(Node* wezel, int szukana)
{
	Node* wynik=NULL;
	if (wezel->id == szukana)
	{
		return wezel;
	}
	else
	{
		if (wezel->syn != NULL)wynik = znajdz(wezel->syn, szukana);
		if (wynik != NULL)return wynik;
		if (wezel->brat != NULL)wynik = znajdz(wezel->brat, szukana);
		return wynik;
	}
}

bool czy_polaczone(Node** tab_root, int k, int id_1, int id_2)
{
	Node* root = tab_root[k];
	Node* el_1 = znajdz(root, id_1);
	Node* el_2 = znajdz(el_1, id_2);
	if (el_2 == NULL)return 0;
	else return 1;
}

int main()
{
	int il_drzew;
	cin >> il_drzew;
	char znak;

	Node** tab_root = new Node * [il_drzew];
	int* licznik = new int [il_drzew];
	int* ujemne = new int[il_drzew];

	for (int k = 0; k < il_drzew; k++)
	{
		licznik[k] = 1;
		int wypelniacz = 1;
		int flaga = 0;
		stworz_root(tab_root, k);
		Node* ostatni = tab_root[k];
		
		cin >> znak;
		while (znak != ';')
		{
			switch (znak)
			{
			case '(':
				dodaj_syna(tab_root, k, ostatni, licznik[k] + 1);
				if (ostatni->wartosc == 0)
				{
					wypelniacz--;
					ostatni->wartosc = wypelniacz;
				}
				licznik[k]++;
				ostatni = ostatni->syn;
				break;

			case ',':
				dodaj_brata(tab_root, k, ostatni, licznik[k] + 1);
				licznik[k]++;
				ostatni = ostatni->brat;
				break;

			case ')':
				ostatni = ostatni->rodzic;
				break;

			default:
				flaga = 1;
				int liczba = 0;
				while (znak > 47 && znak < 58)
				{
					int cyfra = znak - 48;
					liczba = liczba * 10;
					liczba += cyfra;
					cin >> znak;
				}
				ostatni->wartosc = liczba;
			}
			if (flaga == 0)cin >> znak;
			else flaga = 0;
		}
		ujemne[k] = 1-wypelniacz;
		//wypisz(tab_root, k, licznik[k]);
	}

	for (int k = 0; k < il_drzew-1; k++)
	{
		for (int h = k + 1; h < il_drzew; h++)
		{
			int wielkosc1 = licznik[k];
			int wielkosc2 = licznik[h];
			int ujemne1 = ujemne[k];
			int ujemne2 = ujemne[h];
			int dodatnie1 = wielkosc1 - ujemne1;
			int dodatnie2 = wielkosc2 - ujemne2;

			bool** hashmapa = new bool* [wielkosc1];
			for (int t = 1; t < wielkosc1; t++)
			{
				hashmapa[t] = new bool[wielkosc2];
			}

			for (int t = 1; t < dodatnie1; t++)
			{
				for (int f = 0; f < dodatnie2; f++)
				{
					
					if (t == f)hashmapa[t][f] = 1;
					else hashmapa[t][f] = 0;
					
				}
			}

			for (int t = dodatnie1; t < wielkosc1; t++)
			{
				for (int f = 1; f < wielkosc2; f++)
				{
					hashmapa[t][f] = czy_polaczone(tab_root, k, t, f);
					cout << hashmapa[t][f];
				}
				cout << endl;
			}

			


		}
	}

}