// CS103 Assignment 2-Group-Project
// Jordan Wall, Alistair Trotter, Brooklyn Robertson

#include "main.h"
#include "login.h"
#include "register.h"
#include "feedback.h"
#include "menu.h"
#include "admin.h"
#include "discount.h"

/*Global Variables*/
const int menuSize = 7;
int selectionHighlight = 0;
string mainMenu[menuSize] = { "Login", "Register", "Feedback", "Food Menu", "Admin", "Discount", "Exit" };

int main()
{
	PrintArray_MainMenu();
	cout << "\nWelcome to School Lunch Ordering System.\nUse the arrow keys to navigate the menu.\n";
	ArrowSelectionMenu_MainMenu();
}

void WriteInColor(unsigned short color, string outputString)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
	cout << outputString;
	SetConsoleTextAttribute(hcon, 15);
}

void PrintArray_MainMenu() {
	for (int i = 0; i < menuSize; i++)
	{
		if (i == selectionHighlight)
		{
			WriteInColor(3, mainMenu[selectionHighlight]);
			cout << endl;
		}
		else
		{
			WriteInColor(15, mainMenu[i]);
			cout << endl;
		}
	}
}

/*Function to get character for arrow keys selection menu*/
void ArrowSelectionMenu_MainMenu() {
	//cout << "Use arrow keys to make selection\n\n";
	int ch, ch2;

	while (1)
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
				if (selectionHighlight > 0)
				{
					selectionHighlight--;
				}
				else
				{
					selectionHighlight = (menuSize - 1);
				}
				break;
			case KEY_DOWN:
				//This key is assigned to decrease the highlighted number by 1
				if (selectionHighlight < (menuSize - 1))
				{
					selectionHighlight++;
				}
				else
				{
					selectionHighlight = 0;
				}
				break;
			default:
				cout << "\nThis key is unassigned.\n";
				break;
			}

			system("cls");
			PrintArray_MainMenu();

			switch (selectionHighlight)
			{
			case 0:
				cout << "\nRun the login.cpp main function\n";
				break;
			case 1:
				cout << "\nRun the register.cpp main function\n";
				break;
			case 2:
				cout << "\nRun the feedback.cpp main function\n";
				break;
			case 3:
				cout << "\nRun the menu.cpp main function\n";
				break;
			case 4:
				cout << "\nRun the admin.cpp main function\n";
				break;
			case 5:
				cout << "\nRun the discount.cpp main function\n";
				break;
			case 6:
				cout << "\nExit the program\n";
				break;
			}

			break;
		case 13:
			switch (selectionHighlight)
			{
			case 0:
				loginMain();                //Calls main function from login.cpp
				break;
			case 1:
				registerMain();             //Calls main function from register.cpp
				break;
			case 2:
				feedbackMain();             //Calls main function from feedback.cpp
				break;
			case 3:
				menuMain();                 //Calls main function from menu.cpp
				break;
			case 4:
				adminMain();                //Calls main function from admin.cpp
				break;
			case 5:
				discountMain();             //Calls main function from discount.cpp
				break;
			case 6:
				exit(0);					//Exits the program
			default:
				break;
			}
		}
	}
}