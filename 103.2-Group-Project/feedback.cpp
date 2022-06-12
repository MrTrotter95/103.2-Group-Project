#include "main.h"
#include "feedback.h"


/* START OF FEEDBACK PSEUDO CODE FOR ADMIN 
    •Create function: Feedback()
    •Display Options to user Complaint/Compliment/General
    •Display all feedback from parents/user.
    •Potentially include  bool = hasContacted;  change this value to true when a parent submits a complaint
    •Allow user to select one and change value to actioned.
    •Potentially include bool = hasContactedResolved; change this value to true when a admin resolves a complaint.
In simple terms, I want to have a function that will remove a compaint or change it to resolved so it doesn't show up in the list anymore
We will still have a record of a compaint, but it will be marked as resolved.
    •User can exit at any time back to their logged in menu. 
END OF FEEDBACK PSEUDO CODE FOR ADMIN */

/* START OF FEEDBACK PSEUDO CODE FOR PARENT
    Create functiin: ContactUs();
    display options of the types of contact a user can make General Contact / Complaint / Compliment
    Create three functions: GeneralContact(), Complaint(), Compliment().
    These three functions just display a message.
    Allow user to go back to the main menu.
END OF FEEDBACK PSEUDO CODE FOR PARENT */

void PrintArray_ParentFeedbackMenu(string, string);
void ArrowSelectionMenu_ParentFeedback(string, string);
void GeneralContact(string, string);
void SendCompliment(string, string);
void SendComplaint(string, string);
void PrintArray_StaffFeedbackMenu();
void ArrowSelectionMenu_StaffFeedback();
void ViewGeneralMessages();
void ViewCompliments();
void ViewComplaints();
void PrintArray_AdminFeedbackMenu(string, string);
void ArrowSelectionMenu_AdminFeedback(string, string);
void RespondGeneralMessages(string, string);
void RespondCompliments(string, string);
void RespondComplaints(string, string);

/*Start of Feedback functionality*/
void feedbackMain(string userId, string userEmail, string accessLevel) // This must have a User ID comming into it and or access level?
{

	//--- Parent ---//
	if (accessLevel == "1") {
		system("cls");
		PrintArray_ParentFeedbackMenu(userId, userEmail);
		cout << "\nWelcome Parent to the feedback zone.\n";
		ArrowSelectionMenu_ParentFeedback(userId, userEmail);
	}
	//--- Staff ---//
	else if (accessLevel == "2") {
		system("cls");
		PrintArray_StaffFeedbackMenu();
		cout << "\nWelcome Staff to the feedback zone.\n";
		ArrowSelectionMenu_StaffFeedback();
	}
	//--- Admin ---//
	else if (accessLevel == "3") {
		system("cls");
		PrintArray_AdminFeedbackMenu(userId, userEmail);
		cout << "\nWelcome Admin to the feedback zone.\n";
		ArrowSelectionMenu_AdminFeedback(userId, userEmail);
	}
}


/*-------------------------START OF PARENT FEEDBACK MENU SECTION -------------------------*/
const int menuSize_ParentFeedBack = 4;
int selectionHighlight_ParentFeedback = 0;
string mainMenuPrint_ParentFeedback[menuSize_ParentFeedBack] = { "General", "Compliment", "Complaint", "Exit"};

void PrintArray_ParentFeedbackMenu(string userId, string userEmail) {
	for (int i = 0; i < menuSize_ParentFeedBack; i++)
	{
		if (i == selectionHighlight_ParentFeedback)
		{
			WriteInColor(3, mainMenuPrint_ParentFeedback[selectionHighlight_ParentFeedback]);
			cout << endl;
		}
		else
		{
			WriteInColor(15, mainMenuPrint_ParentFeedback[i]);
			cout << endl;
		}
	}
}

