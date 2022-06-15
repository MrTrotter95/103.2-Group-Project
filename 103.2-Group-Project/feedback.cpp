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

void PrintArray_ParentFeedbackMenu();
void ArrowSelectionMenu_ParentFeedback(string, string , string);
void GeneralContact(string, string, string);
void SendCompliment(string, string, string);
void SendComplaint(string, string, string);
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
void feedbackMain(string userId, string userName, string userEmail, string accessLevel) // This must have a User ID comming into it and or access level?
{

	//--- Parent ---//
	if (accessLevel == "1") {
		system("cls");
		PrintArray_ParentFeedbackMenu();
		cout << "\nWelcome Parent to the feedback zone.\n";
		ArrowSelectionMenu_ParentFeedback(userId, userName, userEmail);
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

void PrintArray_ParentFeedbackMenu() {
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

void ArrowSelectionMenu_ParentFeedback(string userId, string userName, string userEmail) {
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
			PrintArray_ParentFeedbackMenu();

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
				GeneralContact(userId, userName, userEmail);

				break;
			case 1:
				SendCompliment(userId, userName, userEmail);

				break;
			case 2:
				SendComplaint(userId, userName, userEmail);

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
void GeneralContact(string userId, string userName, string userEmail) {
	//--- Creating a instance of fstream ---//
	std::fstream fout;
	std::ifstream  data("GeneralContact.csv");


	//--- Temporary Variables ---//
	string userMessage, actioned = "No";
	std::string id, line;
	int token;


	//--- User Instructions ---//
	cout << "Please enter your message.\n\n";
	getline(cin, userMessage);
	while (userMessage.size() > 75) { //--- Max Input Size ---//
		cout << "75 character limit reached. Please try again\n";
		std::cin.clear();
		getline(cin, userMessage);
	}

	//--- Start of file writing logic ---//
	fout.open("GeneralContact.csv", std::ios::out | std::ios::app);
	//--- This loops through each row in csv file and only checks the first cell of each row. ---//
	while (std::getline(data, line))
	{
		std::stringstream  lineStream(line);
		getline(lineStream, id, ',');
	}


	//--- Converting string to int. ---//
	std::istringstream(id) >> token;
	//--- Takes last row in csv file and adds 1 to create a new unique ID. ---//
	token += 1;


	//--- Outputing the user message details to the csv file. ---//
	fout << token << ","
		 << actioned << ","
		 << userName << ","
		 << userEmail << ","
		 << userMessage << "\n";
	fout.close();
	//--- End of file writing logic ---//


	//--- User instructions to end ---//
	cout << "Thank you for getting in touch.\n\nPress enter to return to main menu";
	int ch;
	ch = _getch();
	ArrowSelectionMenu_MainMenu(); // Replace with correct menu might need to pass user ID back through
}

void SendCompliment(string userId, string userName, string userEmail) {
	//--- Creating a instance of fstream ---//
	std::fstream fout;
	std::ifstream  data("Compliments.csv");


	//--- Temporary Variables ---//
	string userMessage, actioned = "No";
	std::string id, line;
	int token;


	//--- User Instructions ---//
	cout << "Please enter your message.\n\n";
	getline(cin, userMessage);
	while (userMessage.size() > 75) { //--- Max Input Size ---//
		cout << "75 character limit reached. Please try again\n";
		std::cin.clear();
		getline(cin, userMessage);
	}


	//--- Start of file writing logic ---//
	fout.open("Compliments.csv", std::ios::out | std::ios::app);
	//--- This loops through each row in csv file and only checks the first cell of each row. ---//
	while (std::getline(data, line))
	{
		std::stringstream  lineStream(line);
		getline(lineStream, id, ',');
	}


	//--- Converting string to int. ---//
	std::istringstream(id) >> token;
	//--- Takes last row in csv file and adds 1 to create a new unique ID. ---//
	token += 1;


	//--- Outputing the user message details to the csv file. ---//
	fout << token << ","
		 << actioned << ","
		 << userName << ","
		 << userEmail << ","
		 << userMessage << "\n";
	fout.close();
	//--- End of file writing logic ---//


	//--- User instructions to end ---//
	cout << "Thank you for your feedback!\n\nPress enter to return to main menu";
	int ch;
	ch = _getch();
	ArrowSelectionMenu_MainMenu(); // Replace with correct menu
}

void SendComplaint(string userId, string userName, string userEmail) {
	//--- Creating a instance of fstream ---//
	std::fstream fout;
	std::ifstream  data("Complaints.csv");

	//--- Temporary Variables ---//
	string userMessage, actioned = "No";
	std::string id, line;
	int token;

	//--- User Instructions ---//
	cout << "Please enter your message.\n\n";
	getline(cin, userMessage);
	while (userMessage.size() > 75) { //--- Max Input Size ---//
		cout << "75 character limit reached. Please try again\n";
		std::cin.clear();
		getline(cin, userMessage);
	}


	//--- Start of file writing logic ---//
	fout.open("Complaints.csv", std::ios::out | std::ios::app);
	//--- This loops through each row in csv file and only checks the first cell of each row. ---//
	while (std::getline(data, line))
	{
		std::stringstream  lineStream(line);
		getline(lineStream, id, ',');
	}


	//--- Converting string to int. ---//
	std::istringstream(id) >> token;
	//--- Takes last row in csv file and adds 1 to create a new unique ID. ---//
	token += 1;


	//--- Outputing the user message details to the csv file. ---//
	fout << token << ","
		 << actioned << ","
		 << userName << ","
		 << userEmail << ","
		 << userMessage << "\n";
	fout.close();
	//--- End of file writing logic ---//


	//--- User instructions to end ---//
	cout << "Thank you for your feedback, we will get back to you as soon as possible.\n\nPress enter to return to main menu";
	int ch;
	ch = _getch();
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
	std::string fileToken, fileName, fileEmail, fileMessage, isRead, fileLine;

	cout << "---Name---\t\t-------------------------------------Message-------------------------------------\n";

	//---This loops through each row of the CSV file ---//
	while (std::getline(data, fileLine))
	{
		std::stringstream  lineStream(fileLine);
		getline(lineStream, fileToken, ',');
		getline(lineStream, fileName, ',');
		getline(lineStream, fileEmail, ',');
		getline(lineStream, fileMessage, ',');
		getline(lineStream, isRead, ',');

		if (isRead == "1") {
			cout << fileName << "\t\t";
			cout << fileMessage << endl;
		}
	}


	//--- User instructions to end ---//
	cout << "Press enter to return to main menu";
	ArrowSelectionMenu_MainMenu(); // Replace with correct menu
}

void ViewCompliments() {
	//--- Creating a instance of ifstream ---//
	std::ifstream  data("Compliments.csv");


	//--- Temporary Variables ---//
	std::string fileId, fileName, fileEmail, fileMessage, isRead, fileLine;


	//---This loops through each row of the CSV file and displays all messages ---//
	while (std::getline(data, fileLine))
	{
		std::stringstream  lineStream(fileLine);
		getline(lineStream, fileId, ',');
		getline(lineStream, fileName, ',');
		getline(lineStream, fileEmail, ',');
		getline(lineStream, fileMessage, ',');
		getline(lineStream, isRead, ',');

		if (isRead == "1") {
			cout << "Name: " << fileName << "\t";
			cout << "Message: " << fileMessage << endl;
		}
	}


	//--- User instructions to end ---//
	cout << "Press enter to return to main menu";
	ArrowSelectionMenu_MainMenu(); // Replace with correct menu
}

void ViewComplaints() {
	//--- Creating a instance of ifstream ---//
	std::ifstream  data("Complaints.csv");


	//--- Temporary Variables ---//
	std::string fileId, fileName, fileEmail, fileMessage, isRead, fileLine;


	//---This loops through each row of the CSV file and displays all messages ---//
	while (std::getline(data, fileLine))
	{
		std::stringstream  lineStream(fileLine);
		getline(lineStream, fileId, ',');
		getline(lineStream, fileName, ',');
		getline(lineStream, fileEmail, ',');
		getline(lineStream, fileMessage, ',');

		if (isRead == "1") {
			cout << "Name: " << fileName << "\t";
			cout << "Message: " << fileMessage << endl;
		}
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
	std::fstream fout_general;
	std::fstream fin_general;

	fin_general.open("GeneralContact.csv", std::ios::in);
	fout_general.open("GeneralContactNew.csv", std::ios::out | std::ios::app);



	std::string line, newData = "Yes";
	int count_gen = 1, cellBounds = 5;
	std::vector<string> general;
	double tokenChoice, targetElement = 1;

	cout << "Token:\tDone:\tName:\t\tEmail:\t\t\t\tMessage:\n";

	while (std::getline(fin_general, line)) {
		std::stringstream lineStream(line);
		string cell;
		while (std::getline(lineStream, cell, ',')) {

			if (count_gen % cellBounds == 0) 
			{
				cout << cell << "\n";
				general.push_back(cell);
				count_gen++;
			}
			else 
			{
				if (count_gen % cellBounds == 1 || count_gen % cellBounds == 2 || count_gen % cellBounds == 3)
				{
					cout << cell << "\t";
					general.push_back(cell);
					count_gen++;
				}
				else if (count_gen % cellBounds == 4) {
					cout << cell << "\t\t";
					general.push_back(cell);
					count_gen++;
				}
				else 
				{
					cout << cell << " ";
					general.push_back(cell);
					count_gen++;
				}
			}
		}
	}


	//Choose Token to edit
	cout << "Please input the ID number of the message you wish to mark as complete: ";
	cin >> tokenChoice;

	general.at((cellBounds * (tokenChoice - 1)) + targetElement) = newData;
	

	// placing data into new CSV
	for (int i = 0; i < general.size(); i++) {
		if (count_gen % cellBounds == 0) {
			fout_general << general[i] << "\n";
			count_gen++;
		}
		else {
			fout_general << general[i] << ",";
			count_gen++;
		}
	}


	fin_general.close();
	fout_general.close();



	std::remove("GeneralContact.csv");
	std::rename("GeneralContactNew.csv", "GeneralContact.csv");
}

void RespondCompliments(string userId, string userEmail) {
	std::fstream fout_compliments;
	std::fstream fin_compliments;
	fin_compliments.open("Compliments.csv", std::ios::in);
	fout_compliments.open("ComplimentsNew.csv", std::ios::out | std::ios::app);




	fin_compliments.close();
	fout_compliments.close();
	
	
}

void RespondComplaints(string userId, string userEmail) {
	std::fstream fout_complaints;
	std::fstream fin_complaints;


	fin_complaints.open("Complaints.csv", std::ios::in);
	fout_complaints.open("ComplaintsNew.csv", std::ios::out | std::ios::app);





	fin_complaints.close();
	fout_complaints.close();
}

/*-------------------------END OF ADMIN FEEDBACK FUNCTIONALITY -------------------------*/