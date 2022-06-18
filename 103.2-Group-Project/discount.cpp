#include "main.h"
#include "discount.h"
#include "admin.h"
#include "login.h"

//--- file pointer ---//
std::fstream fout;
std::fstream fin;
std::fstream finUser;

const int menuSize_discMenu = 4;
int selectionHighlight_discMenu = 0;
string mainMenuPrint_discMenu[menuSize_discMenu] = { "Add Discount", "Set Discount", "Delete Discount", "Return" };

void discountDisplayArray() {
    cout << "**********************************\n*   Welcome to the Discount Menu  *\n* Enter 'q' at any input to exit *\n**********************************\n";
    for (int i = 0; i < menuSize_discMenu; i++)
    {
        if (i == selectionHighlight_discMenu)
        {
            WriteInColor(3, mainMenuPrint_discMenu[selectionHighlight_discMenu]);
            cout << endl;
        }
        else
        {
            WriteInColor(15, mainMenuPrint_discMenu[i]);
            cout << endl;
        }
    }
}



//--- Start of Discount functionality ---//
void discountMain()
{
    int ch, ch2;
    bool loop = true;

    while (loop)
    {
        ch = _getch();

        switch (ch)
        {
        case 224: //This line is the first num received from _getch, and specifies that it is a special character (arrow keys)
            ch2 = _getch(); //This line takes the value of the special character, which we have defined the values and named them as KEY_ followed by their direction.

            switch (ch2)
            {
            case KEY_UP:
                //This key is assigned to increase the highlighted number by 1;
                if (selectionHighlight_discMenu > 0)
                {
                    selectionHighlight_discMenu--;
                }
                else
                {
                    selectionHighlight_discMenu = (menuSize_discMenu - 1);
                }
                break;
            case KEY_DOWN:
                //This key is assigned to decrease the highlighted number by 1
                if (selectionHighlight_discMenu < (menuSize_discMenu - 1))
                {
                    selectionHighlight_discMenu++;
                }
                else
                {
                    selectionHighlight_discMenu = 0;
                }
                break;
            default:
                cout << "\nThis key is unassigned.\n";
                break;
            }

            system("cls");
            discountDisplayArray();

            switch (selectionHighlight_discMenu)
            {
            case 0:
                cout << "\nLogin to access your account and see your orders\n";
                break;
            case 1:
                cout << "\nRegister up now to place orders for your children!\n";
                break;
            case 2:
                cout << "\nGet the contact details of the Admin.\n";
                break;
            case 3:
                cout << "\nExit the program safely.\n";
                break;
            }

            break;
        case 13:
            switch (selectionHighlight_discMenu)
            {
            case 0:
                AddDiscount();
                break;
            case 1:
                SetDiscount();
                break;
            case 2:
                DeleteDiscount();
                break;
            case 3:
                system("cls");
                AdminMenuDisplay();
                AdminArrowKeys();
                break;
            default:
                break;
            }
        }
    }
}

