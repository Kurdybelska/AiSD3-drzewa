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
	Node* wynik = NULL;
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

char czy_polaczone(Node** tab_root, int k, int id_1, int id_2)
{
	Node* root = tab_root[k];
	Node* el_1 = znajdz(root, id_1);
	Node* el_2 = znajdz(el_1, id_2);
	if (el_2 == NULL)return 0;
	else return 1;
}

int policz_synow(Node** tab_root, int k, int id_rodzica)
{
	Node* el = znajdz(tab_root[k], id_rodzica);
	//if (el == NULL)cout << "rodzic o id " << id_rodzica << " jest NULL" << endl;
	int wynik = 0;
	if (el->syn != NULL)
	{
		
		wynik++;
		el = el->syn;
		//cout << "Syn ma id: " << el->id << endl;
		while (el->brat != NULL)
		{
			wynik++;
			el = el->brat;
			//cout << "Syn ma id: " << el->id << endl;
		}
	}
	return wynik;
}

char porownaj_wartosci(Node** tab_root, int k1, int k2, int id_1, int id_2)
{
	char wynik = 0;
	Node* el_1 = znajdz(tab_root[k1], id_1);
	Node* el_2 = znajdz(tab_root[k2], id_2);
	if (el_1->wartosc == el_2->wartosc)wynik = 1;
	return wynik;
}

