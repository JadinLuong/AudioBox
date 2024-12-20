#include "audio/AudioManager.h"
#include "commands/CommandsProcessor.h"
#include "portaudio.h"
#include "utils/Logger.h"

int main() {
	AudioManager audioManager(44100, 256, 1);
	CommandsProcessor commandsProcessor(&audioManager);
	audioManager.openStream(Pa_GetDefaultInputDevice(), 5);

	Logger& logger = Logger::getInstance();

	std::string input;
	logger.print("Welcome to the voice changer application, enter \'help\' on how to navigate the application through the CLI.\n");

	int statusCode = 1;
	while (statusCode == 1) {
		logger.print("[Voice Changer Name]> ");
		std::getline(std::cin, input);
		statusCode = commandsProcessor.process(input);
	}

	audioManager.closeStream();
	audioManager.terminatePortAudio();
	return 0;
}