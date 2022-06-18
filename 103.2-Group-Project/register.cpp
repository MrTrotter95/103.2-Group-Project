#include "main.h"
#include "register.h"
#include "admin.h"
#include "login.h"

class User {
public:
    //--- User Members ---//
    int I_UserId = 1;
    string S_Name = " ";
    char C_Gender = ' ';
    int I_PhoneNum = 0;
    string S_Dob = " ";
    string S_Email = " ";
    string S_Password = " ";
    int I_accessLevel = 1;      // 1=Parent 2=Staff 3=Admin
    float F_DiscountValue = 0;


    //--- Default Constructor ---//
    User() {
    
    }


    //--- Constructor with Arguments ---//
    User(string name, char gender, int phoneNum, string dob, string email, string password, int accessLevel) {
        S_Name = name;
        C_Gender = gender;
        I_PhoneNum = phoneNum;
        S_Dob = dob;
        S_Email = email;
        S_Password = password;
        I_accessLevel = accessLevel;
    }


    //--- Might not need this ---//
    void accountCreated() {
        cout << "\nYour account has been succesfully created!\n";
        cout << "Your username to login is: " << S_Email << endl;
        system("pause");
        loginMain();
    }
};


//--- Start of Register functionality ---//
void registerMain()
{    
    system("cls");
    PrintArray_AccountCreationMenu();
    cout << "\nWhat type of account would you like to create?\n";
    ArrowSelectionMenu_AccountCreation();
}


/*-------------------------START OF CREATE ACCOUNT MENU SECTION -------------------------*/
const int menuSize_AccountCreation = 4;
int selectionHighlight_AccountCreation = 0;
string MenuPrint_AccountCreation[menuSize_AccountCreation] = { "Parent", "Staff", "Admin", "Exit" };

void PrintArray_AccountCreationMenu() {
    cout << "********************************\n*   Register Your New Account  *\n********************************\n";

    for (int i = 0; i < menuSize_AccountCreation; i++)
    {
        if (i == selectionHighlight_AccountCreation)
        {
            WriteInColor(3, MenuPrint_AccountCreation[selectionHighlight_AccountCreation]);
            cout << endl;
        }
        else
        {
            WriteInColor(15, MenuPrint_AccountCreation[i]);
            cout << endl;
        }
    }
}

