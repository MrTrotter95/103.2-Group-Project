
#pragma once
using std::cout;
using std::cin;

//int orderCount;
//int orderId;
//int childId;
//int morningTeaId;
//int morningTeaDrinkId;
//int lunchId;
//int lunchDrinkId;
//float total{ 0 };

std::string childName;



struct Menu {
	int foodId;
	bool foodOrDrink;
	std::string itemName;
	float price;
	bool veg;
	bool vegan;
	bool gf;
}item;



void PlaceOrder(int childid);
int AddChild(int childid);
void CheckChild(int childid);
void ViewOrders(int child);
void ViewMenu();
int menuMain();
double GetPrice(int id);
std::string GetItemName(int id);
//void CheckFlags(int id);