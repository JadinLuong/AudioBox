#include <iostream>
#include <sstream>
#include <iomanip>
#include "CommandsProcessor.h"

CommandsProcessor::CommandsProcessor(AudioManager* am) {
	audioManager = am;
	audioProcessor = audioManager->getAudioProcessor();
	initializeCommands();
}

int CommandsProcessor::process(std::string input) {
	if (!audioManager) {
		throw std::runtime_error("AudioManager must be set.\n");
	}

	std::istringstream stream(input);
	std::vector<std::string> parsedInput;
	std::string currArg;
	while (stream >> currArg) {
		parsedInput.push_back(currArg);
	}

	std::string command = "";
	if (parsedInput.size() > 0) {
		command = parsedInput[0];
	}

	if (commands.find(command) != commands.end()) {
		commands[command](parsedInput);
	}
	else if (command == "") {
		logger.print(command);
	}
	else if (command == "exit") {
		logger.print("Application will now close.\n\n");
		return 0;
	}
	else {
		logger.print(command + " is not a valid command.\n\n");
	}

	return 1;
}

void CommandsProcessor::setAudioManager(AudioManager* am) {
	audioManager = am;
}

void CommandsProcessor::initializeCommands() {
	commands["help"] = [this](std::vector<std::string> parsedInput) { helpCommand(parsedInput); };
	commands["change-parameter"] = [this](std::vector<std::string> parsedInput) { changeParametersCommand(parsedInput); };
	commands["list-effects"] = [this](std::vector<std::string> parsedInput) { listEffectsCommand(parsedInput); };
	commands["toggle-effect"] = [this](std::vector<std::string> parsedInput) { toggleEffectCommand(parsedInput); };
	commands["list-parameters"] = [this](std::vector<std::string> parsedInput) { listParametersCommand(parsedInput); };
	commands["switch-device"] = [this](std::vector<std::string> parsedInput) { switchDeviceCommand(parsedInput); };
}

void CommandsProcessor::helpCommand(std::vector<std::string> parsedInput) {
	if (parsedInput.size() == 1) {
		std::cout << std::left;
		std::cout << std::setw(20) << "COMMAND" << "DESCRIPTION\n";
		std::cout << std::setw(20) << "change-parameter" << "Changes a parameter's value of a specified effect.\n" << std::setw(20) << ""
			<< "Usage: change-parameter <effect-name> <parameter> <value>\n";
		std::cout << std::setw(20) << "toggle-effect" << "Toggles the specified effect ON/OFF.\n" << std::setw(20) << ""
			<< "Usage: toggle-effect <effect-name>\n";
		std::cout << std::setw(20) << "list-effects" << "Lists the all the audio effects that are available.\n" << std::setw(20) << ""
			<< "Usage: list-effects\n";
		std::cout << std::setw(20) << "list-parameters" << "Lists the all parameters of a specified effect and it's current values.\n" << std::setw(20) << ""
			<< "Usage: list-parameters <effect-name>\n";
		std::cout << std::setw(20) << "switch-device" << "Changes the input and output devices.\n" << std::setw(20) << ""
			<< "Usage: switch-device <device-input-ID> <device-output-ID>\n";



		std::cout << "\n";
	}
	else {
		logger.print("help: Invalid argument size.\n"
			"Usage: help\n\n");
	}

}

void CommandsProcessor::changeParametersCommand(std::vector<std::string> parsedInput) {
	if (parsedInput.size() == 4) {
		std::istringstream number(parsedInput[3]);
		float num;
		number >> num;
		if (number.eof() && !number.fail()) {
			audioProcessor.changeParameter(parsedInput[1], parsedInput[2], num);
		}
		else {
			logger.print(parsedInput[3] + " is not a valid number.\n\n");
		}
	}
	else {
		logger.print("change-parameter: Invalid argument size.\n"
			"Valid Structure: change-parameter <effect-name> <parameter> <value>\n\n");
	}
}

void CommandsProcessor::toggleEffectCommand(std::vector<std::string> parsedInput) {
	if (parsedInput.size() == 2) {
		audioManager->getAudioProcessor().toggleEffect(parsedInput[1]);
	}
	else {
		logger.print("toggle-effect: Invalid argument size.\n"
			"Valid Structure: toggle-effect <effect-name>\n\n");
	}
}

void CommandsProcessor::listEffectsCommand(std::vector<std::string> parsedInput) {
	if (parsedInput.size() == 1) {
		std::cout << std::left;
		std::cout << std::setw(20) << "<effect-name>" << "DESCRIPTION\n";

		for (const auto& effect : audioProcessor.getAudioEffects()) {
			std::cout << std::setw(20) << effect.second->getEffectAlias() 
				<< effect.second->getEffectDescription() << "\n";
		}

		std::cout << "\n";
	}
	else {
		logger.print("list-effects: Invalid argument size.\n"
			"Usage: list-effects\n\n");
	}
}

void CommandsProcessor::listParametersCommand(std::vector<std::string> parsedInput) {
	if (parsedInput.size() == 2) {
		if (audioProcessor.getAudioEffects().find(parsedInput[1]) != audioProcessor.getAudioEffects().end()) {
			audioProcessor.getAudioEffects()[parsedInput[1]]->getParameterInfo();
			logger.print("\n");
		}
		else {
			logger.print("\'" + parsedInput[1] + "\'" + " is not a valid effect.\n\n");
		}
	}
	else {
		logger.print("list-parameters: Invalid argument size.\n"
			"Usage: list-parameters <effect-name>\n\n");
	}
}

void CommandsProcessor::switchDeviceCommand(std::vector<std::string> parsedInput) {
	if (parsedInput.size() == 3) {
		try {
			int inputId = std::stoi(parsedInput[1]);
			int outputId = std::stoi(parsedInput[2]);
			audioManager->switchDevice(inputId, outputId);
		}
		catch (...) {
			logger.print("switch-device: Invalid argument values.\n");
		}
	}
	else {
		logger.print("switch-device: Invalid argument size.\n"
			"Usage: switch-device <device-input-ID> <device-output-ID>\n\n");
	}
}