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
	int foodId;
	bool foodOrDrink;
	std::string itemName;
	double price;
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
					foodId = std::stoi(cell);
					break;
				case 1:
					if (cell == "0") {
						std::cout << "  " << "drink\t\t";
						foodOrDrink = true;
					}
					else {
						std::cout << "  " << "food\t\t";
						foodOrDrink = false;
					}
					break;
				case 2:
					std::cout << cell << "\t";
					itemName = cell;
					break;
				case 3:
					std::cout << "$" << cell << "\t\t";
					price = stod(cell);
					break;
				case 4:
					std::cout << "\n" << "  " << cell << "\t";//new line//
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
	std::string line, cell, name,orderId,childId, food1,food2,drink1,drink2,cost;
	std::vector<std::string> allOrders;
	//double cost;


	//open the order csv//
	historyOrder.open("orders.csv", std::ios::in);

	//if its open, while we are still in the file, read each line.
	if (historyOrder.is_open()) {
		std::cout << "\n order.csv is open\n";//debug//

		std::cout << "Order History for " << name << "\n";

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
			std::cout << GetItemName(stoi(food1)) << "\t";
			std::cout << GetItemName(stoi(food2)) << "\t";
			std::cout << GetItemName(stoi(drink1)) << "\t\t\t";
			std::cout << GetItemName(stoi(drink2)) << "\t\t\t";
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

		count = stol(lastId);
		
		count++;

		childId = std::to_string(count); // new child id ready for use//
		
		childProfile.clear();
		
		childProfile.push_back(childId);
		childProfile.push_back(",");//pushing child id into vector as first value//
		retry:
		//creating new childs profile
		std::cout << "Enter childs year level (4-6)\n";
		std::cin >> yearLevel;
		if (yearLevel < 4 || yearLevel > 6) {
			std::cout << "Yeear out of range\n";
			goto retry;
		}
		else {
			childProfile.push_back(std::to_string(yearLevel));//adding year level to profile//
			childProfile.push_back(",");
		}

		//switch to determine class rooom//
		std::cout << "Enter childs teacher: 1. Mr Terrance \t 2. Mrs Roopy \t 3. Mr Pong)\n";
		std::cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "Confirming child in TR\n";
			childProfile.push_back("TR");
			childProfile.push_back(",");
			break;
		case 2:
			std::cout << "Confirming child in RP\n";
			childProfile.push_back("RP");
			childProfile.push_back(",");
			break;
		case 3:
			std::cout << "Confirming child in PO\n";
			childProfile.push_back("PO");
			childProfile.push_back(",");
			break;

		default:
			std::cout << "That teacher dont Exist\n";
			childProfile.push_back("unknown");
			childProfile.push_back(",");
			break;
		}

		//entering childs name//
		std::cout << "Enter Child First Name: \n";
		std::string name;
		cin >> name;
		childProfile.push_back(name);
		childProfile.push_back(",");
		std::cout << "Enter Gender: \n 1.Male\t 2.Female \n";
		cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "Confirming: Male\n";
			childProfile.push_back("Male");
			childProfile.push_back(",");
			break;
		case 2:
			std::cout << "Confirming: Female\n";
			childProfile.push_back("Female");
			childProfile.push_back(",");
			break;
		default:
			childProfile.push_back("Unknown");
			childProfile.push_back(",");
			break;
		}

		//
		////adding & assigning dietary flags//
		//std::string flagNames[3]{ "Vegetarian","Vegan","Gluten Free" };

		//flag:
		//std::cout << "ALLERGIES OR DIERTARY REQUIREMENTS\n\n";
		//for (int i = 0; i < 3; i++) {
		//	std::cout << "Is your child " << flagNames[i] << "?\n 1. Yes \t 2. No \n";//loop prints new flag name to choose
		//	cin >> choice;

		//	switch (choice) {
		//	case 1:
		//		childProfile.push_back("0");//true
		//		childProfile.push_back(",");
		//		break;
		//	case 2:
		//		childProfile.push_back("1");//false
		//		childProfile.push_back(",");
		//		break;
		//	default:
		//		cout << "You must enter a value!";
		//		if (choice != 1) {
		//			goto flag;
		//		}
		//		if(choice != 2) {
		//		goto flag;
		//		}
		//		break;
		//	}
		//}
		fin.close();

		std::cout << "Your Child profile: \n";

		for (unsigned int i = 0; i < childProfile.size(); i++) {
			fout << childProfile[i] << ',';//add to csv file
		}
		fout << "\n";
		std::cout << "Child successfully added, " << name << "'s child ID is: " << childProfile[0] << "\n\n IMPORTANT: " <<
			"Make sure you record this as you will need it to use program.\n";
		return stol(childId);
	
		fout.close();
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

				std::cout << "Child id not found, would you like to add child? \n 1. Yes \t 2. No";
				std::cin >> choice;
				if (choice == 1) {
					AddChild(input);//add child
					isFound = true;
					fin.close();
				}
				else {
					std::cout << "try again....\n Enter child id";
					std::cin >> choice;
					CheckChild(choice);//enter again, try again
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


//void CheckFlags(int id) {
//	//file pointers//
//	std::fstream menuin, childin;
//	std::string selection = std::to_string(id);
//	std::string line, cell, childName, foodType, flag;
//	//int foodFlags[3];
//	//int childFlags[3];
//	int count{ 0 };
//
//	menuin.open("food.csv", std::ios::in);
//	
//
//	//read food file//
//	while (std::getline(menuin, line)) {
//
//		//read line to get full item details//
//		std::stringstream lineStream(line);
//		for (int i = 0; i < 1; i++) {
//			std::getline(lineStream, foodType, ',');//getting the 'food or drink flag'
//		}
//
//		//switch to warn user
//		switch (stoi(foodType)) {
//			int choice;
//		case 0:
//			if (foodType != selection) {
//				std::cout << "Must be drink...\n Enter valid drink item";
//				cin >> choice;
//				CheckFlags(choice);
//			}
//			else {
//				break;
//			}
//		case 1:
//			if (foodType != selection) {
//				std::cout << "Must be food...\n Enter valid food item";
//				cin >> choice;
//				CheckFlags(choice);
//			}
//			else {
//				break;
//			}
//		default:
//			std::cout << "Food weird...";
//			break;
//		}
//
//		//line.clear();
//		////loop to get dietary flags from food file//
//		//for (int i = 0; i < 6; i++) {
//		//	std::getline(lineStream, flag, ',');
//		//	foodFlags[i] = flag.at(i);
//		//}
//		menuin.close();
//	}
//		////start reading chlid file//
//		//childin.open("children.csv", std::ios::in);
//
//		//while (std::getline(menuin, line)) {
//		//	
//		//	std::stringstream lineStream(line);
//		//	while (std::getline(lineStream, cell, ',')) {
//		//		
//		//		if (id == stoi(cell)) {
//		//			
//		//			for (int i = 0; i < 3; i++) {
//		//				std::getline(lineStream, flag, ',');
//		//				flags[i] = flag;
//		//			}
//		//		}
//		//	
//		//	
//		//	}
//
//
//		//}
//		//
//
//		//
//
//		//if (flag != selection) {
//		//	std::cout << "WARNING:\n\n Make sure you are aware of your childs dietary requirements...";
//		//}
//		//	child.close();
//		//	menu.close();
//		//}
//	//}
//}

/*-------------------------START OF PLACE ORDER FUNCTIONALITY-------------------------*/
/*function toplace the order of a child, and store in order.csv  file:*/
void PlaceOrder(int child) {

	//variables used in funciton//
	long orderId;
	int morningTeaId,morningTeaDrinkId,lunchId,lunchDrinkId,choice;
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
	ViewMenu();
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
	

		//user menu selector//
		std::cout << "\nEnter ID of morningTea item: \n";
		std::cin >> morningTeaId;
		//CheckFlags(morningTeaId);//checks input correct//
		std::cout << "Entered: " << GetItemName(morningTeaId);
		total += GetPrice(morningTeaId);//tally price//
		currentOrder.push_back(std::to_string(morningTeaId));//push to 'cart'//

		//#2//
		std::cout << "\nEnter ID of morningTea item: \n";
		std::cin >> morningTeaDrinkId;
		//CheckFlags(morningTeaDrinkId);
		std::cout << "Entered: " << GetItemName(morningTeaDrinkId);
		total += GetPrice(morningTeaDrinkId);
		currentOrder.push_back(std::to_string(morningTeaDrinkId));

		//#3//
		std::cout << "\nEnter ID of lunch item 1: \n";
		std::cin >> lunchId;
		//CheckFlags(lunchId);
		std::cout << "Entered: " << GetItemName(lunchId);
		total += GetPrice(lunchId);
		currentOrder.push_back(std::to_string(lunchId));

		//#4//
		std::cout << "\nEnter ID of lunch item 2: \n";
		std::cin >> lunchDrinkId;
		//CheckFlags(lunchDrinkId);
		std::cout << "Entered: " << GetItemName(lunchDrinkId);
		total += GetPrice(lunchDrinkId);
		currentOrder.push_back(std::to_string(lunchDrinkId));

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