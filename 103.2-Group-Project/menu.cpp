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

#include "menu.h"

/*-------------------------START OF VIEWING FUNCTIONALITY -------------------------*/
void ViewMenu() {
	Menu item;
	std::ifstream menu;
	menu.open("food.csv", std::ios::in);
	std::vector<std::string> fullMenu;
	std::string line, cell;
	int count{ 0 };
	if (menu.is_open()) {

		std::cout << "\n menu.csv is open\n";//debug

		std::cout << "Displaying full menu: \n-Menu ID---Type-\t-Item Name-\t-Price-\t-----------------------Dietary Information-------------\n";

		//while in file, read a row(line)
		while (std::getline(menu, line)) {
			std::cout << "\n";

			std::stringstream lineStream(line);
			while (std::getline(lineStream, cell, ',')) {//read each word as a cell

				//switch where count is the position of each menu element in the line
				switch (count) {
				case 0:
					std::cout << "  " << cell << "\t";
					item.foodId = std::stoi(cell);
					break;
				case 1:
					if (cell == "0") {
						std::cout << "  " << "drink\t\t";
						item.foodOrDrink = true;
					}
					else {
						std::cout << "  " << "food\t\t";
						item.foodOrDrink = false;
					}
					break;
				case 2:
					std::cout << cell << "\t";
					item.itemName = cell;
					break;
				case 3:
					std::cout << "$" << cell << "\t\t";
					item.price = stof(cell);
					break;
				case 4:
					if (cell == "0") {
						std::cout << "Vegetarian\t\t";
						item.veg = true;
					}
					else {
						std::cout << "NOT vegetarian\t";
						item.veg = false;
					}
					break;
				case 5:
					if (cell == "0") {
						std::cout << "Vegan\t\t";
						item.vegan = true;
					}
					else {
						std::cout << "\tNOT vegan\t";
						item.vegan = false;
					}
					break;
				case 6:
					if (cell == "0") {
						std::cout << "Gluten Free\t\t";
						item.gf = true;
					}
					else {
						std::cout << "NOT gluten free\t";
						item.gf = false;
					}
					break;
				case 7:
					std::cout << "\n" << "  " << cell << "\t";
					count = 0;
					break;
				default:
					std::cout << "something went wrong...?";
					break;
				}
				count++;
				fullMenu.push_back(cell);

			}



		}

	}
	menu.close();
}

/*function to view previous orders of child:*/
void ViewOrders(int child) {
	std::vector<std::string> history;
	std::string strId{ std::to_string(child) };
	std::fstream historyOrder;
	std::string line, cell, orderId,childId, food1,food2,drink1,drink2,cost;
	std::vector<std::string> allOrders;
	//double cost;


	//open the order csv//
	historyOrder.open("orders.csv", std::ios::in);

	//if its open, while we are still in the file, read each line.
	if (historyOrder.is_open()) {
		std::cout << "\n order.csv is open\n";//debug//

		std::cout << "Order History for " << childName << "\n";

		//formatting for order view//
		std::cout << "Order Number \t Child ID \t morning tea \t lunch \t total \n";
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
			std::cout << GetItemName(stoi(food1)) << "\t\t\t";
			std::cout << GetItemName(stoi(food2)) << "\t";
			std::cout << GetItemName(stoi(drink1)) << "\n\t\t\t";
			std::cout << GetItemName(stoi(drink2)) << "\n\t\t\t";

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


				//for (int i = 0; i < allOrders.size(); i++) {
				//	cout << allOrders[i];
				//}


				//allOrders.push_back(cell);
				//if (cell == strId) {

				//	//history.push_back(cell);
				//	for (int i = 0; i < allOrders.size(); i++) {
				//		if (cell == strId) {
				//			history.push_back(allOrders[i]);
				//		}
				//	}

				//	for (int i = 0; i < history.size(); i++) {

				//		std::cout << "\t" << history[i] << "\t";
				//		std::cout << "allorders: " << allOrders[i];
				//	}
				/*	std::cout << "\n";
				}*/
				
			
			}
			allOrders.push_back("\n");
			//std::cout << "\n";
			
			
			////for loop to print vector//
			//for (int i = 0; i < 6; i++) {
			//	std::cout << "\t" << history[i] << "\t";
			//}
			//std::cout << "\n";

		}
		historyOrder.close();
	}
	else {
		std::cout << "Orders.csv: file not found";
	}
}
/*-------------------------END OF VIEWING FUNCTIONALITY -------------------------*/

