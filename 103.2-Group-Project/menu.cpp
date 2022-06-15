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
using namespace std;

void ViewMenu() {
	Menu item;
	std::fstream menu;
	menu.open("food.csv", std::ios::in);
	std::vector<std::string> fullMenu;
	std::string line, cell;
	int count{ 0 };
	if (menu.is_open()) {
		std::cout << "\n food.csv is open\n";

		std::cout << "Displaying full menu: \n-Menu ID---Type-\t-Item Name-\t-Price-\t-----------------------Dietary Information-------------\n";
		
		while (std::getline(menu, line)); {
			cout << "\n";
			std::stringstream lineStream(line);
			while (std::getline(lineStream, cell, ',')) {
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
}

	
	//menu.close();


/*function to view orders:
*first we create a string vector called "history" to populate with orders read from the csv file, and to make sure its for the right student, we
are using the students ID in the function call parameter.*/
void ViewOrders(int child) {
	std::vector<string> history;
	string strId = to_string(child);
	std::fstream historyOrder;
	std::string line, cell;

	//open csv
	historyOrder.open("orders.csv", std::ios::in | std::ios::binary);

	//if its open, while we are still in the file, read each line.
	if (historyOrder.is_open()) {
		std::cout << "\n order.csv is open\n";
		bool onRightLine = (cell == strId);

		std::cout << "Orders for ID " << strId;
		while (std::getline(historyOrder, line)) {
			std::stringstream lineStream(line);

			//8 times(as per number of cells in order.csv), read the cell.
			for (int i = 0; i < 8; i++) {
				std::getline(lineStream, cell, ',');
				history.push_back(cell);
				if (i == 2 && !onRightLine) {//cell at i == 2 we have the right childID, but the wrong line, so remove what was just added
					history.pop_back();
				}
				else if (i == 2 && cell == strId) {
					onRightLine = true;
					std::cout << "yess";

				}
				std::cout << "\n";
			}
		}

		historyOrder.close();
	}
	else {
		std::cout << "Orders.csv: file not found";
	}
}

int AddChild(int input) {
	string childId;
	int yearLevel;
	string teacherCode;
	string childName;
	int choice;
	std::fstream classInfo;
	std::vector<std::string> childProfile;
	classInfo.open("children.csv", std::ios::in | std::ios::app);


	if (classInfo.is_open()) {
		std::cout << "\n children.csv is open\n";
		classInfo.seekg(-6, std::ios_base::end);//finding last child ID in file
		string ch;
		classInfo.get(ch[0]);

		childId = stoi(ch) + 1;//assigning orderID to +1 of last id

		//TODO: should i use the vector to push?

		childProfile.push_back(childId);
		//classInfo << childId << ",";//input child id
		std::string line;



		std::cout << "Enter childs year level (4-6)";
		std::cin >> yearLevel;
		if (yearLevel < 1 || yearLevel > 13) {
			std::cout << "Yeear out of range";
			cin >> yearLevel;
			//goto?
		}
		else {
			childProfile.push_back(to_string(yearLevel));
		}

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
		std::cout << "Enter Child name: \n";
		string name;
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

		for (int i = 0; i < 8; i++) {//i know its 8, but i forget the size() converter thing
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
	string strid = to_string(input);
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
				if (strid == cell) {
					std::cout << "Child loaded...";
					kid.close();
					std::cout << "Choose: 1: viewOrders 2.PlaceOrder 3.exit:";
					std::cin >> choice;
					switch (choice) {
					case 1:
						ViewOrders(input);
						break;
					case 2:
						PlaceOrder(input);
						break;
					case 3:
						break;
					default:
						std::cout << "something went wrong here";
						break;

					}
				}


			}
			if (kid.end && !isFound) {

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

float GetPrice(int id) {
	std::string menuId = to_string(id);
	std::ifstream menu;
	menu.open("food.csv");
	std::vector<float> priceVec;

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
				priceVec.push_back(stof(cell));
				return (stof(cell));

			}




		}
	}
	else {
		std::cout << "food.csv: file not found....";
	}
}

void ScanMenu(int input) {
	bool isItem = false;
	std::fstream menu;
	menu.open("food.csv", std::ios::out);
	string line, cell;
	string item = to_string(input);
	string price;
	string currentitem;
	if (menu.is_open()) {
		std::cout << "\n food.csv is open\n";
		while (!isItem) {
			std::stringstream lineStream(line);
			while (std::getline(menu, line)) {

				while (std::getline(lineStream, cell, ',')) {
					if (cell == item) {

						for (int i = 0; i < 3; i++) {
							std::getline(lineStream, cell, ',');
							currentitem = cell;
						}
						std::cout << "Adding " << currentitem << " to order.\t";

						isItem = true;
					}
				}
				menu.close();
			}
		}
	}
}

void PlaceOrder(int child) {
	bool notorder = true;
	float total = 0;
	std::cout << "Running PlaceOrder();";
	std::fstream menu, order, kid;
	std::vector<string> currentOrder;
	std::string line, cell;
	std::string childId{ to_string(child) };
	int count{ 0 };
	ViewMenu();
	order.open("orders.csv", std::ios::in | std::ios::out);

	if (order.is_open()) {
		std::cout << "\n order.csv is open\n";
		order.seekg(-25, std::ios::end);
		std::getline(order, line);
		std::stringstream lineStream(line);

		std::getline(lineStream, cell, ',');
		notorder = false;
		orderId = stoi(cell) + 1;
		order << orderId << ",";
		currentOrder.push_back(to_string(orderId));
		order << childId << ",";
		currentOrder.push_back(childId);
		std::cout << "Enter ID of morningTea item: ";
		std::cin >> morningTeaId;
		//ScanMenu(morningTeaId);
		total += GetPrice(morningTeaId);
		order << morningTeaId << ",";
		currentOrder.push_back(to_string(morningTeaId));
		std::cout << "Enter ID of morningTea DRINK: ";
		std::cin >> morningTeaDrinkId;
		total += GetPrice(morningTeaDrinkId);
		order << morningTeaDrinkId << ",";
		currentOrder.push_back(to_string(morningTeaDrinkId));
		std::cout << "Enter ID of lunch item: ";
		std::cin >> lunchId;
		total += GetPrice(lunchId);
		order << lunchId << ",";
		currentOrder.push_back(to_string(lunchId));
		std::cout << "Enter ID of lunch DRINK : ";
		std::cin >> lunchDrinkId;
		total += GetPrice(lunchDrinkId);
		order << lunchDrinkId << ",";
		currentOrder.push_back(to_string(lunchDrinkId));

		//for loop to print current order as bill
		std::cout << "Bill :\n Order Number \t Child ID \t morning tea: \t Lunch: ";
		for (int i = 0; i < currentOrder.size(); i++) {
			std::cout << currentOrder[i];
		}
		std::cout << "\n\n\n\n Total Order: $" << total;

		int choice;
		std::cout << "Would you like to 1. view orders 2. Choose another child 3. exit \n";
		std::cin >> choice;
		switch (choice) {
		case 1:
			ViewOrders(child);
			break;
		case 2:
			menuMain();
			break;
		case 3:

			break;
		default:
			std::cout << "something went wrong";
		}
	}
	else {
		std::cout << "Orders.csv: file not found";
	}
}


void menuMain()
{
	ViewMenu();
	std::vector<string> bill;
	int choice;
	std::cout << "Enter child ID\n";
	std::cin >> choice;
	CheckChild(choice);
}
