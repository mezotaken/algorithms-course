#include "arithmetic.h"
#include <cstdlib>
#define MAX_JOURNAL_NOTES 50
using namespace std;
char main_menu()
{
	system("cls");
	char res;
	cout << "1. Calculate new expression\n";
	cout << "2. View journal\n";
	cout << "3. Exit\n\n";

	cout << "\n\n";
	cout << "Choose menu item: ";
	cin >> res;
	return res;
}


int main()
{	
	int nCalc = 0;
	string journal[MAX_JOURNAL_NOTES];

	cout.precision(15);
	arithmetic cur("");
	char pmenu;
	do {
		pmenu = main_menu();
		
		switch (pmenu)
		{
		case '1':
		{	
			system("cls");
			cout << "Input expression:"<<endl;
			string input;
			getline(cin, input);
			getline(cin,input);
			cur = arithmetic(input);
			if (cur.IsCorrect())
			{
				journal[nCalc] += (input + " = " + to_string(cur.Calc(cin)));
				journal[nCalc] += ("        |"+cur.getvars());
				cout << journal[nCalc] << endl;
				nCalc++;
				if (nCalc == MAX_JOURNAL_NOTES)
					nCalc = 0;
			}

			system("pause");
			break;
		}

		case '2':
		{
			system("cls");
			for (int i = 0; i < nCalc; i++)
				cout << journal[i] << endl;
			system("pause");
			break;
		}
		case '3': break;
		}
	} while (pmenu != '3');
	return 0;
}