/*-------------------------START OF CHILD FUNCTIONALITY -------------------------*/
/*function to view add a new child:*/
int AddChild(int input) {
	std::string childId;
	int yearLevel;
	std::string teacherCode;
	std::string childName;
	int choice;
	std::fstream classInfo;
	std::vector<std::string> childProfile;
	classInfo.open("children.csv", std::ios::in | std::ios::app);


	if (classInfo.is_open()) {
		std::cout << "\n children.csv is open\n";
		classInfo.seekg(-6, std::ios_base::end);//finding last child ID in file//
		std::string ch;
		std::string line;
		classInfo.get(ch[0]);

		childId = stoi(ch) + 1;//assigning orderID to +1 of last id//

		childProfile.push_back(childId);//pushing child id into vector//

		std::cout << "Enter childs year level (4-6)";
		std::cin >> yearLevel;
		if (yearLevel < 1 || yearLevel > 13) {
			std::cout << "Yeear out of range";

		}
		else {
			childProfile.push_back(std::to_string(yearLevel));
		}

		//switch to determine class rooom//
		std::cout << "Enter childs teacher 1. mr terrance 2.mrs roopy 3.mr pong) ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "Confirming child in TR";
			childProfile.push_back("TR");
			break;
		case 2:
			std::cout << "Confirming child in RP";
			childProfile.push_back("RP");
			break;
		case 3:
			std::cout << "Confirming child in PO";
			childProfile.push_back("PO");
			break;

		default:
			std::cout << "That teacher dont Exist";
			childProfile.push_back("unknown");
			break;
		}

		//entering childs name//
		std::cout << "Enter Child name: \n";
		std::string name;
		cin >> name;
		childProfile.push_back(name);
		std::cout << "Enter Gender: 1.male 2.female ";
		cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "Confirming child male";
			childProfile.push_back("Male");
			break;
		case 2:
			std::cout << "Confirming child female";
			childProfile.push_back("Female");
			break;
		default:
			childProfile.push_back("unknown");
			break;
		}



		std::cout << "Your Child profile: \n";

		for (int i = 0; i < 8; i++) {
			classInfo >> childProfile[i];
		}

		std::cout << "Child successfully added, your child ID is " << childProfile[0];
		return stoi(childId);
		classInfo.close();
	}
	else {
		cout << "children.csv: file not found";
	}
}





void CheckChild(int input) {
	int childId = input;
	std::string strId = std::to_string(input);
	int choice;
	bool isFound = false;
	std::fstream kid;
	std::string line, cell;
	kid.open("children.csv", std::ios::in);
	if (kid.is_open()) {
		while (!isFound) {
			while (std::getline(kid, line)) {
				std::stringstream lineStream(line);
				std::getline(lineStream, cell, ',');
				if (strId == cell) {
					std::cout << "Child found...";
					isFound = true;
					for (int i = 0; i < 3; i++) {
						std::getline(lineStream, cell, ',');//finds child name from file//
					}
					childName = cell;
					cout << "Viewing " << childName << "'s Profile:\n\n";

					kid.close();
				}
			}
			if (kid.eof() && !isFound) {

				std::cout << "Child id not found,, would you like to add child? 1. yes 2.no";
				std::cin >> choice;
				if (choice == 1) {
					AddChild(input);
					kid.close();
				}
				else {
					std::cout << "try again....\n Enter child id";
					std::cin >> input;
					CheckChild(input);
				}
			}
		}
	}
	else {
		std::cout << "children.csv: file not loaded";
	}
}
/*-------------------------END OF CHILD FUNCTIONALITY -------------------------*/

/*-------------------------START OF ORDER FUNCTIONALITY -------------------------*/
/*function to get item name from menuid parameter:*/
std::string GetItemName(int id) {
	std::string menuId = std::to_string(id);
	std::ifstream menu;
	menu.open("food.csv");

	std::string line, cell, price;
	int count{ 0 };
	if (menu.is_open()) {

		while (std::getline(menu, line)) {

			std::stringstream lineStream(line);
			std::getline(lineStream, cell, ',');
			if (menuId == cell) {
				for (int i = 0; i < 2; i++) {
					std::getline(lineStream, cell, ',');
				}

				return cell;//returning cell info back to function call to print item name//
				menu.close();
			}
		}
	}
	else {
		std::cout << "food.csv: file not found....";
	}
}

/*function to get price of item from menuid parameter:*/
double GetPrice(int id) {
	std::string menuId = std::to_string(id);
	std::ifstream menu;
	menu.open("food.csv");

	std::string line, cell, price;
	int count{ 0 };
	if (menu.is_open()) {
		std::cout << "\n menu.csv is open\n";

		while (std::getline(menu, line)) {

			std::stringstream lineStream(line);
			std::getline(lineStream, cell, ',');
			if (menuId == cell) {
				for (int i = 0; i < 3; i++) {
					std::getline(lineStream, cell, ',');
				}
				return (stod(cell));
				menu.close();
			}
		}
	}
	else {
		std::cout << "food.csv: file not found....";
	}
}

