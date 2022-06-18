// CS103 Assignment 2-Group-Project
// Jordan Wall, Alistair Trotter, Brooklyn Robertson

#include "main.h"
#include "login.h"
#include "register.h"
#include "feedback.h"
#include "menu.h"
#include "admin.h"
#include "discount.h"

//--- Variables for menu display ---//
const int menuSize_main = 4;
int selectionHighlight_main = 0;
string mainMenuPrint_main[menuSize_main] = { "Login", "Register", "Contact", "Exit" };


int main()
{
	BeginProgram();
}

void BeginProgram() {
	system("cls");
	PrintArray_MainMenu();
	cout << "\nWelcome to School Lunch Ordering System.\nUse the arrow keys to navigate the menu.\n";
	ArrowSelectionMenu_MainMenu();
}

void WriteInColor(unsigned short color, string outputString)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
	cout << "  " << outputString;
	SetConsoleTextAttribute(hcon, 15);
}

void PrintArray_MainMenu() {
	cout << "********************************\n* School Lunch Ordering System *\n********************************\n";
	for (int i = 0; i < menuSize_main; i++)
	{
		if (i == selectionHighlight_main)
		{
			WriteInColor(3, mainMenuPrint_main[selectionHighlight_main]);
			cout << endl;
		}
		else
		{
			WriteInColor(15, mainMenuPrint_main[i]);
			cout << endl;
		}
	}
}

//--- Function to get character for arrow keys selection menu ---//
void ArrowSelectionMenu_MainMenu() {
	int ch, ch2;
	bool loop = true;

	while (loop)
	{
		ch = _getch();

		switch (ch)
		{
		case 224: //This line is the first num received from _getch, and specifies that it is a special character (arrow keys)
			ch2 = _getch(); //This line takes the value of the special character, which we have defined the values and named them as KEY_ followed by their direction.

			switch (ch2)
			{
			case KEY_UP:
				//This key is assigned to increase the highlighted number by 1;
				if (selectionHighlight_main > 0)
				{
					selectionHighlight_main--;
				}
				else
				{
					selectionHighlight_main = (menuSize_main - 1);
				}
				break;
			case KEY_DOWN:
				//This key is assigned to decrease the highlighted number by 1
				if (selectionHighlight_main < (menuSize_main - 1))
				{
					selectionHighlight_main++;
				}
				else
				{
					selectionHighlight_main = 0;
				}
				break;
			default:
				cout << "\nThis key is unassigned.\n";
				break;
			}

			system("cls");
			PrintArray_MainMenu();

			switch (selectionHighlight_main)
			{
			case 0:
				cout << "\nLogin to access your account and see your orders\n";
				break;
			case 1:
				cout << "\nRegister up now to place orders for your children!\n";
				break;
			case 2:
				cout << "\nGet the contact details of the Admin.\n";
				break;
			case 3:
				cout << "\nExit the program safely.\n";
				break;
			}

			break;
		case 13:
			switch (selectionHighlight_main)
			{
			case 0:
				loginMain();               
				break;
			case 1:
				registerMain();         
				break;
			case 2:
				system("cls");
				cout << "********************************\n*  Contact the administrator   *\n********************************\n  Admin: Miss Harbringer\n  Email: katieharbringer@school.co.nz\n\n";
				system("pause");
				BeginProgram();
				break;
			case 3:
				exit(0);			
			default:
				break;
			}
		}
	}
}