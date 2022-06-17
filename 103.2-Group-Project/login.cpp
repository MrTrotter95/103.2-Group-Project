#include "main.h"
#include "login.h"
#include "admin.h"
#include "discount.h"
#include "feedback.h"

std::ifstream data;

//--- To Check Account Exists on CSV ---//
void CheckPassword(string, string, string, string);

void VerifyAccount(string inputEmail, string inputPassword) {
    //--- Creating a instance of ifstream ---//
    data.open("login.csv");


    //--- Temporary Variables ---//
    std::string fileId, fileName, fileEmail, filePass, fileAccessLvl, fileLine, userId, userEmail, userPass, userAccessLvl;


    //---This loops through each row of the CSV file ---//
    while (std::getline(data, fileLine))
    {
        std::stringstream  lineStream(fileLine);
        getline(lineStream, fileId, ',');
        getline(lineStream, fileName, ',');
        getline(lineStream, fileEmail, ',');
        getline(lineStream, filePass, ',');
        getline(lineStream, fileAccessLvl, ',');


        //--- If fileEmail matches the users input, save that rows data ---//
        if (fileEmail == inputEmail) {
            userId = fileId;
            userEmail = fileEmail;
            userPass = filePass;
            userAccessLvl = fileAccessLvl;
        }
    }


    //--- If users input does not match, break --//
    if (userEmail != inputEmail) {
        cout << "\nAccount does not exist!\n";
    }
    //--- If users input matches the csv email, call check password function ---//
    else if (userEmail == inputEmail) {
        //--- Passing the csv userID, csv userPass, and the inputted password to check ---//
        CheckPassword(userId, userPass, userAccessLvl, inputPassword);
        data.close();
    }

}

const int menuSize_parent = 5;
int selectionHighlight_parent = 0;
string mainMenuPrint_parent[menuSize_parent] = { "Place Order", "Order History", "Add Child", "Feedback", "Return" };

void ParentMenuDisplay() {
    cout << "********************************\n*  Welcome to the Parent Menu  *\n********************************\n";
    for (int i = 0; i < menuSize_parent; i++)
    {
        if (i == selectionHighlight_parent)
        {
            WriteInColor(3, mainMenuPrint_parent[selectionHighlight_parent]);
            cout << endl;
        }
        else
        {
            WriteInColor(15, mainMenuPrint_parent[i]);
            cout << endl;
        }
    }
}

void ParentArrowKeys() {
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
                if (selectionHighlight_parent > 0)
                {
                    selectionHighlight_parent--;
                }
                else
                {
                    selectionHighlight_parent = (menuSize_parent - 1);
                }
                break;
            case KEY_DOWN:
                //This key is assigned to decrease the highlighted number by 1
                if (selectionHighlight_parent < (menuSize_parent - 1))
                {
                    selectionHighlight_parent++;
                }
                else
                {
                    selectionHighlight_parent = 0;
                }
                break;
            default:
                cout << "\nThis key is unassigned.\n";
                break;
            }

            system("cls");
            ParentMenuDisplay();

            switch (selectionHighlight_parent)
            {
            case 0:
                cout << "\nPlace an order for your Child\n";
                break;
            case 1:
                cout << "\nAdd a Child and receive their Child ID\n";
                break;
            case 2:
                cout << "\nCheck your Order History\n";
                break;
            case 3:
                cout << "\nPlace some feedback for the School Admin\n";
                break;
            case 4:
                cout << "\nReturn to the previous menu\n";
                break;
            }

            break;
        case 13:
            switch (selectionHighlight_parent)
            {
            case 0:
                //TODO: place order function
                break;
            case 1:
                //TODO: add child function
                break;
            case 2:
                //TODO: order history
                break;
            case 3:
                PrintArray_ParentFeedbackMenu();
                //ArrowSelectionMenu_ParentFeedback(userId, userPass, userAccessLvl);
                break;
            case 4:
                BeginProgram();
                break;
            default:
                break;
            }
        }
    }
}

const int menuSize_staff = 4;
int selectionHighlight_staff = 0;
string mainMenuPrint_staff[menuSize_staff] = { "View Menu", "Display Orders", "Feedback", "Return" };

void StaffMenuDisplay() {
    cout << "********************************\n*   Welcome to the Staff Menu  *\n********************************\n";
    for (int i = 0; i < menuSize_staff; i++)
    {
        if (i == selectionHighlight_staff)
        {
            WriteInColor(3, mainMenuPrint_staff[selectionHighlight_staff]);
            cout << endl;
        }
        else
        {
            WriteInColor(15, mainMenuPrint_staff[i]);
            cout << endl;
        }
    }
}

void StaffArrowKeys() {
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
                if (selectionHighlight_staff > 0)
                {
                    selectionHighlight_staff--;
                }
                else
                {
                    selectionHighlight_staff = (menuSize_staff - 1);
                }
                break;
            case KEY_DOWN:
                //This key is assigned to decrease the highlighted number by 1
                if (selectionHighlight_staff < (menuSize_staff - 1))
                {
                    selectionHighlight_staff++;
                }
                else
                {
                    selectionHighlight_staff = 0;
                }
                break;
            default:
                cout << "\nThis key is unassigned.\n";
                break;
            }

            system("cls");
            StaffMenuDisplay();

            switch (selectionHighlight_staff)
            {
            case 0:
                cout << "\nView the current active Food Menu\n";
                break;
            case 1:
                cout << "\nDisplay all active orders\n";
                break;
            case 2:
                cout << "\nGet the contact details of the Admin.\n";
                break; 
            case 3:
                cout << "\nGet the contact details of the Admin.\n";
                break;
            }

            break;
        case 13:
            switch (selectionHighlight_staff)
            {
            case 0:
                FoodMenuStaff_ViewMenu();
                break;
            case 1:
                PrintOrders();
                break;
            case 2:
                PrintArray_StaffFeedbackMenu();
                ArrowSelectionMenu_StaffFeedback();
                break;
            case 3:
                BeginProgram();
                break;
            default:
                break;
            }
        }
    }
}

