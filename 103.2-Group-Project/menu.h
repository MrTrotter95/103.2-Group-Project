
#pragma once
using std::cout;
using std::cin;

int orderCount;
int orderId;
int childId;
int morningTeaId;
int morningTeaDrinkId;
int lunchId;
int lunchDrinkId;
float total{ 0 };
float price{ 0 };





struct Menu {
	int foodId;
	bool foodOrDrink;
	std::string itemName;
	float price;
	bool veg;
	bool vegan;
	bool gf;
}item;


int foodId;
void PlaceOrder(int childid);
int AddChild(int childid);
void CheckChild(int childid);
void ViewOrders(int child);
void ViewMenu();
void menuMain();
float GetPrice(int id);
void ScanMenu(int input);