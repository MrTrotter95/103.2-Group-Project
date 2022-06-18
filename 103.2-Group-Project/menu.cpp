// testest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <iomanip>
#include "menu.h"

/*-------------------------START OF VIEWING FUNCTIONALITY -------------------------*/
void ViewMenu() {
	bool foodOrDrink;
	std::string menuId,itemName;
	double price;
	std::ifstream menu;
	menu.open("food.csv", std::ios::in);
	std::vector<std::string> menuFood;
	std::vector<std::string> menuDrink;
	std::string line, cell;
	int count{ 0 };
	if (menu.is_open()) {

		std::cout << "Displaying full menu: \n Menu ID \t Type \t Item Name \t\t Price \n";

		menuFood.clear();
		menuDrink.clear();
		//while in file, read a row(line)
		while (std::getline(menu, line)) {
			
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
					else if (cell == "1"){
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

		std::cout << "\nFOOD ITEMS: \n ID \t Type \t\t Item \t\t Price\n";
		for (int i = 0; i < menuFood.size(); i++) {

			k++;
				switch (k) {
				case 3:
					std::cout << std::setw(20);//field size is 20 char for formatting menu alignment//
					std::cout << menuFood[i] << "\t";
					
					break;

				case 4:
					std::cout << menuFood[i];
					std::cout << "\n";
					k = 0;
					break;
				default:
					std::cout << menuFood[i] << "\t";
					break;
					break;
				}

			

		}
		//displaying drinks//
		std::cout << "\n\DRINK ITEMS: \n ID \t Type \t Item \t Price\n";
		for (int i = 0; i < menuDrink.size(); i++) {
			std::cout << menuDrink[i] << "\t";
			k ++;
			if (k == 4) {
				std::cout << "\n\n";
				k = 0;
			}
		}
	}
	menu.close();
}

/*function to view previous orders of child:*/
void ViewOrders(int child) {
	int choice;
	std::vector<std::string> history;
	std::string strId{ std::to_string(child) };
	std::fstream historyOrder;
	std::string line, cell, name,orderId,childId, food1,food2,drink1,drink2,cost;
	std::vector<std::string> allOrders;
	

	//open the order csv//
	historyOrder.open("orders.csv", std::ios::in);

	//if its open, while we are still in the file, read each line.//
	if (historyOrder.is_open()) {

		std::cout << "Order History for " << name << "\n";

		//formatting for order view//
		std::cout << "Order Number \t Child ID \t Morning Tea \t Lunch \t Total \n";
		while (std::getline(historyOrder, line))
		{
			std::stringstream  lineStream(line);

			//grabbing all the variables ill need to display
			std::getline(lineStream, orderId, ',');
			std::getline(lineStream, childId, ',');
			std::getline(lineStream, food1, ',');
			std::getline(lineStream, drink1, ',');
			std::getline(lineStream, food2, ',');
			std::getline(lineStream, drink2, ',');
			std::getline(lineStream,cost , ',');

			//specifying which child's orders to display
			if (strId == childId) {
				std::cout << orderId <<  "\t\t" << childId << "\t";
			}

			std::cout << GetItemName(stoi(food1)) << "\t";
			std::cout << GetItemName(stoi(food2)) << "\t";
			std::cout << GetItemName(stoi(drink1)) << "\n\t\t\t";
			std::cout << GetItemName(stoi(drink2)) << "\t\t\t\t";
			std::cout << "$" << stod(cost) << "\n";
			
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
		std::cout << "Orders.csv: file not found";
	}

	retryOptions:
	std::cout << "Would you like to: \t 1. Place Order  \t 2. Change child \t 3. Exit";
	std::cin >> choice;
	switch (choice) {
	case 1:
		PlaceOrder(child);
		break;
	case 2:
		cout << "Enter Child ID";
		cin >> choice;
		CheckChild(choice);
	case 3:
		cout << "Thanks!!!!!!";
	default:
		std::cout << "something went wrong here";
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

	std::string lastId,childId,teacherCode,childName,line,value;
	int yearLevel, choice;
	long int count;
	std::vector<std::string> childProfile;
	

	//opening file to read//
	fin.open("children.csv", std::ios::in);
	fout.open("children.csv", std::ios::app);
	//finding last child profile in file//
		while (std::getline(fin, line))
		{
			childProfile.clear();

			std::stringstream lineStream(line);
			while (getline(lineStream,value, ','))
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
		std::cout << "Enter childs year level (4-6)\n";
		std::cin >> yearLevel;
		while (yearLevel < 4 || yearLevel > 6 || !isdigit(yearLevel)) {
			std::cout << "Yeear out of range\n";
			cin >> yearLevel;
		}
			childProfile.push_back(std::to_string(yearLevel));//adding year level to profile//
		

		//switch to determine class rooom//
		std::cout << "Enter childs teacher: 1. Mr Terrance \t 2. Mrs Roopy \t 3. Mr Pong)\n";
		std::cin >> choice;

		while (choice < 1 || choice > 3 || !isdigit(choice)) {//making sure only numbers entered and numbers are 1 2 or 3//
			std::cout << "Input invalid, please try again...\n";
			cin >> choice;
		}

		switch (choice) {
		case 1:
			std::cout << "Confirming child in TR\n";
			childProfile.push_back("TR");
			break;
		case 2:
			std::cout << "Confirming child in RP\n";
			childProfile.push_back("RP");
			break;
		case 3:
			std::cout << "Confirming child in PO\n";
			childProfile.push_back("PO");
			break;

		default:
			std::cout << "That teacher dont Exist\n";
			childProfile.push_back("unknown");
			break;
		}

		//entering childs name//
		std::cout << "Enter Child First Name: \n";
		std::string name;
		std::cin >> name;

		while (std::any_of(name.begin(), name.end(), ::isdigit)) { //--- Characters Only ---//
			std::cout << "Numbers found in name, please only use characters\n";
			std::cin.clear();
			std::cin >> name;
		}

		childProfile.push_back(name);//name valid, add to file//
		childProfile.push_back(",");
		std::cout << "Enter Gender: \n 1.Male\t 2.Female \n";
		std::cin >> choice;
		while (choice == 1 || choice == 2 || !isdigit(choice)) {//making sure only numbers entered and numbers are 1 or 2 //
			std::cout << "Invalid input, please try again....\n";
			std::cin >> choice;
		}
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

		std::cout << "\n Your Child profile: \n" << "ID \t NAME \t YEAR \t TEACHER CODE \t GENDER \n";
		for (unsigned int i = 0; i < childProfile.size(); i++) {
			std::cout << childProfile[i] << "\t";
			fout << childProfile[i] << ',';//add to csv file
		}
		fout << "\n";

		std::cout << "Child successfully added, " << name << "'s child ID is: " << childProfile[0] << "\n\n\t\t****** IMPORTANT: ******" <<
			"\n\t\tMake sure you record this as you will need it to use program.\n";
	
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
	std::string strId = std::to_string(input);
	std::string line, cell, name;
	bool isFound = false;
	
	//opening file to read//
	fin.open("children.csv", std::ios::in);

	while (!isFound) {//bool condition while child to be found
	while (std::getline(fin, line)) {
		std::stringstream lineStream(line);
		std::getline(lineStream, cell, ',');
			if (strId == cell) {
			std::cout << "Child found...";
				isFound = true;
				for (int i = 0; i < 3; i++) {
					std::getline(lineStream, cell, ',');//finds child name from file//
				}
				name = cell;
				std::cout << "Viewing " << name << "'s Profile:\n\n";

				fin.close();
				}
			}
			if (fin.eof() && !isFound) {//if file ends and child still not found

				std::cout << "Child id not found, What would you like to do? \n 1. Add new child \t 2. Try Again\n";
				std::cin >> choice;
				while (choice < 1 || choice > 2 || !isdigit(choice)) {
					std::cout << "Invalid input.... Try again.....";
					std::cin >> choice;
				}
				switch (choice) {
				case 1:
					AddChild(choice);//add child
					break;
				case 2:
					std::cin >> choice;
					CheckChild(choice);//enter again, try again
					break;
				default:
					std::cout << "Something went wrong, Lets go back to the main menu.\n";
					menuMain();
				}
			}
		
	}
}
/*-------------------------END OF CHILD FUNCTIONALITY -------------------------*/



/*-------------------------START OF ORDER FUNCTIONALITY -------------------------*/
/*function to get item name from menuid parameter:*/
std::string GetItemName(int id) {
	//pointers to file//
	std::fstream fout;
	std::fstream fin;

	//function variables//
	std::string line, cell, price;
	std::string menuId = std::to_string(id);
	int count{ 0 };
	bool isFound = false;

	//opening file to read//
	fin.open("food.csv", std::ios::in);

	//start reading the menu file//
	while (std::getline(fin, line)) {

		std::stringstream lineStream(line);

		//start reading each value//
		std::getline(lineStream, cell, ',');

		//if the menu id is found, read next value twice to reach item name//
		if (menuId == cell) {
			for (int i = 0; i < 2; i++) {
				std::getline(lineStream, cell, ',');
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
	std::string menuId = std::to_string(id);
	std::string line, cell, price;
	
	fin.open("food.csv", std::ios::in);

	//read file as line//
		while (std::getline(fin, line)) {

			//then read each value//
			std::stringstream lineStream(line);
			std::getline(lineStream, cell, ',');
			if (menuId == cell) {
				for (int i = 0; i < 3; i++) {
					std::getline(lineStream, cell, ',');//3rd iteration is price value
				}
				return (stod(cell));//returning price as a double to function call
				fin.close();
			}
		}
	}

void CheckFoodOrDrink(int input) {
	std::fstream fin;
	std::string line, cell;
	std::string userInput = std::to_string(input);
	int choice;
	fin.open("food.csv", std::ios::in);

	while (getline(fin, line)) {

		std::stringstream lineStream(line);

		getline(lineStream, cell, ','); // getting menu ID//
		
	}

		//switch to warn user
		switch (userInput != cell) {
			
		case 0:
				std::cout << "Must be drink...\n Enter valid drink item\n";
				std::cin >> choice;
				CheckFoodOrDrink(choice);
				break;
		case 1:
				std::cout << "Must be food...\n Enter valid food item\n";
				std::cin >> choice;
				CheckFoodOrDrink(choice);
				break;
		default:
			std::cout << "Something Went Wrong...";

			break;
		}

		fin.close();
	}







/*-------------------------START OF PLACE ORDER FUNCTIONALITY-------------------------*/
/*function toplace the order of a child, and store in order.csv  file:*/
void PlaceOrder(int child) {

	//variables used in funciton//
	long orderId;
	int choice;
	int intChild = child;

	bool notorder = true;
	double total = 0;

	//file pointers//
	std::fstream fin;
	std::fstream fout;
	std::vector<std::string> currentOrder;
	std::string line, cell, lastId, newId;
	std::string id{ std::to_string(child) };
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
		std::cout << "\nEnter ID of morningTea item: \n";
		std::cin >> choice;
		while (choice || !isdigit(choice)) {
			std::cout << "Out of Range.... Try again\n";
			std::cin >> choice;
		}
		CheckFoodOrDrink(choice);
		std::cout << "Entered: " << GetItemName(choice);
		total += GetPrice(choice);//tally price//
		currentOrder.push_back(std::to_string(choice));//push to 'cart'//

		//#2//
		std::cout << "\nEnter ID of morningTea food: \n";
		std::cin >> choice;
		while (choice || !isdigit(choice)) {
			std::cout << "Out of Range.... Try again\n";
			std::cin >> choice;
		}
		CheckFoodOrDrink(choice);
		std::cout << "Entered: " << GetItemName(choice);
		total += GetPrice(choice);
		currentOrder.push_back(std::to_string(choice));

		//#3//
		std::cout << "\nEnter ID of lunch item 1: \n";
		std::cout << "\nEnter ID of morningTea item: \n";
		std::cin >> choice;
		while (choice || !isdigit(choice)) {
			std::cout << "Out of Range.... Try again\n";
			std::cin >> choice;
		}
		CheckFoodOrDrink(choice);
		std::cout << "Entered: " << GetItemName(choice);
		total += GetPrice(choice);
		currentOrder.push_back(std::to_string(choice));

		//#4//
		std::cout << "\nEnter ID of lunch item 2: \n";
		std::cout << "\nEnter ID of morningTea item: \n";
		std::cin >> choice;
		while (choice || !isdigit(choice)) {
			std::cout << "Out of Range.... Try again\n";
			std::cin >> choice;
		}
		CheckFoodOrDrink(choice);
		std::cout << "Entered: " << GetItemName(choice);
		total += GetPrice(choice);
		currentOrder.push_back(std::to_string(choice));

		//pushing final price to order cart//
		currentOrder.push_back(std::to_string(total));

		//for loop to print current order as bill//
		std::cout << "\n\nBill :\n Order Number \t Child ID \t morning tea: \t Lunch: \n\t";

		for (unsigned int j = 0; j < (currentOrder.size()-1); j++) {
			std::cout  << currentOrder[j] << "\t";
		}

		std::cout << "\n\n Total Order: $" << total;

		//pushing bill to order.csv//
		for (unsigned int k = 0; k < currentOrder.size(); k++) {
			fout << currentOrder[k] << ',';
		}
		fout << "\n";

		retryOptions:
		std::cout << "Would you like to: \t 1. Place another order \t 2. View all orders for child \t 3. Change child \t 4. Exit";
		std::cin >> choice;
		switch (choice) {
		case 1:
			PlaceOrder(intChild);
			break;
		case 2:
			ViewOrders(intChild);
			break;
		case 3:
			cout << "Enter Child ID";
			cin >> choice;
			CheckChild(choice);
			break;
		default:
			std::cout << "something went wrong here";
			goto retryOptions;//retry function
			break;

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
	

	//variables needed//
	int choice;
	int childId;
	
	//food order functinoality starts with checking a childs existence in the system
	std::cout << "Enter child ID\n";
	std::cin >> childId;
	while (!isdigit(childId)) {
		std::cout << "Must only be numbers";
	}
	cin >> childId;
	CheckChild(childId);
	
	retryMain:
	//menu main options
	std::cout << "Choose: \n 1: View Previous Orders 2.PlaceOrder 3.Exit:";
	std::cin >> choice;
	switch (choice) {
	case 1:
		ViewOrders(childId);
		break;
	case 2:
		PlaceOrder(childId);
		break;
	case 3:
		return 0;
		break;
	default:
		std::cout << "something went wrong here";
		goto retryMain;
		break;

	}
}
/*-------------------------END OF MENU MAIN-------------------------*/