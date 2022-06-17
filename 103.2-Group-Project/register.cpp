#include "main.h"
#include "register.h"


void PrintArray_AccountCreationMenu();
void ArrowSelectionMenu_AccountCreation();
void CreateParentAcc();
void CreateStaffAcc();
void CreateAdminAcc();
void SaveLoginDetails(class User);
void SaveUserDetails(class User);

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
        cout << "Your username to login is: " << S_Email;
        cout << "\nYour Access level is: " << I_accessLevel << endl;
        // Call the relevant function to take user to new menu
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
    bool loop = true;
    int InputUserPin;     // To Store User Input And Compare To AdminPin
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
                cin >> InputUserPin;


                //--- While loop to ensure the userinput is a valid number ---//
                while (std::cin.fail()) {
                    std::cout << "\nPlease input a valid integer" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(256, '\n');
                    std::cin >> InputUserPin;
                }


                //--- If user input is wrong ---//
                if (InputUserPin != adminPin) {
                    cout << "Pin is not correct, press enter to be redirected to menu\n";
                    int ch;
                    ch = _getch();
                    registerMain();
                    //Implement Functionality to try again / go back to main menu
                }
                //--- If user input is correct ---//
                else if (InputUserPin == adminPin) {
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
    cout << "--- Creating Parent account ---\n\n";


    //--- Temporary Variables For Account Registration ---//
    char input_Gender;
    int input_PhoneNum;
    string input_Name, input_dob, input_email, input_password;
    int userAccType = 1;       // To Determine What Account They Would Like To Create


    //--- Name ---//
    cout << "--- Please enter your first name ---\nName:";
    cin >> input_Name;
    while (input_Name.size() > 15) { //--- Max Input Size ---//
        cout << "15 character limit reached. Please try again\n";
        std::cin.clear();
        cin >> input_Name;
    }
    while (std::any_of(input_Name.begin(), input_Name.end(), ::isdigit)) { //--- Characters Only ---//
        cout << "Numbers found in name, please only use characters\n";
        std::cin.clear();
        cin >> input_Name;
    }


    //--- Gender ---//
    cin.ignore();
    cout << "--- Please select your gender ---\nFemale\nMale\nOther\n";
    cout << "Example: F | M | O\nGender:";
    cin >> input_Gender;
    while (input_Gender != 'f' && input_Gender != 'F' && input_Gender != 'm' && input_Gender != 'M' && input_Gender != 'o' && input_Gender != 'O') {     //--- Approved Characters Only ---//
        cout << "invalid input\nPlease enter select one from the following: f , F , m , M , o , O\n";
        cin >> input_Gender;
    }


    //--- Phone Number ---//
    cin.ignore();
    cout << "\n--- Please enter your phone number ---\nNumber:";
    cin >> input_PhoneNum;
    while (std::cin.fail()) {
        std::cout << "\nPlease enter only numeric values" << std::endl;
        std::cin >> input_PhoneNum;
    }



    //--- Date of birth ---//
    cin.ignore();
    cout << "\n--- Please enter your date of birth ---\nExample dd/mm/yyyy:";
    cin >> input_dob;
    while (input_dob[2] != '/' || input_dob[5] != '/') {
        cout << "Invalid input\nPlease ensure format is dd/mm/yyyy\n:";
        cin >> input_dob;
    }


    //--- Email ---//
    cin.ignore();
    cout << "\n--- Please enter your email address ---\nEmail:";
    cin >> input_email;
    while (input_email.size() > 25) { //--- Max Input Size ---//
        cout << "25 character limit reached. Please try again\n";
        std::cin.clear();
        cin >> input_email;
    }

    //--- Password ---//
    cin.ignore();
    cout << "\n--- Please input your password ---\nPassword:";
    cin >> input_password;
    while (input_password.size() > 15) { //--- Max Input Size ---//
        cout << "15 character limit reached. Please try again\n";
        std::cin.clear();
        cin >> input_password;
    }


    //--- Passing user input to constructor ---//
    User account(input_Name, input_Gender, input_PhoneNum, input_dob, input_email, input_password, userAccType);


    //--- Passing account to csv writing functions ---//
    SaveLoginDetails(account);
    SaveUserDetails(account);
}

