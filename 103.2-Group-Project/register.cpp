#include "main.h"
#include "register.h"

class User {
public:
    int I_UserId = 1;
    char C_Gender = 'O';
    long int I_PhoneNum = 0;
    int I_dob = 0;
    string S_email = "";
    string S_password = "";
    float F_discountValue = 0;
    string S_contactMessage = "";
    bool B_isComplaint = false;
    bool B_isCompliment = false;
    float F_tab = 0;
    int I_accessLevel = 1; // 1 Parent, 2 staff, 3 admin

    //Default Constructor
    User() {
    
    }
    //Constructor
    User(char gender, long int phoneNum, int dob, string email, string password, int accessLevel) {
        C_Gender = gender;
        I_PhoneNum = phoneNum;
        I_dob = dob;
        S_email = email;
        S_password = password;
        I_accessLevel = accessLevel;
        //implement the functionality to write to the csv file
    }

    void accountCreated() {
        cout << "\nYour account has been succesfully created!\n";
        cout << "Your username to login is: " << S_email;
        cout << "\nYour Access level is: " << I_accessLevel << endl;
    }
};

void saveLoginDetails(User account) {
    std::fstream fout;

    std::string filename = "login.csv";
    fout.open(filename, std::ios::out);



    fout.close();

    /*
    // file pointer
    std::fstream fout;
    std::fstream fin;

    // opens an existing csv file or creates a new file.
    fout.open("login.csv", std::ios::out | std::ios::app);

    fin.open("login.csv", std::ios::in);

    fin.is_open();
    while (!fin.eof()) {
        getline(fin, userId, ',');
    }*/


    fout << account.I_UserId << ", "
         << account.S_email << ", "
         << account.S_password << ", "
         << account.I_accessLevel << "\n";
}

/* START OF CLASS USER PSUEDO CODE

    Members include:
• UserId: int
• Gender: char
• PhoneNum: long int?
• DOB: int
• Password: string
• Email: string;
• AccessLevel: int;
• DiscountValue: float;
• Children: null
• ContactMessage: string
• IsComplaint: bool
• IsResolved: bool
• Tab: float

    Constructors include:
•Default Constructor
•Constructor with parameters

    Functions include:
•Login()
    Create login atempt loop with max tries = 3
    Display user instructions to user
    Allow user to input details
    store them in a varaible
    check if user exists (if user doesn't exist diplay warning) (if user input is wrong key types display warning)
    Check password is a match (is user input doesn't match display warning)
    If password doesn't match increase counter by 1.
    If counter == 3 execute function ForgotPass();
    If Password does match display confirmation message.
    Pass details into loggedIn() function.
•ForgotPass()
    Display message to user
    Execute Main Menu Function
END OF CLASS USER PSUEDO CODE*/

/*START OF PSUDEO CODE
    Using a paramemter Constuctor from Class User,
    Display user instructions to user
    allow user to input detail
    Include error checking to make sure the user inputs the correct key.
    Store them in a temporary variable
    Ask to confirm their password.
    Compare both inputs to each other.
    (if false) try again message.
    (if true) continue.
    Assign user input to the instance of the class
    Save these values to the csv file?
    Display a confirmation message to the user.
    Execute the next function / open the relevant signed in menu (parent/admin).?? Potentially?
 END OF PSUDEO CODE*/


/*Start of Register functionality*/
void registerMain()
{
    cout << "register.cpp connected..\n";

    // user Variables to handle user input for registration
    char input_Gender;
    long int input_PhoneNum;
    int input_dob;
    string input_email;
    string input_password;
    int userAccType; // To Determine what account they would like to create

    int InputUserPin;
    int adminPin = 1234;
    
    cout << "What type of account would you like to create?\n1. Parent\n2. Staff\n3. Admin\n: ";
    cin >> userAccType;
    if (userAccType == 1) {
        cout << "--- Creating Parent account ---\n\n";
        cout << "--- Please select your gender ---\nFemale\nMale\nOther\n ";
        cin >> input_Gender;

        cout << "\n--- Please enter your phone number ---\nNumber:";
        cin >> input_PhoneNum;

        cout << "\n--- Please enter your date of birth ---\nDOB:";
        cin >> input_dob;

        cout << "\n--- Please enter your email address ---\nEmail:";
        cin >> input_email;

        cout << "\n--- Please input your password ---\nPassword:";
        cin >> input_password;

        //Pass the user input in the constructor.
        User account(input_Gender, input_PhoneNum, input_dob, input_email, input_password, userAccType);
        saveLoginDetails(account);
    }
    else if (userAccType == 2) {
        cout << "--- Creating Staff account ---\n\n";
        cout << "--- Please select your gender ---\nFemale\nMale\nOther\n ";
        cin >> input_Gender;

        cout << "\n--- Please enter your phone number ---\nNumber:";
        cin >> input_PhoneNum;

        cout << "\n--- Please enter your date of birth ---\nDOB:";
        cin >> input_dob;

        cout << "\n--- Please enter your email address ---\nEmail:";
        cin >> input_email;

        cout << "\n--- Please input your password ---\nPassword:";
        cin >> input_password;

        //Pass the user input in the constructor.
        User account(input_Gender, input_PhoneNum, input_dob, input_email, input_password, userAccType);
        saveLoginDetails(account);
    }
    else if (userAccType == 3) {
        cout << "Please enter pin: ";
        cin >> InputUserPin;
        //While loop to ensure the userinput is a valid number
        int counter = 0;
        while (std::cin.fail()) {
            std::cout << "\nPlease input a valid integer" << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> InputUserPin;
        }
        if (InputUserPin != adminPin) {
            cout << "Pin is not correct, Please try again.\n";
            //Implement Functionality to try again / go back to main menu
        }
        else if (InputUserPin == adminPin) {
            cout << "--- Pin entered correctly ---\n";
            cout << "--- Creating Admin Account ---\n";
            cout << "--- Please select your gender ---\nFemale\nMale\nOther\n ";
            cin >> input_Gender;

            cout << "\n--- Please enter your phone number ---\nNumber:";
            cin >> input_PhoneNum;

            cout << "\n--- Please enter your date of birth ---\nDOB:";
            cin >> input_dob;

            cout << "\n--- Please enter your email address ---\nEmail:";
            cin >> input_email;

            cout << "\n--- Please input your password ---\nPassword:";
            cin >> input_password;

            //Pass the user input in the constructor.
            User account(input_Gender, input_PhoneNum, input_dob, input_email, input_password, userAccType);
            saveLoginDetails(account);
            
        }
    }







}