//--- Making a new discount ---//
void AddDiscount() {
    //--- Temporary Variables ---//
    double value = 0;
    std::string name, line, word, temp;
    std::vector<std::string> row;
    std::vector<std::vector<std::string>> discContent;

    fin.open("discounts.csv", std::ios::in);


    //--- Statement to populate discContent vector with discounts.csv ---//
    while (getline(fin, line))
    {
        row.clear();

        std::stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word);
            discContent.push_back(row);
        }
    }


    //--- Output for the user ---//
    cout << "List of available discounts and their discount value:\n";

    bool isDiscName = true;


    //--- Statement to print the discounts ---//
    for (int i = 0; i < discContent.size(); i++)
    {
        for (int j = 0; j < discContent[i].size(); j++)
        {
            if (i % 2 == 1)
            {
                if (isDiscName == true)
                {
                    cout << "Name: " << discContent[i][j] << "\n";
                    isDiscName = false;
                }
                else if (isDiscName == false)
                {
                    cout << "Value: " << discContent[i][j] << "\n";
                    isDiscName = true;
                }
            }
        }
        if (i % 2 == 1) {
            cout << endl;
        }
    }

    fin.close();

    //--- Opens existing csv or creates new file ---//
    fout.open("discounts.csv", std::ios::out | std::ios::app);
    cin.ignore();
    cout << "******************************\nMake a new discount\n";
    cout << "Discount name [string]: ";
    getline(cin, temp);


    if (temp.size() > 0 && temp.size() < 15)
    {
        name = temp;
    }
    else if (temp == "q")
    {
        system("pause");
        fout.close();
        system("cls");
        discountDisplayArray();
        discountMain();
    }
    else {
        cout << "Name is too long\n";
        system("pause");
        fout.close();
        system("cls");
        discountDisplayArray();
        discountMain();
    }

    cout << "Discount value [double]: ";
    cin >> temp;

    if (isDecimalNumber(temp))
    {
        value = stod(temp);
    }
    else if (temp == "q")
    {
        system("pause");
        fout.close();
        system("cls");
        discountDisplayArray();
        discountMain();
    }
    else
    {
        cout << "Incorrect input\n";
        system("pause");
        fout.close();
        system("cls");
        discountDisplayArray();
        discountMain();
    }

    fout << name << ',' << value << ',' << "\n";

    fout.close();

    int selection;

    cout << "\nWould you like to add another entry?\n1. Add another entry\n2. Return to Menu\nSelection: ";
    cin >> selection;

    switch (selection)
    {
    case 1:
        AddDiscount();
        break;
    case 2:
        system("cls");
        discountDisplayArray();
        discountMain();
        break;
    default:
        system("cls");
        discountDisplayArray();
        discountMain();
        break;
    }
}

//--- Setting a discount as Parents discount value ---//
void SetDiscount() {
    //--- Function Streams ---//
    fin.open("discounts.csv", std::ios::in);
    finUser.open("userDetails.csv", std::ios::in);
    fout.open("userDetailsNew.csv", std::ios::out | std::ios::app);


    //--- Temporary Variables ---//
    std::string line, lineDisc, temp;
    int count = 1, count2 = 1, idCount = 1, selection;
    std::vector<string> users, discs;
    double idChoice = 0, discChoice = 0;


    //--- Statement to populate users vector with userDetails ---//
    while (std::getline(finUser, line))
    {
        std::stringstream lineStream(line);
        string cell;
        while (std::getline(lineStream, cell, ','))
        {
            if (count % 5 == 0)
            {
                cout << cell << "\n";
                users.push_back(cell);
                count++;
            }
            else
            {
                cout << cell << " ";
                users.push_back(cell);
                count++;
            }
        }
    }


    //--- Output for the user ---//
    cout << "\n" << "************************\nDiscounts available:\n";


    //--- Statement to print discs vector ---//
    while (std::getline(fin, lineDisc))
    {
        std::stringstream discSs(lineDisc);
        string cell;
        while (std::getline(discSs, cell, ','))
        {
            if (count2 % 2 == 0)
            {
                cout << cell << "\n";
                discs.push_back(cell);
                count2++;
            }
            else
            {
                cout << idCount << ": " << cell << " ";
                discs.push_back(cell);
                count2++;
                idCount++;
            }
        }
    }

    cout << "\nWhich ID to edit discount?\n[ID]: ";
    cin >> temp;
    if (isNumber(temp))
    {
        idChoice = stoi(temp);
    }
    else if (temp == "q")
    {
        system("pause");
        fin.close();
        finUser.close();
        fout.close();
        std::remove("userDetailsNew.csv");
        system("cls");
        discountDisplayArray();
        discountMain();
    }
    else
    {
        cout << "Incorrect input\n";
        system("pause");
        fin.close();
        finUser.close();
        fout.close();
        std::remove("userDetailsNew.csv");
        system("cls");
        discountDisplayArray();
        discountMain();
    }


    cout << "\nWhich discount number to give User [" << idChoice << "]: ";
    cin >> temp;
    if (isNumber(temp))
    {
        discChoice = stoi(temp);
    }
    else if (temp == "q")
    {
        system("pause");
        fin.close();
        finUser.close();
        fout.close();
        std::remove("userDetailsNew.csv");
        system("cls");
        discountDisplayArray();
        discountMain();
    }
    else
    {
        cout << "Incorrect input\n";
        system("pause");
        fin.close();
        finUser.close();
        fout.close();
        std::remove("userDetailsNew.csv");
        system("cls");
        discountDisplayArray();
        discountMain();
    }


    //--- Statement to change selected user's discount value to selected discount value ---//
    users.at((5 * (idChoice - 1)) + 4) = discs[(discChoice * 2) - 1];
    cout << users[(5 * (idChoice - 1)) + 4];


    for (int i = 0; i < users.size(); i++)
    {
        if (count % 5 == 0)
        {
            fout << users[i] << "\n";
            count++;
        }
        else
        {
            fout << users[i] << ',';
            count++;
        }
    }


    //--- Statement to close up filestreams ---//
    fin.close();
    finUser.close();
    fout.close();


    //--- Statement to remove old csv and rename new csv ---//
    std::remove("userDetails.csv");
    std::rename("userDetailsNew.csv", "userDetails.csv");


    //--- User Instructions ---//
    cout << "\nWould you like to set another discount?\n1. Set another discount\n2. Return to Menu\nSelection: ";
    cin >> selection;


    switch (selection)
    {
    case 1:
        discountDisplayArray();
        SetDiscount();
        break;
    case 2:
        system("cls");
        discountDisplayArray();
        discountMain();
        break;
    default:
        system("cls");
        discountDisplayArray();
        discountMain();
        break;
    }

}

