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
const int menuSize_main = 7;
int selectionHighlight_main = 0;
string mainMenuPrint_main[menuSize_main] = { "Login", "Register", "Feedback", "Food Menu", "Admin", "Discount", "Exit" };


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
	cout << outputString;
	SetConsoleTextAttribute(hcon, 15);
}

void PrintArray_MainMenu() {
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

/*Function to get character for arrow keys selection menu*/
void ArrowSelectionMenu_MainMenu() {
	//cout << "Use arrow keys to make selection\n\n";
	int ch, ch2;
	bool loop = true;

	string parent = "1";         // Delete after testing 
	string staff = "2";          // Delete after testing
	string admin = "3";          // Delete after testing

	string userId = "1";         // Delete after testing
	string userEmail = "email1"; // Delete after testing

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
				cout << "\nRun the login.cpp main function\n";
				break;
			case 1:
				cout << "\nRun the register.cpp main function\n";
				break;
			case 2:
				cout << "\nRun the feedback.cpp main function\n";
				break;
			case 3:
				cout << "\nRun the menu.cpp main function, then end the loop.\n";
				break;
			case 4:
				cout << "\nRun the admin.cpp main function, view Admin menu, then re-run main menu when returning to main menu.\n";
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
			switch (selectionHighlight_main)
			{
			case 0:
				loginMain();                //Calls main function from login.cpp
				break;
			case 1:
				registerMain();             //Calls main function from register.cpp
				break;
			case 2:
				feedbackMain(userId, userEmail, admin);    //Calls main function from feedback.cpp
				break;
			case 3:
				loop = false;
				menuMain();                 //Calls main function from menu.cpp
				break;
			case 4:
				loop = false;
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