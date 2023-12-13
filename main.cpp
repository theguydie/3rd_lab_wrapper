#include <iostream>

#include "Wrapper.h"
#include "Engine.h"

struct Subject {
	int f3(int a, int b) { return a > b ? a : b; }
};

int main() {
	Subject subj;

	Wrapper<Subject, int, int> wrapper(&subj, &Subject::f3, { {"arg1", 0}, {"arg2", 0} });

	Engine engine;

	engine.register_command(&wrapper, "command1");

	std::cout << engine.execute("command1", { {"arg1", 4},{"arg2", 5} }) << std::endl;

	return 0;
}