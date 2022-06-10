#include "main.h"
#include "register.h"

class User {
public:
    int I_UserId = 0;
    char C_Gender = 'N';
    long int I_PhoneNum = 0;
    int I_dob = 0;
    string S_email = "";
    string S_password = "";
    float F_discountValue = 0;
    string S_contactMessage = "";
    bool B_isComplaint = false;
    bool B_isCompliment = false;
    float F_tab = 0;
    //A linked list to store children? Because they will have a first name, last name, etc?

    //Default Constructor
    User() {

    }
    //Constructor
    User(char gender, long int phoneNum, int dob, string email, string password) {
        C_Gender = gender;
        I_PhoneNum = phoneNum;
        I_dob = dob;
        S_email = email;
        S_password = password;
    }


    void accountCreated() {
        cout << "Your account has been succesfully created!\n";
        cout << "Your username to login is " << S_email;
    }
};

class Admin : public User {
public:
    //Bool is changed to true when an admin account is created. Used to confirm access to admin login screen.?
    bool B_isAdmin = false;

    //constructor with paremeters
    Admin(char gender, long int phoneNum, int dob, string email, string password, bool isAdmin) {
        S_email = email;
        S_password = password;
        B_isAdmin = isAdmin;
    }

    void adminCreated() {
        cout << "Your admin account has been succesfully created!\n";
        cout << "Your username to login is " << S_email;
    }
};

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

    char input_Gender;
    long int input_PhoneNum;
    int input_dob;
    string input_email;
    string input_password;

    int userAccType = 0, InputUserPin, adminPin = 1234;
    cout << "What type of account would you like to create?\n1. Admin\n2. Parent\n\nInput: ";
    cin >> userAccType;
    if (userAccType == 1) {
        cout << "Please enter pin: ";
        cin >> InputUserPin;
        if (InputUserPin != adminPin) {
            cout << "Pin is not correct, Please try again.\n";
        }
        else if (InputUserPin == adminPin) {
            cout << "Pin is correct: You are creating an admin account please complete the following:\n";
            cout << "Please tell us your gender\nF\nM\nO\n ";
            cin >> input_Gender;
            //While loop to ensure the userinput is a valid number
            while (std::cin.fail()) {
                std::cout << "\nPlease input a valid option" << std::endl;
                std::cin.clear();
                std::cin.ignore(256, '\n');
                std::cin >> input_Gender;
            };

            cout << "\nPlease tell us your phone number: ";
            cin >> input_PhoneNum;
            //While loop to ensure the userinput is a valid number
            while (std::cin.fail()) {
                std::cout << "\nPlease input a valid integer" << std::endl;
                std::cin.clear();
                std::cin.ignore(256, '\n');
                std::cin >> input_PhoneNum;
            };

            cout << "\nPlease tell us your date of birth: ";
            cin >> input_dob;
            //While loop to ensure the userinput is a valid number
            while (std::cin.fail()) {
                std::cout << "\nPlease input a valid integer" << std::endl;
                std::cin.clear();
                std::cin.ignore(256, '\n');
                std::cin >> input_dob;
            };

            cout << "\nPlease tell us your email address. Your email will be your username: ";
            cin >> input_email;
            //While loop to ensure the userinput is a valid number
            while (std::cin.fail()) {
                std::cout << "\nPlease input a valid string" << std::endl;
                std::cin.clear();
                std::cin.ignore(256, '\n');
                std::cin >> input_email;
            };

            cout << "\nPlease input your password: ";
            cin >> input_password;
            //While loop to ensure the userinput is a valid number
            while (std::cin.fail()) {
                std::cout << "\nPlease input a valid string" << std::endl;
                std::cin.clear();
                std::cin.ignore(256, '\n');
                std::cin >> input_password;
            };

            //Pass the user input in the constructor.
            bool isAdmin = true;
            Admin adminAccount(input_Gender, input_PhoneNum, input_dob, input_email, input_password, isAdmin);
            adminAccount.accountCreated();
        }
    }
    else if (userAccType == 2) {
        cout << "Please tell us your gender\nF\nM\nO\n ";
        cin >> input_Gender;
        //While loop to ensure the userinput is a valid number
        while (std::cin.fail()) {
            std::cout << "\nPlease input a valid option" << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> input_Gender;
        };

        cout << "\nPlease tell us your phone number: ";
        cin >> input_PhoneNum;
        //While loop to ensure the userinput is a valid number
        while (std::cin.fail()) {
            std::cout << "\nPlease input a valid integer" << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> input_PhoneNum;
        };

        cout << "\nPlease tell us your date of birth: ";
        cin >> input_dob;
        //While loop to ensure the userinput is a valid number
        while (std::cin.fail()) {
            std::cout << "\nPlease input a valid integer" << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> input_dob;
        };

        cout << "\nPlease tell us your email address. Your email will be your username: ";
        cin >> input_email;
        //While loop to ensure the userinput is a valid number
        while (std::cin.fail()) {
            std::cout << "\nPlease input a valid string" << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> input_email;
        };

        cout << "\nPlease input your password: ";
        cin >> input_password;
        //While loop to ensure the userinput is a valid number
        while (std::cin.fail()) {
            std::cout << "\nPlease input a valid string" << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> input_password;
        };

        //Pass the user input in the constructor.
        User account(input_Gender, input_PhoneNum, input_dob, input_email, input_password);
        account.accountCreated();
    }







}