#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../utils/Logger.h"

class AudioEffect {
protected:
	double sampleRate;
	unsigned long bufferSize;
	std::string effectName;
	std::string effectAlias;
	std::string effectDescription;
	bool effectStatus;
	Logger& logger = Logger::getInstance();
public:
	virtual void process(float* input) = 0;
	virtual ~AudioEffect() = default;
	virtual void changeParameter(std::string parameter, float value) = 0;
	virtual void getParameterInfo() = 0;

	std::string getEffectDescription() {
		return effectDescription;
	}

	std::string getEffectAlias() {
		return effectAlias;
	}

	std::string getEffectName() {
		return effectName;
	}

	void enable() {
		effectStatus = true;
	}
	void disable() {
		effectStatus = false;
	}
	bool isEffectOn() {
		return effectStatus;
	}

	void changeParameterLog(std::string parameter, float value) {
		logger.print(effectName + " Effect [Parameter Change]: " + parameter + " = " + std::to_string(value) + "\n\n");
	}

	void changeParameterInvalidLog(std::string parameter) {
		logger.print("\'" + parameter + "\'" + " is not a valid parameter for the " + effectName + " effect.\n\n");
	}
};