void ArrowSelectionMenu_AccountCreation() {
    //--- Temporary Variables ---//
    int ch, ch2;
    string temp;
    bool loop = true;
    int InputUserPin = 0; // To Store User Input And Compare To AdminPin
    int adminPin = 1234; //To Grant Access To Admin 

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
                if (selectionHighlight_AccountCreation > 0)
                {
                    selectionHighlight_AccountCreation--;
                }
                else
                {
                    selectionHighlight_AccountCreation = (menuSize_AccountCreation - 1);
                }
                break;
            case KEY_DOWN:
                //This key is assigned to decrease the highlighted number by 1
                if (selectionHighlight_AccountCreation < (menuSize_AccountCreation - 1))
                {
                    selectionHighlight_AccountCreation++;
                }
                else
                {
                    selectionHighlight_AccountCreation = 0;
                }
                break;
            default:
                cout << "\nThis key is unassigned.\n";
                break;
            }

            system("cls");
            PrintArray_AccountCreationMenu();

            switch (selectionHighlight_AccountCreation)
            {
            case 0:
                cout << "\nCreate a parent account\n";
                break;
            case 1:
                cout << "\nCreate a staff account\n";
                break;
            case 2:
                cout << "\nCreate a admin account\n";
                break;
            case 3:
                cout << "\nExit the program\n";
                break;
            }
            break;
        case 13:
            switch (selectionHighlight_AccountCreation)
            {
            case 0:
                CreateParentAcc();
                break;
            case 1:
                CreateStaffAcc();
                break;
            case 2:
                //--- Request Admin Pin ---//
                cout << "Please enter pin: ";
                cin >> temp;

                if (temp == "q")
                {
                    system("pause");
                    system("cls");
                    PrintArray_AccountCreationMenu();
                    ArrowSelectionMenu_AccountCreation();
                }
                //--- This statement will check if the input temporary string has any numbers ---//
                else if (isNumber(temp) && temp.size() == 4)
                {
                    InputUserPin = stoi(temp);
                }
                else
                {
                    cout << "Incorrect input. [FOR TESTER: Input is 1234]\n";
                    system("pause");
                    system("cls");
                    PrintArray_AccountCreationMenu();
                    ArrowSelectionMenu_AccountCreation();
                }

                //--- If user input is correct ---//
                if (InputUserPin == adminPin) {
                    CreateAdminAcc();
                }
                break;
            case 3:
                loop = false;
                BeginProgram();	//Calls main menu function
            default:
                break;
            }
        }
    }
}
/*-------------------------END OF CREATE ACCOUNT MENU SECTION -------------------------*/
void CreateParentAcc() {
    cout << "--- Creating Parent account ---\n\n[Press any key to begin..]\n\n";
    //--- Temporary Variables For Account Registration ---//
    char input_Gender = 'm';
    int input_PhoneNum = 0;
    string input_Name, input_dob, input_email, input_password, temp;
    string check = " ", emailCheck1 = "@", emailCheck2 = ".";
    int userAccType = 1;       //--- To Determine What Account They Would Like To Create ---//


    //--- Name ---//
    cin.ignore();
    cout << "--- Please enter your first name ---\nName: ";
    std::getline(cin, temp);

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has any spaces ---//
    else if (temp.find(check) == std::string::npos)
    {
        if (temp.size() < 15)
        {
            if (!isDecimalNumber(temp))
            {
                input_Name = temp;
            }
            else
            {
                cout << "No numbers or characters allowed\n";
                system("pause");
                system("cls");
                PrintArray_AccountCreationMenu();
                ArrowSelectionMenu_AccountCreation();
            }
        }
        else
        {
            cout << "Please keep it to 15 character limit\n";
            system("pause");
            system("cls");
            PrintArray_AccountCreationMenu();
            ArrowSelectionMenu_AccountCreation();
        }
    }
    else
    {
        cout << "Incorrect input\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }


    //--- Gender ---//
    cout << "--- Please select your gender ---\nFemale\nMale\nOther\n";
    cout << "Example: F | M | O\nGender: ";
    cin >> temp;

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has any spaces ---//
    else if (temp.find(check) == std::string::npos)
    {
        if (temp == "f" || temp == "F" || temp == "m" || temp == "M" || temp == "o" || temp == "O" )
        {
            input_Gender = temp.at(0);
        }
        else
        {
            cout << "Incorrect input\n";
            system("pause");
            system("cls");
            PrintArray_AccountCreationMenu();
            ArrowSelectionMenu_AccountCreation();
        }
    }
    else
    {
        cout << "Incorrect input\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }


    //--- Phone Number ---//
    cout << "\n--- Please enter your phone number ---\nNumber:";
    cin >> temp;

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has any numbers ---//
    else if (isNumber(temp) && temp.size() < 15)
    {
        input_PhoneNum = stoi(temp);
    }
    else
    {
        cout << "Incorrect input\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }


    //--- Date of birth ---//
    cout << "\n--- Please enter your date of birth ---\nExample [DDMMYYYY]:";
    cin >> temp;

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has any numbers ---//
    else if (isNumber(temp) && temp.size() == 8)
    {
        input_dob = temp;
    }
    else
    {
        cout << "Incorrect input. Ensure it is in the format of [DDMMYYYY]\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }


    //--- Email ---//
    cout << "\n--- Please enter your email address ---\nEmail:";

    cin >> temp;

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has the right criteria for an email ---//
    else if (temp.size() < 25 && temp.find(emailCheck1) != std::string::npos && temp.find(emailCheck2) != std::string::npos)
    {
        input_email = temp;
    }
    else
    {
        cout << "Incorrect input. Ensure you are using a domain name in your email\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }

    //--- Password ---//
    cout << "\n--- Please input your password ---\nPassword:";
    cin >> temp;

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has any numbers ---//
    else if (input_password.size() < 15)
    {
        input_password = temp;
    }
    else
    {
        cout << "Incorrect input. Ensure it is less than 15 characters\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }


    //--- Passing user input to constructor ---//
    User account(input_Name, input_Gender, input_PhoneNum, input_dob, input_email, input_password, userAccType);


    //--- Passing account to csv writing functions ---//
    SaveLoginDetails(account);
    SaveUserDetails(account);
}

void CreateStaffAcc() {
    cout << "--- Creating Staff account ---\n\n[Press any key to begin..]\n\n";


    //--- Temporary Variables For Account Registration ---//
    char input_Gender = 'm';
    int input_PhoneNum = 0;
    string input_Name, input_dob, input_email, input_password, temp;
    string check = " ", emailCheck1 = "@", emailCheck2 = ".";
    int userAccType = 1;       // To Determine What Account They Would Like To Create

    //--- Name ---//
    cin.ignore();
    cout << "--- Please enter your first name ---\nName: ";
    std::getline(cin, temp);

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has any spaces ---//
    else if (temp.find(check) == std::string::npos)
    {
        if (temp.size() < 15)
        {
            if (!isDecimalNumber(temp))
            {
                input_Name = temp;
            }
            else
            {
                cout << "No numbers or characters allowed\n";
                system("pause");
                system("cls");
                PrintArray_AccountCreationMenu();
                ArrowSelectionMenu_AccountCreation();
            }
        }
        else
        {
            cout << "Please keep it to 15 character limit\n";
            system("pause");
            system("cls");
            PrintArray_AccountCreationMenu();
            ArrowSelectionMenu_AccountCreation();
        }
    }
    else
    {
        cout << "Incorrect input\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }


    //--- Gender ---//
    cout << "--- Please select your gender ---\nFemale\nMale\nOther\n";
    cout << "Example: F | M | O\nGender: ";
    cin >> temp;

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has any spaces ---//
    else if (temp.find(check) == std::string::npos)
    {
        if (temp == "f" || temp == "F" || temp == "m" || temp == "M" || temp == "o" || temp == "O")
        {
            input_Gender = temp.at(0);
        }
        else
        {
            cout << "Incorrect input\n";
            system("pause");
            system("cls");
            PrintArray_AccountCreationMenu();
            ArrowSelectionMenu_AccountCreation();
        }
    }
    else
    {
        cout << "Incorrect input\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }


    //--- Phone Number ---//
    cout << "\n--- Please enter your phone number ---\nNumber:";
    cin >> temp;

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has any numbers ---//
    else if (isNumber(temp) && temp.size() < 15)
    {
        input_PhoneNum = stoi(temp);
    }
    else
    {
        cout << "Incorrect input\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }


    //--- Date of birth ---//
    cout << "\n--- Please enter your date of birth ---\nExample [DDMMYYYY]:";
    cin >> temp;

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has any numbers ---//
    else if (isNumber(temp) && temp.size() == 8)
    {
        input_dob = temp;
    }
    else
    {
        cout << "Incorrect input. Ensure it is in the format of [DDMMYYYY]\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }


    //--- Email ---//
    cout << "\n--- Please enter your email address ---\nEmail:";

    cin >> temp;

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has the right criteria for an email ---//
    else if (temp.size() < 25 && temp.find(emailCheck1) != std::string::npos && temp.find(emailCheck2) != std::string::npos)
    {
        input_email = temp;
    }
    else
    {
        cout << "Incorrect input. Ensure you are using a domain name in your email\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }

    //--- Password ---//
    cout << "\n--- Please input your password ---\nPassword:";
    cin >> temp;

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has any numbers ---//
    else if (input_password.size() < 15)
    {
        input_password = temp;
    }
    else
    {
        cout << "Incorrect input. Ensure it is less than 15 characters\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }


    //--- Passing user input to constructor ---//
    User account(input_Name, input_Gender, input_PhoneNum, input_dob, input_email, input_password, userAccType);


    //--- Passing account to csv writing functions ---//
    SaveLoginDetails(account);
    SaveUserDetails(account);
}

void CreateAdminAcc() {
    cout << "--- Pin entered correctly ---\n";
    cout << "--- Creating Admin Account ---\n\n";

    //--- Temporary Variables For Account Registration ---//
    char input_Gender = 'm';
    int input_PhoneNum = 0;
    string input_Name, input_dob, input_email, input_password, temp;
    string check = " ", emailCheck1 = "@", emailCheck2 = ".";
    int userAccType = 1;       // To Determine What Account They Would Like To Create

    //--- Name ---//
    cin.ignore();
    cout << "--- Please enter your first name ---\nName: ";
    std::getline(cin, temp);

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has any spaces ---//
    else if (temp.find(check) == std::string::npos)
    {
        if (temp.size() < 15)
        {
            if (!isDecimalNumber(temp))
            {
                input_Name = temp;
            }
            else
            {
                cout << "No numbers or characters allowed\n";
                system("pause");
                system("cls");
                PrintArray_AccountCreationMenu();
                ArrowSelectionMenu_AccountCreation();
            }
        }
        else
        {
            cout << "Please keep it to 15 character limit\n";
            system("pause");
            system("cls");
            PrintArray_AccountCreationMenu();
            ArrowSelectionMenu_AccountCreation();
        }
    }
    else
    {
        cout << "Incorrect input\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }


    //--- Gender ---//
    cout << "--- Please select your gender ---\nFemale\nMale\nOther\n";
    cout << "Example: F | M | O\nGender: ";
    cin >> temp;

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has any spaces ---//
    else if (temp.find(check) == std::string::npos)
    {
        if (temp == "f" || temp == "F" || temp == "m" || temp == "M" || temp == "o" || temp == "O")
        {
            input_Gender = temp.at(0);
        }
        else
        {
            cout << "Incorrect input\n";
            system("pause");
            system("cls");
            PrintArray_AccountCreationMenu();
            ArrowSelectionMenu_AccountCreation();
        }
    }
    else
    {
        cout << "Incorrect input\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }


    //--- Phone Number ---//
    cout << "\n--- Please enter your phone number ---\nNumber:";
    cin >> temp;

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has any numbers ---//
    else if (isNumber(temp) && temp.size() < 15)
    {
        input_PhoneNum = stoi(temp);
    }
    else
    {
        cout << "Incorrect input\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }


    //--- Date of birth ---//
    cout << "\n--- Please enter your date of birth ---\nExample [DDMMYYYY]:";
    cin >> temp;

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has any numbers ---//
    else if (isNumber(temp) && temp.size() == 8)
    {
        input_dob = temp;
    }
    else
    {
        cout << "Incorrect input. Ensure it is in the format of [DDMMYYYY]\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }


    //--- Email ---//
    cout << "\n--- Please enter your email address ---\nEmail:";

    cin >> temp;

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has the right criteria for an email ---//
    else if (temp.size() < 25 && temp.find(emailCheck1) != std::string::npos && temp.find(emailCheck2) != std::string::npos)
    {
        input_email = temp;
    }
    else
    {
        cout << "Incorrect input. Ensure you are using a domain name in your email\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }

    //--- Password ---//
    cout << "\n--- Please input your password ---\nPassword:";
    cin >> temp;

    if (temp == "q")
    {
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }
    //--- This statement will check if the input temporary string has any numbers ---//
    else if (input_password.size() < 15)
    {
        input_password = temp;
    }
    else
    {
        cout << "Incorrect input. Ensure it is less than 15 characters\n";
        system("pause");
        system("cls");
        PrintArray_AccountCreationMenu();
        ArrowSelectionMenu_AccountCreation();
    }

    //--- Passing user input to constructor ---//
    User account(input_Name, input_Gender, input_PhoneNum, input_dob, input_email, input_password, userAccType);


    //--- Passing account to csv writing functions ---//
    SaveLoginDetails(account);
    SaveUserDetails(account);
}

void SaveLoginDetails(User account) {
    //--- Creating a instance of fstream & ifstream ---//
    std::fstream fout;
    std::ifstream  data("login.csv");


    //--- Temporary Variables ---//
    std::string id, line;
    int newId;


    //--- Start of file writing logic ---//
    fout.open("login.csv", std::ios::out | std::ios::app);
    //This loops through each row in csv file and only checks the first cell of each row.
    while (std::getline(data, line))
    {
        std::stringstream  lineStream(line);
        getline(lineStream, id, ',');
    }


    //--- Converting string to int. ---//
    std::istringstream(id) >> newId;
    //--- Takes last row in csv file and adds 1 to create a new unique ID. ---/
    newId += 1;


    //--- Assigning the created account details to the csv file. ---//
    fout << newId << ","
        << account.S_Name << ","
        << account.S_Email << ","
        << account.S_Password << ","
        << account.I_accessLevel << "\n";
    fout.close();
    //--- End of file writing logic ---//
}

void SaveUserDetails(User account) {
    //--- Creating a instance of fstream & ifstream ---//
    std::fstream fout;
    std::ifstream  data("userDetails.csv");


    //--- Temporary Variables ---//
    std::string id, line;
    int newId;


    //--- Start of file writing logic ---//
    fout.open("userDetails.csv", std::ios::out | std::ios::app);
    //--- This loops through each row in csv file and only checks the first cell of each row. ---//
    while (std::getline(data, line))
    {
        std::stringstream  lineStream(line);
        getline(lineStream, id, ',');
    }


    //--- Converting string to int. ---//
    std::istringstream(id) >> newId;
    //--- Takes last row in csv file and adds 1 to create a new unique ID. ---//
    newId += 1;


    //--- Assigning the created account details to the csv file. ---//
    fout << newId << ","
        << account.C_Gender << ","
        << account.I_PhoneNum << ","
        << account.S_Dob << ","
        << account.F_DiscountValue << "\n";
    fout.close();
    //--- End of file writing logic ---//

    account.accountCreated();
}