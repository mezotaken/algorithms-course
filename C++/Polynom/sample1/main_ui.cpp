#include "polynom.h"
#include <iostream>
using namespace std;

char menu()
{
	system("cls");
	char res;
	cout << "1. Add\n";
	cout << "2. Substract\n";
	cout << "3. Mult\n";
	cout << "4. Const Mult\n";
	cout << "5. Exit\n";

	cout << "\n\n";
	cout << "Choose menu item: ";
	cin >> res;
	return res;
}

void main() {
	char pmenu;
	polynom p1, p2;
	string s1, s2;
	double c;
	do {
		pmenu = menu();

		switch (pmenu)
		{
		case '1':
		{
			system("cls");

			cout << "Enter the first polynom:\n";
			cin >> s1;
			p1 = polynom(s1);
			cout << "Enter the second polynom:\n";
			cin >> s2;
			p2 = polynom(s2);
			cout << p1 << '+' << p2 << '=' << p1 + p2 << '\n';

			system("pause");
			break;
		}

		case '2':
		{
			system("cls");

			cout << "Enter the first polynom:\n";
			cin >> s1;
			p1 = polynom(s1);
			cout << "Enter the second polynom:\n";
			cin >> s2;
			p2 = polynom(s2);
			cout << '(' << p1 << ')' << '-' << '(' << p2 << ')' << '=' << p1 - p2 << '\n';

			system("pause");
			break;
		}
		case '3':
		{
			system("cls");

			cout << "Enter the first polynom:\n";
			cin >> s1;
			p1 = polynom(s1);
			cout << "Enter the second polynom:\n";
			cin >> s2;
			p2 = polynom(s2);
			cout << '(' << p1 << ')' << '*' << '(' << p2 << ')' << '=' << p1 * p2 << '\n';

			system("pause");
			break;
		}
		case '4':
		{
			system("cls");

			cout << "Enter polynom:\n";
			cin >> s1;
			p1 = polynom(s1);
			cout << "Enter const:\n";
			cin >> c;

			cout << '(' << p1 << ')' << '*' << c << '=' << p1 * c << '\n';

			system("pause");
			break;
		}
		case '5': break;
		}
	} while (pmenu != '5');
}