int main()
{
	int il_drzew;
	cin >> il_drzew;
	char znak;

	Node** tab_root = new Node * [il_drzew];
	int* dodatnie = new int[il_drzew];
	int* ujemne = new int[il_drzew];

	for (int k = 0; k < il_drzew; k++)
	{
		dodatnie[k] = 0;
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
				dodaj_syna(tab_root, k, ostatni, dodatnie[k] + 1);
				if (ostatni->wartosc == 0)
				{
					wypelniacz--;
					ostatni->wartosc = wypelniacz;
					ostatni->id = wypelniacz;
				}
				//licznik[k]++;
				ostatni = ostatni->syn;
				break;

			case ',':
				dodaj_brata(tab_root, k, ostatni, dodatnie[k] + 1);
				//licznik[k]++;
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
				dodatnie[k]++;
			}
			if (flaga == 0)cin >> znak;
			else flaga = 0;
		}
		ujemne[k] = 1 - wypelniacz;
		//wypisz(tab_root, k, licznik[k]);
	}

	for (int k = 0; k < il_drzew - 1; k++)
	{
		for (int h = k + 1; h < il_drzew; h++)
		{
			int ujemne1 = ujemne[k];
			int ujemne2 = ujemne[h];
			int dodatnie1 = dodatnie[k];
			int dodatnie2 = dodatnie[h];
			int wielkosc1 = ujemne1 + dodatnie1;
			int wielkosc2 = ujemne2 + dodatnie2;
			cout << "ujemne1: " << ujemne1 << endl << "  ujemne2: " << ujemne2 << endl;
			cout << "dodatnie1: " << dodatnie1 << endl << "  dodatnie2: " << dodatnie2 << endl;
			cout << "wielkosc tablicy: " << wielkosc1 << " x " << wielkosc2 << endl;

			char** hashmapa = new char* [wielkosc1+1];
			for (int t = 0; t <= wielkosc1; t++)
			{
				hashmapa[t] = new char[wielkosc2+1];
			}

			for (int t = 1; t <= dodatnie1; t++)
			{
				for (int f = 1; f <= dodatnie2; f++)
				{

					//if (t == f)hashmapa[t][f] = 1;
					//else hashmapa[t][f] = 0;
					hashmapa[t][f] = porownaj_wartosci(tab_root, k, h, t, f);

				}
			}

			for (int t = 1; t <= dodatnie1; t++)
			{
				for (int f = dodatnie2 + 1; f <= wielkosc2; f++)
				{
					int id_kolumny = 1 - f + dodatnie2;
					//cout << id_kolumny << " -> " << t << ": " ;
					hashmapa[t][f] = czy_polaczone(tab_root, h, id_kolumny, t);
					//cout << hashmapa[t][f] << endl;
					//cout << "wiersz: " << t << "  kolumna: " << f << "  id_kolumny: " << id_kolumny << endl;
					if (hashmapa[t][f] == 205)cout << "PROBLEM: " << t << " x " << f << endl;
				}
				//cout << endl;
			}


			for (int t = dodatnie2 + 1; t <= wielkosc2; t++)
			{
				for (int f = 1; f <= dodatnie1; f++)
				{
					int id_wiersza = 1 - t + dodatnie1;
					//cout << id_kolumny << " -> " << t << ": ";
					hashmapa[t][f] = czy_polaczone(tab_root, k, id_wiersza, f);
					//cout << hashmapa[t][f] << endl;
					//cout << "wiersz: " << t << "  kolumna: " << f << "  id_kolumny: " << id_kolumny << endl;
					if (hashmapa[t][f] == 205)cout << "PROBLEM: " << t << " x " << f << endl;
				}
				//cout << endl;
			}

			int flaga = 1;
			while(flaga==1)
			{
				flaga = 0;
				
				for (int t = wielkosc1; t > dodatnie1; t--)
				{
					for (int f = wielkosc2; f > dodatnie2; f--)
					{
						int id_rodzica_1 = 1 - t + dodatnie1;
						int id_rodzica_2 = 1 - f + dodatnie2;
						int synowie1 = policz_synow(tab_root, k, id_rodzica_1);
						int synowie2 = policz_synow(tab_root, h, id_rodzica_2);
											

						if (synowie1 == 0 || synowie2 == 0)
						{
							//cout << "t: " << t << " f: " << f << endl;
							cout << "wstawiam 0 po prostu" << endl;
							hashmapa[t][f] = 0;
						}
						else
						{
							int wiersze, kolumny;

							Node* rodzic_1 = znajdz(tab_root[k], id_rodzica_1);
							Node* rodzic_2 = znajdz(tab_root[h], id_rodzica_2);
							Node* el_1, * el_2;

							if (synowie1 > synowie2)
							{
								wiersze = synowie1;
								kolumny = synowie2;
								
								el_1 = rodzic_1->syn;
								el_2 = rodzic_2->syn;
							}
							else
							{
								wiersze = synowie2;
								kolumny = synowie1;

								el_1 = rodzic_2->syn;
								el_2 = rodzic_1->syn;
							}
							
							int* pion = new int[wiersze];
							int* poziom = new int[kolumny];

							pion[0] = el_1->id;
							poziom[0] = el_2->id;

							for (int g = 1; g < wiersze; g++)
							{
								el_1 = el_1->brat;
								pion[g] = el_1->id;
							}
							for (int g = 1; g < kolumny; g++)
							{
								el_2 = el_2->brat;
								poziom[g] = el_2->id;
							}



							char** tab = new char* [wiersze];
							for (int g = 0; g < wiersze; g++)
							{
								tab[g] = new char[kolumny];
							}

							for (int g = 0; g < wiersze; g++)
							{
								int wiersz = pion[g];
								for (int r = 0; r < kolumny; r++)
								{
									int kolumna = poziom[r];
									//cout << "wiersz: " << wiersz << "  kolumna: " << kolumna << endl;
									if (wiersz < 0)wiersz = dodatnie1 + 1 - wiersz;
									if (kolumna < 0)kolumna = dodatnie2 + 1 - kolumna;
									tab[g][r] = hashmapa[wiersz][kolumna];
									cout << tab[g][r];
									//cout << "wiersz: " << wiersz << " kolumna: " << kolumna << endl;
									//cout << "wiersz: " << wiersz << "  kolumna: " << kolumna << "  " << tab[g][r] << endl;
									
									if (tab[g][r] == 205)
									{
										cout << "PROBLEM" << endl;
										flaga = 1;
									}
									
								}
								cout << endl;
							}
							cout << endl;

							
							//cout << "lewa dolna polowa" << endl;

							int max = 0;
							int kolumna;
							int suma;
							for (int i = 0; i < wiersze; i++)                                      //lewa dolna po這wa
							{
								//cout << "i: " << i << endl;
								suma = 0;
								kolumna = 0;
								
								for (int k = i; k < wiersze; k++)
								{
									//cout << "wiersz: " << k << " kolumna: " << kolumna << endl;
									if (kolumna >= kolumny)break;
									suma = suma + tab[k][kolumna];
									//cout << "suma: " << suma << endl;
									kolumna++;
									//if (kolumna >= kolumny)break;
								}
								if (suma > max)max = suma;
								//if (kolumna >= kolumny)break;
							}
							

							//cout << endl<<"prawa gorna polowa:" << endl;
							
							for (int i = wiersze-1; i > 0; i--)                                     //prawa g鏎na po這wa
							{
								//cout << "i: " << i << endl;
								suma = 0;
								kolumna = kolumny - 1;
								
								for (int k = i; k > 0; k--)
								{
									//cout << "wiersz: " << k << " kolumna: " << kolumna << endl;
									if (kolumna < 0)break;
									suma = suma + tab[k][kolumna];
									//cout << "suma: " << suma << endl;
									kolumna--;
									//if (kolumna<0)break;
								}
								if (suma > max)max = suma;
								//if (kolumna < 0)break;
							}

							//cout << endl <<"prawa dolna polowa" << endl;

							for (int i = 0; i < wiersze; i++)                                        //prawa dolna po這wa
							{
								//cout << "i: " << i << endl;
								suma = 0;
								kolumna = kolumny-1;
								//if (kolumna < 0)break;
								for (int k = i; k < wiersze; k++)
								{
									if (kolumna < 0)break;
									//cout << "wiersz: " << k << " kolumna: " << kolumna << endl;
									suma = suma + tab[k][kolumna];
									//cout << "suma: " << suma << endl;
									kolumna--;
									//if (kolumna < 0)break;
								}
								if (suma > max)max = suma;
								//if (kolumna < 0)break;
							}

							//cout << endl << "lewa gorna polowa" << endl;

							for (int i = 0; i < wiersze; i++)                                          //lewa g鏎na po這wa
							{
								//cout << "i: " << i << endl;
								suma = 0;
								kolumna = i;
								//if (kolumna >= kolumny)break;
								for (int k = i; k < wiersze; k++)
								{
									//cout << "wiersz: " << k << " kolumna: " << kolumna << endl;
									if (kolumna >= kolumny)break;
									suma = suma + tab[k][kolumna];
									//cout << "suma: " << suma << endl;
									kolumna++;
									
								}
								if (suma > max)max = suma;
								//if (kolumna>=kolumny)break;
							}

							hashmapa[t][f] = max;
							cout << t << " x " << f << "  " << max << endl<<endl;
						}

					}
				}
				cout << "--------------------------------------------------------------" << endl;
			}

			for (int r = 1; r <= wielkosc1; r++)
			{
				for (int i = 1; i <= wielkosc2; i++)
				{
					cout << hashmapa[r][i];
				}
				cout << endl;
			}
			
		}
	}
	/*
	cout << "TEST:" << endl;
	int licznik = 1;
	int tablica[5][5];
	for (int t = wielkosc1; t > 0; t--)
	{
		for (int f = t; f > 0; f--)
		{
			tablica[f][t] = licznik++;

		}
		for (int f = t - 1; f > 0; f--)
		{
			tablica[t][f] = licznik++;
		}
	}

	for (int k = 1; k <= 4; k++)
	{
		for (int i = 1; i <= 4; i++)
		{
			cout << tablica[k][i];
		}
		cout << endl;
	}
	*/
}