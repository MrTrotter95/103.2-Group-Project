#include "main.h"
#include "menu.h"

/*Start of Food Menu functionality*/
void DisplayMenu() {
    int choice;
    //reading menu
    std::stringstream x;
    std::fstream menu;
    std::vector<std::string> item;
    std::string line, word, temp;
    menu.open("foodmenu.csv", std::ios::in);
    if (!menu) {
        cout << "File not found/....";
    }
    else {

        while (menu >> temp) {
            
            cout << "What menu? 1. morning tea, 2.lunch, 4.all day 7.Everything? ";

            cin >> choice;

            item.clear();
            cout << "hi";
            //read row and store in variable string "item"
            getline(menu, line);
            cout << "hello";
            std::stringstream x(line);
            cout << "watup";


            while (getline(x, word, ',')) {
                item.push_back(word);
                cout << "push happened ";
            }
            
            
            
                int type = stoi(item[1]);
                if (choice == type) {

                    switch (type) {
                    case 1:
                        //type = FoodType::MorningTea;
                        cout << "Morning Tea Menu: \n" <<
                            "item " << item[0] << "\t " << item[3] << "\t $" << item[4] << endl;
                        break;
                    case 2:
                        cout << "Lunch Menu: \n" <<
                            "item " << item[0] << "\t " << item[3] << "\t $" << item[4] << endl;
                        //   type = FoodType::Lunch;
                        break;
                    case 4:
                        cout << "All Day Menu: \n" <<
                            "item " << item[0] << "\t " << item[3] << "\t $" << item[4] << endl;
                        // type = FoodType::Both;
                        break;
                    case 7:
                        cout << "Full Menu: \n" <<
                            "item " << item[0] << "\t " << item[3] << "\t $" << item[4] << endl;
                        break;
                    default:
                        cout << "Something went wrong...";
                        break;
                    }
                }
        }
    }

};
void AddFood() {
    int choice;
    cout << "What menu item would you like to add?\n" <<
        "1. Lunch \t 2. Morning tea \t 3. Drinks: \n";
    cin >> choice;

    std::fstream foodFile;
    foodFile.open("foodmenu.csv", std::ios::out | std::ios::app);
        
        if (foodFile.is_open())
        {
            foodFile << "This is a line.\n";
            foodFile << "This is another line.\n";
            foodFile.close();
        }
        else cout << "Unable to open file";
}

//void DisplayMenu()
//{
//    std::fstream foodFile;
//    std::vector<string> row;
//    string line, word, temp;
//    foodFile.open("foodmenu.csv", std::ios::in);
//
//    if (foodFile.is_open())
//    {
//        while (getline(foodFile, line))
//        {
//            cout << line << '\n';
//        }
//        foodFile.close();
//    }
//
//    else cout << "Unable to open file";
//}












void menuMain()
{
    
    DisplayMenu();
    cout << "menu.cpp connected..\n";
}