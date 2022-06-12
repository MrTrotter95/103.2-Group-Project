#include "main.h"
#include "admin.h"

/*Pseudocode*/

//Enter selection of Admin menu from within staff menu.
//Perform a check on User Access Level int variable stored within their user profile.
//EXIT: If User isn't an admin, recursive function to send them back to Staff Menu.
//PASS: If User is an admin, send them to the admin main menu.

//Accounts: Admins will be able to check User Account details in full by entering their User ID.
//	LINK TO REGISTRATION.CPP - Needs access to csv
//Below that they will be able to take three actions, Edit Account, Delete Account and Print Payment Report.
// 
//	Edit Account will allow you to take the CSV file and adjust all elements.
//		This will be useful for password changing, however previous password will not be shown, the Admin can only overwrite it with a temporary password.
//
//	Delete Account will remove the User from the records.
//
//	Print Payment Report will allow us to print their order history.
//
//Food Menu: Admins will have the functionality of editing, deleting and adding menu items.
//
//Feedback: Admins will have access to feedback, to be able to confirm they are actioned.
//	LINK TO FEEDBACK.CPP - Needs access to csv
//Sales Report: Will be able to print a record of sales, either daily or weekly.
//
//Discount: Display discounts available, and add, set or delete discounts. Will also be able to add Users to the discount categories.
//	LINK TO DISCOUNT.CPP

/*Global Variables*/
const int menuSize_admin = 6;
int selectionHighlight_admin = 0;
string mainMenuPrint_admin[menuSize_admin] = { "Accounts", "Food Menu", "Feedback", "Sales Reports", "Discount", "Return to Main Menu" };

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
				cout << "\nRun the discount function\n";
				break;
			case 5:
				cout << "\nReturn to main menu\n";
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
				cout << "Call discount function";
				//discountMain();             //Calls discount function
				break;
			case 5:
				loop = false;
				BeginProgram();	//Calls main menu function
			default:
				break;
			}
		}
	}
}