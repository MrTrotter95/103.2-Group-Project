// testest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "admin.h"
#include "main.h"
#include "login.h"
#include "menu.h"
/*-------------------------START OF VIEWING FUNCTIONALITY -------------------------*/
void ViewMenu() {
	bool foodOrDrink;
	string menuId, itemName;
	double price;
	std::ifstream menu;
	menu.open("food.csv", std::ios::in);
	std::vector<string> menuFood;
	std::vector<string> menuDrink;
	string line, cell;
	int count{ 0 };
	if (menu.is_open()) {

		std::cout << "Displaying full menu: \n Menu ID \t Type \t Item Name \t\t Price \n";

		menuFood.clear();
		menuDrink.clear();
		//while in file, read a row(line)
		while (getline(menu, line)) {

			std::stringstream lineStream(line);

			while (std::getline(lineStream, cell, ',')) {//read each word as a cell


				//switch where count is the position of each menu element in the line//
				//changing display of bools to 'food' or 'drink' for readability//

				switch (count) {
				case 0:
					menuId = cell;
					count++;
					break;
				case 1:
					if (cell == "0") {
						menuDrink.push_back(menuId);
						menuDrink.push_back("Drink");
						foodOrDrink = true;
					}
					else if (cell == "1") {
						menuFood.push_back(menuId);
						menuFood.push_back("Food");
						foodOrDrink = false;
					}
					count++;
					//count++;
					break;
				case 2:
					switch (foodOrDrink) {
					case true:
						menuDrink.push_back(cell);
						break;
					case false:
						menuFood.push_back(cell);
					}
					itemName = cell;
					count++;
					break;
				case 3:
					switch (foodOrDrink) {
					case true:
						menuDrink.push_back("$" + cell);
						break;
					case false:
						menuFood.push_back("$" + cell);
					}
					price = stod(cell);
					count = 0;
					break;
				default:
					break;
				}
			}
		}


		//displaying food//
		int k{ 0 };

		cout << "\nFOOD ITEMS: \n ID \t Type \t\t Item \t\t Price\n";
		for (int i = 0; i < menuFood.size(); i++) {

			k++;
			switch (k) {
			case 3:
				cout << std::setw(20);//field size is 20 char for formatting menu alignment//
				cout << menuFood[i] << "\t";

				break;

			case 4:
				cout << menuFood[i];
				cout << "\n";
				k = 0;
				break;
			default:
				cout << menuFood[i] << "\t";
				break;
				break;
			}



		}
		//displaying drinks//
		cout << "\n\DRINK ITEMS: \n ID \t Type \t Item \t Price\n";
		for (int i = 0; i < menuDrink.size(); i++) {
			cout << menuDrink[i] << "\t";
			k++;
			if (k == 4) {
				cout << "\n\n";
				k = 0;
			}
		}
	}
	menu.close();
}

/*function to view previous orders of child:*/
void ViewOrders(int child) {
	int choice;
	std::vector<string> history;
	string strId{ std::to_string(child) };
	std::fstream historyOrder;
	string line, cell, name, orderId, childId, f1, f2, f3, f4, cost;
	std::vector<string> allOrders;


	//open the order csv//
	historyOrder.open("orders.csv", std::ios::in);

	//if its open, while we are still in the file, read each line.//
	if (historyOrder.is_open()) {

		cout << "Order History for " << name << "\n";

		//formatting for order view//
		cout << "Order Number \t Child ID \t Morning Tea \t Lunch \t\t Total \n\n";
		while (getline(historyOrder, line))
		{
			std::stringstream  lineStream(line);

			//grabbing all the variables ill need to display
			getline(lineStream, orderId, ',');
			getline(lineStream, childId, ',');
			getline(lineStream, f1, ',');
			getline(lineStream, f2, ',');
			getline(lineStream, f3, ',');
			getline(lineStream, f4, ',');
			getline(lineStream, cost, ',');

			//specifying which child's orders to display
			if (strId == childId) {
				cout << orderId << "\t\t" << childId << "\t\t";
				cout << GetItemName(f1);
				cout << "\t";
				cout << GetItemName(f3);
				cout << "\t";
				cout << "$" << stod(cost);
				cout << "\n\t\t\t\t";
				cout << GetItemName(f2);
				cout << "\t";
				cout << GetItemName(f4);
				cout << "\n\n";
			}



		}

		//while loop to grab cells//
		while (std::getline(historyOrder, line)) {
			std::stringstream lineStream(line);
			//std::cout << line;
			while (std::getline(lineStream, cell, ',')) {
				//std::cout << "\t" << cell << "\t";

				allOrders.push_back(cell);
				allOrders.push_back(",");

			}
			allOrders.push_back("\n");
		}
		historyOrder.close();
	}
	else {
		cout << "Orders.csv: file not found";
	}

retryOptions:
	cout << "Would you like to: \t 1. Place Order  \t 2. Change child \t 3. Exit";
	cin >> choice;
	switch (choice) {
	case 1:
		PlaceOrder(child);
		break;
	case 2:
		cout << "Enter Child ID";
		cin >> choice;
		CheckChild(choice);
	case 3:
		menuMain();
	default:
		cout << "something went wrong here";
		goto retryOptions;
		break;

	}
}
/*-------------------------END OF VIEWING FUNCTIONALITY -------------------------*/

