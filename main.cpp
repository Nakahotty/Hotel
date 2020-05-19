#include "Hotel.h"
#include "ConsoleEngine.h"
#include <time.h>

int main() {
	srand(time(NULL));
	ConsoleEngine console;
	console.run();

	/*ofstream out("period.txt");
	ifstream in("period.txt");

	Period test;
	Room room1(45, 3, 1);
	Room test2(100, 1, 0);

	room1.saveRoom(out);
	test2.loadRoom(in);
	test2.print();*/

	/*
	String traicho = "nasko";

	Period period1(Date(2020, 15, 05), Date(2020, 20, 05));
	nasko.checkin(4, period1, traicho , 1);

	nasko.saveHotel(out);
	nasko.loadHotel(in); */


}