#include "Operation.h"

class ConsoleEngine {
private:
	String cmd;
	Vector<String> commands;

	// 13 commands
	String commands_arr[13] = { "open", "close", "save", "saveas", "help", "exit",
								"checkin", "availability", "checkout", "report", "find", "find!", "unavailable" };

	void initCommands() {
		for (size_t i = 0; i < 13; i++) {
			commands.push_back(commands_arr[i]);
		}
	}
public:
	ConsoleEngine() {
		initCommands();
	}

	// Starting the hotel app
	void run();

	// Handling text
	int countLetters(String text, char letter);
	int indexOf(String text, char letter);
	static String subString(String text, int startPosition, int endPosition);
	Vector<String> split(String text);
	int toInt(String txt);

	// For switch
	int checkOperation(String cmd);
	bool is_empty(ifstream& pFile)
	{
		return pFile.peek() == ifstream::traits_type::eof();
	}
};