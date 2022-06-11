#include "main.h"
#include "register.h"

class User {
public:
    //User Members
    int I_UserId = 1;
    char C_Gender = 'O';
    long int I_PhoneNum = 0;
    string I_dob = " ";
    string S_email = " ";
    string S_password = " ";
    float F_discountValue = 0;
    string S_contactMessage = " "; //This will store the users feedback.
    bool B_isComplaint = false;  //If True, this will show in feedback report
    bool B_isCompliment = false; //If True, this will show in feedback report
    float F_tab = 0;
    int I_accessLevel = 1; // 1=Parent 2=Staff 3=Admin

    //Default Constructor
    User() {
    
    }
    
    //Constructor with Arguments
    User(char gender, long int phoneNum, string dob, string email, string password, int accessLevel) {
        C_Gender = gender;
        I_PhoneNum = phoneNum;
        I_dob = dob;
        S_email = email;
        S_password = password;
        I_accessLevel = accessLevel;
    }

    void accountCreated() {
        cout << "\nYour account has been succesfully created!\n";
        cout << "Your username to login is: " << S_email;
        cout << "\nYour Access level is: " << I_accessLevel << endl;
    }
};

void SaveLoginDetails(User account) {
    //Creating a instance of fstream & ifstream
    std::fstream fout;
    std::ifstream  data("login.csv");
    
    // Temporary Variables
    std::string id, line;
    int newId;

    //Start of file writing logic
    fout.open("login.csv", std::ios::out | std::ios::app);
    //This loops through each row in csv file and only checks the first cell of each row.
    while (std::getline(data, line))
    {
        std::stringstream  lineStream(line);
        getline(lineStream, id, ',');
    }

    //Converting string to int.
    std::istringstream(id) >> newId;
    //Takes last row in csv file and adds 1 to create a new unique ID.
    newId += 1;

    // Assigning the created account details to the csv file.
    fout << newId << ","
        << account.S_email << ","
        << account.S_password << ","
        << account.I_accessLevel << "\n";
    fout.close();
    //End of file writing logic
}

void SaveUserDetails(User account) {
    //Creating a instance of fstream & ifstream
    std::fstream fout;
    std::ifstream  data("userDetails.csv");

    // Temporary Variables
    std::string id, line;
    int newId;

    //Start of file writing logic
    fout.open("userDetails.csv", std::ios::out | std::ios::app);
    //This loops through each row in csv file and only checks the first cell of each row.
    while (std::getline(data, line))
    {
        std::stringstream  lineStream(line);
        getline(lineStream, id, ',');
    }

    //Converting string to int.
    std::istringstream(id) >> newId;
    //Takes last row in csv file and adds 1 to create a new unique ID.
    newId += 1;

    // Assigning the created account details to the csv file.
    fout << newId << ","
        << account.C_Gender << ","
        << account.I_PhoneNum << ","
        << account.I_dob << "\n";
    fout.close();
    //End of file writing logic
}

