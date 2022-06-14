#include "main.h"
#include "admin.h"
#include "discount.h"

//--- Global Variables ---//
const int menuSize_admin = 6;
int selectionHighlight_admin = 0;
string mainMenuPrint_admin[menuSize_admin] = {	
											"Accounts",
											"Food Menu",
											"Feedback",
											"Sales Reports",
											"Discount",
											"Return to Main Menu"
											};

//--- File Pointers ---//
std::fstream fout_admin;														//Creates file stream for writing to files
std::fstream fin_admin;															//Creates file stream for reading files
std::fstream finUser_admin;														//Creates second file stream for reading files
std::fstream foutUser_admin;													//Creates second file stream for writing to files

//--- Admin Main Function ---//
void adminMain()
{
	system("cls");																//Clears screen
	PrintArray_AdminMenu();														//Run Print Array for admin menu
	cout << "\nWelcome Admin User.\n";											//Welcome the Admin, so User knows they're within main menu for Admin
    ArrowSelectionMenu_AdminMenu();												//Enables arrow key interaction
}

/*------------------------- START OF ADMIN MAIN MENU SECTION -------------------------*/
//--- Prints Array for Main Menu ---//
void PrintArray_AdminMenu() {
	for (int i = 0; i < menuSize_admin; i++)									//For loop running through the admin menu size
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

//--- Allows for keystrokes in menu selection ---//
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
				AccountAdmin();                //Calls account function
				break;
			case 1:
				FoodMenuAdmin();             //Calls food menu function
				break;
			case 2:
				FeedbackAdmin();            //Calls feedback function
				break;
			case 3:
				SalesReportAdmin();                 //Calls sales report function
				break;
			case 4:
				discountMain();             //Calls discount function
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

/*------------------------- END OF ADMIN MAIN MENU SECTION -------------------------*/
/*------------------------- START OF ADMIN ACCOUNT SECTION -------------------------*/

//--- Main Menu for Administration of Accounts ---//
void AccountAdmin() {
	system("cls");
	int selection;

	cout << "What would you like to do?" <<
		"\n1.Edit an Account" <<
		"\n2.Delete an Account" <<
		"\n3.Settle a Tab" <<
		"\n4.Change a Password" <<
		"\n5.Return to Admin Menu" <<
		"\nSelection: ";
	cin >> selection;

	switch (selection)
	{
	case 1:
		AccountAdmin_EditAcc();
		break;
	case 2:
		AccountAdmin_DelAcc();
		break;
	case 3:
		AccountAdmin_SettleTab();
		break;
	case 4:
		AccountAdmin_ChangePass();
		break;
	case 5:
		adminMain();
		break;
	default:
		break;
	}
} //DONE

//--- Submenu for Editing of Account Details (userDetails.csv) ---//
void AccountAdmin_EditAcc() {

	// Function Streams
	finUser_admin.open("userDetails.csv", std::ios::in);
	fout_admin.open("userDetailsNew.csv", std::ios::out | std::ios::app);

	// Function Variables
	std::string line, newData;
	int count = 1, cellBounds = 5, selection;
	std::vector<string> users;
	double idChoice, targetElement;

	// While Loop to populate vector users and cout cells
	while (std::getline(finUser_admin, line))
	{
		std::stringstream lineStream(line);
		string cell;
		while (std::getline(lineStream, cell, ','))
		{
			if (count % cellBounds == 0)
			{
				cout << cell << "\n";
				users.push_back(cell);
				count++;
			}
			else
			{
				cout << cell << " ";
				users.push_back(cell);
				count++;
			}
		}
	}

	// Prompt to choose ID to edit
	cout << "\nWhich ID to edit?\n[ID]: ";
	cin >> idChoice;
	cout << "\nWhich element to edit for User?\n1. Gender, 2. Phone Number or 3. Date of Birth [" << idChoice << "]: ";
	cin >> targetElement;
	cout << "\nWhat would you like to change that element to?\n[New Data]: ";
	cin >> newData;

	// Checking if input is correct, then setting targetted cell as newData, else recursion of this function
	if (targetElement >= 1 && targetElement <= 3)
	{
		if (targetElement == 1)
		{
			if (newData == "m" || newData == "f" || newData == "o")
			{
				users.at((cellBounds * (idChoice - 1)) + targetElement) = newData;
				cout << users[(cellBounds * (idChoice - 1)) + targetElement];
			}
			else
			{
				cout << "Invalid selection, must enter an m, f or o. Try again.\n";
				AccountAdmin_EditAcc();
			}
		}
		else if (targetElement == 2)
		{
			if (isNumber(newData))
			{
				users.at((cellBounds * (idChoice - 1)) + targetElement) = newData;
				cout << users[(cellBounds * (idChoice - 1)) + targetElement];
			}
			else
			{
				cout << "Invalid selection, must enter a phone number. Try again.\n";
				AccountAdmin_EditAcc();
			}
		}
		else if (targetElement == 3)
		{
			if (isNumber(newData))
			{
				users.at((cellBounds * (idChoice - 1)) + targetElement) = newData;
				cout << users[(cellBounds * (idChoice - 1)) + targetElement];
			}
			else
			{
				cout << "Invalid selection, must enter a date in the format of: DDMMYY. Try again.\n";
				AccountAdmin_EditAcc();
			}
		}
		else 
		{
			cout << "Invalid selection, must enter 1, 2 or 3.\n";
			AccountAdmin_EditAcc();
		}
	}
	else if (targetElement == 4)
	{
		cout << "You can only edit the discount value within the Discount Menu\n";
		AccountAdmin_EditAcc();
	}
	else if (targetElement == 0)
	{
		cout << "You cannot edit the ID for a User\n";
		AccountAdmin_EditAcc();
	}
	else
	{
		cout << "Invalid selection, try again.\n";
		AccountAdmin_EditAcc();
	}

	// Filestreaming into new file, userDetailsNew.csv
	for (int i = 0; i < users.size(); i++)
	{
		if (count % cellBounds == 0)
		{
			fout_admin << users[i] << "\n";
			count++;
		}
		else
		{
			fout_admin << users[i] << ',';
			count++;
		}
	}

	finUser_admin.close();
	fout_admin.close();

	//Deletes old CSV and renames new CSV to old CSV
	std::remove("userDetails.csv");
	std::rename("userDetailsNew.csv", "userDetails.csv");

	// Prompt for next action to take
	cout << "\nWould you like to edit another account?\n1. Edit another account\n2. Return to Menu\nSelection: ";
	cin >> selection;

	switch (selection)
	{
	case 1:
		AccountAdmin_EditAcc();
		break;
	case 2:
		AccountAdmin();
		break;
	default:
		adminMain();
		break;
	}
}

//--- Submenu for Deleting Accounts (userDetails.csv and login.csv) ---//
void AccountAdmin_DelAcc() {

	// Function Streams
	fin_admin.open("userDetails.csv", std::ios::in);
	fout_admin.open("userDetailsNew.csv", std::ios::out | std::ios::app);
	finUser_admin.open("login.csv", std::ios::in);
	foutUser_admin.open("loginNew.csv", std::ios::out | std::ios::app);

	//Function Variables
	std::string line, line2, newData;
	int count = 1, count2 = 1, cellBounds = 5, loginCellBounds = 4, selection;
	std::vector<string> users, logins;
	double idChoice;

	while (std::getline(fin_admin, line))
	{
		std::stringstream lineStream(line);
		string cell;
		while (std::getline(lineStream, cell, ','))
		{
			if (count % cellBounds == 0)
			{
				//cout << cell << "\n";
				users.push_back(cell);
				count++;
			}
			else
			{
				//cout << cell << " ";
				users.push_back(cell);
				count++;
			}
		}
	}

	while (std::getline(finUser_admin, line2))
	{
		std::stringstream lineStream(line2);
		string cell;
		while (std::getline(lineStream, cell, ','))
		{
			if (count2 % loginCellBounds == 0)
			{
				cout << cell << "\n";
				logins.push_back(cell);
				count2++;
			}
			else
			{
				if (count2 % loginCellBounds == 3)
				{
					cout << "***********"<< " ";
					logins.push_back(cell);
					count2++;
				}
				else
				{
					cout << cell << " ";
					logins.push_back(cell);
					count2++;
				}
			}
		}
	}

	cout << "\nWhich ID to delete?\n[ID]: ";
	cin >> idChoice;
	cout << "\nYou are deleting User [" << idChoice << "], are you sure?\n[y/n]: ";
	cin >> newData;

	if (newData == "y")
	{
		cout << "Account [" << idChoice << "] deleted.\n";

		// Deletes User from userDetails.csv
		for (int i = 0; i < users.size(); i++)
		{
			if (i < cellBounds * (idChoice - 1) || i >(cellBounds * (idChoice - 1)) + (cellBounds - 1))
			{
				if (count % cellBounds == 0)
				{
					fout_admin << users[i] << "\n";
					count++;
				}
				else
				{
					fout_admin << users[i] << ',';
					count++;
				}
			}
		}

		// Deletes User from login csv 
		for (int i = 0; i < logins.size(); i++)
		{
			if (i < loginCellBounds * (idChoice - 1) || i >(loginCellBounds * (idChoice - 1)) + (loginCellBounds - 1))
			{
				if (count2 % loginCellBounds == 0)
				{
					foutUser_admin << logins[i] << "\n";
					count2++;
				}
				else
				{
					foutUser_admin << logins[i] << ',';
					count2++;
				}
			}
		}
	}
	else if (newData == "n")
	{
		cout << "You chose not to delete this account.\n";
		AccountAdmin_DelAcc();
	}
	else
	{
		AccountAdmin_DelAcc();
	}

	fin_admin.close();
	fout_admin.close();
	finUser_admin.close();
	foutUser_admin.close();

	std::remove("userDetails.csv");
	std::rename("userDetailsNew.csv", "userDetails.csv");

	std::remove("login.csv");
	std::rename("loginNew.csv", "login.csv");

	cout << "\nWould you like to edit another account?\n1. Edit another account\n2. Return to Menu\nSelection: ";
	cin >> selection;

	switch (selection)
	{
	case 1:
		AccountAdmin_DelAcc();
		break;
	case 2:
		AccountAdmin();
		break;
	default:
		adminMain();
		break;
	}
}

//--- Submenu for Settling Parent Tabs ---//
void AccountAdmin_SettleTab() {
	//print users
	//target user to edit
	//confirm settle tab
	//output to new csv
	//delete old csv and rename new csv
	//loop menu
}

//--- Submenu for Changing User Password ---//
void AccountAdmin_ChangePass() {

	finUser_admin.open("login.csv", std::ios::in);
	fout_admin.open("loginNew.csv", std::ios::out | std::ios::app);


	std::string line, lineDisc, newData;
	int count = 1, count2 = 1, idCount = 1, selection;
	std::vector<string> users;
	double idChoice;

	while (std::getline(finUser_admin, line))
	{
		std::stringstream lineStream(line);
		string cell;
		while (std::getline(lineStream, cell, ','))
		{
			if (count % 4 == 0)
			{
				cout << cell << "\n";
				users.push_back(cell);
				count++;
			}
			else
			{
				cout << cell << " ";
				users.push_back(cell);
				count++;
			}
		}
	}

	cout << "\nWhich ID to change password?\n[ID]: ";
	cin >> idChoice;
	cout << "\nWhat would you like to change the password to?\n[New Password]: ";
	cin >> newData;

	users.at((4 * (idChoice - 1)) + 2) = newData;
	cout << users[(4 * (idChoice - 1)) + 2];

	for (int i = 0; i < users.size(); i++)
	{
		if (count % 4 == 0)
		{
			fout_admin << users[i] << "\n";
			count++;
		}
		else
		{
			fout_admin << users[i] << ',';
			count++;
		}
	}

	finUser_admin.close();
	fout_admin.close();

	std::remove("login.csv");
	std::rename("loginNew.csv", "login.csv");

	cout << "\nWould you like to edit another password?\n1. Edit another password\n2. Return to Menu\nSelection: ";
	cin >> selection;

	switch (selection)
	{
	case 1:
		AccountAdmin_ChangePass();
		break;
	case 2:
		AccountAdmin();
		break;
	default:
		adminMain();
		break;
	}
}

/*------------------------- END OF ADMIN ACCOUNT SECTION -------------------------*/
/*------------------------- START OF ADMIN FOOD MENU SECTION -------------------------*/

//--- Main Menu for Administration of Food Menu ---//
void FoodMenuAdmin() {
	system("cls");
	int selection;

	cout << "What would you like to do?\n1. View Menu\n2. Add New Item\n3. Edit Existing Item\n4. Delete Existing Item\n5. Return to Admin Menu\nSelection: ";
	cin >> selection;

	switch (selection)
	{
	case 1:
		FoodMenuAdmin_ViewMenu();
		break;
	case 2:
		FoodMenuAdmin_AddItem();
		break;
	case 3:
		FoodMenuAdmin_EditItem();
		break;
	case 4:
		FoodMenuAdmin_DelItem();
		break;
	case 5:
		adminMain();
		break;
	default:
		break;
	}
}

//--- Submenu to Display Currently Active Menu ---//
void FoodMenuAdmin_ViewMenu() {
	// Function Streams
	fin_admin.open("food.csv", std::ios::in);

	// Function Variables
	std::string line, newData;
	int count = 1, cellBounds = 7, selection;
	std::vector<string> food;
	double idChoice, targetElement;

	// While Loop to populate vector users and cout cells
	cout << "\nID\t1: Food\t\tName\t\t\tPrice\tVege\tVegan\tGluten Free\n";
	cout << "\t0: Drink\t\t\t\t$\t1: Is not Vege, Vegan or GF\n";
	cout << "***********************************************************************************\n";
	while (std::getline(fin_admin, line))
	{
		std::stringstream lineStream(line);
		string cell;
		while (std::getline(lineStream, cell, ','))
		{
			if (count % cellBounds == 0)
			{
				cout << cell << "\n";
				food.push_back(cell);
				count++;
			}
			else
			{
				if (count % cellBounds == 2 || count % cellBounds == 3)
				{
					cout << cell << "\t\t";
					food.push_back(cell);
					count++;
				}
				else {
					cout << cell << "\t";
					food.push_back(cell);
					count++;
				}
			}
		}
	}

	fin_admin.close();

	// Prompt for next action to take
	cout << "\n1. Return to Menu\nSelection: ";
	cin >> selection;

	switch (selection)
	{
	case 1:
		FoodMenuAdmin();
		break;
	default:
		adminMain();
		break;
	}
}

//--- Submenu to Add Food Item to Currently Active Menu ---//
void FoodMenuAdmin_AddItem() {
	// Function Streams
	fin_admin.open("food.csv", std::ios::in);
	fout_admin.open("foodNew.csv", std::ios::out | std::ios::app);

	// Function Variables
	std::string line, newIsFood, newFoodName, newFoodPrice, newIsVege, newIsVegan, newIsGF;
	int count = 1, count2 = 1, cellBounds = 7, selection;
	std::vector<string> food;

	// While Loop to populate vector users and cout cells
	cout << "\nID\t1: Food\t\tName\t\t\tPrice\tVege\tVegan\tGluten Free\n";
	cout << "\t0: Drink\t\t\t\t$\t1: Is not Vege, Vegan or GF\n";
	cout << "***********************************************************************************\n";
	while (std::getline(fin_admin, line))
	{
		std::stringstream lineStream(line);
		string cell;
		while (std::getline(lineStream, cell, ','))
		{
			if (count % cellBounds == 0)
			{
				cout << cell << "\n";
				food.push_back(cell);
				count++;
			}
			else
			{
				if (count % cellBounds == 2 || count % cellBounds == 3)
				{
					cout << cell << "\t\t";
					food.push_back(cell);
					count++;
				}
				else {
					cout << cell << "\t";
					food.push_back(cell);
					count++;
				}
			}
		}
	}

	// Prompt to choose ID to edit

	cout << "\nIs your new item a 1: Food or 0: Drink?\n[1 or 0]: ";
	cin >> newIsFood;
	if (newIsFood == "1" || newIsFood == "0")
	{
		cin.ignore();
		cout << "\nName your new food item\n[Name]: ";
		getline(cin, newFoodName);
		if (!newFoodName.empty())
		{
			cout << "\nWhat is the price of " << newFoodName << "?\n[$]: ";
			cin >> newFoodPrice;
			if (isNumber(newFoodPrice))
			{
				cout << "\nIs " << newFoodName << " Vegetarian? 0: Yes, 1: No\n[0 or 1]: ";
				cin >> newIsVege;
				if (newIsVege == "0" || newIsVege == "1")
				{
					cout << "\nIs " << newFoodName << " Vegan? 0: Yes, 1: No\n[0 or 1]: ";
					cin >> newIsVegan;
					if (newIsVegan == "0" || newIsVegan == "1")
					{
						cout << "\nIs " << newFoodName << " Gluten Free? 0: Yes, 1: No\n[0 or 1]: ";
						cin >> newIsGF;
						if (newIsGF == "0" || newIsGF == "1")
						{
							for (int i = 0; i < food.size(); i++)
							{
								if (count2 % cellBounds == 0)
								{
									fout_admin << food[i] << "\n";
									count2++;
								}
								else
								{
									fout_admin << food[i] << ',';
									count2++;
								}
							}

							fout_admin << ((count / cellBounds) + 1) << ','  << newIsFood << ',' << newFoodName << ',' << newFoodPrice << ',' << newIsVege << ',' << newIsVegan << ',' << newIsGF << "\n";
						}
						else
						{
							cout << "Incorrect entry. Please enter a 0 for Yes, or 1 for No\n";
						}
					}
					else
					{
						cout << "Incorrect entry. Please enter a 0 for Yes, or 1 for No\n";
					}
				}
				else
				{
					cout << "Incorrect entry. Please enter a 0 for Yes, or 1 for No\n";
				}
			}
			else
			{
				cout << "Incorrect entry. Please enter a price amount\n";
			}
		}
		else
		{
			cout << "Incorrect entry. Food item needs a name\n";
		}
	}
	else
	{
		cout << "Incorrect entry. Enter a 1 for Food or 0 for Drink only.\n";
	}

	fin_admin.close();
	fout_admin.close();

	//Deletes old CSV and renames new CSV to old CSV
	std::remove("food.csv");
	std::rename("foodNew.csv", "food.csv");

	// Prompt for next action to take
	cout << "\nWould you like to add another item?\n1. Add another item\n2. Return to Menu\nSelection: ";
	cin >> selection;

	switch (selection)
	{
	case 1:
		FoodMenuAdmin_AddItem();
		break;
	case 2:
		FoodMenuAdmin();
		break;
	default:
		adminMain();
		break;
	}
}

//--- Submenu to Edit Food Item within Currently Active Menu ---//
void FoodMenuAdmin_EditItem() {
	// Function Streams
	fin_admin.open("food.csv", std::ios::in);
	fout_admin.open("foodNew.csv", std::ios::out | std::ios::app);

	// Function Variables
	std::string line, newData;
	int count = 1, cellBounds = 7, selection;
	std::vector<string> food;
	double idChoice, targetElement;

	// While Loop to populate vector users and cout cells
	cout << "\nID\t1: Food\t\tName\t\t\tPrice\tVege\tVegan\tGluten Free\n";
	cout << "\t0: Drink\t\t\t\t$\t1: Is not Vege, Vegan or GF\n";
	cout << "***********************************************************************************\n";
	while (std::getline(fin_admin, line))
	{
		std::stringstream lineStream(line);
		string cell;
		while (std::getline(lineStream, cell, ','))
		{
			if (count % cellBounds == 0)
			{
				cout << cell << "\n";
				food.push_back(cell);
				count++;
			}
			else
			{
				if (count % cellBounds == 2 || count % cellBounds == 3)
				{
					cout << cell << "\t\t";
					food.push_back(cell);
					count++;
				}
				else {
					cout << cell << "\t";
					food.push_back(cell);
					count++;
				}
			}
		}
	}

	// Prompt to choose ID to edit
	cout << "\nWhich Food ID to edit?\n[ID]: ";
	cin >> idChoice;
	cout << "\nWhich element to edit for Food Item?\n1. Is Food, 2. Name, 3. Price, 4. Vege Flag, 5. Vegan Flag or 6. Gluten Flag [ Food ID: " << idChoice << "]: ";
	cin >> targetElement;
	cin.ignore();
	cout << "\nWhat would you like to change that element to?\n[New Data]: ";
	getline(cin, newData);

	// Checking if input is correct, then setting targetted cell as newData, else recursion of this function
	if (targetElement >= 1 && targetElement <= 6)
	{
		if (targetElement == 1)
		{
			if (newData == "1" || newData == "0")
			{
				food.at((cellBounds * (idChoice - 1)) + targetElement) = newData;
				cout << food[(cellBounds * (idChoice - 1)) + targetElement];
			}
			else
			{
				cout << "Invalid selection, must enter a 1 or 0. Try again.\n";
				FoodMenuAdmin_EditItem();
			}
		}
		else if (targetElement == 2)
		{
			if (!newData.empty())
			{
				food.at((cellBounds * (idChoice - 1)) + targetElement) = newData;
				cout << food[(cellBounds * (idChoice - 1)) + targetElement];
			}
			else
			{
				cout << "Invalid selection, must enter a name. Try again.\n";
				FoodMenuAdmin_EditItem();
			}
		}
		else if (targetElement == 3)
		{
			if (isNumber(newData))
			{
				food.at((cellBounds * (idChoice - 1)) + targetElement) = newData;
				cout << food[(cellBounds * (idChoice - 1)) + targetElement];
			}
			else
			{
				cout << "Invalid selection, must enter a price without $. Try again.\n";
				FoodMenuAdmin_EditItem();
			}
		} else if (targetElement == 4)
		{
			if (newData == "1" || newData == "0")
			{
				food.at((cellBounds * (idChoice - 1)) + targetElement) = newData;
				cout << food[(cellBounds * (idChoice - 1)) + targetElement];
			}
			else
			{
				cout << "Invalid selection, must enter a 1 or 0. Try again.\n";
				FoodMenuAdmin_EditItem();
			}
		} else if (targetElement == 5)
		{
			if (newData == "1" || newData == "0")
			{
				food.at((cellBounds * (idChoice - 1)) + targetElement) = newData;
				cout << food[(cellBounds * (idChoice - 1)) + targetElement];
			}
			else
			{
				cout << "Invalid selection, must enter a 1 or 0. Try again.\n";
				FoodMenuAdmin_EditItem();
			}
		} else if (targetElement == 6)
		{
			if (newData == "1" || newData == "0")
			{
				food.at((cellBounds * (idChoice - 1)) + targetElement) = newData;
				cout << food[(cellBounds * (idChoice - 1)) + targetElement];
			}
			else
			{
				cout << "Invalid selection, must enter a 1 or 0. Try again.\n";
				FoodMenuAdmin_EditItem();
			}
		}
		else
		{
			cout << "Invalid selection, must enter 1, 2, 3, 4, 5 or 6.\n";
			FoodMenuAdmin_EditItem();
		}
	}
	else if (targetElement == 0)
	{
		cout << "You cannot edit the ID for a food item\n";
		FoodMenuAdmin_EditItem();
	}
	else
	{
		cout << "Invalid selection, try again.\n";
		FoodMenuAdmin_EditItem();
	}

	// Filestreaming into new file, foodNew.csv
	for (int i = 0; i < food.size(); i++)
	{
		if (count % cellBounds == 0)
		{
			fout_admin << food[i] << "\n";
			count++;
		}
		else
		{
			fout_admin << food[i] << ',';
			count++;
		}
	}

	fin_admin.close();
	fout_admin.close();

	//Deletes old CSV and renames new CSV to old CSV
	std::remove("food.csv");
	std::rename("foodNew.csv", "food.csv");

	// Prompt for next action to take
	cout << "\nWould you like to edit another item?\n1. Edit another item\n2. Return to Menu\nSelection: ";
	cin >> selection;

	switch (selection)
	{
	case 1:
		FoodMenuAdmin_EditItem();
		break;
	case 2:
		FoodMenuAdmin();
		break;
	default:
		adminMain();
		break;
	}
}

//--- Submenu to Delete Food Item within Currently Active Menu ---//
void FoodMenuAdmin_DelItem() {
	// Function Streams
	fin_admin.open("food.csv", std::ios::in);
	fout_admin.open("foodNew.csv", std::ios::out | std::ios::app);

	//Function Variables
	std::string line, newData;
	int count = 1, cellBounds = 7, selection;
	std::vector<string> food;
	double idChoice;

	// While Loop to populate vector users and cout cells
	cout << "\nID\t1: Food\t\tName\t\t\tPrice\tVege\tVegan\tGluten Free\n";
	cout << "\t0: Drink\t\t\t\t$\t1: Is not Vege, Vegan or GF\n";
	cout << "***********************************************************************************\n";
	while (std::getline(fin_admin, line))
	{
		std::stringstream lineStream(line);
		string cell;
		while (std::getline(lineStream, cell, ','))
		{
			if (count % cellBounds == 0)
			{
				cout << cell << "\n";
				food.push_back(cell);
				count++;
			}
			else
			{
				if (count % cellBounds == 2 || count % cellBounds == 3)
				{
					cout << cell << "\t\t";
					food.push_back(cell);
					count++;
				}
				else {
					cout << cell << "\t";
					food.push_back(cell);
					count++;
				}
			}
		}
	}

	cout << "\nWhich ID to delete?\n[ID]: ";
	cin >> idChoice;
	cout << "\nYou are deleting Food Item [" << idChoice << "], are you sure?\n[y/n]: ";
	cin >> newData;

	if (newData == "y")
	{
		cout << food[(cellBounds * (idChoice - 1) + 2)] << " deleted.\n";

		// Deletes Food from food.csv
		for (int i = 0; i < food.size(); i++)
		{
			if (i < cellBounds * (idChoice - 1) || i >(cellBounds * (idChoice - 1)) + (cellBounds - 1))
			{
				if (count % cellBounds == 0)
				{
					fout_admin << food[i] << "\n";
					count++;
				}
				else
				{
					fout_admin << food[i] << ',';
					count++;
				}
			}
		}
	}
	else if (newData == "n")
	{
		cout << "You chose not to delete this item.\n";
		FoodMenuAdmin_DelItem();
	}
	else
	{
		FoodMenuAdmin_DelItem();
	}

	fin_admin.close();
	fout_admin.close();

	std::remove("food.csv");
	std::rename("foodNew.csv", "food.csv");

	cout << "\nWould you like to delete another item?\n1. Delete another item\n2. Return to Menu\nSelection: ";
	cin >> selection;

	switch (selection)
	{
	case 1:
		FoodMenuAdmin_DelItem();
		break;
	case 2:
		FoodMenuAdmin();
		break;
	default:
		adminMain();
		break;
	}
}

/*------------------------- END OF ADMIN FOOD MENU SECTION -------------------------*/
/*------------------------- START OF ADMIN FEEDBACK SECTION -------------------------*/

//--- Main Menu for Administration of Feedback ---//
void FeedbackAdmin() {
	system("cls");
	int selection;

	cout << "Menu not yet implemented..\n1. Add Discount\n2. Set Discount\n3. Delete Discount\n4. Return to Admin Menu\nSelection: ";
	cin >> selection;

	switch (selection)
	{
	case 1:
		AddDiscount();
		break;
	case 2:
		SetDiscount();
		break;
	case 3:
		DeleteDiscount();
		break;
	case 4:
		adminMain();
		break;
	default:
		break;
	}
}

//--- Submenu to Mark Feedback as Complete ---//
void FeedbackAdmin_Mark() {

}

//--- Submenu to Display Resolved Feedback ---//
void FeedbackAdmin_Resolved() {

}

/*------------------------- END OF ADMIN FEEDBACK SECTION -------------------------*/
/*------------------------- START OF ADMIN SALES SECTION -------------------------*/

//--- Main Menu for Sales Reports ---//
void SalesReportAdmin() {
	system("cls");
	int selection;

	cout << "Menu not yet implemented..\n1. Add Discount\n2. Set Discount\n3. Delete Discount\n4. Return to Admin Menu\nSelection: ";
	cin >> selection;

	switch (selection)
	{
	case 1:
		AddDiscount();
		break;
	case 2:
		SetDiscount();
		break;
	case 3:
		DeleteDiscount();
		break;
	case 4:
		adminMain();
		break;
	default:
		break;
	}
}

/*------------------------- END OF ADMIN SALES SECTION -------------------------*/
/*------------------------- START OF ADMIN DISCOUNT SECTION -------------------------*/

//--- Main Menu for Administration of Discount ---//
void DiscountAdmin() {
	system("cls");
	discountMain();
}

/*-------------------------END OF ADMIN DISCOUNT SECTION -------------------------*/

/*------------------------- MISC FUNCTIONS -------------------------*/

//--- Checks if string is a number and returns true if so ---//
bool isNumber(const string& str)
{
	for (char const& c : str) {
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}