/*-------------------------START OF CHILD FUNCTIONALITY -------------------------*/
/*function to view add a new child:*/
void AddChild(int childid) {
	//pointers to file//
	std::fstream fout;
	std::fstream fin;

	//function variables//

	std::string lastId, childId, teacherCode, childName, line, value;
	int yearLevel, choice;
	char error{ 'n' };
	long int count;
	std::vector<std::string> childProfile;


	//opening file to read//
	fin.open("children.csv", std::ios::in);
	fout.open("children.csv", std::ios::out | std::ios::app);

	//finding last child profile in file//
	while (std::getline(fin, line))
	{
		childProfile.clear();

		std::stringstream lineStream(line);
		while (getline(lineStream, value, ','))
		{

			childProfile.push_back(value);

		}
	}
	for (auto i = childProfile.rbegin(); i != childProfile.rend(); i++) {

		lastId = *i;//assigning variable to store last known child id in file
	}
	fin.close();

	count = stol(lastId);

	count++;

	childId = std::to_string(count); // new child id ready for use//

	childProfile.clear();

	childProfile.push_back(childId);//pushing child id into vector as first value//

	//creating new childs profile
yearTry:
	try {
		cout << "Enter childs year level (4-6)\n";
		cin >> yearLevel;


		throw yearLevel;

	}



	catch (int) {
		if (yearLevel < 4 || yearLevel > 6) {
			cout << "Year out of range (must be 4 , 5 or 6)\n";
			cin.clear();
			goto yearTry;
		}
		else {
			childProfile.push_back(std::to_string(yearLevel));
		}
	}




	//switch to determine class rooom//
teacherTry:
	try {
		cout << "Enter childs teacher: 1. Mr Terrance \t 2. Mrs Roopy \t 3. Mr Pong)\n";
		cin >> choice;
		throw choice;
	}
	catch (char) {
		cout << "Must be number\n";
		goto teacherTry;
	}
	catch (int) {
		if (choice < 1 || choice > 3) {
			cout << "Input out of range (must be 1, 2 or 3)\n";
			goto teacherTry;
		}
		else {
			switch (choice) {
			case 1:
				cout << "Confirming child in TR\n";
				childProfile.push_back("TR");
				break;
			case 2:
				cout << "Confirming child in RP\n";
				childProfile.push_back("RP");
				break;
			case 3:
				cout << "Confirming child in PO\n";
				childProfile.push_back("PO");
				break;

			default:
				cout << "That teacher dont Exist\n";
				childProfile.push_back("unknown");
				break;
			}
		}
	}




	//entering childs name//
	cout << "Enter Child First Name: \n";
	string name;
	cin >> name;

	while (std::any_of(name.begin(), name.end(), ::isdigit)) { //--- Characters Only ---//
		cout << "Numbers found in name, please only use characters\n";
		cin.clear();
		cin >> name;
	}

	childProfile.push_back(name);//name valid, add to file//

gender:
	try {
		cout << "Enter Gender: \n 1.Male\t 2.Female \n";
		cin >> choice;
		throw choice;
	}
	catch (char) {
		cout << "Must be number\n";
		cin.clear();
		goto teacherTry;
	}
	catch (int) {
		if (yearLevel < 1 || yearLevel < 2) {
			cout << "Must choose male or female.\n";
			goto teacherTry;
		}
		else {
			switch (choice) {
			case 1:
				std::cout << "Confirming: Male\n";
				childProfile.push_back("Male");
				break;
			case 2:
				std::cout << "Confirming: Female\n";
				childProfile.push_back("Female");
				break;
			default:
				childProfile.push_back("Unknown");
				break;
			}
		}
	}




	cout << "\n Your Child profile: \n" << "ID \t YEAR \t TEACHER CODE \t NAME \t GENDER \n";
	for (unsigned int i = 0; i < childProfile.size(); i++) {

		cout << childProfile[i] << "\t";
		fout << childProfile[i] << ',';//add to csv file

	}
	fout << "\n";



	cout << "Child successfully added, " << name << "'s child ID is: " << childProfile[0] << "\n\n\t\t****** IMPORTANT: ******" <<
		"\n\t\tMake sure you record this as you will need it to use program.\n\n\n";

	fout.close();

	CheckChild(stol(childProfile[0]));
}


