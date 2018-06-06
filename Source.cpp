#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <time.h>

using namespace std;

string plansza[26];
int x[100], y[100]; //maksymalna dlugosc to 100
int kierunek = 3, rozmiar = 4; //pozycja poczatku weza, kierunek poruszania sie, pozycja konca weza
char przycisk;
void ruch(int y, int x);
void zmianakierunku();


HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Position;
CONSOLE_CURSOR_INFO cursor_info;

//grawitacja(x,y,z)-> grawitacja(x+-, y+-, z+)
void setCursor(int x, int y)
{
	Position.Y = x;
	Position.X = y;
	SetConsoleCursorPosition(hOut, Position);
}

int main()
{
	GetConsoleCursorInfo(hOut, &cursor_info);
	cursor_info.bVisible = 0;
	SetConsoleCursorInfo(hOut, &cursor_info);

	//inicjacja weza o dlugosci 4
	x[0] = 26;
	y[0] = 12;
	for (int i = 1; i<rozmiar; i++)
	{
		x[i] = x[i - 1] - 1;
		y[i] = 12;
	}


	//Stworzenie planszy
	for (int i = 0; i<26; i++)
		plansza[i] = "|                                                 |";

	//Pozycja startowa
	for (int i = 0; i<rozmiar; i++)
		plansza[y[0]].replace(x[i], 1, "o");

	plansza[5].replace(7, 1, ".");

	//Wczytanie planszy
	//for (int j=0; j<25; j++)
	//cout<<plansza[j]<<endl;
	while (1)
	{
		for (int i = 1; i<rozmiar; i++)
		{
			if ((x[0] == x[i]) && (y[0] == y[i]))
			{
				cout << "Przegrales. Zdobyles " << rozmiar - 4 << " punktow";
				cin.get(); cin.get();
				exit(0);
			}
		}
		//czyszcze poprzedni obieg
		setCursor(0, 0);
		//wyswietlam plansze na sekunde
		cout << "__________________________________________________" << endl;
		for (int j = 1; j<25; j++)
			cout << plansza[j] << endl;							
		cout << "**************************************************" << endl;
		if ((kierunek == 1) || (kierunek == 3))
			Sleep(50);
		else
			Sleep(75);
		//jesli cos zostanie wcisniete to to co zostalo wcisniete jest sprawdzane czy jest ruchem. Jesli tak to zmiana kierunku na ta co trzeba
		if (_kbhit())
			zmianakierunku();

		//ostatnia w wezu kulka znika z pola na ktorym byla
		plansza[y[rozmiar - 1]].replace(x[rozmiar - 1], 1, " ");
		//wspolrzedne zmieniaja sie w zaleznosci od kierunku
		switch (kierunek)
		{
		case 0:
		{
			if (y[0]>1)
			{
				ruch(y[0] - 1, x[0]);
				y[0]--;
				plansza[y[0]].replace(x[0], 1, "o");
			}

			//jesli za blisko granicy pola gry-przegrywasz
			else
			{
				cout << "Przegrales. Zdobyles " << rozmiar - 4 << " punktow";
				cin.get(); cin.get();
				exit(0);
			}
			break;
		}
		case 1:
		{
			if (x[0]>1)
			{
				ruch(y[0], x[0] - 1);
				x[0]--;
				plansza[y[0]].replace(x[0], 1, "o");
			}

			//jesli za blisko granicy pola gry-przegrywasz
			else
			{
				cout << "Przegrales. Zdobyles " << rozmiar - 4 << " punktow";
				cin.get(); cin.get();
				exit(0);
			}
			break;
		}
		case 2:
		{
			if (y[0]<24)
			{
				ruch(y[0] + 1, x[0]);
				y[0]++;
				plansza[y[0]].replace(x[0], 1, "o");
			}

			//jesli za blisko granicy pola gry-przegrywasz
			else
			{
				cout << "Przegrales. Zdobyles " << rozmiar - 4 << " punktow";
				cin.get(); cin.get();
				exit(0);
			}
			break;
		}
		case 3:
		{
			if (x[0]<49)
			{
				ruch(y[0], x[0] + 1);
				x[0]++;
				plansza[y[0]].replace(x[0], 1, "o");
			}

			//jesli za blisko granicy pola gry-przegrywasz
			else
			{
				cout << "Przegrales. Zdobyles " << rozmiar - 4 << " punktow";
				cin.get(); cin.get();
				exit(0);
			}
			break;
		}
		}


	}
	return 0;
}

void ruch(int q, int r)
{
	int a = 0, b = 0;
	srand(time(NULL));
	bool losowa = 1;
	if (plansza[q][r] == '.')
	{
		//randomowe a i b
		do
		{
			losowa = 1;
			a = rand() % 21 + 2;
			b = rand() % 45 + 2;
			for (int i = 0; i<rozmiar; i++)
			{
				if ((a == y[i]) && (b == x[i]))
					losowa = 0;
			}
		} while (losowa == 0);
		plansza[a][b] = '.';
		rozmiar++;
	}
	for (int i = rozmiar - 1; i>0; i--)
	{
		y[i] = y[i - 1];
		x[i] = x[i - 1];
		plansza[y[i]].replace(x[i], 1, "o");
	}
}

void zmianakierunku()
{

	przycisk = _getch();
	_getch();

	if ((przycisk == 'w') && (!(kierunek == 2)))
	{
		kierunek = 0;
	}
	else if ((przycisk == 'a') && (!(kierunek == 3)))
	{
		kierunek = 1;
	}
	else if ((przycisk == 's') && (!(kierunek == 0)))
	{
		kierunek = 2;
	}
	else if ((przycisk == 'd') && (!(kierunek == 1)))
	{
		kierunek = 3;
	}
}
