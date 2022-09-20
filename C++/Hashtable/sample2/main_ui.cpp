#include "ord_table.h"
#include "hash_table.h"
#include "unord_table.h"
#include "polynom.h"
#include <iostream>
using namespace std;

char main_menu()
{
	system("cls");
	char res;
	cout << "1. Add polynom\n";
	cout << "2. Delete polynom\n";
	cout << "3. Perform an operation with polynoms\n";
	cout << "4. Show the status of the tables\n";
	cout << "5. Exit\n";

	cout << "\n\n";
	cout << "Choose menu item: ";
	cin >> res;
	return res;
}

char calc_menu()
{
	system("cls");
	char res;
	cout << "1. Add\n";
	cout << "2. Substract\n";
	cout << "3. Mult\n";
	cout << "4. Const Mult\n";
	cout << "5. To main menu\n";

	cout << "\n\n";
	cout << "Choose menu item: ";
	cin >> res;
	return res;
}

char save_menu()
{
	system("cls");
	char res;
	cout << "1. Save result\n";
	cout << "2. Continue without saving\n";
	cout << "\n\n";
	cout << "Choose menu item: ";
	cin >> res;
	return res;
}

void main() {
	unord_table<string, polynom> ut;
	ord_table<string, polynom> ot;
	hash_table<string, polynom> ht;
	polynom t;
	char pmenu;
	do {
		pmenu = main_menu();

		switch (pmenu)
		{

		case '1':
		{
			system("cls");
			string pname;
			string inp;
			try
			{
				cout << "Input polynom:\n";
				cin >> inp;
				t = polynom(inp);
				ut.Insert(t.str() ,t);
				ot.Insert(t.str(), t);
				ht.Insert(t.str(), t);
			}
			catch (...)
			{
				system("cls");
				cout << "Duplicated name\n";
				system("pause");
			}
			break;
		}

		case '2':
		{
			system("cls");

			string pname;
			try 
			{
				cout << "Input polynom:\n";
				cin >> pname;
				ut.Delete(pname);
				ot.Delete(pname);
				ht.Delete(pname);
			}
			catch (...)
			{
				system("cls");
				cout << "There's no such polynom in tables!\n";
				system("pause");
			}
			break;
		}
		case '3':
		{
			system("cls");

			do 
			{
				pmenu = calc_menu();

				switch (pmenu)
				{
				case '1':
				{
					string pn1, pn2;
					system("cls");
					try
					{
						cout << "Input first name:\n";
						cin >> pn1;
						cout << "Input second name:\n";
						cin >> pn2;

						cout << "Unordered table data result:\n";
						cout << '(' << *ut.Find(pn1) << ')' << '+' << '(' << *ut.Find(pn2) << ')' << '=' << *ut.Find(pn1) + *ut.Find(pn2) << '\n';

						cout << "Ordered table data result:\n";
						cout << '(' << *ot.Find(pn1) << ')' << '+' << '(' << *ot.Find(pn2) << ')' << '=' << *ot.Find(pn1) + *ot.Find(pn2) << '\n';

						cout << "Hash table data result:\n";
						cout << '(' << *ht.Find(pn1) << ')' << '+' << '(' << *ht.Find(pn2) << ')' << '=' << *ht.Find(pn1) + *ht.Find(pn2) << '\n';
						system("pause");
					}
					catch (...)
					{
						system("cls");
						cout << "There's no such polynom in tables!\n";
						system("pause");
						break;
					}
					do
					{
						pmenu = save_menu();
						switch (pmenu)
						{
						case '1':
						{
							polynom res;
							try
							{
								res = *ot.Find(pn1) + *ot.Find(pn2);
								ut.Insert(res.str(), res);
								ot.Insert(res.str(), res);
								ht.Insert(res.str(), res);
							}
							catch (...)
							{
								system("cls");
								cout << "Duplicatated name!\n";
								system("pause");
							}
							break;
						}
						case '2': break;
						}
					} while (pmenu != '1' && pmenu != '2');
					break;
				}
				case '2':
				{
					string pn1, pn2;
					system("cls");
					try
					{
						cout << "Input first name:\n";
						cin >> pn1;
						cout << "Input second name:\n";
						cin >> pn2;

						cout << "Unordered table data result:\n";
						cout << '(' << *ut.Find(pn1) << ')' << '-' << '(' << *ut.Find(pn2) << ')' << '=' << *ut.Find(pn1) - *ut.Find(pn2) << '\n';

						cout << "Ordered table data result:\n";
						cout << '(' << *ot.Find(pn1) << ')' << '-' << '(' << *ot.Find(pn2) << ')' << '=' << *ot.Find(pn1) - *ot.Find(pn2) << '\n';

						cout << "Hash table data result:\n";
						cout << '(' << *ht.Find(pn1) << ')' << '-' << '(' << *ht.Find(pn2) << ')' << '=' << *ht.Find(pn1) - *ht.Find(pn2) << '\n';
						system("pause");
					}
					catch (...)
					{
						system("cls");
						cout << "There's no such polynom in tables!\n";
						system("pause");
						break;
					}
					do
					{
						pmenu = save_menu();
						switch (pmenu)
						{
						case '1':
						{
							polynom res;
							try
							{
								res = *ot.Find(pn1) - *ot.Find(pn2);
								ut.Insert(res.str(), res);
								ot.Insert(res.str(), res);
								ht.Insert(res.str(), res);
							}
							catch (...)
							{
								system("cls");
								cout << "Duplicatated name!\n";
								system("pause");
							}
							break;
						}
						case '2': break;
						}
					} while (pmenu != '1' && pmenu != '2');
					break;
				}
				case '3':
				{
					string pn1, pn2;
					system("cls");
					try
					{
						cout << "Input first name:\n";
						cin >> pn1;
						cout << "Input second name:\n";
						cin >> pn2;

						cout << "Unordered table data result:\n";
						cout << '(' << *ut.Find(pn1) << ')' << '*' << '(' << *ut.Find(pn2) << ')' << '=' << *ut.Find(pn1) * *ut.Find(pn2) << '\n';

						cout << "Ordered table data result:\n";
						cout << '(' << *ot.Find(pn1) << ')' << '*' << '(' << *ot.Find(pn2) << ')' << '=' << *ot.Find(pn1) * *ot.Find(pn2) << '\n';

						cout << "Hash table data result:\n";
						cout << '(' << *ht.Find(pn1) << ')' << '*' << '(' << *ht.Find(pn2) << ')' << '=' << *ht.Find(pn1) * *ht.Find(pn2) << '\n';
						system("pause");
					}
					catch (...)
					{
						system("cls");
						cout << "There's no such polynom in tables!\n";
						system("pause");
						break;
					}
					do
					{
						pmenu = save_menu();
						switch (pmenu)
						{
						case '1':
						{
							polynom res;
							try
							{
								res = *ot.Find(pn1) * *ot.Find(pn2);
								ut.Insert(res.str(), res);
								ot.Insert(res.str(), res);
								ht.Insert(res.str(), res);
							}
							catch (...)
							{
								system("cls");
								cout << "Duplicatated name!\n";
								system("pause");
							}
							break;
						}
						case '2': break;
						}
					} while (pmenu != '1' && pmenu != '2');
					break;
				}
				case '4':
				{
					string pn1;
					double c;
					system("cls");
					try
					{
						cout << "Input first name:\n";
						cin >> pn1;
						cout << "Input constant value:\n";
						cin >> c;

						cout << "Unordered table data result:\n";
						cout << '(' << *ut.Find(pn1) << ')' << '*' << '(' << c << ')' << '=' << *ut.Find(pn1) * c << '\n';

						cout << "Ordered table data result:\n";
						cout << '(' << *ot.Find(pn1) << ')' << '*' << '(' << c << ')' << '=' << *ot.Find(pn1) * c << '\n';

						cout << "Hash table data result:\n";
						cout << '(' << *ht.Find(pn1) << ')' << '*' << '(' << c << ')' << '=' << *ht.Find(pn1) * c << '\n';
						system("pause");
					}
					catch (...)
					{
						system("cls");
						cout << "There's no such polynom in tables!\n";
						system("pause");
						break;
					}
					do
					{
						pmenu = save_menu();
						switch (pmenu)
						{
						case '1':
						{
							polynom res;
							try
							{
								res = *ot.Find(pn1) *c;
								ut.Insert(res.str(), res);
								ot.Insert(res.str(), res);
								ht.Insert(res.str(), res);
							}
							catch (...)
							{
								system("cls");
								cout << "Duplicatated name!\n";
								system("pause");
							}
							break;
						}
						case '2': break;
						}
					} while (pmenu != '1' && pmenu != '2');
					break;
				}
				case '5': break;
				}
			} while (pmenu != '5');
			pmenu = '1';
			break;

		}
		case '4':
		{
			system("cls");
			cout << "Unordered table status:\n";
			cout << ut<<endl;
			cout << "Ordered table status:\n";
			cout << ot << endl;
			cout << "Hash table status:\n";
			cout << ht << endl;
			system("pause");
			break;
		}
		case '5': break;
		}
	} while (pmenu != '5');

}
