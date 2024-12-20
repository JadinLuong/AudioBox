#include <iostream>
#include "Logger.h"

Logger::Logger() {

}

Logger& Logger::getInstance() {
	static Logger instance;
	return instance;
}

void Logger::print(std::string message) {
	std::cout << message;
}