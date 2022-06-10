#include "main.h"
#include "menu.h"

/*Start of Food Menu functionality*/

  /*view menu*/
void DisplayMenu(Menu type) {
    cout << "Displaying Full Menu..." << endl << "Morning Tea Items: " << endl << "Chips: " << endl;
    for (std::string x : type.chipOptions) {
        std::cout << x << "\t";
    }
    cout << "\nCookies: " << endl;
    for (std::string x : type.cookieOptions) {
        std::cout << x << "\t";
    }
    cout << "\nFruit: " << endl;
    for (std::string x : type.fruitOptions) {
        std::cout << x << "\t";
    }
    cout << "\nMuffins: " << endl;
    for (std::string x : type.muffinOptions) {
        std::cout << x << "\t";
    }
    cout << "\n\nLunch Items: " << endl << "Sandwiches: " << endl;
    for (std::string x : type.sandwichOptions) {
        std::cout << x << "\t";
    }
    cout << "\nPasta: " << endl;
    for (std::string x : type.pastaOptions) {
        std::cout << x << "\t";
    }
    cout<< "\nSoup: " << endl;
    for (std::string x : type.soupOptions) {
        std::cout << x << "\t";
    }
    cout << "\n\nDrinks: " << endl << "Juice: " << endl;
    for (std::string x : type.juiceOptions) {
        std::cout << x << "\t";
    }
    cout << "\nWater: " << endl;
    for (std::string x : type.waterOptions) {
        std::cout << x << "\t";
    }
    cout << "\nHot drinks: " << endl;
    for (std::string x : type.hotOptions) {
        std::cout << x << "\t";
    }
    cout << "\nSmoothies: " << endl;
    for (std::string x : type.smoothieOptions) {
        std::cout << x << "\t";
    }
}









void menuMain()
{
    
    DisplayMenu(Menu());
    cout << "menu.cpp connected..\n";
}