void CreateStaffAcc() {
    cout << "--- Creating Staff account ---\n\n";


    //--- Temporary Variables For Account Registration ---//
    char input_Gender;
    long int input_PhoneNum;
    string input_Name, input_dob, input_email, input_password;
    int userAccType = 2;       // To Determine What Account They Would Like To Create


    //--- Name ---//
    cin.ignore();
    cout << "--- Please enter your first name ---\nName:";
    cin >> input_Name;
    while (input_Name.size() > 15) { //--- Max Input Size ---//
        cout << "15 character limit reached. Please try again\n";
        std::cin.clear();
        cin >> input_Name;
    }
    while (std::any_of(input_Name.begin(), input_Name.end(), ::isdigit)) { //--- Characters Only ---//
        cout << "Numbers found in name, please only use characters\n";
        std::cin.clear();
        cin >> input_Name;
    }

  
    //--- Gender ---//
    cin.ignore();
    cout << "--- Please select your gender ---\nFemale\nMale\nOther\n";
    cout << "Example: F | M | O\nGender:";
    cin >> input_Gender;
    while (input_Gender != 'f' && input_Gender != 'F' && input_Gender != 'm' && input_Gender != 'M' && input_Gender != 'o' && input_Gender != 'O') {     //--- Approved Characters Only ---//
        cout << "invalid input\nPlease enter select one from the following: f , F , m , M , o , O\n";
        cin >> input_Gender;
    }


    //--- Phone Number ---//
    cin.ignore();
    cout << "\n--- Please enter your phone number ---\nNumber:";
    cin >> input_PhoneNum;
    while (std::cin.fail()) {
        std::cout << "\nPlease enter only numeric values" << std::endl;
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> input_PhoneNum;
    }


    //--- Date of birth ---//
    cin.ignore();
    cout << "\n--- Please enter your date of birth ---\nExample dd/mm/yyyy:";
    cin >> input_dob;
    while (input_dob[2] != '/' || input_dob[5] != '/') {
        cout << "Invalid input\nPlease ensure format is dd/mm/yyyy\n:";
        cin >> input_dob;
    }


    //--- Email ---//
    cin.ignore();
    cout << "\n--- Please enter your email address ---\nEmail:";
    cin >> input_email;
    while (input_email.size() > 25) { //--- Max Input Size ---//
        cout << "25 character limit reached. Please try again\n";
        std::cin.clear();
        cin >> input_email;
    }

    //--- Password ---//
    cin.ignore();
    cout << "\n--- Please input your password ---\nPassword:";
    cin >> input_password;
    while (input_password.size() > 15) { //--- Max Input Size ---//
        cout << "15 character limit reached. Please try again\n";
        std::cin.clear();
        cin >> input_password;
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
    char input_Gender;
    long int input_PhoneNum;
    string input_Name, input_dob, input_email, input_password;
    int userAccType = 3;       // To Determine What Account They Would Like To Create


    //--- Name ---//
    cin.ignore();
    cout << "--- Please enter your first name ---\nName:";
    cin >> input_Name;
    while (input_Name.size() > 15) { //--- Max Input Size ---//
        cout << "15 character limit reached. Please try again\n";
        std::cin.clear();
        cin >> input_Name;
    }
    while (std::any_of(input_Name.begin(), input_Name.end(), ::isdigit)) { //--- Characters Only ---//
        cout << "Numbers found in name, please only use characters\n";
        std::cin.clear();
        cin >> input_Name;
    }


    //--- Gender ---//
    cin.ignore();
    cout << "--- Please select your gender ---\nFemale\nMale\nOther\n";
    cout << "Example: F | M | O\nGender:";
    cin >> input_Gender;
    while (input_Gender != 'f' && input_Gender != 'F' && input_Gender != 'm' && input_Gender != 'M' && input_Gender != 'o' && input_Gender != 'O') {     //--- Approved Characters Only ---//
        cout << "invalid input\nPlease enter select one from the following: f , F , m , M , o , O\n";
        cin >> input_Gender;
    }


    //--- Phone Number ---//
    cin.ignore();
    cout << "\n--- Please enter your phone number ---\nNumber:";
    cin >> input_PhoneNum;
    while (std::cin.fail()) {
        std::cout << "\nPlease enter only numeric values" << std::endl;
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> input_PhoneNum;
    }


    //--- Date of birth ---//
    cin.ignore();
    cout << "\n--- Please enter your date of birth ---\nExample dd/mm/yyyy:";
    cin >> input_dob;
    while (input_dob[2] != '/' || input_dob[5] != '/') {
        cout << "Invalid input\nPlease ensure format is dd/mm/yyyy\n:";
        cin >> input_dob;
    }


    //--- Email ---//
    cin.ignore();
    cout << "\n--- Please enter your email address ---\nEmail:";
    cin >> input_email;
    while (input_email.size() > 25) { //--- Max Input Size ---//
        cout << "25 character limit reached. Please try again\n";
        std::cin.clear();
        cin >> input_email;
    }


    //--- Password ---//
    cin.ignore();
    cout << "\n--- Please input your password ---\nPassword:";
    cin >> input_password;
    while (input_password.size() > 15) { //--- Max Input Size ---//
        cout << "15 character limit reached. Please try again\n";
        std::cin.clear();
        cin >> input_password;
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
        << account.I_accessLevel << ","
        << account.F_DiscountValue << "\n";
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
        << account.S_Dob << "\n";
    fout.close();
    //--- End of file writing logic ---//

    account.accountCreated();
}