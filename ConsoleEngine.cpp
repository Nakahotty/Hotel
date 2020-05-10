#include "ConsoleEngine.h"

void ConsoleEngine::run() {
	bool exited = 0;

	do {
		cin >> cmd;
		Vector<String> arguments = split(cmd);
		arguments.print();

		switch (checkOperation(cmd)) {
		case 1:
			// Open
			cout << "Opening file..." << endl;
			break;
		case 2:
			// Close
			cout << "Closing file..." << endl;
			break;
		case 3:
			// Save
			cout << "Saving file..." << endl;
			break;
		case 4:
			// Save as
			cout << "Saving file as..." << endl;
			break;
		case 5:
			// Help
			cout << "The following commands are supported: " << endl;
			cout << "open <file> - Opens <file>" << endl;
			cout << "close - Closes currently oppened file" << endl;
			cout << "save - Saves the currently oppened file" << endl;
			cout << "saveas <file> - Saves the currently oppened file in <file>" << endl;
			cout << "help - Prints this information" << endl;
			cout << "exit - Exits the program" << endl;
			cout << "checkin <room> <from> <to> <note> <guests> - Registration in <room> in the period <from> <to> with <guests>" << endl;
			cout << "availability <date> - Checks room availability on <date>" << endl;
			cout << "checkout <room> - Checks out guests from <room>" << endl;
			cout << "find <beds> <from> <to> - Finds available room with <beds> in the period <from> <to>" << endl;
			cout << "find! <beds> <from> <to> - Finds urgent search for a special guest with <beds> in the period" << endl;
			cout << "unavailable <room> <from> <to> <note> - Setting <room> as unavailable for period <from> <to>" << endl;
			break;
		case 6:
			// Exit
			cout << "Exiting the program..."<<endl;
			exited = 1;
			break;
		case 7:
			// Checkin
			
			break;
		case 8:
			// Availability
			break;
		case 9:
			// Checkout
			break;
		case 10:
			// Report
			break;
		case 11:
			// Find
			break;
		case 12:
			// Find important
			break;
		case 13:
			// Unavailable
			break;
		default:
			cout << "Invalid command entered!" << endl;
			break;
		}
	} while (!exited);
}


String ConsoleEngine::subString(String text, int startPosition, int endPosition) {
	String result;
	for (size_t i = 0; i < endPosition - startPosition; i++) {
		result[i] = text[startPosition + i];
	}

	result[endPosition - startPosition] = 0;
	return result;
}

int ConsoleEngine::countLetters(String text, char letter)
{
	int counter = 0;
	for (size_t i = 0; i < text.length(); i++) {
		if (text[i] == letter)
			counter++;
	}

	return counter;
}

int ConsoleEngine::indexOf(String text, char letter)
{
	for (size_t i = 0; i < text.length(); i++) {
		if (text[i] == letter) {
			return i;
		}
	}

	return -1;
}

Vector<String> ConsoleEngine::split(String text)
{
	Vector<String> result;
	while (countLetters(text, ' ')) {
		result.push_back(subString(text, 0, indexOf(text, ' ')));
		text = subString(text, indexOf(text, ' ') + 1, text.length() + 1);
	}

	result.push_back(text);
	return result;
}

int ConsoleEngine::checkOperation(String cmd) {
	Vector<String> cmdParts = split(cmd);

	for (size_t i = 0; i < 13; i++) {
		if (cmdParts[0] == commands_arr[i]) {
			return i + 1;
		}
			
	}

	return -1;
}
