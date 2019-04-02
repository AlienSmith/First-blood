#include "MT_MAIN.hpp"
#include <iostream>
#include <thread>
void Hello() {
	std::cout << "Hello World \n";
}
int Entrance() {
	std::thread t(Hello);
	t.join();
	return 0;
}