void CheckFlags(int id) {
	std::string selection = std::to_string(id);
	std::ifstream menu,child;
	menu.open("food.csv");
	child.open("children.csv");
	std::string line, cell, childName, foodType, flag;
	int count{ 0 };
	if (menu.is_open() && child.is_open()) {
		std::cout << "\n menu.csv and children.csv are open\n";//debug


	while (std::getline(menu, line)) {

		std::stringstream lineStream(line);
		for (int i = 0; i < 2; i++) {
			std::getline(lineStream, foodType, ',');//getting the 'food or drink flag'
		}

		//switch to warn user
		switch (stoi(foodType)) {
		case 0:
			if (foodType != selection) {
				std::cout << "Must be drink...\n Enter valid drink item";
				
			}
			else {
				break;
			}
		case 1:
			if (foodType != selection) {
				std::cout << "Must be food...\n Enter valid food item";
				
			}
			else {
				break;
			}
		default:
			std::cout << "Food weird...";
			break;
		}

		for (int i = 0; i < 3; i++) {
			std::getline(lineStream, flag, ',');//getting the dietary flags
		}

		if (flag != selection) {
			std::cout << "WARNING:\n\n Make sure you are aware of your childs dietary requirements...";
		}
			child.close();
			menu.close();
		}
	}

}
/*-------------------------START OF PLACE ORDER FUNCTIONALITY-------------------------*/
/*function toplace the order of a child, and store in order.csv  file:*/
void PlaceOrder(int child) {

	//variables used in funciton//
	int orderId;
	int morningTeaId;
	int morningTeaDrinkId;
	int lunchId;
	int lunchDrinkId;

	bool notorder = true;
	double total = 0;
	std::cout << "Running PlaceOrder();";//debug
	std::fstream menu, order, kid;
	std::vector<std::string> currentOrder;
	std::string line, cell;
	std::string id{ std::to_string(child) };
	int count{ 0 };
	ViewMenu();
	order.open("orders.csv", std::ios::in | std::ios::out);

	if (order.is_open()) {
		std::cout << "\n order.csv is open\n";//debug
		order.seekg(-25, std::ios::end);//gives us position of LAST order id in file//
		std::getline(order, line);
		std::stringstream lineStream(line);

		std::getline(lineStream, cell, ',');
		notorder = false;
		orderId = stoi(cell) + 1;//new order id is +1 of last order id//
		currentOrder.push_back(std::to_string(orderId));
		currentOrder.push_back(id);

		//user menu selector//
		std::cout << "Enter ID of morningTea item: ";
		std::cin >> morningTeaId;
		CheckFlags(morningTeaId);//checks input correct//
		total += GetPrice(morningTeaId);//tally price//
		currentOrder.push_back(GetItemName(morningTeaId));//push to 'cart'//

		//#2//
		std::cout << "Enter ID of morningTea DRINK: ";
		std::cin >> morningTeaDrinkId;
		CheckFlags(morningTeaDrinkId);
		total += GetPrice(morningTeaDrinkId);
		currentOrder.push_back(GetItemName(morningTeaDrinkId));

		//#3//
		std::cout << "Enter ID of lunch item: ";
		std::cin >> lunchId;
		CheckFlags(lunchId);
		total += GetPrice(lunchId);
		currentOrder.push_back(GetItemName(lunchId));

		//#4//
		std::cout << "Enter ID of lunch DRINK : ";
		std::cin >> lunchDrinkId;
		CheckFlags(lunchDrinkId);
		total += GetPrice(lunchDrinkId);
		currentOrder.push_back(GetItemName(lunchDrinkId));

		//pushing final price to order cart//
		currentOrder.push_back(std::to_string(total));

		//for loop to print current order as bill//
		std::cout << "Bill :\n Order Number \t Child ID \t morning tea: \t Lunch: \n";
		for (int i = 0; i < currentOrder.size(); i++) {
			std::cout << currentOrder[i] << "\t";
		}

		std::cout << "\n\n\n\n Total Order: $" << total;

		//pushing bill to order.csv//
		for (int i = 0; i < currentOrder.size(); i++) {
			order << currentOrder[i] << ",";
		}
		order.close();
	}
	else {
		std::cout << "Orders.csv: file not found";
	}
}
/*-------------------------END OF PLACE ORDER FUNCTIONALITY-------------------------*/

/*-------------------------END OF ORDER FUNCTIONALITY-------------------------*/




/*-------------------------START OF MENU MAIN-------------------------*/
/*main menu function, user input to get child id, checks it then switches it as per user request*/
int menuMain()
{
	//global variables needed
	std::vector<std::string> bill;
	int choice;
	int childId;
	//food order functinoality starts with checking a childs existence in the system
	std::cout << "Enter child ID\n";
	std::cin >> childId;
	CheckChild(childId);

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
		break;

	}
}
/*-------------------------END OF MENU MAIN-------------------------*/