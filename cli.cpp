// ConsoleApplication1.cpp : Simple Command Line Interpreter.
// Copyright (c) Emily Pham 9/22/2019
//

#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <sstream>
#include <algorithm>


DWORD WINAPI execute(LPVOID command) {

	char* cmd = static_cast<char*>(command);

	system(cmd);

	return 0;
}


void tokenize(std::string const& str, const char delim, std::vector<std::string>& tokens) {

	tokens.clear();

	std::stringstream ss(str);
	std::string s;

	while (std::getline(ss, s, delim)) {
		tokens.push_back(s);
	}
}

int main() {

	DWORD ThreadID;
	HANDLE ThreadHandle;

	std::string input;
	const char delim = ' ';
	std::vector<std::string> tokens;
	std::vector<std::string> supportedCommands = { "dir", "help", "vol", "path", "tasklist",
												  "notepad", "echo", "color", "ping" };

	std::cout << "Welcome to myShell " << std::endl;

	while (1) {

		std::cout << "==> ";

		std::getline(std::cin, input);

		if (input == "exit" || input == "quit") {
			std::cout << "Thanks for using myShell!" << std::endl;
			break;
		}

		tokenize(input, delim, tokens); //tokenize the input string

		if (std::find(supportedCommands.begin(), supportedCommands.end(), tokens[0]) == supportedCommands.end()
			|| tokens.size() > 4) {

			std::cout << "Command not found" << std::endl; //check if input is in the supported commands list
		}

		else {

			std::string cmd = input;

			LPVOID param = (LPVOID)cmd.c_str();

			ThreadHandle = CreateThread(NULL, 0, execute, param, 0, &ThreadID);

			if (ThreadHandle != NULL) {
				WaitForSingleObject(ThreadHandle, INFINITE);
				CloseHandle(ThreadHandle);
			}

		}
	}

}
