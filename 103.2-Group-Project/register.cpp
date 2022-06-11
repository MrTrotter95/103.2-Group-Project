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
    char C_Gender = 'O';
    long int I_PhoneNum = 0;
    string S_Dob = " ";
    string S_Email = " ";
    string S_Password = " ";
    int I_accessLevel = 1;      // 1=Parent 2=Staff 3=Admin

    /* ONES I'm going to remove
    float F_DiscountValue = 0;
    string S_contactMessage = " ";  //This will store the users feedback.
    float F_tab = 0;*/


    //--- Default Constructor ---//
    User() {
    
    }
    

    //--- Constructor with Arguments ---//
    User(string name, char gender, long int phoneNum, string dob, string email, string password, int accessLevel) {
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
    long int input_PhoneNum;
    string input_Name, input_dob, day, month, year, input_email, input_password;
    int userAccType = 1;       // To Determine What Account They Would Like To Create


    //--- Name ---//
    cout << "--- Please enter your full name ---\nName: ";
    getline(cin, input_Name);

    //--- Gender ---//
    cout << "--- Please select your gender ---\nFemale\nMale\nOther\n ";
    cin >> input_Gender;


    //--- Phone Number ---//
    cout << "\n--- Please enter your phone number ---\nNumber:"; //Would be a good idea to set a max input amoun allowed.
    cin >> input_PhoneNum;
    while (std::cin.fail()) {
        std::cout << "\nPlease enter only numeric values" << std::endl;
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> input_PhoneNum;
    }


    //--- Date of birth ---//
    cout << "\n--- Please enter your date of birth ---\nExample dd/mm/yyyy:  "; //Need to work on this
    /*cout << "Day: ";
    cin >> day;
    cout << "Month: ";
    cin >> month;
    cout << "Year: ";
    cin >> year;*/
    cin >> input_dob;


    //--- Email ---//
    cout << "\n--- Please enter your email address ---\nEmail:";
    cin >> input_email;


    //--- Password ---//
    cout << "\n--- Please input your password ---\nPassword:";
    cin >> input_password;


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
    string input_Name, input_dob, day, month, year, input_email, input_password;
    int userAccType = 2;       // To Determine What Account They Would Like To Create


    //--- Name ---//
    cout << "--- Please enter your full name ---\nName: ";
    getline(cin, input_Name);


    //--- Gender ---//
    cout << "--- Please select your gender ---\nFemale\nMale\nOther\n ";
    cin >> input_Gender; //Use Jordans menu select option for this input.


    //--- Phone Number ---//
    cout << "\n--- Please enter your phone number ---\nNumber:";
    cin >> input_PhoneNum;


    //--- Date of birth ---//
    cout << "\n--- Please enter your date of birth ---\nDOB:";
    cin >> input_dob;


    //--- Email ---//
    cout << "\n--- Please enter your email address ---\nEmail:";
    cin >> input_email;


    //--- Password ---//
    cout << "\n--- Please input your password ---\nPassword:";
    cin >> input_password;


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
    string input_Name, input_dob, day, month, year, input_email, input_password;
    int userAccType = 3;       // To Determine What Account They Would Like To Create


    //--- Name ---//
    cout << "--- Please enter your full name ---\nName: ";
    getline(cin, input_Name);



    //--- Gender ---//
    cout << "--- Please select your gender ---\nFemale\nMale\nOther\n ";
    cin >> input_Gender; //Use Jordans menu select option for this input.


    //--- Phone Number ---//
    cout << "\n--- Please enter your phone number ---\nNumber:";
    cin >> input_PhoneNum;


    //--- Date of birth ---//
    cout << "\n--- Please enter your date of birth ---\nDOB:";
    cin >> input_dob;


    //--- Email ---//
    cout << "\n--- Please enter your email address ---\nEmail:";
    cin >> input_email;


    //--- Password ---//
    cout << "\n--- Please input your password ---\nPassword:";
    cin >> input_password;


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
        << account.S_Dob << "\n";
    fout.close();
    //--- End of file writing logic ---//
   
    account.accountCreated();
}