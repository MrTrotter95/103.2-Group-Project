#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using std::cout; using std::cin;

void AddFood();
void DisplayMenu();

/*list variables needed during menu
global to start but will localise when needed*/

/*
* 'thing(enum or struct or class or vector etc)' to store place for diet, food, drink
* 'thing' to store child and parent info to create instances for orders
* parent 'thing would include user id to link together
* those 'things' are part of an order 'thing'
*
*/






/*           PLACE ORDER PlaceOrder(user userID);
* user chooses child, creates new instance of order
* order instance makes them choose through the items - this will be a function to loop each item to cin
* user inputs 1,2,3,4,5 etc depending on options 1=sandwich 2=drink etc
* eg, user chooses 1! switchcase to choose case 1, cout which kind - 1=ham 2=cheese and onion, etc THIS WILL BE ENUM
* will go back to displaying same previous menu in case user wants another sandwich for that one child
* they can choose 2 for drink. then same as above for enum to pick what kind
* will go back where for example, 5=order
* order will calc price, and say 'confirm?'
* if no, goes back to add more stuff (or remove)
* then confirm order.
* goes to payment(???? gimme info on payment)
*/








/*          ORDER VIEW ViewOrder(Order orderID, user userID);
* views the order instance:
* couts all attributes of the instance
* ------thinking of adding a contact or feedback part here? like complain about order or contact regarding order(this is why userID param)
* give option to make new order
* link goes to order using orderID in param that links to alistairs func to contact
*/
//class Child {
//	string name;
//	int classroom;
//	Diet requirement;
//};
//
//class Order {
//	int orderId;
//	OrderTime time;
//	Child name;
//	Child classroom;
//	Child Diet;
//	Menu lunchItems;
//	Menu snackItems;
//};

//enum Diet {
//	Vegan = 1,
//	NutAllergy = 2,
//	DairyFree = 4,
//	GlutenFree = 8,
//	EggFree = 16
//};
//
//enum OrderTime {
//	Morning = 0,
//	Lunch = 2
//};
//class for menu items

/*Class Menu, contains the info for a menu item. It will have an id, a type of food(enum flag)
an enum flag for diet rewuirement, a name and a price*/

class Menu {
private:
	int menuId;
	int foodType;
	int diet;
	string name;
	float price;

public:
	Menu() {//default constructor
		menuId = 0;
		foodType = 0;
		diet = 0;
		name = "Test";
		price = 0;
		
	}
	void CheckDiet(int choice) {

		cout << "Is this food dairyfree? 1.Y 2.N\n";
		cin >> choice;
		if (choice == 1) {
			diet += 2;
		}
		cout << "Is this food nutfree? 1.Y 2.N\n";
		cin >> choice;
		if (choice == 1) {
			diet += 1;
		}
		cout << "Is this food halal? 1.Y 2.N\n";
		cin >> choice;
		if (choice == 1) {
			diet += 4;
		}
		cout << "Is this food glutenfree? 1.Y 2.N\n";
		cin >> choice;
		if (choice == 1) {
			diet += 8;
		}
		cout << "Is this food vegetarian friendly? 1.Y 2.N\n";
		cin >> choice;
		if (choice == 1) {
			diet += 16;
		}
		cout << "Is this food free of shellfish? 1.Y 2.N\n";
		cin >> choice;
		if (choice == 1) {
			diet += 32;
		}
		

	}
	//function to add menu item
	void AddItem() {
		std::fstream foodFile;
		foodFile.open("foodmenu.csv", std::ios::out | std::ios::app);

		if (foodFile.is_open())
		{
		int input{ 0 };
		cout << "Enter menu id:\n";
		foodFile >> menuId;
		cout << "Please enter correct number correlating to food type :\n" <<
			"Morning Tea Item = 1 \nLunch Item = 2\nAvailable for both times = 4\n";
		foodFile >> foodType;
		CheckDiet(input);
		cout << "Enter Food Name: \n";
		foodFile >> name;
		cout << "Enter Food Price: ";
		foodFile >> price;	
			foodFile.close();
		}
		else cout << "Unable to open file";
		
	}
		void DeleteItem();


};

enum Diet {
	NutFree = 1,
	DairyFree = 2,
	IsHalal = 4,
	GlutenFree = 8,
	Vegetarian = 16,
	ShellFishFree = 32
};


enum FoodType {
	MorningTea = 1,
	Lunch = 2,
	Both = 4,
};

class Child {
private:
	int childId;
	int dietRequirements;
	char classroom;
	int parentId;

public:
	void PlaceOrder() {
		int input;
		cout << "Please enter child ID: ";
		cin >> input;
		std::fstream kids;
		kids.open("order.csv", std::ios::out | std::ios::app);

		if (kids.is_open())
		{
			//TODO: assuming i create an instance of order here btw
			int input{ 0 };
			cout << "Enter child id:\n";
			kids >> childId;
			DisplayMenu(bool[]childdiet);
			cout << "Please enter number correlating to item you want to purchase\n";
			cin >> input;
			kids >> Order::cart.push(input);//TODO: this obviously doesnt work but i think you know what i mean when i say it lol
			// TODO: code to calculate all vector floats together to create total order bill // 
			kids.close();
		}
		else cout << "Unable to open file";

	}
};
//TODO: so i have 'cart' in a vector, thinknig that can store all the info of items in there
struct Order {
	int orderId;
	int childId;
	std::vector<string> cart;
	float total;
	bool payStatus;
	

};









void menuMain();