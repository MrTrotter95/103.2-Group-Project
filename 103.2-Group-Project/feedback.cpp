#include "main.h"
#include "feedback.h"
#include "login.h"

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
string mainMenuPrint_ParentFeedback[menuSize_ParentFeedBack] = { "General", "Compliment", "Complaint", "Return"};

void PrintArray_ParentFeedbackMenu() {
	cout << "********************************\n*   Welcome to the Parent Feedback Menu  *\n********************************\n";
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
string mainMenuPrint_StaffFeedback[menuSize_StaffFeedBack] = { "General", "Compliments", "Complaints", "Return" };


void PrintArray_StaffFeedbackMenu() {
	cout << "********************************\n*   Welcome to the Staff Feedback Menu  *\n********************************\n";
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
	std::string fileToken, fileResolved, fileName, fileEmail, fileMessage, fileLine;


	cout << "Name\t\tMessage\n";


	//---This loops through each row of the CSV file ---//
	while (std::getline(data, fileLine))
	{
		std::stringstream  lineStream(fileLine);
		getline(lineStream, fileToken, ',');
		getline(lineStream, fileResolved, ',');
		getline(lineStream, fileName, ',');
		getline(lineStream, fileEmail, ',');
		getline(lineStream, fileMessage, ',');

		if (fileResolved == "No") {
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
	std::string fileId, fileResolved, fileName, fileEmail, fileMessage, fileLine;


	cout << "Name\t\tMessage\n";


	//---This loops through each row of the CSV file and displays all messages ---//
	while (std::getline(data, fileLine))
	{
		std::stringstream  lineStream(fileLine);
		getline(lineStream, fileId, ',');
		getline(lineStream, fileResolved, ',');
		getline(lineStream, fileName, ',');
		getline(lineStream, fileEmail, ',');
		getline(lineStream, fileMessage, ',');

		if (fileResolved == "No") {
			cout << fileName << "\t";
			cout << fileMessage << endl;
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
	std::string fileId, fileResolved, fileName, fileEmail, fileMessage, fileLine;


	cout << "Name\t\tMessage\n";


	//---This loops through each row of the CSV file and displays all messages ---//
	while (std::getline(data, fileLine))
	{
		std::stringstream  lineStream(fileLine);
		getline(lineStream, fileId, ',');
		getline(lineStream, fileResolved, ',');
		getline(lineStream, fileName, ',');
		getline(lineStream, fileEmail, ',');
		getline(lineStream, fileMessage, ',');


		if (fileResolved == "No") {
			cout << fileName << "\t";
			cout << fileMessage << endl;
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
string mainMenuPrint_AdminFeedback[menuSize_AdminFeedBack] = { "General", "Compliments", "Complaints", "Return" };


void PrintArray_AdminFeedbackMenu(string userId, string userEmail) {
	cout << "********************************\n*   Welcome to the Admin Feedback Menu  *\n********************************\n";
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
				system("cls");
				AdminMenuDisplay();
				AdminArrowKeys();
				break;
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


	//--- Initializing the required csv files ---//
	fin_general.open("GeneralContact.csv", std::ios::in);
	fout_general.open("GeneralContactNew.csv", std::ios::out | std::ios::app);


	//--- Temporary Variables ---//
	std::string line, newData = "Yes";
	int count_gen = 1, cellBounds = 5;
	std::vector<string> general;
	double tokenChoice, targetElement = 1;


	//--- Table Row ---//
	cout << "Token:\tDone:\tName:\t\tEmail:\t\t\t\tMessage:\n";


	//--- Loops through csv file ---//
	while (std::getline(fin_general, line)) {
		std::stringstream lineStream(line);
		string cell;
		while (std::getline(lineStream, cell, ',')) {
			//--- Formating & adding data to vector ---//
			if (count_gen % cellBounds == 0) // End of row
			{
				cout << cell << "\n";
				general.push_back(cell);
				count_gen++;
			}
			else 
			{	
				if (count_gen % cellBounds == 1 || count_gen % cellBounds == 2 || count_gen % cellBounds == 3) // First 3 columns
				{
					cout << cell << "\t";
					general.push_back(cell);
					count_gen++;
				}
				else if (count_gen % cellBounds == 4) // 4th column
				{ 
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


	//--- User Instructions ---//
	cout << "Please input the ID number of the message you wish to mark as complete: ";
	cin >> tokenChoice;


	//--- Targets correct cell in vector and changes value to "yes" after user input ---//
	general.at((cellBounds * (tokenChoice - 1)) + targetElement) = newData;
	

	//--- Adding vector information to new csv ---//
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


	//--- Closing csv files ---//
	fin_general.close();
	fout_general.close();


	//--- Renaming "GeneralContactNew" to "GeneralContact"
	std::remove("GeneralContact.csv");
	std::rename("GeneralContactNew.csv", "GeneralContact.csv");
}

void RespondCompliments(string userId, string userEmail) {
	//--- Creating a instance of ifstream & fstream ---//
	std::fstream fout_compliments;
	std::fstream fin_compliments;


	//--- Initializing the required csv files ---//
	fin_compliments.open("Compliments.csv", std::ios::in);
	fout_compliments.open("ComplimentsNew.csv", std::ios::out | std::ios::app);


	//--- Temporary Variables ---//
	std::string line, newData = "Yes";
	int count_gen = 1, cellBounds = 5;
	std::vector<string> compliments;
	double tokenChoice, targetElement = 1;


	//--- Table Row ---//
	cout << "Token:\tDone:\tName:\t\tEmail:\t\t\t\tMessage:\n";


	//--- Loops through csv file ---//
	while (std::getline(fin_compliments, line)) {
		std::stringstream lineStream(line);
		string cell;
		while (std::getline(lineStream, cell, ',')) {
			//--- Formating & adding data to vector ---//
			if (count_gen % cellBounds == 0) // End of row
			{
				cout << cell << "\n";
				compliments.push_back(cell);
				count_gen++;
			}
			else
			{
				if (count_gen % cellBounds == 1 || count_gen % cellBounds == 2 || count_gen % cellBounds == 3) // First 3 columns
				{
					cout << cell << "\t";
					compliments.push_back(cell);
					count_gen++;
				}
				else if (count_gen % cellBounds == 4) // 4th column
				{
					cout << cell << "\t\t";
					compliments.push_back(cell);
					count_gen++;
				}
				else
				{
					cout << cell << " ";
					compliments.push_back(cell);
					count_gen++;
				}
			}
		}
	}


	//--- User Instructions ---//
	cout << "Please input the ID number of the message you wish to mark as complete: ";
	cin >> tokenChoice;


	//--- Targets correct cell in vector and changes value to "yes" after user input ---//
	compliments.at((cellBounds * (tokenChoice - 1)) + targetElement) = newData;


	//--- Adding vector information to new csv ---//
	for (int i = 0; i < compliments.size(); i++) {
		if (count_gen % cellBounds == 0) {
			fout_compliments << compliments[i] << "\n";
			count_gen++;
		}
		else {
			fout_compliments << compliments[i] << ",";
			count_gen++;
		}
	}


	//--- Closing csv files ---//
	fin_compliments.close();
	fout_compliments.close();
	

	//--- Renaming "ComplimentsNew" to "Compliments" ---//
	std::remove("Compliments.csv");
	std::rename("ComplimentsNew.csv", "Compliments.csv");
}

void RespondComplaints(string userId, string userEmail) {
	//--- Creating a instance of ifstream & fstream ---//
	std::fstream fout_complaints;
	std::fstream fin_complaints;


	//--- Initializing the required csv files ---//
	fin_complaints.open("Complaints.csv", std::ios::in);
	fout_complaints.open("ComplaintsNew.csv", std::ios::out | std::ios::app);


	//--- Temporary Variables ---//
	std::string line, newData = "Yes";
	int count_gen = 1, cellBounds = 5;
	std::vector<string> complaints;
	double tokenChoice, targetElement = 1;


	//--- Table Row ---//
	cout << "Token:\tDone:\tName:\t\tEmail:\t\t\t\tMessage:\n";


	//--- Loops through csv file ---//
	while (std::getline(fin_complaints, line)) {
		std::stringstream lineStream(line);
		string cell;
		while (std::getline(lineStream, cell, ',')) {
			//--- Formating & adding data to vector ---//
			if (count_gen % cellBounds == 0) // End of row
			{
				cout << cell << "\n";
				complaints.push_back(cell);
				count_gen++;
			}
			else
			{
				if (count_gen % cellBounds == 1 || count_gen % cellBounds == 2 || count_gen % cellBounds == 3) // First 3 columns
				{
					cout << cell << "\t";
					complaints.push_back(cell);
					count_gen++;
				}
				else if (count_gen % cellBounds == 4) // 4th column
				{
					cout << cell << "\t\t";
					complaints.push_back(cell);
					count_gen++;
				}
				else
				{
					cout << cell << " ";
					complaints.push_back(cell);
					count_gen++;
				}
			}
		}
	}


	//--- User Instructions ---//
	cout << "Please input the ID number of the message you wish to mark as complete: ";
	cin >> tokenChoice;


	//--- Targets correct cell in vector and changes value to "yes" after user input ---//
	complaints.at((cellBounds * (tokenChoice - 1)) + targetElement) = newData;


	//--- Adding vector information to new csv ---//
	for (int i = 0; i < complaints.size(); i++) {
		if (count_gen % cellBounds == 0) {
			fout_complaints << complaints[i] << "\n";
			count_gen++;
		}
		else {
			fout_complaints << complaints[i] << ",";
			count_gen++;
		}
	}



	//--- Closing csv files ---//
	fin_complaints.close();
	fout_complaints.close();


	//--- Renaming "ComplimentsNew" to "Complaints" ---//
	std::remove("Complaints.csv");
	std::rename("ComplaintsNew.csv", "Complaints.csv");
}
/*-------------------------END OF ADMIN FEEDBACK FUNCTIONALITY -------------------------*/