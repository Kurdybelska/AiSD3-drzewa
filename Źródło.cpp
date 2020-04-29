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


Node* szukaj(Node* node, int id)
{
	if (node->id == id)return node;
	else
	{
		Node* node2 = node->syn;
		if (node2 != NULL)szukaj(node2, id);
		node2 = node->rodzic;
		if (node2 != NULL)szukaj(node2, id);
	}
}

//sprawdzone, dziala
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

int main()
{
	int il_drzew;
	cin >> il_drzew;
	char znak;

	Node** tab_root = new Node * [il_drzew];
	int* licznik = new int [il_drzew];
	

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
		wypisz(tab_root, k, licznik[k]);
	}
}