//---Deleting a Discount ---//
void DeleteDiscount() {
    std::string deleteName, deleteNameRow, line, word, name, value, temp;
    std::vector<std::string> row;
    std::vector<std::vector<std::string>> discContent;
    bool isDiscName = true;
    bool isDiscNamePrint = true;

    fin.open("discounts.csv", std::ios::in);
    fout.open("discountsNew.csv", std::ios::out | std::ios::app);

    while (getline(fin, line))
    {
        row.clear();

        std::stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word);
            discContent.push_back(row);
        }
    }

    cout << "List of available discounts and their discount value:\n";

    isDiscNamePrint = true;
    for (int i = 0; i < discContent.size(); i++)
    {
        for (int j = 0; j < discContent[i].size(); j++)
        {
            if (i % 2 == 1)
            {
                if (isDiscNamePrint == true)
                {
                    cout << "Name: " << discContent[i][j] << "\n";
                    isDiscNamePrint = false;
                }
                else if (isDiscNamePrint == false)
                {
                    cout << "Value: " << discContent[i][j] << "\n";
                    isDiscNamePrint = true;
                }
            }
        }
        if (i % 2 == 1) {
            cout << endl;
        }
    }


    //--- User Instructions ---//
    cin.ignore();
    cout << "Enter the name of the discount to be deleted\n";
    getline(cin, temp);
    

    if (temp == "q")
    {
        system("pause");
        fin.close();
        fout.close();
        std::remove("discountsNew.csv");
        system("cls");
        discountDisplayArray();
        discountMain();
    }
    else if (temp != " ")
    {
        deleteName = temp;
    }
    else
    {
        cout << "Incorrect input\n";
        system("pause");
        fin.close();
        fout.close();
        std::remove("discountsNew.csv");
        system("cls");
        discountDisplayArray();
        discountMain();
    }

    isDiscName = true;
    for (int i = 0; i < discContent.size(); i++)
    {
        for (int j = 0; j < discContent[i].size(); j++)
        {
            if (i % 2 == 1)
            {
                if (discContent[i][j] != deleteName)
                {
                    if (isDiscName == true)
                    {
                        cout << "Name: " << discContent[i][j] << "\n";
                        isDiscName = false;
                        fout << discContent[i][j] << ',';
                    }
                    else
                    {
                        cout << "Value: " << discContent[i][j] << "\n";
                        isDiscName = true;
                        fout << discContent[i][j] << "\n";
                    }
                }
                else if (discContent[i][j] == deleteName)
                {
                    break;
                }
            }
        }
        if (i % 2 == 1) {
            cout << endl;
        }
    }

    fin.close();
    fout.close();

    std::remove("discounts.csv");
    std::rename("discountsNew.csv", "discounts.csv");

    int selection;


    //--- User instructions ---//
    cout << "\nWould you like to delete another discount?\n1. Delete another discount\n2. Return to Menu\nSelection: ";
    cin >> selection;

    switch (selection)
    {
    case 1:
        discountDisplayArray();
        DeleteDiscount();
        break;
    case 2:
        system("cls");
        discountDisplayArray();
        discountMain();
        break;
    default:
        system("cls");
        discountDisplayArray();
        discountMain();
        break;
    }
}