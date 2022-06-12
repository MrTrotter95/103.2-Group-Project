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
	void checkDiet(int choice) {

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
		void addItem() {
			int input{0};
		cout << "Enter menu id:\n";
		cin >> menuId;
		cout << "Please enter correct number correlating to food type :\n" <<
			"Morning Tea Item = 1 \nLunch Item = 2\nAvailable for both times = 3\n";
		cin >> foodType;
		checkDiet(input);
		cout << "Enter Food Name: \n";
		cin >> name;
		cout << "Enter Food Price: ";
		cin >> price;
	}
		


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



//struct Menu {
	/*enum LunchItems {
		Sandwich = 1,
		Pasta = 2,
		Soup = 4
	};

	enum SnackItems {
		Chips = 1,
		Cookie = 2,
		Muffin = 4,
		Fruit = 8
	};

	enum DrinkItems {
		Juice = 1,
		Hot = 2,
		Smoothie = 4,
		Water = 8
	};*/


//	std::vector<std::string> sandwichOptions{ "Ham","Cheese & Onion","Bacon & Egg","Veggie mix" };
//	std::vector<std::string> pastaOptions{ "Spaghetti Bolagnese","Bacon Cabonara","Mac & Cheese","Chicken bake" };
//	std::vector<std::string> soupOptions{ "Pumpkin","Hearty Beef","Broccoli Cheese","Chicken Noodle" };
//
//	std::vector<std::string> chipOptions{ "Twisties","Salt & Vinegar","Ready Salted","Kettle Chicken" };
//	std::vector<std::string> cookieOptions{ "Choc","Triple Choc Chip","Vegan Cocoa Chip" };
//	std::vector<std::string> muffinOptions{ "Blueberry","Spiced Apple","Cheese" };
//	std::vector<std::string> fruitOptions{ "Apple","Banana","Orange","Pear" };
//
//
//	std::vector<std::string> juiceOptions{ "Orange","Apple" };
//	std::vector<std::string> hotOptions{ "Hot Chocolate","Hot Blackcurrent" };
//	std::vector<std::string> smoothieOptions{ "Blueberry & Banana","Vegan Milkshake","Choc Peanut" };
//	std::vector<std::string> waterOptions{ "Kiwi-Blue 250ml","Pump 750ml","Pump Sparkling Water" };
////default constructor







void menuMain();