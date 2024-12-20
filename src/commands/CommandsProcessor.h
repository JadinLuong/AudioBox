#pragma once
#include <iostream>
#include <unordered_map>
#include <functional>
#include "../audio/AudioManager.h"
#include "../audio/AudioProcessor.h"
#include "../utils/Logger.h"

class CommandsProcessor {
private:
	AudioManager* audioManager;
	AudioProcessor audioProcessor;
	std::unordered_map<std::string, std::function<void(std::vector<std::string>)>> commands;

	Logger& logger = Logger::getInstance();

public:
	CommandsProcessor(AudioManager* am);
	int process(std::string command);
	void setAudioManager(AudioManager* am);
	void initializeCommands();
	void helpCommand(std::vector<std::string> parsedInput);
	void changeParametersCommand(std::vector<std::string> parsedInput);
	void toggleEffectCommand(std::vector<std::string> parsedInput);
	void listEffectsCommand(std::vector<std::string> parsedInput);
	void listParametersCommand(std::vector<std::string> parsedInput);
	void switchDeviceCommand(std::vector<std::string> parsedInput);
};