/*--- Start of Register functionality ---*/
void registerMain()
{
    cout << "register.cpp connected..\n";

    /*--- Temporary Variables For Account Registration ---*/
    char input_Gender;
    long int input_PhoneNum;
    string input_dob, day, month, year, input_email, input_password;
    int userAccType;       // To Determine What Account They Would Like To Create
    int InputUserPin;     // To Store User Input And Compare To AdminPin
    int adminPin = 1234; //To Grant Access To Admin 
    
    /*--- Start Of Menu/User Instructions To Register An Account ---*/
    cout << "What type of account would you like to create?\n1. Parent\n2. Staff\n3. Admin\n: ";
    cin >> userAccType;
    if (userAccType == 1) {
        cout << "--- Creating Parent account ---\n\n";


        /*--- Gender ---*/
        cout << "--- Please select your gender ---\nFemale\nMale\nOther\n ";
        cin >> input_Gender;


        /*--- Phone Number ---*/
        cout << "\n--- Please enter your phone number ---\nNumber:"; //Would be a good idea to set a max input amoun allowed.
        cin >> input_PhoneNum;
        while (std::cin.fail()) {
            std::cout << "\nPlease enter only numeric values" << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> input_PhoneNum;
        }


        /*--- Date of birth ---*/
        cout << "\n--- Please enter your date of birth ---\nExample dd/mm/yyyy:  "; //Need to work on this
        cout << "Day: ";
        cin >> day;
        cout << "Month: ";
        cin >> month;
        cout << "Year: ";
        cin >> year;
        //cin >> input_dob;


        /*--- Email ---*/
        cout << "\n--- Please enter your email address ---\nEmail:";
        cin >> input_email;


        /*--- Password ---*/
        cout << "\n--- Please input your password ---\nPassword:";
        cin >> input_password;


        /*--- Passing user input to constructor ---*/
        User account(input_Gender, input_PhoneNum, input_dob, input_email, input_password, userAccType);
        
        
        /*--- Passing account to csv writing functions ---*/
        SaveLoginDetails(account);
        SaveUserDetails(account);
    }
    else if (userAccType == 2) {
        cout << "--- Creating Staff account ---\n\n";


        /*--- Gender ---*/
        cout << "--- Please select your gender ---\nFemale\nMale\nOther\n ";
        cin >> input_Gender; //Use Jordans menu select option for this input.


        /*--- Phone Number ---*/
        cout << "\n--- Please enter your phone number ---\nNumber:";
        cin >> input_PhoneNum;


        /*--- Date of birth ---*/
        cout << "\n--- Please enter your date of birth ---\nDOB:";
        cin >> input_dob;


        /*--- Email ---*/
        cout << "\n--- Please enter your email address ---\nEmail:";
        cin >> input_email;


        /*--- Password ---*/
        cout << "\n--- Please input your password ---\nPassword:";
        cin >> input_password;

        /*--- Passing user input to constructor ---*/
        User account(input_Gender, input_PhoneNum, input_dob, input_email, input_password, userAccType);


        /*--- Passing account to csv writing functions ---*/
        SaveLoginDetails(account);
        SaveUserDetails(account);
    }
    else if (userAccType == 3) {
        /*--- Request Admin Pin ---*/
        cout << "Please enter pin: ";
        cin >> InputUserPin;
        
        
        /*--- While loop to ensure the userinput is a valid number ---*/
        int counter = 0;
        while (std::cin.fail()) {
            std::cout << "\nPlease input a valid integer" << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> InputUserPin;
        }

        /*--- If user input is wrong ---*/
        if (InputUserPin != adminPin) {
            cout << "Pin is not correct, Please try again.\n";
            //Implement Functionality to try again / go back to main menu
        }
        /*--- If user input is correct ---*/
        else if (InputUserPin == adminPin) {
            cout << "--- Pin entered correctly ---\n";
            cout << "--- Creating Admin Account ---\n";


            /*--- Gender ---*/
            cout << "--- Please select your gender ---\nFemale\nMale\nOther\n ";
            cin >> input_Gender; //Use Jordans menu select option for this input.


            /*--- Phone Number ---*/
            cout << "\n--- Please enter your phone number ---\nNumber:";
            cin >> input_PhoneNum;


            /*--- Date of birth ---*/
            cout << "\n--- Please enter your date of birth ---\nDOB:";
            cin >> input_dob;


            /*--- Email ---*/
            cout << "\n--- Please enter your email address ---\nEmail:";
            cin >> input_email;
            

            /*--- Password ---*/
            cout << "\n--- Please input your password ---\nPassword:";
            cin >> input_password;


            /*--- Passing user input to constructor ---*/
            User account(input_Gender, input_PhoneNum, input_dob, input_email, input_password, userAccType);


            /*--- Passing account to csv writing functions ---*/
            SaveLoginDetails(account);
            SaveUserDetails(account);
        }
    }







}