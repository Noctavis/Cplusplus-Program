#include <Python.h>
#include <iostream>
#define NOMINMAX
#include <Windows.h>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

// Creates a struct for passing multiple data types between functions and main
struct ValidateInput {
	string item;
	int choice;
	int count;
};

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("Grocer");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"Grocer");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"Grocer");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// Outputs menu
void displayMenu() {
	cout << "+" << setfill('-') << setw(65) << "+" << endl;
	cout << "|" << right << setfill(' ') << setw(19) << "" << "Available Program Functions" << setfill(' ') << setw(19) << "|" << endl;
	cout << "+" << setfill('-') << setw(65) << "+" << endl;
	cout << "| 1: Display list of items purchased" << setfill(' ') << setw(30) << "|" << endl;
	cout << "+" << setfill('-') << setw(65) << "+" << endl;
	cout << "| 2: Display the number of times a specific item was purchased" << setfill(' ') << setw(4) << "|" << endl;
	cout << "+" << setfill('-') << setw(65) << "+" << endl;
	cout << "| 3: Display text-based histogram listing all items purchased" << setfill(' ') << setw(5) << "|" << endl;
	cout << "+" << setfill('-') << setw(65) << "+" << endl;
	cout << "| 4: Exit" << setfill(' ') << setw(57) << "|" << endl;
	cout << "+" << setfill('-') << setw(65) << "+" << endl;
	cout << "|" << right << setfill(' ') << setw(13) << "" << "Enter your selection as 1, 2, 3, or 4." << setfill(' ') << setw(14) << "|" << endl;
	cout << "+" << setfill('-') << setw(65) << "+" << endl;
	cout << "Your selection: ";
}

// Iterates through word and ensures it is a word
string iterateThroughWord(string word) {
	for (int i = 0; i < word.size(); i++) {
		if (!(isalpha(word.at(i)))) {
			cout << "Invalid input." << endl << "Please input the grocery item." << endl;
			i = 0;
			getline(cin, word);
			word.at(0) = toupper(word.at(0));
		}
	}
	return word;
}
// Validates user's input
ValidateInput validateUserInput(bool expectInteger) {
	ValidateInput validateStruct;
	int input;
	string item;
	int i;
	int numItems;
	while (1) { // Loop to get usable input
		try {
			if (expectInteger) { // Checking to see if it's the question from the menu, if it is enters loop
				// Checks input and ensure it's a number
				if (!(cin >> input)) {
					cerr << "Invalid input." << endl << "Please choose 1, 2, 3, or 4.\n";
					cin.clear(); // Reset state
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume wrong input
					continue; // Restart loop
				}
				// Check input and ensure it's one of the choices in the menu
				else if ((input < 1) || (input > 4)) {
					throw runtime_error("Invalid input.");
				}
				// Verified input is valid and returns it
				else {
					cout << endl;
					validateStruct.choice = input;
					return validateStruct;
				}
			}
			else { // Validates userinput for grocery item				
				cin.ignore();
				while (1) {
					getline(cin, item);
					item.at(0) = toupper(item.at(0)); // Capitalizes first letter of user's input
					item = iterateThroughWord(item); // Calls function to ensure the input is a word
					numItems = callIntFunc("CheckIfItemInList", item); // Calls Python function to check file to see if it is in the list, and if it is get the number of times the word appears.
					// If it is in the file then it takes the return from Python and returns the struct containing the name and quantity
					if (numItems >= 1) {
						validateStruct.item = item;
						validateStruct.count = numItems;
						return validateStruct;
					}
					// If it is not in the file it informs the user and restarts loop.
					else {
						system("cls");
						cout << "Item not in list." << endl << "Which item would you like to view?" << endl;
						cout << "Your item: ";
						continue;
					}
				}
			}
		}
		// Catches errors and restarts loop
		catch (runtime_error& excpt) {
			cout << excpt.what() << endl;
			cout << "Please choose 1, 2, 3, or 4." << endl;
		}
	}
}
// Opens file created by Python and outputs data in a histogram
void printFileContents() {
	ifstream inFS;
	string item;
	int quantity;
	string specialChar;
	int i;

	inFS.open("frequency.dat");
	// Checks if file is open and if not leaves function
	if (!inFS.is_open()) {
		cout << "File failed to open." << endl;
		return;
	}
	cout << "+" << setfill('~') << setw(65) << "+" << endl;
	cout << "!" << right << setfill(' ') << setw(45) << "Purchased Items Histogram" << setfill(' ') << setw(20) << "!" << endl;
	cout << "+" << setfill('~') << setw(65) << "+" << endl;
	cout << "+" << setfill('-') << setw(65) << "+" << endl;
	cout << "|" << right << setfill(' ') << setw(16) << "Item" << setw(16) << "|" << setw(20) << "Quantity" << setw(13) << "|" << endl;
	cout << "+" << setfill('-') << setw(65) << "+" << endl;
	// Iterates through each item and updates the character for the number of items purchased
	while (inFS >> item >> quantity) {
		for (i = 0; i < quantity; i++) {
			specialChar = specialChar + "+";
		}
		item = item.substr(0, (item.size() - 1)); // Removes ":" from string
		cout << "| " << left << setfill(' ') << setw(30) << item << "| " << setfill(' ') << setw(31) << specialChar << "|" << endl;
		cout << "+" << setfill('-') << setw(64) << "" << "+" << endl;
		specialChar.clear(); // Removes data for the special character in preparation for the next item in the list
	}
	inFS.close();

}// Pauses and clears console for better user experience
void pauseAndClear() {
	system("pause"); // Pauses program until a key is entered
	system("cls"); // Clears console screen for better user experience
}
void main() {
	ValidateInput userInput;
	while (1) {
		displayMenu(); // Calls function to display menu
		userInput = validateUserInput(true); // Calls function to get and validate user's input. Passes true to utilize correct validate code
		system("cls");
		if (userInput.choice == 1) {
			CallProcedure("PrintItemsPurchased"); // Calls Python function to PrintItemsPurchased
			cout << endl;
			pauseAndClear(); // Calls function to pause and clear console for better user experience
		}
		else if (userInput.choice == 2) {
			cout << "Which item would you like to view?" << endl;
			cout << endl << "Your item: ";
			userInput = validateUserInput(false); // Calls function to get and validate user's input. Passes false to utilize correct validate code
			// Outputs data based on user's input
			cout << endl << "+" << setfill('~') << setw(34) << "+" << endl;
			cout << "| " << left << setfill(' ') << setw(15) << userInput.item << "| " << setfill(' ') << setw(15) << userInput.count << "|" << endl;
			cout << "+" << setfill('~') << setw(33) << "" << "+" << endl;
			cout << endl;
			pauseAndClear(); // Calls function to pause and clear console for better user experience
		}
		else if (userInput.choice == 3) {
			CallProcedure("CreateListFile"); // Calls Python function to create a file
			printFileContents(); // Calls function to read Python file and output data formatted in C++
			cout << endl;
			pauseAndClear(); // Calls function to pause and clear console for better user experience
		}
		else {
			break; // Ends loop
		}
	}
	cout << "Goodbye!" << endl;
}