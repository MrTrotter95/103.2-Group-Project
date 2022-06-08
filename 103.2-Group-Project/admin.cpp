#include "main.h"
#include "admin.h"

/*Global Variables*/
//Alistair - 08.06.22 test push to remote repository. Comment can be deleted after
const int menuSize_admin = 7;
int selectionHighlight_admin = 0;
string mainMenuPrint_admin[menuSize_admin] = { "Accounts", "Food Menu", "Feedback", "Sales Reports", "Inventory Reports", "Discount", "Return to Main Menu" };

/*Start of Admin functionality*/
void adminMain()
{
	system("cls");
	PrintArray_AdminMenu();
	cout << "\nWelcome Admin User.\n";
    ArrowSelectionMenu_AdminMenu();
}

void PrintArray_AdminMenu() {
	for (int i = 0; i < menuSize_admin; i++)
	{
		if (i == selectionHighlight_admin)
		{
			WriteInColor(3, mainMenuPrint_admin[selectionHighlight_admin]);
			cout << endl;
		}
		else
		{
			WriteInColor(15, mainMenuPrint_admin[i]);
			cout << endl;
		}
	}
}

void ArrowSelectionMenu_AdminMenu() {
	//cout << "Use arrow keys to make selection\n\n";
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
				if (selectionHighlight_admin > 0)
				{
					selectionHighlight_admin--;
				}
				else
				{
					selectionHighlight_admin = (menuSize_admin - 1);
				}
				break;
			case KEY_DOWN:
				//This key is assigned to decrease the highlighted number by 1
				if (selectionHighlight_admin < (menuSize_admin - 1))
				{
					selectionHighlight_admin++;
				}
				else
				{
					selectionHighlight_admin = 0;
				}
				break;
			default:
				cout << "\nThis key is unassigned.\n";
				break;
			}

			system("cls");
			PrintArray_AdminMenu();

			switch (selectionHighlight_admin)
			{
			case 0:
				cout << "\nRun the account function\n";
				break;
			case 1:
				cout << "\nRun the food menu function\n";
				break;
			case 2:
				cout << "\nRun the feedback function\n";
				break;
			case 3:
				cout << "\nRun the sales reports function.\n";
				break;
			case 4:
				cout << "\nRun the inventory reports function.\n";
				break;
			case 5:
				cout << "\nRun the discount function\n";
				break;
			case 6:
				cout << "\nExit the program\n";
				break;
			}

			break;
		case 13:
			switch (selectionHighlight_admin)
			{
			case 0:
				cout << "Call account function";
				//loginMain();                //Calls account function
				break;
			case 1:
				cout << "Call food menu function";
				//registerMain();             //Calls food menu function
				break;
			case 2:
				cout << "Call feedback function";
				//feedbackMain();             //Calls feedback function
				break;
			case 3:
				cout << "Call sales report function";
				//menuMain();                 //Calls sales report function
				break;
			case 4:
				cout << "Call inventory function";
				//adminMain();                //Calls inventory report function
				break;
			case 5:
				cout << "Call discount function";
				//discountMain();             //Calls discount function
				break;
			case 6:
				loop = false;
				BeginProgram();	//Calls main menu function
			default:
				break;
			}
		}
	}
}