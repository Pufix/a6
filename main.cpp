#include<iostream>
#include<string>
#include<cstring>
#include "ui.h"
#include "tests.h"
void run(userInterface &ui) {
	ui.startUp();
	bool running = true;
	do {
		running = ui.run();
	} while (running);
}
void test() {
	TEST_ALL();
}
int main() {
	userInterface ui;
	run(ui);
	ui.serv.repo.movieDump();
	ui.serv.repo.userDump();
	return 0;
}
//int main() {
//	test();
//	return 0;
//}
