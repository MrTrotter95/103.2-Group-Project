#include "main.h"
#include "login.h"

//--- To Check Account Exists on CSV ---//
void CheckPassword(string, string, string, string);

void VerifyAccount(string inputEmail, string inputPassword) {
    //--- Creating a instance of ifstream ---//
    std::ifstream  data("login.csv");


    //--- Temporary Variables ---//
    std::string fileId, fileEmail, filePass, fileAccessLvl, fileLine, userId, userEmail, userPass, userAccessLvl;


    //---This loops through each row of the CSV file ---//
    while (std::getline(data, fileLine))
    {
        std::stringstream  lineStream(fileLine);
        getline(lineStream, fileId, ',');
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
    }

}


//--- To Compare User Input Password Matches CSV ---//
void CheckPassword(string userId, string userPassword, string userAccessLvl, string inputPassword) {

        //--- If password is correct ---//
        if (inputPassword == userPassword) {
            cout << "Password was correct\n";
            // Pass userId to loginMain
        }
        //--- If Password is incorrect ---//
        else if (inputPassword != userPassword) {
            cout << "\nPassword does not match please try again\n";
        }
}


/*Start of Login functionality*/
void loginMain()
{
    //-- Loop controlls user attempts, Max 3 --//
    int userTries = 0;
    while (userTries < 3) {
        //--- Temporary Variables ---//
        string input_Email;
        string input_Password;


        //--- Email ---//
        cout << "--- Please enter your email ---\n";
        cout << "Email: ";
        cin >> input_Email;


        //--- Password ---//
        cout << "\nPlease enter you password: ";
        cin >> input_Password;


        //--- Pass Info To Functions ---//
        VerifyAccount(input_Email, input_Password);


        //--- This will execute if Verification & Password are incorrect ---//
        userTries++;
        cout << "Attempts: " << userTries << endl << endl;
    }


    //--- Call main menu funciton ---//
    cout << "Attempts exceeded, Please contact the school to reset your password.\n";
    cout << "Press enter to go back to the Main Menu"; //Add if functionality to to wait for user to press enter or
    int ch;
    ch = _getch();
    BeginProgram();
}