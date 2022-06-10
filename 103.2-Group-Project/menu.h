#pragma once
#include <iostream>
#include <string>
using std::cout; using std::cin;

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
struct Payment {
	bool status; //?
};
class Order {
	int id;
	Child name;
	Child classroom;
	Child Diet;
	Menu lunchItem;
	Menu snackItem;
	Payment status;
};

enum Diet {
	string allergen; // can be null /empty (option will say 4=none for example)
/*use binary flags*/
string religion;//can be null /empty
string preference;//help with word to describe vegetarian , vegan or fine for meat
};


class Menu {

	struct lunchItem {
		string foodType;
		string name;
		Diet requirement;
		float price;
		char size;

	};


	struct snackItem {
		string foodType;
		string name;
		Diet requirement;
		float price;

	};

};

class Child {
	string name;
	int classroom;
	Diet requirement;
};




void menuMain();