void CheckChild(int input) {
	//pointers to file//
	std::fstream fout;
	std::fstream fin;

	//function variables//
	int childId = input;
	int choice;
	string strId = std::to_string(input);
	string line, cell, name;
	bool isFound = false;

	//opening file to read//
	fin.open("children.csv", std::ios::in);

	while (!isFound) {//bool condition while child to be found
		while (getline(fin, line)) {
			std::stringstream lineStream(line);
			getline(lineStream, cell, ',');
			if (strId == cell) {
				cout << "Child found...";

				for (int i = 0; i < 3; i++) {
					std::getline(lineStream, cell, ',');//finds child name from file//
				}
				name = cell;
				cout << "Viewing " << name << "'s Profile:\n\n";
				isFound = true;
				fin.close();
			}
		}
		if (fin.eof()) {//if file ends
			if (!isFound) {
				cout << "Child id not found, What would you like to do? \n 1. Add new child \t 2. Try Again\n";
				cin >> choice;

				switch (choice) {
				case 1:
					AddChild(choice);//add child
					break;
				case 2:
					cout << "Enter Child ID:\n";
					cin >> choice;
					CheckChild(choice);//enter again, try again
					cin.ignore();
					break;
				default:
					cout << "Something went wrong, Lets go back to the menu.\n";
					menuMain();
				}
			}
		}
	}
}

/*-------------------------END OF CHILD FUNCTIONALITY -------------------------*/



/*-------------------------START OF ORDER FUNCTIONALITY -------------------------*/
/*function to get item name from menuid parameter:*/

string GetItemName(string id) {
	//pointers to file//
	std::fstream fout;
	std::fstream fin;

	//function variables//
	string line, cell, price;
	string menuId{ id };
	int count{ 0 };
	bool isFound = false;

	//opening file to read//
	fin.open("food.csv", std::ios::in);

	//start reading the menu file//
	while (getline(fin, line)) {

		std::stringstream lineStream(line);

		//start reading each value//
		getline(lineStream, cell, ',');

		//if the menu id is found, read next value twice to reach item name//
		if (menuId == cell) {
			for (int i = 0; i < 2; i++) {
				getline(lineStream, cell, ',');
			}
			return cell;//returning cell info back to function call to print item name//
			fin.close();
		}
	}
}


/*function to get price of item from menuid parameter:*/
double GetPrice(int id) {

	//file pointer to stream//
	std::fstream fin;

	//function variables//
	string menuId = std::to_string(id);
	string line, cell, price;

	fin.open("food.csv", std::ios::in);

	//read file as line//
	while (getline(fin, line)) {

		//then read each value//
		std::stringstream lineStream(line);
		getline(lineStream, cell, ',');
		if (menuId == cell) {
			for (int i = 0; i < 3; i++) {
				std::getline(lineStream, cell, ',');//3rd iteration is price value
			}
			return (stod(cell));//returning price as a double to function call
			fin.close();
		}
	}
}



