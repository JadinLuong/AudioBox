#pragma once
#include <iostream>

class Logger {
private:
	Logger();
	Logger(const Logger&) = delete;
	void operator=(const Logger&) = delete;
public:
	static Logger& getInstance();
	void print(std::string message);
};