void ArrowSelectionMenu_ParentFeedback(string userId, string userEmail) {
	//cout << "Use arrow keys to make selection\n\n";
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
				if (selectionHighlight_ParentFeedback > 0)
				{
					selectionHighlight_ParentFeedback--;
				}
				else
				{
					selectionHighlight_ParentFeedback = (menuSize_ParentFeedBack - 1);
				}
				break;
			case KEY_DOWN:
				//This key is assigned to decrease the highlighted number by 1
				if (selectionHighlight_ParentFeedback < (menuSize_ParentFeedBack - 1))
				{
					selectionHighlight_ParentFeedback++;
				}
				else
				{
					selectionHighlight_ParentFeedback = 0;
				}
				break;
			default:
				cout << "\nThis key is unassigned.\n";
				break;
			}

			system("cls");
			PrintArray_ParentFeedbackMenu(userId, userEmail);

			switch (selectionHighlight_ParentFeedback)
			{
			case 0:
				cout << "\nGeneral Contact\n";
				break;
			case 1:
				cout << "\nSend us a compliment\n";
				break;
			case 2:
				cout << "\nSubmit a complaint\n";
				break;
			case 3:
				cout << "\nExit the program\n";
				break;
			}
			break;
		case 13:
			switch (selectionHighlight_ParentFeedback)
			{
			case 0:
				GeneralContact(userId, userEmail);

				break;
			case 1:
				SendCompliment(userId, userEmail);

				break;
			case 2:
				SendComplaint(userId, userEmail);

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
/*-------------------------END OF PARENT FEEDBACK MENU SECTION -------------------------*/
/*-------------------------START OF PARENT FEEDBACK FUNCTIONALITY -------------------------*/
void GeneralContact(string userId, string userEmail) {
	//--- Creating a instance of fstream ---//
	std::fstream fout;


	//--- Temporary Variables ---//
	string userMessage;


	//--- User Instructions ---//
	cout << "Please enter your message.\n\n";
	getline(cin, userMessage);


	//--- Start of file writing logic ---//
	fout.open("GeneralContact.csv", std::ios::out | std::ios::app);


	//--- Assigning the userId & message to the csv file. ---//
	fout << userId << ","
		 << userEmail << ","
		 << userMessage << "\n";
	fout.close();
	//--- End of file writing logic ---//


	//--- User instructions to end ---//
	cout << "Thank you for getting in touch.\n\nPress enter to return to main menu";
	ArrowSelectionMenu_MainMenu(); // Replace with correct menu might need to pass user ID back through
}

void SendCompliment(string userId, string userEmail) {
	//--- Creating a instance of fstream ---//
	std::fstream fout;


	//--- Temporary Variables ---//
	string userMessage;


	//--- User Instructions ---//
	cout << "Please enter your message.\n\n";
	getline(cin, userMessage);


	//--- Start of file writing logic ---//
	fout.open("Compliments.csv", std::ios::out | std::ios::app);


	//--- Assigning the userId, email and message to the csv file. ---//
	fout << userId << ","
		 << userEmail << ","
		 << userMessage << "\n";
	fout.close();
	//--- End of file writing logic ---//


	//--- User instructions to end ---//
	cout << "Thank you for your feedback!\n\nPress enter to return to main menu";
	ArrowSelectionMenu_MainMenu(); // Replace with correct menu
}

void SendComplaint(string userId, string userEmail) {
	//--- Creating a instance of fstream ---//
	std::fstream fout;


	//--- Temporary Variables ---//
	string userMessage;


	//--- User Instructions ---//
	cout << "Please enter your message.\n\n";
	getline(cin, userMessage);


	//--- Start of file writing logic ---//
	fout.open("Complaints.csv", std::ios::out | std::ios::app);


	//--- Assigning the userId & message to the csv file. ---//
	fout << userId << ","
		 << userEmail << ","
		 << userMessage << "\n";
	fout.close();
	//--- End of file writing logic ---//


	//--- User instructions to end ---//
	cout << "Thank you for your feedback, we will get back to you as soon as possible.\n\nPress enter to return to main menu";
	ArrowSelectionMenu_MainMenu(); // Replace with correct menu
}
/*-------------------------END OF PARENT FEEDBACK FUNCTIONALITY -------------------------*/
/*-------------------------START OF STAFF FEEDBACK MENU SECTION -------------------------*/
const int menuSize_StaffFeedBack = 4;
int selectionHighlight_StaffFeedback = 0;
string mainMenuPrint_StaffFeedback[menuSize_StaffFeedBack] = { "General", "Compliments", "Complaints", "Exit" };


void PrintArray_StaffFeedbackMenu() {
	for (int i = 0; i < menuSize_StaffFeedBack; i++)
	{
		if (i == selectionHighlight_StaffFeedback)
		{
			WriteInColor(3, mainMenuPrint_StaffFeedback[selectionHighlight_StaffFeedback]);
			cout << endl;
		}
		else
		{
			WriteInColor(15, mainMenuPrint_StaffFeedback[i]);
			cout << endl;
		}
	}
}

void ArrowSelectionMenu_StaffFeedback() {
	//cout << "Use arrow keys to make selection\n\n";
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
				if (selectionHighlight_StaffFeedback > 0)
				{
					selectionHighlight_StaffFeedback--;
				}
				else
				{
					selectionHighlight_StaffFeedback = (menuSize_StaffFeedBack - 1);
				}
				break;
			case KEY_DOWN:
				//This key is assigned to decrease the highlighted number by 1
				if (selectionHighlight_StaffFeedback < (menuSize_StaffFeedBack - 1))
				{
					selectionHighlight_StaffFeedback++;
				}
				else
				{
					selectionHighlight_StaffFeedback = 0;
				}
				break;
			default:
				cout << "\nThis key is unassigned.\n";
				break;
			}

			system("cls");
			PrintArray_StaffFeedbackMenu();

			switch (selectionHighlight_StaffFeedback)
			{
			case 0:
				cout << "\nView All General Contact Messages Received\n";
				break;
			case 1:
				cout << "\nView All Compliements Received\n";
				break;
			case 2:
				cout << "\nView All Complaints Received\n";
				break;
			case 3:
				cout << "\nExit the program\n";
				break;
			}
			break;
		case 13:
			switch (selectionHighlight_StaffFeedback)
			{
			case 0:
				ViewGeneralMessages();

				break;
			case 1:
				ViewCompliments();

				break;
			case 2:
				ViewComplaints();

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
/*-------------------------END OF STAFF FEEDBACK MENU SECTION -------------------------*/
/*-------------------------START OF STAFF FEEDBACK FUNCTIONALITY -------------------------*/
void ViewGeneralMessages() {
	//--- Creating a instance of ifstream ---//
	std::ifstream  data("GeneralContact.csv");


	//--- Temporary Variables ---//
	std::string fileId, fileEmail, fileMessage, fileLine;


	//---This loops through each row of the CSV file ---//
	while (std::getline(data, fileLine))
	{
		std::stringstream  lineStream(fileLine);
		getline(lineStream, fileId, ',');
		getline(lineStream, fileEmail, ',');
		getline(lineStream, fileMessage, ',');

		cout << "Email: " << fileEmail << "\t";
		cout << "Message: " << fileMessage << endl;
	}


	//--- User instructions to end ---//
	cout << "Press enter to return to main menu";
	ArrowSelectionMenu_MainMenu(); // Replace with correct menu
}

void ViewCompliments() {
	//--- Creating a instance of ifstream ---//
	std::ifstream  data("Compliments.csv");


	//--- Temporary Variables ---//
	std::string fileId, fileEmail, fileMessage, fileLine;


	//---This loops through each row of the CSV file and displays all messages ---//
	while (std::getline(data, fileLine))
	{
		std::stringstream  lineStream(fileLine);
		getline(lineStream, fileId, ',');
		getline(lineStream, fileEmail, ',');
		getline(lineStream, fileMessage, ',');

		cout << "Email: " << fileEmail << "\t";
		cout << "Message: " << fileMessage << endl;

	}


	//--- User instructions to end ---//
	cout << "Press enter to return to main menu";
	ArrowSelectionMenu_MainMenu(); // Replace with correct menu
}

void ViewComplaints() {
	//--- Creating a instance of ifstream ---//
	std::ifstream  data("Complaints.csv");


	//--- Temporary Variables ---//
	std::string fileId, fileEmail, fileMessage, fileLine;


	//---This loops through each row of the CSV file and displays all messages ---//
	while (std::getline(data, fileLine))
	{
		std::stringstream  lineStream(fileLine);
		getline(lineStream, fileId, ',');
		getline(lineStream, fileEmail, ',');
		getline(lineStream, fileMessage, ',');

		cout << "Email: " << fileEmail << "\t";
		cout << "Message: " << fileMessage << endl;
	}


	//--- User instructions to end ---//
	cout << "Press enter to return to main menu";
	ArrowSelectionMenu_MainMenu(); // Replace with correct menu
}
/*-------------------------END OF STAFF FEEDBACK FUNCTIONALITY -------------------------*/
/*-------------------------START OF ADMIN FEEDBACK MENU SECTION -------------------------*/
const int menuSize_AdminFeedBack = 4;
int selectionHighlight_AdminFeedback = 0;
string mainMenuPrint_AdminFeedback[menuSize_AdminFeedBack] = { "General", "Compliments", "Complaints", "Exit" };


void PrintArray_AdminFeedbackMenu(string userId, string userEmail) {
	for (int i = 0; i < menuSize_AdminFeedBack; i++)
	{
		if (i == selectionHighlight_AdminFeedback)
		{
			WriteInColor(3, mainMenuPrint_AdminFeedback[selectionHighlight_AdminFeedback]);
			cout << endl;
		}
		else
		{
			WriteInColor(15, mainMenuPrint_AdminFeedback[i]);
			cout << endl;
		}
	}
}

void ArrowSelectionMenu_AdminFeedback(string userId, string userEmail) {
	//cout << "Use arrow keys to make selection\n\n";
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
				if (selectionHighlight_AdminFeedback > 0)
				{
					selectionHighlight_AdminFeedback--;
				}
				else
				{
					selectionHighlight_AdminFeedback = (menuSize_AdminFeedBack - 1);
				}
				break;
			case KEY_DOWN:
				//This key is assigned to decrease the highlighted number by 1
				if (selectionHighlight_AdminFeedback < (menuSize_AdminFeedBack - 1))
				{
					selectionHighlight_AdminFeedback++;
				}
				else
				{
					selectionHighlight_AdminFeedback = 0;
				}
				break;
			default:
				cout << "\nThis key is unassigned.\n";
				break;
			}

			system("cls");
			PrintArray_AdminFeedbackMenu(userId, userEmail);

			switch (selectionHighlight_AdminFeedback)
			{
			case 0:
				cout << "\nRespond To General Messages\n";
				break;
			case 1:
				cout << "\nRespond To Compliments Received\n";
				break;
			case 2:
				cout << "\nRespond To Complaints Received\n";
				break;
			case 3:
				cout << "\nExit the program\n";
				break;
			}
			break;
		case 13:
			switch (selectionHighlight_AdminFeedback)
			{
			case 0:
				RespondGeneralMessages(userId, userEmail);

				break;
			case 1:
				RespondCompliments(userId, userEmail);

				break;
			case 2:
				RespondComplaints(userId, userEmail);

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
/*-------------------------END OF ADMIN FEEDBACK MENU SECTION -------------------------*/
/*-------------------------START OF ADMIN FEEDBACK FUNCTIONALITY -------------------------*/
void RespondGeneralMessages(string userId, string userEmail) {
	//--- Creating a instance of ifstream & fstream ---//
	std::fstream fout;
	std::ifstream  data("GeneralContact.csv");


	//--- Temporary Variables ---//
	std::string fileId, fileEmail, fileMessage, fileLine;


	//---This loops through each row of the CSV file ---//
	while (std::getline(data, fileLine))
	{
		std::stringstream  lineStream(fileLine);
		getline(lineStream, fileId, ',');
		getline(lineStream, fileEmail, ',');
		getline(lineStream, fileMessage, ',');

		cout << "ID: " << fileId << "\t";
		cout << "Email: " << fileEmail << "\t";
		cout << "Message: " << fileMessage << endl;
	}


	//--- User instructions ---//
	cout << "Please input the ID number of the message you wish to mark as complete: ";
	string userInput;
	cin >> userInput; 


	/*
	//Start of file writing logic
	fout.open("GeneralContact.csv", std::ios::out | std::ios::app);
	while (std::getline(data, fileLine)) {
		std::stringstream  lineStream(fileLine);
		getline(lineStream, fileId, ',');
		getline(lineStream, fileEmail, ',');
		getline(lineStream, fileMessage, ',');

		if (userInput == fileId) {
			break;
		}
		else if (userInput != fileId) {
			RespondGeneralMessages(userId, userEmail);
		}
	}

	fout << " " << ","
		<< " " << ","
		<< " " << "\n";
	fout.close();
	*/
}

void RespondCompliments(string userId, string userEmail) {
	//--- Creating a instance of ifstream & fstream ---//
	std::fstream fout;
	std::ifstream  data("Compliments.csv");


	//--- Temporary Variables ---//
	std::string fileId, fileEmail, fileMessage, fileLine;


	//---This loops through each row of the CSV file ---//
	while (std::getline(data, fileLine))
	{
		std::stringstream  lineStream(fileLine);
		getline(lineStream, fileId, ',');
		getline(lineStream, fileEmail, ',');
		getline(lineStream, fileMessage, ',');

		cout << "ID: " << fileId << "\t";
		cout << "Email: " << fileEmail << "\t";
		cout << "Message: " << fileMessage << endl;
	}


	//--- User instructions ---//
	cout << "Please input the ID number of the message you wish to mark as complete: ";
	string userInput;
	cin >> userInput;
}

void RespondComplaints(string userId, string userEmail) {
	//--- Creating a instance of ifstream & fstream ---//
	std::fstream fout;
	std::ifstream  data("Complaints.csv");


	//--- Temporary Variables ---//
	std::string fileId, fileEmail, fileMessage, fileLine;


	//---This loops through each row of the CSV file ---//
	while (std::getline(data, fileLine))
	{
		std::stringstream  lineStream(fileLine);
		getline(lineStream, fileId, ',');
		getline(lineStream, fileEmail, ',');
		getline(lineStream, fileMessage, ',');

		cout << "ID: " << fileId << "\t";
		cout << "Email: " << fileEmail << "\t";
		cout << "Message: " << fileMessage << endl;
	}


	//--- User instructions ---//
	cout << "Please input the ID number of the message you wish to mark as complete: ";
	string userInput;
	cin >> userInput;
}

/*-------------------------END OF ADMIN FEEDBACK FUNCTIONALITY -------------------------*/