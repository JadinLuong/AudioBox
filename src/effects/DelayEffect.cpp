#include <iostream>
#include "DelayEffect.h"

DelayEffect::DelayEffect(double sr, unsigned long bs) {
	sampleRate = sr;
	bufferSize = bs;

	effectName = "Delay";
	effectAlias = "delay-effect";
	effectDescription = "Delay Effect plays a delayed version of the original audio alongside itself.";

	delayBuffer.resize(((delayMS * sampleRate) / 1000), 0.0f);
	effectStatus = false;
}

void DelayEffect::process(float* input) {
	for (unsigned long i = 0; i < bufferSize; i++) {
		float drySignal = input[i];
		float wetSignal = delayBuffer[delayIndex];

		input[i] = drySignal + wetSignal * feedback;

		delayBuffer[delayIndex] = input[i];

		if (delayIndex >= delayBuffer.size() - 1) {
			delayIndex = 0;
		}
		else {
			delayIndex++;
		}
	}
}

void DelayEffect::changeParameter(std::string parameter, float value) {
	if (parameter == "delay") {
		delayMS = value;
		changeParameterLog("Delay", value);
	}
	else if (parameter == "feedback") {
		feedback = value;
		changeParameterLog("Feedback", value);
	}
	else {
		changeParameterInvalidLog(parameter);
	}
}

void DelayEffect::getParameterInfo() {
	std::cout << "Delay: " << delayMS << std::endl;
	std::cout << "Feedback: " << feedback << std::endl;
}