const int menuSize_adminMenu = 6;
int selectionHighlight_adminMenu = 0;
string mainMenuPrint_adminMenu[menuSize_adminMenu] = { "Accounts", "Menu", "Feedback", "Sales Reports", "Discounts", "Return" };

void AdminMenuDisplay() {
    cout << "********************************\n*   Welcome to the Admin Menu  *\n********************************\n";
    for (int i = 0; i < menuSize_adminMenu; i++)
    {
        if (i == selectionHighlight_adminMenu)
        {
            WriteInColor(3, mainMenuPrint_adminMenu[selectionHighlight_adminMenu]);
            cout << endl;
        }
        else
        {
            WriteInColor(15, mainMenuPrint_adminMenu[i]);
            cout << endl;
        }
    }
}

void AdminArrowKeys() {

    string parent = "1";         // Delete after testing 
    string staff = "2";          // Delete after testing
    string admin = "3";          // Delete after testing

    string userId = "1";         // Delete after testing
    string userName = "Alistair";// Delete after testing
    string userEmail = "Alistair@email.com"; // Delete after testing

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
                if (selectionHighlight_adminMenu > 0)
                {
                    selectionHighlight_adminMenu--;
                }
                else
                {
                    selectionHighlight_adminMenu = (menuSize_adminMenu - 1);
                }
                break;
            case KEY_DOWN:
                //This key is assigned to decrease the highlighted number by 1
                if (selectionHighlight_adminMenu < (menuSize_adminMenu - 1))
                {
                    selectionHighlight_adminMenu++;
                }
                else
                {
                    selectionHighlight_adminMenu = 0;
                }
                break;
            default:
                cout << "\nThis key is unassigned.\n";
                break;
            }

            system("cls");
            AdminMenuDisplay();

            switch (selectionHighlight_adminMenu)
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
            switch (selectionHighlight_adminMenu)
            {
            case 0:
                system("cls");
                AccountAdminMenuDisplay();
                AccountAdmin();
                break;
            case 1:
                system("cls");
                FoodMenuAdminMenuDisplay();
                FoodMenuAdmin();
                break;
            case 2:
                system("cls");
                PrintArray_AdminFeedbackMenu(userId, userEmail);
                ArrowSelectionMenu_AdminFeedback(userId, userEmail);
                break;
            case 3:
                PrintSales();
                break;
            case 4:
                system("cls");
                discountDisplayArray();
                discountMain();
                break;
            case 5:
                BeginProgram();
                break;
            default:
                break;
            }
        }
    }
}

//--- To Compare User Input Password Matches CSV ---//
void CheckPassword(string userId, string userPassword, string userAccessLvl, string inputPassword) {

        //--- If password is correct ---//
        if (inputPassword == userPassword) {

            if (userAccessLvl == "1")
            {
                data.close();
                system("cls");
                ParentMenuDisplay();
                cout << "\nWelcome to the Parent Main Menu.\nChoose an option to proceed.\n";
                ParentArrowKeys();

            }
            else if (userAccessLvl == "2")
            {
                data.close();
                system("cls");
                StaffMenuDisplay();
                cout << "\nWelcome to the Staff Main Menu.\nChoose an option to proceed.\n";
                StaffArrowKeys();
            }
            else if (userAccessLvl == "3")
            {
                data.close();
                system("cls");
                AdminMenuDisplay();
                cout << "\nWelcome ADMIN USER.\n";
                AdminArrowKeys();
            }
            else
            {
                cout << "Something went wrong\n";
            }


            int ch;
            ch = _getch();
            // Pass userId to loginMain
        }
        //--- If Password is incorrect ---//
        else if (inputPassword != userPassword) {
            cout << "\nPassword does not match please try again\n";
        }
}


//--- Start of Login functionality ---//
void loginMain()
{
    system("cls");
    cout << "********************************\n* Login to access your account *\n* Enter 'q' at anytime to exit *\n********************************\n";
    //-- Loop controlls user attempts, Max 3 --//
    int userTries = 0;
    while (userTries < 3) {
        //--- Temporary Variables ---//
        string temp, input_Email, input_Password;


        //--- Email ---//
        cout << "--- Please enter your email ---\n";
        cout << "Email: ";
        cin >> temp;


        if (temp != "q")
        {
            input_Email = temp;
        }
        else
        {
            break;
        }


        //--- Password ---//
        cout << "\nPlease enter you password: ";
        cin >> temp;


        if (temp != "q")
        {
            input_Password = temp;
        }
        else
        {
            break;
        }


        if (temp != "q")
        {
            //--- Pass Info To Functions ---//
            VerifyAccount(input_Email, input_Password);

            //--- This will execute if Verification & Password are incorrect ---//
            userTries++;
            cout << "Attempts: " << userTries << endl << endl;
        }
    }


    //--- Call main menu funciton ---//
    if (userTries > 2)
    {
        data.close();
        cout << "Attempts exceeded, Please contact the school to reset your password.\n";
        system("pause");
        BeginProgram();
    }
    else
    {
        cout << "Login cancelled.\n";
    }

    data.close();
    cout << "Press enter to go back to the Main Menu"; //Add if functionality to to wait for user to press enter or
    int ch;
    ch = _getch();
    BeginProgram();
}