/*-------------------------START OF PLACE ORDER FUNCTIONALITY-------------------------*/
/*function toplace the order of a child, and store in order.csv  file:*/
void PlaceOrder(int child) {

	//variables used in funciton//
	long orderId;
	string choice;
	int intChild = child;

	bool notorder = true;
	double total = 0;

	//file pointers//
	std::fstream fin;
	std::fstream fout;
	std::vector<string> currentOrder;
	string line, cell, lastId, newId;
	string id{ std::to_string(child) };
	int count{ 0 };



	fin.open("orders.csv", std::ios::in);
	fout.open("orders.csv", std::ios::app);

	//finding last order in file//
	while (std::getline(fin, line))
	{
		currentOrder.clear();

		std::stringstream lineStream(line);
		while (getline(lineStream, cell, ','))
		{
			currentOrder.push_back(cell);
		}

		for (auto g = currentOrder.rbegin(); g != currentOrder.rend(); g++) {
			lastId = *g;//assigning variable to store last known order id in file
		}
	}

	long counter = stol(lastId);//last id to long int

	counter++; //increment by 1 for new id

	orderId = counter; // new child id ready for use//

	currentOrder.clear();

	currentOrder.push_back(std::to_string(orderId));//pushing new order id into vector as first value//
	currentOrder.push_back(id);//pushing child's own id//

	ViewMenu();//display menu items//


		//user menu selector//
	cout << "\nEnter ID of morningTea item 1: \n";
	cin >> choice;
	while (!isNumber(choice)) {
		cout << "Out of Range.... Try again\n";
		cin >> choice;
	}

	cout << "Entered: " << GetItemName(choice) << "\n";
	total += GetPrice(stoi(choice));//tally price//
	currentOrder.push_back(choice);//push to 'cart'//

	//#2//
	cout << "\nEnter ID of morningTea item 2: \n";
	cin >> choice;
	while (!isNumber(choice)) {
		cout << "Out of Range.... Try again\n";
		cin >> choice;
	}

	cout << "Entered: " << GetItemName(choice) << "\n";
	total += GetPrice(stod(choice));
	currentOrder.push_back(choice);

	//#3//
	cout << "\nEnter ID of lunch item 1: \n";
	cin >> choice;
	while (!isNumber(choice)) {
		cout << "Out of Range.... Try again\n";
		cin >> choice;
	}

	cout << "Entered: " << GetItemName(choice) << "\n";
	total += GetPrice(stoi(choice));
	currentOrder.push_back(choice);

	//#4//
	cout << "\nEnter ID of lunch item 2: \n";
	cin >> choice;
	while (!isNumber(choice)) {
		cout << "Out of Range.... Try again\n";
		cin >> choice;
	}

	cout << "Entered: " << GetItemName(choice) << "\n";
	total += GetPrice(stoi(choice));
	currentOrder.push_back(choice);

	//pushing final price to order cart//
	currentOrder.push_back(std::to_string(total));

	//for loop to print current order as bill//
	cout << "\n\nBill :\n Order Number \t Child ID \t Morning Tea: \t\t\t Lunch: \n\t";

	for (unsigned int j = 0; j < (currentOrder.size()); j++) {

		switch (j) {
		case 2:
			cout << "\t" << GetItemName(currentOrder[j]) << " & " << GetItemName(currentOrder[j + 1]) << "\t";
			break;
		case 3:
			break;
		case 4:
			cout << "\t" << GetItemName(currentOrder[j]) << " & " << GetItemName(currentOrder[j + 1]) << "\t";
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			std::cout << currentOrder[j] << "\t";
			break;
		}
	}

	cout << "\n\n Total Order: $" << total << "\n\n";

	//pushing bill to order.csv//
	for (unsigned int k = 0; k < currentOrder.size(); k++) {
		fout << currentOrder[k] << ',';
	}
	fout << "\n";

retryOptions:
	cout << "Would you like to: \t 1. Place another order \t 2. View all orders for child \t 3. Change child \t 4. Exit";
	cin >> choice;
	switch (stoi(choice)) {
	case 1:
		PlaceOrder(intChild);
		break;
	case 2:
		ViewOrders(intChild);
		break;
	case 3:
		cout << "Enter Child ID";
		cin >> choice;
		CheckChild(stoi(choice));
		break;
	case 4:
		cout << "Going back....\n";
		menuMain();
		break;
	default:
		cout << "Going back....\n\n\n";
		menuMain();

	}
	fin.close();
	fout.close();
}


/*-------------------------END OF PLACE ORDER FUNCTIONALITY-------------------------*/

/*-------------------------END OF ORDER FUNCTIONALITY-------------------------*/



/*-------------------------START OF MENU MAIN-------------------------*/
/*main menu function, user input to get child id, checks it then switches it as per user request*/
int menuMain()
{
	string userId, userName, userEmail;
	int choice;
	long childId;

	cout << "Would you Like to go back to the parent menu? 1. Yes \t 2. No\n\n";
	cin >> choice;

	switch (choice) {
	case 1:
		ParentMenuDisplay();
		ParentArrowKeys(userId, userName, userEmail);
		break;

	case 2:
	retry:
		try {
			cout << "Enter childs ID: \n\n";//food order functionality starts with checking a childs existence in the system
			cin >> childId;
			if (!cin) {
				throw childId;
			}
			else {
				CheckChild(childId);
			}
		}
		catch (char) {
			cout << "Error values must be numeric.\n";
			cin.clear(); // Clear error flags
			cin.ignore(); // Clear out the input buffer
			goto retry;
		}
	retryMain:
		//menu main options
		cout << "Choose: \n 1: View Previous Orders 2.PlaceOrder 3.Exit:";
		cin >> choice;

		switch (choice) {
		case 1:
			ViewOrders(childId);
			break;
		case 2:
			PlaceOrder(childId);
			break;
		case 3:
			ParentMenuDisplay();
			ParentArrowKeys(userId, userName, userEmail);
			break;
		default:
			menuMain();
			break;
		}
		break;
	}
	



	
}
/*-------------------------END OF MENU MAIN-------------------------*/